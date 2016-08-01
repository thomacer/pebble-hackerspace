#include "win_object.h"

static Window* s_window = NULL;

static PebbleObject* current_object_struct = NULL;

static void window_appear (Window* window) {
  current_object_struct->win_draw(window, current_object_struct);
}

static void window_disappear (Window* window) {
  current_object_struct->win_destroy(current_object_struct);
  current_object_struct = NULL;
}

void win_object_show(PebbleObject* object_struct) {
  if (object_struct->win_draw) {
    current_object_struct = object_struct;
    window_stack_push(s_window, true);
  }
}

void win_object_init (void) {
  if (s_window) {
    return;
  }

  s_window = window_create();

  window_set_window_handlers(s_window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_object_deinit (void) {
    window_destroy(s_window);
    s_window = NULL;
}
