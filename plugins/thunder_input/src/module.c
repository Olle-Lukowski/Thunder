#define ECS_META_IMPL IMPL
#include "input/module.h"

#include "input/keys.h"

void ThunderInputImport(ecs_world_t *world) {
  ECS_MODULE(world, ThunderInput);

  ECS_META_COMPONENT(world, KeyCode);
  ECS_META_COMPONENT(world, KeyPressed);
  ECS_META_COMPONENT(world, KeyReleased);
  ECS_META_COMPONENT(world, KeyRepeated);
}
