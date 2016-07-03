#include "./win_sensor.h"

static Window* s_window = NULL;

static int current_sensor_type = 0;
static void* current_sensor_struct = NULL;

/* Used to keep in memory the information about
 * the current window showed
 */
static void* window_current_sensor_struct = NULL;

/* Those two functions are empty because a sensor window depend on the sensor
 * you select to show so there is no real design to be constructed at the
 * load time. The design will be made at when the window is shown.
 */
static void window_load (Window* window) {}
static void window_unload (Window* window) {}

static void window_appear (Window* window) {
    switch (current_sensor_type) {
        case KEY_SENSOR_PEOPLE_NOW_PRESENT:
            window_current_sensor_struct = current_sensor_struct;
            PeopleNowPresent_draw (window, (PeopleNowPresent*) window_current_sensor_struct);
            break;
    }
}

/* @note : Can be problematic when the window disappear but it's still
 *      in the stack.
 */
static void window_disappear (Window* window) {
    switch (current_sensor_type) {
        case KEY_SENSOR_PEOPLE_NOW_PRESENT:
            PeopleNowPresent_destroy (window, (PeopleNowPresent*) current_sensor_struct);
            window_current_sensor_struct = NULL;
            break;
    }
}

void win_sensor_show(void) {
  window_stack_push(s_window, true);
}

void win_sensor_init (void) {
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
}
