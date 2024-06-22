#ifndef TH_LOG_SINKS_CONSOLE_H_
#define TH_LOG_SINKS_CONSOLE_H_

#include "log/log.h"

typedef struct th_log_console_sink th_log_console_sink_t;
struct th_log_console_sink {
  th_log_sink_header_t header;
  th_log_level_t min_level;
};

void th_log_console_sink_init(
  th_log_console_sink_t *sink,
  th_log_level_t min_level,
  bool ansi_color
);

#endif /* TH_LOG_SINKS_CONSOLE_H_ */
