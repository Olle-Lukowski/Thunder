#ifndef TH_LOG_LOG_H_
#define TH_LOG_LOG_H_

#include <stdbool.h>
#include <time.h>

#ifndef TH_LOG_PART_SIZE
#define TH_LOG_PART_SIZE 1024
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
  int line;
  const char *restrict func;
  char message[TH_LOG_PART_SIZE + 1]; /* +1 for '\0' */
  time_t timestamp;
  bool is_last_part;
};

typedef struct th_log_sink_header th_log_sink_header_t;

typedef void (*th_log_sink_func)(
  th_log_sink_header_t *header,
  th_log_level_t level,
  const th_log_entry_t *restrict entry
);

/* Use this header as the first field of a struct to make it a valid sink. */
struct th_log_sink_header {
  th_log_sink_func callback;
};

extern th_log_sink_header_t *th_log_sinks[];

void th_log(th_log_level_t level, const th_log_entry_t *restrict entry);
void th_log_args(
  th_log_level_t level,
  const char *restrict file,
  int line,
  const char *restrict func,
  const char *restrict format,
  ...
);

bool th_log_add_sink(th_log_sink_header_t *header);
void th_log_clear_sinks();

#define TH_LOG_TRACE(...) \
  th_log_args(TH_LOG_LEVEL_TRACE, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TH_LOG_DEBUG(...) \
  th_log_args(TH_LOG_LEVEL_DEBUG, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TH_LOG_INFO(...)  \
  th_log_args(TH_LOG_LEVEL_INFO, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TH_LOG_WARN(...)  \
  th_log_args(TH_LOG_LEVEL_WARN, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TH_LOG_ERROR(...) \
  th_log_args(TH_LOG_LEVEL_ERROR, __FILE__, __LINE__, __func__, __VA_ARGS__)
#define TH_LOG_FATAL(...) \
  th_log_args(TH_LOG_LEVEL_FATAL, __FILE__, __LINE__, __func__, __VA_ARGS__)

#endif /* TH_LOG_LOG_H_ */
