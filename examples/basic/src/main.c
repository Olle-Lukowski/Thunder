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
    /* Do anything with the data here */
  }
}

void setup(ecs_world_t *world, ecs_app_desc_t *app) {
  th_log_console_sink_init(&sink, TH_LOG_LEVEL_TRACE, true);
  th_log_add_sink((th_log_sink_header_t *)&sink);

  th_log_file_sink_init(&file_sink, TH_LOG_LEVEL_TRACE, "log.txt");
  th_log_add_sink((th_log_sink_header_t *)&file_sink);

  TH_LOG_FATAL("Hello, World!");
  TH_LOG_WARN("Hello, World!");
  TH_LOG_ERROR("Hello, World!");

  /* 
   * allows us to view stats and interact with the world at
   * https://www.flecs.dev/explorer/v4/ 
   */
  app->enable_rest = true;
  app->enable_stats = true;
  /* Change this number depending on how many threads you want to use */
  ecs_set_threads(world, 1);

  /* 
   * Scripts allow for easy spawning and managing of entities, it is my personal
   * preference for managing scenes. 
   */
  ecs_entity_t s = ecs_script(world, { .filename = "examples/basic/src/main.flecs" });
  if (!s)
    TH_LOG_FATAL("Failed to load main.flecs");

  ECS_TAG(world, SomeTag);

  for (int i = 0; i < 5; i ++) {
    static const char *names[] = {"Bob", "Alice", "Charlie", "Daisy", "Eve"};
    ecs_entity_t e = ecs_entity(world, { .name = names[i] });
    ecs_add(world, e, SomeTag);
  }

  ECS_SYSTEM(world, SomeSystem, EcsOnUpdate, [in] (Identifier, Name), SomeTag);
  ecs_system(world, {
    .entity = ecs_id(SomeSystem),
    .multi_threaded = true
  });
}

void cleanup() {
  th_log_file_sink_deinit(&file_sink);
  th_log_clear_sinks();
}
