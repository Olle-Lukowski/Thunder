#include <core/setup.h>
#include <core/cleanup.h>
#include <log/log.h>
#include <log/sinks/console.h>
#include <input/module.h>

th_log_console_sink_t sink;

void setup(ecs_world_t *world, ecs_app_desc_t *app) {
  app->enable_rest = true;
  app->enable_stats = true;

  ecs_entity_t s = ecs_script(world, { .code = "" });

  th_log_console_sink_init(&sink, TH_LOG_LEVEL_TRACE, true);
  th_log_add_sink((th_log_sink_header_t *)&sink);
}

void cleanup() { }
