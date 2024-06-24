#include "windowing/window.h"

static bool glfw_initialized = false;
static int glfw_window_count = 0;

bool th_window_create(
  th_window_t *window,
  int width,
  int height,
  const char *title
) {
  if (!glfw_initialized) {
    if (!glfwInit())
      return false;

    glfw_initialized = true;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  window->window = glfwCreateWindow(
    width,
    height,
    title,
    NULL,
    NULL
  );

  if (!window->window) {
    if (glfw_window_count == 0 && glfw_initialized) {
      glfwTerminate();
      glfw_initialized = false;
    }
    return false;
  } else {
    ++glfw_window_count;
  }

  return true;
}

void th_window_destroy(const th_window_t *window) {
  glfwDestroyWindow(window->window);
  --glfw_window_count;
  if (glfw_window_count == 0) {
    glfwTerminate();
    glfw_initialized = false;
  }
}

bool th_window_update(const th_window_t *window) {
  glfwPollEvents();
  return !glfwWindowShouldClose(window->window);
}

void th_window_set_size(const th_window_t *window, int width, int height) {
  glfwSetWindowSize(window->window, width, height);
}

void th_window_set_title(const th_window_t *window, const char *title) {
  glfwSetWindowTitle(window->window, title);
}
