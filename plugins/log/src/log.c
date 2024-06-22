#include "log/log.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

const char *th_log_level_names[] = {
  "TRACE",
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR",
  "FATAL",
};

th_log_sink_header_t *th_log_sinks[TH_LOG_MAX_SINKS] = {NULL};

void th_log(th_log_level_t level, const th_log_entry_t *restrict entry) {
  for (int i = 0; i < TH_LOG_MAX_SINKS; i++) {
    if (th_log_sinks[i]) {
      th_log_sinks[i]->callback(th_log_sinks[i], level, entry);
    }
  }
}

void th_log_args(
  th_log_level_t level,
  const char *restrict file,
  int line,
  const char *restrict func,
  const char *restrict format,
  ...
) {
  va_list args;
  va_start(args, format);
  
  th_log_entry_t entry = {0};
  entry.level = level;
  entry.file = file;
  entry.line = line;
  entry.func = func;
  time(&entry.timestamp);

  int total_size = vsnprintf(NULL, 0, format, args);
  if (total_size < 0) {
    va_end(args);
    return;
  }
  
  int offset = 0;
  while (offset < total_size) {
    int to_write = TH_LOG_PART_SIZE;
    /* 
     * this is a hacky way to ensure that we properly format the specifier.
     * if we don't do this, it might get cut off.
     */
    for (int i = 1; i < to_write; i++) {
      if (format[offset + i] == '%' && format[offset + i + 1] != '%') {
        to_write = i;
        break;
      }
    }
    int written = vsnprintf(entry.message, to_write + 1, format + offset, args);
    
    if (written < 0) {
      va_end(args);
      return;
    }

    offset += written < to_write ? written : to_write;
    if (offset >= total_size) {
      entry.is_last_part = true;
    }
    th_log(level, &entry);
  }

  va_end(args);
}

bool th_log_add_sink(th_log_sink_header_t *header) {
  static int sink_count = 0;
  if (sink_count >= TH_LOG_MAX_SINKS) {
    return false;
  }
  th_log_sinks[sink_count++] = header;
  return true;
}

void th_log_clear_sinks() {
  for (int i = 0; i < TH_LOG_MAX_SINKS; i++) {
    th_log_sinks[i] = NULL;
  }
}
