#include "log/sinks/console.h"

#include <stdio.h>

/* Foreground colors */
#define FG_BLACK   "\x1b[30m"
#define FG_RED     "\x1b[31m"
#define FG_GREEN   "\x1b[32m"
#define FG_YELLOW  "\x1b[33m"
#define FG_BLUE    "\x1b[34m"
#define FG_MAGENTA "\x1b[35m"
#define FG_CYAN    "\x1b[36m"
#define FG_WHITE   "\x1b[37m"
#define FG_RESET   "\x1b[39m"

/* Background colors */
#define BG_BLACK   "\x1b[40m"
#define BG_RED     "\x1b[41m"
#define BG_GREEN   "\x1b[42m"
#define BG_YELLOW  "\x1b[43m"
#define BG_BLUE    "\x1b[44m"
#define BG_MAGENTA "\x1b[45m"
#define BG_CYAN    "\x1b[46m"
#define BG_WHITE   "\x1b[47m"
#define BG_RESET   "\x1b[49m"

/* Text attributes */
#define ATTR_RESET        "\x1b[0m"
#define ATTR_BOLD         "\x1b[1m"
#define ATTR_UNDERLINE    "\x1b[4m"
#define ATTR_REVERSE      "\x1b[7m"
#define ATTR_NO_BOLD      "\x1b[21m"
#define ATTR_NO_UNDERLINE "\x1b[24m"
#define ATTR_NO_REVERSE   "\x1b[27m"

static void console_callback_color(
  th_log_sink_header_t *header,
  th_log_level_t level,
  const th_log_entry_t *restrict entry
) {
  th_log_console_sink_t *sink = (th_log_console_sink_t *)header;

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
    const char *color = NULL;
    switch (level) {
      case TH_LOG_LEVEL_DEBUG:
        color = FG_BLUE;
        break;
      case TH_LOG_LEVEL_INFO:
        color = FG_GREEN;
        break;
      case TH_LOG_LEVEL_WARN:
        color = FG_YELLOW;
        break;
      case TH_LOG_LEVEL_ERROR:
        color = FG_RED;
        break;
      case TH_LOG_LEVEL_FATAL:
        color = ATTR_BOLD FG_RED;
        break;
      default:
        color = ATTR_RESET FG_RESET;
        break; /* Trace needs no special treatment */
    }

    printf(
      "%s[%s] [%s:%d] [%s] %s",
      color,
      th_log_level_names[level],
      entry->file,
      entry->line,
      entry->func,
      entry->message
    );
  } else {
    printf("%s", entry->message);
  }

  if (sink->message_in_progress && entry->is_last_part) {
    printf(ATTR_RESET FG_RESET "\n");
    sink->message_in_progress = false;
    sink->thread_writing = false;
  }

  pthread_mutex_unlock(&sink->lock);
}

static void console_callback(
  th_log_sink_header_t *header,
  th_log_level_t level,
  const th_log_entry_t *restrict entry
) {
  th_log_console_sink_t *sink = (th_log_console_sink_t *)header;

  if (sink->min_level > level)
    return;

  pthread_mutex_lock(&sink->lock);

  if (sink->thread_writing) {
    pthread_mutex_unlock(&sink->lock);
    return;
  }

  if (!sink->message_in_progress) {
    sink->message_in_progress = true;
    sink->thread_writing = true;
    printf(
      "[%s] [%s:%d] [%s] %s",
      th_log_level_names[level],
      entry->file,
      entry->line,
      entry->func,
      entry->message
    );
  } else {
    printf("%s", entry->message);
  }

  if (sink->message_in_progress && entry->is_last_part) {
    printf("\n");
    sink->message_in_progress = false;
    sink->thread_writing = false;
  }

  pthread_mutex_unlock(&sink->lock);
}

bool th_log_console_sink_init(
  th_log_console_sink_t *sink,
  th_log_level_t min_level,
  bool ansi_color
) {
  sink->header.callback = ansi_color ? 
    console_callback_color : console_callback;
  sink->min_level = min_level;
  sink->message_in_progress = false;
  sink->thread_writing = false;

  if (pthread_mutex_init(&sink->lock, NULL))
    return false;

  return true;
}

void th_log_console_sink_deinit(th_log_console_sink_t *sink) {
  pthread_mutex_destroy(&sink->lock);
}
