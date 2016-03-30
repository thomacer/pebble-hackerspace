#include "./win_contact.h"
#include "../libs/pebble-assist.h"

static Window* s_window = NULL;

static SimpleMenuLayer* s_menu_layer = NULL;

static uint16_t space_contact_current_number = 0;

#define NUMBER_OF_SECTIONS 1
static SimpleMenuSection s_menu_sections[NUMBER_OF_SECTIONS];
#define NUMBER_OF_CONTACT_ITEMS 4
static SimpleMenuItem s_contact_menu_items[NUMBER_OF_CONTACT_ITEMS];


static void action_callback (int index, void *ctx) {

}


/* ------------------------------------------------------------------------
 *                      Partie création des layers.
 * ------------------------------------------------------------------------
 */
static void window_load (Window *window) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Launching window loading.");

  space_contact_current_number = 0;

  if (t_contact_irc) {
    s_contact_menu_items[space_contact_current_number++] = (SimpleMenuItem) {
        .title = "IRC",
        .subtitle = t_contact_irc->value->cstring,
        .callback = action_callback,
    };
    DEBUG("Added irc : %i", space_contact_current_number);
  }

  if (t_contact_twitter) {
    s_contact_menu_items[space_contact_current_number++] = (SimpleMenuItem) {
        .title = "Twitter",
        .subtitle = t_contact_twitter->value->cstring,
        .callback = action_callback,
    };
    DEBUG("Added twitter in position : %i", space_contact_current_number);
  }

  if (t_contact_facebook) {
    s_contact_menu_items[space_contact_current_number++] = (SimpleMenuItem) {
        .title = "Facebook",
        .subtitle = t_contact_facebook->value->cstring,
        .callback = action_callback,
    };
    DEBUG("Added facebook : %i", space_contact_current_number);
  }

  if (t_contact_email) {
    s_contact_menu_items[space_contact_current_number++] = (SimpleMenuItem) {
        .title = "Mail",
        .subtitle = t_contact_email->value->cstring,
        .callback = action_callback,
    };
    DEBUG("Added mail : %i", space_contact_current_number);
  }



  s_menu_sections[0] = (SimpleMenuSection) {
      .title = "Contacts section",
      .num_items = space_contact_current_number,
      .items = s_contact_menu_items,
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

void win_contact_show(void) {
  window_stack_push(s_window, true);
}

void win_contact_init(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "CREATING NEW WINDOW : contact_window");
  s_window = window_create();

  window_set_window_handlers(s_window, (WindowHandlers) {
    .appear = window_load,
    .unload = window_unload,
  });
}

void win_contact_deinit(void) {
    /* window_unload(s_window); */
    window_destroy(s_window);
}
