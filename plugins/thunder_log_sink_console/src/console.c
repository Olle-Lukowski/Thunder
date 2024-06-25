#include "log/sinks/console.h"

#include <stdio.h>
#include <stdlib.h>

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
  th_log_entry_t *restrict entry
) {
  th_log_console_sink_t *sink = (th_log_console_sink_t *)header;

  if (sink->min_level > entry->level)
    return;

  const char *color = NULL;
  switch (entry->level) {
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

  char buf[TH_LOG_SMALL_MSG_LIMIT];

  // check if the entire message would fit
  va_list copy;
  va_copy(copy, entry->args);

  int total_len = vsnprintf(
    NULL,
    0,
    entry->format,
    copy
  );

  va_end(copy);

  if (total_len <= TH_LOG_SMALL_MSG_LIMIT) {
    vsnprintf(
      buf,
      sizeof(buf),
      entry->format,
      entry->args
    );

    printf(
      "%s[%s] [%s:%d] [%s] %s" ATTR_RESET FG_RESET "\n",
      color,
      th_log_level_names[entry->level],
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

    printf(
      "%s[%s] [%s:%d] [%s] %s" ATTR_RESET FG_RESET "\n",
      color,
      th_log_level_names[entry->level],
      entry->file,
      entry->line,
      entry->func,
      msg
    );

    free(msg);
  }
}

static void console_callback(
  th_log_sink_header_t *header,
  th_log_entry_t *restrict entry
) {
  th_log_console_sink_t *sink = (th_log_console_sink_t *)header;

  if (sink->min_level > entry->level)
    return;

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
    printf(
      "[%s] [%s:%d] [%s] %s" ATTR_RESET FG_RESET "\n",
      th_log_level_names[entry->level],
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

    printf(
      "[%s] [%s:%d] [%s] %s" ATTR_RESET FG_RESET "\n",
      th_log_level_names[entry->level],
      entry->file,
      entry->line,
      entry->func,
      msg
    );

    free(msg);
  }
}

bool th_log_console_sink_init(
  th_log_console_sink_t *sink,
  th_log_level_t min_level,
  bool ansi_color
) {
  sink->header.callback = ansi_color ? 
    console_callback_color : console_callback;
  sink->min_level = min_level;

  return true;
}
