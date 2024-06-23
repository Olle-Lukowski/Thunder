#include "log/sinks/file.h"

static void file_callback(
  th_log_sink_header_t *header,
  th_log_level_t level,
  const th_log_entry_t *restrict entry
) {
  th_log_file_sink_t *sink = (th_log_file_sink_t *)header;

  if (sink->min_level > level)
    return;

  pthread_mutex_lock(&sink->lock);

  if (sink->thread_writing && entry->is_first_part) {
    pthread_mutex_unlock(&sink->lock);
    return;
  }

  if (!sink->message_in_progress) {
    sink->message_in_progress = true;
    sink->thread_writing = true;
    struct tm *timeinfo = localtime(&entry->timestamp);
    fprintf(
      sink->file,
      "[%s] [%02d:%02d:%02d] [%s:%d] [%s] %s",
      th_log_level_names[level],
      timeinfo->tm_hour,
      timeinfo->tm_min,
      timeinfo->tm_sec,
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
    sink->message_in_progress = false;
    sink->thread_writing = false;
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
  sink->message_in_progress = false;
  sink->thread_writing = false;

  sink->file = fopen(path, "a");
  if (!sink->file) {
    return false;
  }

  if (pthread_mutex_init(&sink->lock, NULL)) {
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
