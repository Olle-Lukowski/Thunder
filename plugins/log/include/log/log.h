#ifndef TH_LOG_LOG_H_
#define TH_LOG_LOG_H_

#include <stdbool.h>
#include <stdarg.h>
#include <time.h>

#ifndef TH_LOG_SMALL_MSG_LIMIT
#define TH_LOG_SMALL_MSG_LIMIT 1024
#endif

#ifndef TH_LOG_MAX_SINKS
#define TH_LOG_MAX_SINKS 16
#endif

typedef enum th_log_level th_log_level_t;
enum th_log_level {
  TH_LOG_LEVEL_TRACE,
  TH_LOG_LEVEL_DEBUG,
  TH_LOG_LEVEL_INFO,
  TH_LOG_LEVEL_WARN,
  TH_LOG_LEVEL_ERROR,
  TH_LOG_LEVEL_FATAL,
};

extern const char *th_log_level_names[];

typedef struct th_log_entry th_log_entry_t;
struct th_log_entry {
  th_log_level_t level;
  const char *restrict file;
  const char *restrict func;
  const char *restrict format;
  va_list args;
  time_t timestamp;
  int line;
};

typedef struct th_log_sink_header th_log_sink_header_t;

typedef void (*th_log_sink_func)(
  th_log_sink_header_t *header,
  th_log_entry_t *restrict entry
);

/* Use this header as the first field of a struct to make it a valid sink. */
struct th_log_sink_header {
  th_log_sink_func callback;
};

extern th_log_sink_header_t *th_log_sinks[];

void th_log(
  th_log_level_t level,
  int line,
  const char *restrict file,
  const char *restrict func,
  const char *restrict format,
  ...
);

bool th_log_add_sink(th_log_sink_header_t *header);
void th_log_clear_sinks();

#define TH_LOG_TRACE(...) \
  th_log(TH_LOG_LEVEL_TRACE, __LINE__, __FILE__, __func__, __VA_ARGS__)
#define TH_LOG_DEBUG(...) \
  th_log(TH_LOG_LEVEL_DEBUG, __LINE__, __FILE__, __func__, __VA_ARGS__)
#define TH_LOG_INFO(...) \
  th_log(TH_LOG_LEVEL_INFO, __LINE__, __FILE__, __func__, __VA_ARGS__)
#define TH_LOG_WARN(...) \
  th_log(TH_LOG_LEVEL_WARN, __LINE__, __FILE__, __func__, __VA_ARGS__)
#define TH_LOG_ERROR(...) \
  th_log(TH_LOG_LEVEL_ERROR, __LINE__, __FILE__, __func__, __VA_ARGS__)
#define TH_LOG_FATAL(...) \
  th_log(TH_LOG_LEVEL_FATAL, __LINE__, __FILE__, __func__, __VA_ARGS__)

#endif /* TH_LOG_LOG_H_ */
