#define ECS_META_IMPL IMPL

#include "windowing/module.h"

#include "windowing/window.h"

#include "log/log.h"

ECS_COMPONENT_DECLARE(th_window_t);
ECS_ENTITY_DECLARE(OnWindowUpdate);

static int window_count = 0;

ECS_CTOR(th_window_t, ptr, {
  ptr->window = NULL;
  ++window_count;
});

ECS_MOVE(th_window_t, dst, src, {
  if (dst->window)
    th_window_destroy(dst);

  dst->window = src->window;
  src->window = NULL;
});

ECS_COPY(th_window_t, dst, src, {
  if (dst->window)
    th_window_destroy(dst);

  dst->window = src->window;
});

ECS_DTOR(th_window_t, ptr, {
  if (ptr->window)
    th_window_destroy(ptr);
  --window_count;
});

static void OnWindowCreate(ecs_iter_t *it) {
  Window *restrict windows = ecs_field(it, Window, 0);

  for (int i = 0; i < it->count; i++) {
    th_window_t window;

    if (windows[i].should_close)
      /* We can't destroy the window before it's created */
      windows[i].should_close = false; 

    if (!th_window_create(
      &window,
      windows[i].width,
      windows[i].height,
      windows[i].title
    )) {
      TH_LOG_ERROR("Failed to create window '%s'", windows[i].title);
      ecs_delete(it->world, it->entities[i]);
      continue;
    }

    ecs_set(it->world, it->entities[i], th_window_t, {window.window});
  }
}

static void UpdateWindows(ecs_iter_t *it) {
  const Window *restrict windows = ecs_field(it, Window, 0);
  const th_window_t *restrict windows_th = ecs_field(it, th_window_t, 1);

  for (int i = 0; i < it->count; i++) {
    if (windows[i].should_close) {
      ecs_delete(it->world, it->entities[i]);
    } else {
      if (!th_window_update(&windows_th[i])) {
        TH_LOG_INFO("Window '%s' closed", windows[i].title);
        ecs_delete(it->world, it->entities[i]);
      } else {
        if (ecs_iter_changed(it)) {
          /* 
           * at least one window in this table was changed, in case it was this
           * one, we need to update the values.
           */
          th_window_set_size(
            &windows_th[i],
            windows[i].width,
            windows[i].height
          );
          th_window_set_title(&windows_th[i], windows[i].title);
        }
      }
    }
  }
}

static void QuitIfNoWindows(ecs_iter_t *it) {
  if (window_count == 0) {
    TH_LOG_INFO("All windows closed, quitting...");
    ecs_quit(it->world);
  }
}

void ThunderWindowingImport(ecs_world_t *world) {
  ECS_MODULE(world, ThunderWindowing);

  ECS_META_COMPONENT(world, Window);
  ECS_COMPONENT_DEFINE(world, th_window_t);

  ecs_set_hooks(world, th_window_t, {
    .ctor = ecs_ctor(th_window_t),
    .move = ecs_move(th_window_t),
    .copy = ecs_copy(th_window_t),
    .dtor = ecs_dtor(th_window_t),
  });

  ECS_ENTITY_DEFINE(world, OnWindowUpdate);
  ecs_add_id(world, OnWindowUpdate, EcsPhase);

  ecs_entity_t main_window = ecs_entity(world, { .name = "MainWindow" });

  ECS_OBSERVER(world, OnWindowCreate, EcsOnSet, Window, !th_window_t);

  ecs_set(world, main_window, Window, {1280, 720, false, "Thunder"});

  ECS_SYSTEM(world, UpdateWindows, EcsOnUpdate, [in] Window, [in] th_window_t);
  ecs_add_pair(world, OnWindowUpdate, EcsDependsOn, ecs_id(UpdateWindows));

  ECS_SYSTEM(world, QuitIfNoWindows, OnWindowUpdate, 0);
}

