#ifndef TH_WINDOWING_WINDOW_H_
#define TH_WINDOWING_WINDOW_H_

#include <stdbool.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

typedef struct th_window th_window_t;
struct th_window {
  GLFWwindow *window;
};

bool th_window_create(
  th_window_t *window,
  int width,
  int height,
  const char *title
);
void th_window_destroy(const th_window_t *window);

bool th_window_update(const th_window_t *window);

void th_window_set_size(const th_window_t *window, int width, int height);
void th_window_set_title(const th_window_t *window, const char *title);

#endif /* TH_WINDOWING_WINDOW_H_ */
