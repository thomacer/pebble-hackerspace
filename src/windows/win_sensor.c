#include "./win_sensor.h"

static Window* s_window = NULL;

static void* current_sensor_struct = NULL;

static void window_appear (Window* window) {
  ((Sensor*) current_sensor_struct)->win_draw(window, current_sensor_struct);
}

static void window_disappear (Window* window) {
  ((Sensor*) current_sensor_struct)->win_destroy(current_sensor_struct);
  current_sensor_struct = NULL;
}

void win_sensor_show(void* sensor_struct) {
  current_sensor_struct = sensor_struct;
  window_stack_push(s_window, true);
}

void win_sensor_init (void) {
  if (s_window) {
    return;
  }

  s_window = window_create();

  window_set_window_handlers(s_window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_sensor_deinit (void) {
    window_destroy(s_window);
    s_window = NULL;
}
