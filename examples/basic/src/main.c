#include <core/setup.h>
#include <core/cleanup.h>
#include <log/log.h>
#include <log/sinks/console.h>
#include <log/sinks/file.h>

th_log_console_sink_t sink;
th_log_file_sink_t file_sink;

void SomeSystem(ecs_iter_t *it) {
  const EcsIdentifier *restrict ids = ecs_field(it, EcsIdentifier, 0);

  for (int i = 0; i < it->count; i++) {
    ecs_entity_t e = it->entities[i];
    TH_LOG_INFO("Hello, %s!", ids[i].value);
  }
}

void setup(ecs_world_t *world, ecs_app_desc_t *app) {
  th_log_console_sink_init(&sink, TH_LOG_LEVEL_TRACE, true);
  th_log_add_sink((th_log_sink_header_t *)&sink);

  th_log_file_sink_init(&file_sink, "log.txt", TH_LOG_LEVEL_TRACE);
  th_log_add_sink((th_log_sink_header_t *)&file_sink);

  TH_LOG_FATAL("Hello, World!");
  TH_LOG_WARN("Hello, World!");
  TH_LOG_ERROR("Hello, World!");

  /* 
   * allows us to view stats and interact with the world at
   * https://www.flecs.dev/explorer/v4/ 
   */
  ECS_IMPORT(world, FlecsStats);
  app->enable_rest = true;

  ECS_TAG(world, SomeTag);

  for (int i = 0; i < 5; i ++) {
    static const char *names[] = {"Bob", "Alice", "Charlie", "Daisy", "Eve"};
    ecs_entity_t e = ecs_entity(world, { .name = names[i] });
    ecs_add_id(world, e, SomeTag);
  }

  ECS_SYSTEM(world, SomeSystem, EcsOnUpdate, [in] (Identifier, Name), SomeTag);
  ecs_system(world, {
    .entity = ecs_id(SomeSystem),
    .multi_threaded = true
  });
}

void cleanup() {
  th_log_file_sink_deinit(&file_sink);
  th_log_console_sink_deinit(&sink);
  th_log_clear_sinks();
}
