#include "./win_sensor_menu.h"

static Window* s_window = NULL;
static SimpleMenuLayer* s_menu_layer = NULL;

static uint32_t number_of_sensors = 0;
static SimpleMenuItem* s_sensors_menu = NULL;
static SimpleMenuSection s_sensors_menu_section[1];

static void window_load (Window* window) {
  number_of_sensors = sensor_people_now_present->length;
  s_sensors_menu = malloc(sizeof(SimpleMenuItem) * number_of_sensors);

  for (uint32_t i = 0; i < number_of_sensors; ++i) {
    PeopleNowPresent* current = sensor_people_now_present->array[i];
    s_sensors_menu[i] = (SimpleMenuItem) {
      .title = "PeopleNowPresent",
      /* .subtitle = current->value, */
      .callback = NULL,
    };
  }

  s_sensors_menu_section[0] = (SimpleMenuSection) {
    .title = "Sensors",
    .num_items = number_of_sensors,
    .items = s_sensors_menu,
  };

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_menu_layer = simple_menu_layer_create(bounds, window, s_sensors_menu_section, 1, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_menu_layer));
}

static void window_unload (Window* window) {
  simple_menu_layer_destroy(s_menu_layer);
  free(s_sensors_menu);
}

void win_sensor_menu_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}

void win_sensor_menu_deinit(void) {
  window_destroy(s_window);
}
