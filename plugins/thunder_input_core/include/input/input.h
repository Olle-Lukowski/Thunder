#ifndef TH_INPUT_INPUT_H_
#define TH_INPUT_INPUT_H_

#include "windowing/window.h"

typedef enum th_input_action th_input_action_t;
enum th_input_action {
  TH_INPUT_KEY_ACTION_PRESSED,
  TH_INPUT_KEY_ACTION_RELEASED,
  TH_INPUT_KEY_ACTION_REPEATED,
};

typedef struct th_input_key_event th_input_key_event_t;
struct th_input_key_event {
  int key;
  th_input_action_t action;
};

typedef struct th_input_mouse_motion_event th_input_mouse_motion_event_t;
struct th_input_mouse_motion_event {
  double x;
  double y;
};

typedef struct th_input_mouse_button_event th_input_mouse_button_event_t;
struct th_input_mouse_button_event {
  int button;
  th_input_action_t action;
};

typedef struct th_input_mouse_scroll_event th_input_mouse_scroll_event_t;
struct th_input_mouse_scroll_event {
  double dx;
  double dy;
};

typedef struct th_input_ctx th_input_ctx_t;
struct th_input_ctx {
  th_window_t window;
  th_input_key_event_t *key_events;
  th_input_mouse_motion_event_t *mouse_motion_events;
  th_input_mouse_button_event_t *mouse_button_events;
  th_input_mouse_scroll_event_t *mouse_scroll_events;
  int key_events_count;
  int mouse_motion_events_count;
  int mouse_button_events_count;
  int mouse_scroll_events_count;
  int key_events_capacity;
  int mouse_motion_events_capacity;
  int mouse_button_events_capacity;
  int mouse_scroll_events_capacity;
};

void th_input_update(th_input_ctx_t *ctx);
void th_input_register_callbacks(th_input_ctx_t *ctx);

#endif /* TH_INPUT_INPUT_H_ */
