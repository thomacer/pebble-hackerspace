#include "./win_sensor.h"

static Window* s_window = NULL;

static void* current_sensor_struct = NULL;

/* Those two functions are empty because a sensor window depend on the sensor
 * you select to show so there is no real design to be constructed at the
 * load time. The design will be made at when the window is shown.
 */
static void window_load (Window* window) {}
static void window_unload (Window* window) {}

static void window_appear (Window* window) {
  ((Sensor*) current_sensor_struct)->Sensor_draw(window, current_sensor_struct);
}

/* @note : Can be problematic when the window disappear but it's still
 *      in the stack.
 */
static void window_disappear (Window* window) {
  ((Sensor*) current_sensor_struct)->Sensor_destroy(current_sensor_struct);
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
    /* .load = window_load, */
    .load = window_load,
    .appear = window_appear,
    .disappear = window_disappear,
    .unload = window_unload,
  });
}

void win_sensor_deinit (void) {
    window_destroy(s_window);
    s_window = NULL;
}
