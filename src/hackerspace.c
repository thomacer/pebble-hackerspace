#include <pebble.h>

#define NUMBER_OF_SCRAPPED_INFO 8

#define KEY_SPACE 0
#define KEY_EMAIL 1
#define KEY_IRC 2
#define KEY_FACEBOOK 3
#define KEY_TWITTER 4
#define KEY_OPEN_STATE 5
#define KEY_NUMBER_OF_PEOPLE_PRESENT 6
#define KEY_LIST_OF_PEOPLE_PRESENT 7

static char* space_info_title[NUMBER_OF_SCRAPPED_INFO];
static char* space_info_subtitle[NUMBER_OF_SCRAPPED_INFO];
/* static char** space_info_icons[NUMBER_OF_SCRAPPED_INFO]; */

/* This variable will be set when we get the JSON from SpaceAPI. */
static uint16_t space_info_current_number = 0;

static Window* window;
static char space_name_buffer[32];

static MenuLayer* s_menu_layer;

static GBitmap *s_logo_bitmap;


/* ------------------------------------------------------------------------
 *                      Partie communication avec l'API.
 * ------------------------------------------------------------------------
 */

/* Fonction applée lorsqu'on envoie quelque chose mais qu'un problême se prodoit.
 */
static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

/* Fonction appelée lorsqu'on envoie quelque chose, avec succès.
 */
static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void inbox_connected_person_callback(DictionaryIterator *iterator, void *context) {
  Tuple *space_tuple = dict_find(iterator, KEY_SPACE);
  Tuple *email_tuple = dict_find(iterator, KEY_EMAIL);
  Tuple *irc_tuple = dict_find(iterator, KEY_IRC);
  Tuple *facebook_tuple = dict_find(iterator, KEY_FACEBOOK);
  Tuple *twitter_tuple = dict_find(iterator, KEY_TWITTER);
  Tuple *number_tuple = dict_find(iterator, KEY_NUMBER_OF_PEOPLE_PRESENT);
  /* Tuple *person_present_tuple = dict_find(iterator, KEY_LIST_OF_PEOPLE_PRESENT); */

  space_info_current_number = 0;

  if (space_tuple) {
    snprintf(space_name_buffer, sizeof(space_name_buffer), "%s", space_tuple->value->cstring);
  }

  if (email_tuple) {
    static char email_buffer[32];
    static char email_subtitle_buffer[32];
    snprintf(email_buffer, sizeof(email_buffer), "Mail.");
    snprintf(email_subtitle_buffer, sizeof(email_subtitle_buffer), "%s", email_tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added mail connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = email_buffer;
    space_info_subtitle[space_info_current_number] = email_subtitle_buffer;
    ++space_info_current_number;
  }

  if (irc_tuple) {
    static char irc_buffer[32];
    static char irc_subtitle_buffer[32];
    snprintf(irc_buffer, sizeof(irc_buffer), "IRC");
    snprintf(irc_subtitle_buffer, sizeof(irc_subtitle_buffer), "%s", irc_tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added irc connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = irc_buffer;
    space_info_subtitle[space_info_current_number] = irc_subtitle_buffer;
    ++space_info_current_number;
  }

  if (facebook_tuple) {
    static char facebook_buffer[32];
    static char facebook_subtitle_buffer[32];
    snprintf(facebook_buffer, sizeof(facebook_buffer), "Facebook");
    snprintf(facebook_subtitle_buffer, sizeof(facebook_subtitle_buffer), "%s", facebook_tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added facebook connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = facebook_buffer;
    space_info_subtitle[space_info_current_number] = facebook_subtitle_buffer;
    ++space_info_current_number;
  }

  if (twitter_tuple) {
    static char twitter_buffer[32];
    static char twitter_subtitle_buffer[32];
    snprintf(twitter_buffer, sizeof(twitter_buffer), "Twitter");
    snprintf(twitter_subtitle_buffer, sizeof(twitter_subtitle_buffer), "%s", twitter_tuple->value->cstring);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added twitter connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = twitter_buffer;
    space_info_subtitle[space_info_current_number] = twitter_subtitle_buffer;
    ++space_info_current_number;
  }

  if (number_tuple) {
    static char number_of_people_buffer[32];
    static char number_of_people_subtitle_buffer[32];
    snprintf(number_of_people_buffer, sizeof(number_of_people_buffer), "Persons connected.");
    snprintf(number_of_people_subtitle_buffer, sizeof(number_of_people_subtitle_buffer), "%d", (int) number_tuple->value->int32);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added number of person connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = number_of_people_buffer;
    space_info_subtitle[space_info_current_number] = number_of_people_subtitle_buffer;
    ++space_info_current_number;
  }


  /* text_layer_set_text(number_of_people_layer, number_of_people_buffer); */

  layer_mark_dirty(menu_layer_get_layer(s_menu_layer));
  menu_layer_reload_data(s_menu_layer);
}

/* ------------------------------------------------------------------------
 *                      Gestion lignes de la liste
 * ------------------------------------------------------------------------
 */

/* @desc Return number of sections.
 *
 * @param {menu_layer} :
 * @param {data} :
 *
 * @return {uint16_t} : Number of sections.
 */
/* - Header.
 * - Navigation.
 */
#define NUMBER_OF_SECTIONS 2
static uint16_t menu_get_num_sections_callback(MenuLayer* menu_layer, void* data) {
    return NUMBER_OF_SECTIONS;
}

/* @desc Get number of "items" by "section".
 *
 * @param {menu_layer} :
 * @param {section_index} :
 * @param {data} :
 */
/* Only 1 image is shown. */
#define NUMBER_OF_ITEM_IN_HEADER 1
static uint16_t menu_get_num_rows_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
    switch (section_index) {
        case 0:
            return NUMBER_OF_ITEM_IN_HEADER;
        case 1:
            return space_info_current_number;
        default:
            return 0;
    }
}

/* @desc Get header size.
 *
 * @param {menu_layer} :
 * @param {section_index} :
 * @param {data} :
 */
static int16_t menu_get_header_height_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

/* @desc Get cell size.
 */
static int16_t menu_get_cell_height_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    switch (cell_index->section) {
        case 0:
            switch (cell_index->row) {
                case 0:
                    return gbitmap_get_bounds(s_logo_bitmap).size.h;
                default:
                    return MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT;
            }
        default:
            return MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT;
    }
    /* if (menu_layer_is_index_selected(menu_layer, cell_index)) { */
    /* } else { */
    /*     return MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT; */
    /* } */
}

/* @desc Draw the headers sections.
 *
 * @param {ctx} :
 * @param {cell_layer} :
 * @param {section_index} :
 * @param {data} :
 */
static void menu_draw_header_callback(GContext* ctx, const Layer* cell_layer, uint16_t section_index, void* data) {
    switch (section_index) {
        case 0:
            menu_cell_basic_header_draw(ctx, cell_layer, space_name_buffer);
            break;
        case 1:
            if (space_info_current_number == 1) {
                menu_cell_basic_header_draw(ctx, cell_layer, "Navigation command");
            } else if (space_info_current_number == 1) {
                menu_cell_basic_header_draw(ctx, cell_layer, "Navigation commands");
            }
            break;
    }
}

/* @desc Draw items in the section.
 */
static void menu_draw_row_callback(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* data) {
    switch (cell_index->section) {
        case 0: ;
            GSize size = layer_get_frame(cell_layer).size;
            const uint8_t x_offset = (size.w - gbitmap_get_bounds(s_logo_bitmap).size.w) / 2;
            const uint8_t y_offset = (size.h - gbitmap_get_bounds(s_logo_bitmap).size.h) / 2;
            graphics_draw_bitmap_in_rect(ctx, s_logo_bitmap, GRect(x_offset, y_offset, size.w, size.h));
            break;
        case 1:
            menu_cell_basic_draw(ctx, cell_layer, space_info_title[cell_index->row], space_info_subtitle[cell_index->row],NULL);
            break;
    }
}

/* @desc Assign functions callback to items.
 */
static void menu_select_callback(MenuLayer* menu_layer, MenuIndex* cell_index, void* data) {
}

/* ------------------------------------------------------------------------
 *                      Partie création des layers.
 * ------------------------------------------------------------------------
 *
 * +-------------------------
 * | Section
 * | +--------------------
 * | | +---------------
 * | | | HackerSpace Name (header)
 * | | +---------------
 * | | +---------------
 * | | | HackerSpace logo (item)
 * | | +---------------
 * | +--------------------
 * |
 * | Section
 * | +--------------------
 * | | +---------------
 * | | | Navigation Commands (header)
 * | | +---------------
 * | | +---------------
 * | | | Contact (item)
 * | | +---------------
 * | | +---------------
 * | | | HackerSpace is open (item)
 * | | +---------------
 * | |
 * | +--------------------
 * |
 * +------------------------
 *
 * ------------------------------------------------------------------------
 */
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create GBitmap
  s_logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);

  s_menu_layer = menu_layer_create(bounds);
  menu_layer_set_callbacks(s_menu_layer, NULL, (MenuLayerCallbacks) {
    .get_num_sections = menu_get_num_sections_callback,
    .get_num_rows = menu_get_num_rows_callback,
    .get_header_height = menu_get_header_height_callback,
    .draw_header = menu_draw_header_callback,
    .draw_row = menu_draw_row_callback,
    .select_click = menu_select_callback,
    .get_cell_height = menu_get_cell_height_callback,
  });

  // Bind the menu layer's click config provider to the window for interactivity
  menu_layer_set_click_config_onto_window(s_menu_layer, window);

  layer_add_child(window_layer, menu_layer_get_layer(s_menu_layer));

  /* space_layer = text_layer_create(GRect(0, 42, bounds.size.w, 20)); */
  /* text_layer_set_text(space_layer, "Loading ..."); */
  /* text_layer_set_text_alignment(space_layer, GTextAlignmentCenter); */
  /* layer_add_child(window_layer, text_layer_get_layer(space_layer)); */

  /* number_of_people_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20)); */
  /* text_layer_set_text(number_of_people_layer, "Loading ..."); */
  /* text_layer_set_text_alignment(number_of_people_layer, GTextAlignmentCenter); */
  /* layer_add_child(window_layer, text_layer_get_layer(number_of_people_layer)); */
}

static void window_unload(Window *window) {
  // Destroy GBitmap
  gbitmap_destroy(s_logo_bitmap);

  menu_layer_destroy(s_menu_layer);
}

static void init(void) {
  strcpy(space_name_buffer, "Hackerspace");

  window = window_create();
  /* window_set_click_config_provider(window, click_config_provider); */
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);

  // Register callbacks
  app_message_register_inbox_received(inbox_connected_person_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
