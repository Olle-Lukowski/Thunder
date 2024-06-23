#include "core/setup.h"
#include "core/cleanup.h"

int main(int argc, char *argv[]) {
  ecs_world_t *world = ecs_init_w_args(argc, argv);
  ecs_app_desc_t app = {0};

  setup(world, &app);

  int result = ecs_app_run(world, &app);

  cleanup();

  return result;
}
