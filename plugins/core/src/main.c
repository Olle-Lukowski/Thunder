#include "core/setup.h"

int main(int argc, char *argv[]) {
  ecs_world_t *world = ecs_init_w_args(argc, argv);
  ecs_app_desc_t app = {0};

  setup(world, &app);

  return ecs_app_run(world, &app);
}
