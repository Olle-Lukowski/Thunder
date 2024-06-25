#ifndef TH_WINDOWING_MODULE_H_
#define TH_WINDOWING_MODULE_H_

#ifndef ECS_META_IMPL
#define ECS_META_IMPL EXTERN
#endif

#include <stdint.h>

#include <flecs.h>

ECS_STRUCT(Window, {
  int32_t width;
  int32_t height;
  bool should_close;
  const char *title;
});

extern ECS_ENTITY_DECLARE(OnWindowUpdate);

void ThunderWindowingImport(ecs_world_t *world);

#endif /* TH_WINDOWING_MODULE_H_ */
