#ifndef TH_LOG_SINKS_FILE_H_
#define TH_LOG_SINKS_FILE_H_

#include <stdio.h>

#include "log/log.h"

typedef struct th_log_file_sink th_log_file_sink_t;
struct th_log_file_sink {
  th_log_sink_header_t header;
  th_log_level_t min_level;
  FILE *file;
};

bool th_log_file_sink_init(
  th_log_file_sink_t *sink,
  th_log_level_t min_level,
  const char *restrict path
);
void th_log_file_sink_deinit(th_log_file_sink_t *sink);

#endif /* TH_LOG_SINKS_FILE_H_ */
