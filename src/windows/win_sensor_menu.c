#include "./win_sensor_menu.h"

static Window* s_window = NULL;
static SimpleMenuLayer* s_menu_layer = NULL;

static uint32_t number_of_sensors = 0;
static SimpleMenuItem* s_sensors_menu = NULL;
static SimpleMenuSection s_sensors_menu_section[1];

static char** s_title_array = NULL;
static char** s_subtitle_array = NULL;

static void draw_sensor (int index, void* context) {
  win_sensor_show((void*) sensor_people_now_present->array[index]);
}

static void window_load (Window* window) {}
static void window_unload (Window* window) {}

static void window_appear (Window* window) {
  number_of_sensors = sensor_people_now_present->length;
  s_sensors_menu = malloc(sizeof(SimpleMenuItem) * number_of_sensors);
  s_title_array = malloc(sizeof(char*) * number_of_sensors);
  s_subtitle_array = malloc(sizeof(char*) * number_of_sensors);


  for (uint32_t i = 0; i < number_of_sensors; ++i) {
    PeopleNowPresent* current = sensor_people_now_present->array[i];
    if (current->name) {
      s_title_array[i] = current->name;
    } else {
      // TODO : Change to something generic
      s_title_array[i] = "People now present.";
    }

    if (current->location) {
      s_subtitle_array[i] = current->location;
    } else {
      s_subtitle_array[i] = NULL;
    }

    s_sensors_menu[i] = (SimpleMenuItem) {
      .title = s_title_array[i],
      .subtitle = s_subtitle_array[i],
      .callback = draw_sensor,
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

static void window_disappear (Window* window) {
  simple_menu_layer_destroy(s_menu_layer);
  free(s_sensors_menu);
  s_sensors_menu = NULL;
  free(s_title_array);
  s_title_array = NULL;
  free(s_subtitle_array);
  s_subtitle_array = NULL;
}

void win_sensor_menu_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = window_load,
    .appear = window_appear,
    .disappear = window_disappear,
    .unload = window_unload,
  });
  win_sensor_init();
  window_stack_push(s_window, true);
}

void win_sensor_menu_deinit(void) {
  win_sensor_deinit();
  window_destroy(s_window);
}
