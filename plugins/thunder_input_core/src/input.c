#include "input/input.h"

#include <stdlib.h>

static void glfw_key_callback(
  GLFWwindow *window,
  int key,
  int scancode,
  int action,
  int mods
) {
  th_input_ctx_t *ctx = (th_input_ctx_t *)glfwGetWindowUserPointer(window);
  th_input_key_event_t event = {
    .key = key,
  };

  switch (action) {
    case GLFW_PRESS:
      event.action = TH_INPUT_KEY_ACTION_PRESSED;
      break;
    case GLFW_RELEASE:
      event.action = TH_INPUT_KEY_ACTION_RELEASED;
      break;
    case GLFW_REPEAT:
      event.action = TH_INPUT_KEY_ACTION_REPEATED;
      break;
  }

  if (!ctx->key_events) {
    ctx->key_events_capacity = 16; /* TODO: make this configurable */
    ctx->key_events = malloc(
      sizeof(th_input_key_event_t) * ctx->key_events_capacity
    );
    ctx->key_events_count = 0;
  }
  
  if (ctx->key_events_count >= ctx->key_events_capacity) {
    ctx->key_events_capacity *= 2;
    ctx->key_events = realloc(
      ctx->key_events,
      sizeof(th_input_key_event_t) * ctx->key_events_capacity
    );
  }

  ctx->key_events[ctx->key_events_count++] = event;
}

static void glfw_mouse_callback(
  GLFWwindow *window,
  double x,
  double y
) {
  th_input_ctx_t *ctx = (th_input_ctx_t *)glfwGetWindowUserPointer(window);
  th_input_mouse_motion_event_t event = {
    .x = x,
    .y = y
  };

  if (!ctx->mouse_motion_events) {
    ctx->mouse_motion_events_capacity = 16; /* TODO: make this configurable */
    ctx->mouse_motion_events = malloc(
      sizeof(th_input_mouse_motion_event_t) * ctx->mouse_motion_events_capacity
    );
    ctx->mouse_motion_events_count = 0;
  }
  
  if (ctx->mouse_motion_events_count >= ctx->mouse_motion_events_capacity) {
    ctx->mouse_motion_events_capacity *= 2;
    ctx->mouse_motion_events = realloc(
      ctx->mouse_motion_events,
      sizeof(th_input_mouse_motion_event_t) * ctx->mouse_motion_events_capacity
    );
  }

  ctx->mouse_motion_events[ctx->mouse_motion_events_count++] = event;
}

static void glfw_mouse_button_callback(
  GLFWwindow *window,
  int button,
  int action,
  int mods
) {
  th_input_ctx_t *ctx = (th_input_ctx_t *)glfwGetWindowUserPointer(window);
  th_input_mouse_button_event_t event = {
    .button = button,
  };
  switch (action) {
    case GLFW_PRESS:
      event.action = TH_INPUT_KEY_ACTION_PRESSED;
      break;
    case GLFW_RELEASE:
      event.action = TH_INPUT_KEY_ACTION_RELEASED;
      break;
    case GLFW_REPEAT:
      event.action = TH_INPUT_KEY_ACTION_REPEATED;
      break;
  }

  if (!ctx->mouse_button_events) {
    ctx->mouse_button_events_capacity = 16; /* TODO: make this configurable */
    ctx->mouse_button_events = malloc(
      sizeof(th_input_mouse_button_event_t) * ctx->mouse_button_events_capacity
    );
    ctx->mouse_button_events_count = 0;
  }
  
  if (ctx->mouse_button_events_count >= ctx->mouse_button_events_capacity) {
    ctx->mouse_button_events_capacity *= 2;
    ctx->mouse_button_events = realloc(
      ctx->mouse_button_events,
      sizeof(th_input_mouse_button_event_t) * ctx->mouse_button_events_capacity
    );
  }

  ctx->mouse_button_events[ctx->mouse_button_events_count++] = event;
}

static void glfw_scroll_callback(
  GLFWwindow *window,
  double xoffset,
  double yoffset
) {
  th_input_ctx_t *ctx = (th_input_ctx_t *)glfwGetWindowUserPointer(window);

  th_input_mouse_scroll_event_t event = {
    .dx = xoffset,
    .dy = yoffset
  };

  if (!ctx->mouse_scroll_events) {
    ctx->mouse_scroll_events_capacity = 16; /* TODO: make this configurable */
    ctx->mouse_scroll_events = malloc(
      sizeof(th_input_mouse_scroll_event_t) * ctx->mouse_scroll_events_capacity
    );
    ctx->mouse_scroll_events_count = 0;
  }
  
  if (ctx->mouse_scroll_events_count >= ctx->mouse_scroll_events_capacity) {
    ctx->mouse_scroll_events_capacity *= 2;
    ctx->mouse_scroll_events = realloc(
      ctx->mouse_scroll_events,
      sizeof(th_input_mouse_scroll_event_t) * ctx->mouse_scroll_events_capacity
    );
  }

  ctx->mouse_scroll_events[ctx->mouse_scroll_events_count++] = event;
}

void th_input_update(th_input_ctx_t *ctx) {
  glfwSetWindowUserPointer(ctx->window.window, ctx);
}

void th_input_register_callbacks(th_input_ctx_t *ctx) {
  glfwSetKeyCallback(
    ctx->window.window,
    glfw_key_callback
  );

  glfwSetCursorPosCallback(
    ctx->window.window,
    glfw_mouse_callback
  );

  glfwSetMouseButtonCallback(
    ctx->window.window,
    glfw_mouse_button_callback
  );

  glfwSetScrollCallback(
    ctx->window.window,
    glfw_scroll_callback
  );
}
