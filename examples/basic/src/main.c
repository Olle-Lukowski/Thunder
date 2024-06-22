#include <core/setup.h>
#include <log/log.h>
#include <log/sinks/console.h>
#include <log/sinks/file.h>

void setup(ecs_world_t *world, ecs_app_desc_t *app) {

  /* 
   * allows us to view stats and interact with the world at
   * https://www.flecs.dev/explorer/v4/ 
   */
  ECS_IMPORT(world, FlecsStats);
  app->enable_rest = true;

  th_log_console_sink_t sink;
  th_log_console_sink_init(&sink, TH_LOG_LEVEL_TRACE, true);
  th_log_add_sink((th_log_sink_header_t *)&sink);

  th_log_file_sink_t file_sink;
  th_log_file_sink_init(&file_sink, "log.txt", TH_LOG_LEVEL_TRACE);
  th_log_add_sink((th_log_sink_header_t *)&file_sink);

  TH_LOG_FATAL("Hello, World!");
  TH_LOG_WARN("Hello, World!");
  TH_LOG_ERROR("Hello, World!");

  ecs_entity_t e = ecs_entity(world, { .name = "Bobber" });
}

