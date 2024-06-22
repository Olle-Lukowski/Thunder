#include "log/sinks/file.h"

static void file_callback(
  th_log_sink_header_t *header,
  th_log_level_t level,
  const th_log_entry_t *restrict entry
) {
  static bool message_in_progress = false;
  th_log_file_sink_t *sink = (th_log_file_sink_t *)header;

  if (sink->min_level > level) {
    return;
  }

  pthread_mutex_lock(&sink->lock);

  if (!message_in_progress) {
    message_in_progress = true;
    fprintf(
      sink->file,
      "[%s] [%s:%d] [%s] %s",
      th_log_level_names[level],
      entry->file,
      entry->line,
      entry->func,
      entry->message
    );
  } else {
    fprintf(sink->file, "%s", entry->message);
  }

  if (entry->is_last_part) {
    fprintf(sink->file, "\n");
    fflush(sink->file);
    message_in_progress = false;
  }

  pthread_mutex_unlock(&sink->lock);
}

bool th_log_file_sink_init(
  th_log_file_sink_t *sink,
  const char *path,
  th_log_level_t min_level
) {
  sink->header.callback = file_callback;
  sink->min_level = min_level;

  sink->file = fopen(path, "a");
  if (!sink->file) {
    return false;
  }

  if (pthread_mutex_init(&sink->lock, NULL) != 0) {
    fclose(sink->file);
    return false;
  }

  return true;
}

void th_log_file_sink_deinit(th_log_file_sink_t *sink) {
  if (sink->file) {
    fclose(sink->file);
  }

  pthread_mutex_destroy(&sink->lock);
}