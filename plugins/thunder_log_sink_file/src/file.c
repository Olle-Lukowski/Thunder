#include "log/sinks/file.h"

#include <stdlib.h>

static void file_callback(
  th_log_sink_header_t *header,
  th_log_entry_t *restrict entry
) {
  th_log_file_sink_t *sink = (th_log_file_sink_t *)header;

  if (sink->min_level > entry->level)
    return;

  struct tm *timeinfo = localtime(&entry->timestamp);

  char buf[TH_LOG_SMALL_MSG_LIMIT];

  // check if the entire message would fit
  va_list copy;
  va_copy(copy, entry->args);

  int total_len = vsnprintf(
    buf,
    sizeof(buf),
    entry->format,
    copy
  );

  va_end(copy);
  if (total_len <= TH_LOG_SMALL_MSG_LIMIT) {
    fprintf(
      sink->file,
      "[%s] [%02d:%02d:%02d] [%s:%d] [%s] %s\n",
      th_log_level_names[entry->level],
      timeinfo->tm_hour,
      timeinfo->tm_min,
      timeinfo->tm_sec,
      entry->file,
      entry->line,
      entry->func,
      buf
    );
  } else {
    char *msg = malloc(total_len + 1);

    vsnprintf(
      msg,
      total_len + 1,
      entry->format,
      entry->args
    );

    fprintf(
      sink->file,
      "[%s] [%02d:%02d:%02d] [%s:%d] [%s] %s\n",
      th_log_level_names[entry->level],
      timeinfo->tm_hour,
      timeinfo->tm_min,
      timeinfo->tm_sec,
      entry->file,
      entry->line,
      entry->func,
      msg
    );

    free(msg);
  }
}

bool th_log_file_sink_init(
  th_log_file_sink_t *sink,
  th_log_level_t min_level,
  const char *restrict path
) {
  sink->header.callback = file_callback;
  sink->min_level = min_level;

  sink->file = fopen(path, "a");
  if (!sink->file)
    return false;

  return true;
}

void th_log_file_sink_deinit(th_log_file_sink_t *sink) {
  if (sink->file) {
    fclose(sink->file);
  }
}
