#include "log/log.h"

#include <string.h>
#include <stdio.h>

const char *th_log_level_names[] = {
  "TRACE",
  "DEBUG",
  "INFO",
  "WARN",
  "ERROR",
  "FATAL",
};

th_log_sink_header_t *th_log_sinks[TH_LOG_MAX_SINKS] = {NULL};

void th_log(
  th_log_level_t level,
  int line,
  const char *restrict file,
  const char *restrict func,
  const char *restrict format,
  ...
) {
  th_log_entry_t entry = {0};
  entry.level = level;
  entry.file = file;
  entry.line = line;
  entry.func = func;
  entry.format = format;
  time(&entry.timestamp);

  va_list main_args;
  va_start(main_args, format);

  for (int i = 0; i < TH_LOG_MAX_SINKS; i++) {
    if (th_log_sinks[i]) {
      va_copy(entry.args, main_args);
      th_log_sinks[i]->callback(th_log_sinks[i], &entry);
      va_end(entry.args);
    }
  }

  va_end(entry.args);
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
