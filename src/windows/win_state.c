#include "./win_state.h"
#include "../libs/pebble-assist.h"

static Window* window = NULL;

static SimpleMenuLayer* s_menu_layer = NULL;

static uint16_t space_state_current_number = 0;

#define NUMBER_OF_SECTIONS 1
static SimpleMenuSection s_menu_sections[NUMBER_OF_SECTIONS];
#define NUMBER_OF_MAX_STATE_ITEMS 4
static SimpleMenuItem s_state_menu_items[NUMBER_OF_MAX_STATE_ITEMS];


static void action_callback (int index, void *ctx) {
    return;
}


/* ------------------------------------------------------------------------
 *                      Partie création des layers.
 * ------------------------------------------------------------------------
 */
static void window_load (Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Launching \"state\" window loading.");

  space_state_current_number = 0;

  if (t_number) {
    static char number_of_people_subtitle[32];
    if ((int) t_number->value->int32 > 1) {
        snprintf(number_of_people_subtitle, sizeof(number_of_people_subtitle), "%d persons.", (int) t_number->value->int32);
    } else {
        snprintf(number_of_people_subtitle, sizeof(number_of_people_subtitle), "%d person.", (int) t_number->value->int32);
    }
    s_state_menu_items[space_state_current_number] = (SimpleMenuItem) {
        .title = "People connected.",
        .subtitle = number_of_people_subtitle,
        .callback = action_callback,
    };
    DEBUG("Added number (%i) in position : %i", (int) t_number->value->int32, space_state_current_number);
    space_state_current_number++;
  }

  s_menu_sections[0] = (SimpleMenuSection) {
      .title = "Contacts section",
      .num_items = space_state_current_number,
      .items = s_state_menu_items,
  };

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_menu_layer = simple_menu_layer_create(bounds, window, s_menu_sections, NUMBER_OF_SECTIONS, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_menu_layer));

  DEBUG("Finished doing the menu layer for the contact window.");
}

static void window_unload(Window *window) {
  simple_menu_layer_destroy(s_menu_layer);
}

void win_state_show(void) {
  window_stack_push(window, true);
}

void win_state_init(void) {
  DEBUG("CREATING NEW WINDOW : state_window");
  window = window_create();

  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
}

void win_state_deinit(void) {
    window_unload(window);
    window_destroy(window);
}
