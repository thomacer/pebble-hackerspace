#include "win_basic.h"

static Window* window;

static void window_load (Window* window) {

}

static void window_unload (Window* window) {

}

void win_basic_update(void) {

}

void win_basic_show(void) {
  window_stack_push(window, true);
}

void win_basic_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
}

void win_basic_deinit(void) {

}
