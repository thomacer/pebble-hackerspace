#include "win_main.h"

static Window* window;

static MenuLayer* s_menu_layer;

/* Logo in the first section. */
static GBitmap* s_logo_bitmap;

/* This variable will be set when we get the JSON from SpaceAPI, it keep
 * track of the number of items in the second section.
 */
static uint16_t space_info_current_number = 0;

#define MAX_NUMBER_OF_MENU 3
static char* space_info_title[MAX_NUMBER_OF_MENU];
static char* space_info_subtitle[MAX_NUMBER_OF_MENU];
/* static char** space_info_icons[MAX_NUMBER_OF_MENU]; */
static void (*space_info_callback[MAX_NUMBER_OF_MENU]) () = {};

/* ------------------------------------------------------------------------
 *                      MENU HANDLING
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
#define NUMBER_OF_SECTIONS 3
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
#define NUMBER_OF_ITEM_IN_OTHER 1
static uint16_t menu_get_num_rows_callback(MenuLayer* menu_layer, uint16_t section_index, void* data) {
    switch (section_index) {
        case 0:
            return NUMBER_OF_ITEM_IN_HEADER;
        case 1:
            return space_info_current_number;
        case 2:
            return NUMBER_OF_ITEM_IN_OTHER;
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
    return MENU_CELL_ROUND_FOCUSED_SHORT_CELL_HEIGHT;
}

/* @desc Draw the headers sections.
 *
 * @param {ctx} :
 * @param {cell_layer} :
 * @param {section_index} :
 * @param {data} :
 */
static void menu_draw_header_callback(GContext* ctx, const Layer* cell_layer, uint16_t section_index, void* data) {
    static char space_state[32];
    switch (section_index) {
        case 0:
          if (basic_info) {
            if (basic_info->state == Open) {
              snprintf(space_state, 32, "%s is open", space_name_buffer);
            } else if (basic_info->state == Closed){
              snprintf(space_state, 32, "%s is closed", space_name_buffer);
            } else if (basic_info->state == Undefined) {
              snprintf(space_state, 32, "%s", space_name_buffer);
            }
          } else {
            snprintf(space_state, 32, "%s", space_name_buffer);
          }

          menu_cell_basic_header_draw(ctx, cell_layer, space_state);
          break;
        case 1:
          menu_cell_basic_header_draw(ctx, cell_layer, "SpaceAPI content");
          break;
        case 2:
          menu_cell_basic_header_draw(ctx, cell_layer, "Other");
    }
}

/* @desc Draw items in the section.
 */
static void menu_draw_row_callback(GContext* ctx, const Layer* cell_layer, MenuIndex* cell_index, void* data) {
    switch (cell_index->section) {
        case 0: ;
          if (basic_info) {
            if (basic_info->state == Open) {
              menu_cell_basic_draw(ctx, cell_layer, space_name_buffer, "is open", NULL);
            } else if (basic_info->state == Closed) {
              menu_cell_basic_draw(ctx, cell_layer, space_name_buffer, "is closed", NULL);
            } else {
              menu_cell_basic_draw(ctx, cell_layer, space_name_buffer, NULL, NULL);
            }
          } else {
            // If basic_info is not initialized there is still no data received from the API.
            menu_cell_basic_draw(ctx, cell_layer, space_name_buffer, "Loading ...", NULL);
          }
          break;
        case 1:
          menu_cell_basic_draw(ctx, cell_layer, space_info_title[cell_index->row], space_info_subtitle[cell_index->row], NULL);
          break;
        case 2:
          menu_cell_basic_draw(ctx, cell_layer, "About", "About the app.", NULL);
          break;
    }
}

/* @desc Assign functions callback to items.
 */
static void menu_select_callback(MenuLayer* menu_layer, MenuIndex* cell_index, void* data) {
    switch (cell_index->section) {
        case 0:
          win_basic_show();
          break;
        case 1:
          if (space_info_callback[cell_index->row] != NULL) {
              (*space_info_callback[cell_index->row]) ();
          }
          break;
        case 2:
          win_about_show();
          break;
        default:
          break;
    }
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
}

static void window_unload(Window *window) {
  // Destroy GBitmap
  gbitmap_destroy(s_logo_bitmap);

  menu_layer_destroy(s_menu_layer);
}

void win_main_update(void) {
  // Section 1 : SpaceAPI content.

  space_info_current_number = 0;

  /* Drawing the second section with info about person present
   * in the hackerspace.
   */
  if (sensors_array && sensors_array->length) {
    static char sensor_menu_buffer[BUFFER_SIZE];
    /* static char sensor_menu_subtitle_buffer[BUFFER_SIZE]; */
    snprintf(sensor_menu_buffer, BUFFER_SIZE, "Sensors menu.");
    /* snprintf(number_of_people_subtitle_buffer, BUFFER_SIZE, "%ld persons", current->value); */
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Added number of person connected in position : %i", space_info_current_number);
    space_info_title[space_info_current_number] = sensor_menu_buffer;
    /* space_info_subtitle[space_info_current_number] = number_of_people_subtitle_buffer; */
    space_info_subtitle[space_info_current_number] = NULL;
    space_info_callback[space_info_current_number] = win_sensor_menu_show;
    ++space_info_current_number;
  }

  if (contacts_section) {
    /* Creating the "Contact" menu button
     * It will acces to another window.
     */
    static char contact_window_buffer[BUFFER_SIZE];
    static char contact_window_subtitle_buffer[BUFFER_SIZE];
    snprintf(contact_window_buffer, BUFFER_SIZE, contacts_section->number > 1 ?  "Contacts" : "Contact");
    snprintf(contact_window_subtitle_buffer, BUFFER_SIZE, "Contact info about %s", space_name_buffer);
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Contact section added : %i", space_info_current_number);
    space_info_title[space_info_current_number] = contact_window_buffer;
    space_info_subtitle[space_info_current_number] = contact_window_subtitle_buffer;
    space_info_callback[space_info_current_number] = win_contact_show;

    ++space_info_current_number;
  }

  if (key_masters) {
    static char keymaster_window_buffer[BUFFER_SIZE];
    /* static char keymaster_window_subtitle_buffer[BUFFER_SIZE]; */
    snprintf(keymaster_window_buffer, BUFFER_SIZE,
        key_masters->length > 1 ? "Keymasters list" : "Keymaster");
    /* snprintf(keymaster_window_subtitle_buffer, BUFFER_SIZE, "keymaster info about %s", space_name_buffer); */
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Keymaster section added : %i", space_info_current_number);
    space_info_title[space_info_current_number] = keymaster_window_buffer;
    /* space_info_subtitle[space_info_current_number] = keymaster_window_subtitle_buffer; */
    space_info_callback[space_info_current_number] = win_keymasters_show;

    ++space_info_current_number;
  }

  layer_mark_dirty(menu_layer_get_layer(s_menu_layer));
  menu_layer_reload_data(s_menu_layer);
}

void win_main_init(void) {
  strcpy(space_name_buffer, "Hackerspace");

  load_icons();

  // Section 0 : SpaceAPI basic info
  win_basic_init();
  // Section 1 : SpaceAPI info
  win_contact_init();
  win_sensor_menu_init();
  // Section 2 : About.
  win_about_init();

  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
}

void win_main_deinit(void) {
  win_basic_deinit();
  win_contact_deinit();
  win_sensor_menu_deinit();
  win_about_deinit();

  free_icons();

  window_destroy(window);
}
