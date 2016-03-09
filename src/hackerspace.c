#include <pebble.h>

#define KEY_SPACE 0
#define KEY_EMAIL 1
#define KEY_IRC 2
#define KEY_FACEBOOK 3
#define KEY_TWITTER 4
#define KEY_OPEN_STATE 5
#define KEY_NUMBER_OF_PEOPLE_PRESENT 6
#define KEY_LIST_OF_PEOPLE_PRESENT 7

static Window *window;
static TextLayer *space_layer;
static TextLayer *number_of_people_layer;

static BitmapLayer *s_logo_layer;
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
  static char space_buffer[32];
  static char number_of_people_buffer[8];

  Tuple *space_tuple = dict_find(iterator, KEY_SPACE);
  Tuple *number_tuple = dict_find(iterator, KEY_NUMBER_OF_PEOPLE_PRESENT);
  /* Tuple *person_present_tuple = dict_find(iterator, KEY_LIST_OF_PEOPLE_PRESENT); */

  snprintf(space_buffer, sizeof(space_buffer), "%d", (char*) space_tuple->value->cstring);
  snprintf(number_of_people_buffer, sizeof(number_of_people_buffer), "%d", (int) number_tuple->value->int32);

  text_layer_set_text(space_layer, space_buffer);
  text_layer_set_text(number_of_people_layer, number_of_people_buffer);
}

/* ------------------------------------------------------------------------
 *                      Partie création des layers.
 * ------------------------------------------------------------------------
 */
static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create GBitmap
  s_logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);
  // Create BitmapLayer to display the GBitmap
  s_logo_layer = bitmap_layer_create(bounds);

  // Set the bitmap onto the layer and add to the window
  bitmap_layer_set_bitmap(s_logo_layer, s_logo_bitmap);
  layer_add_child(window_layer, bitmap_layer_get_layer(s_logo_layer));


  space_layer = text_layer_create(GRect(0, 42, bounds.size.w, 20));
  text_layer_set_text(space_layer, "Loading ...");
  text_layer_set_text_alignment(space_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(space_layer));

  number_of_people_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(number_of_people_layer, "Loading ...");
  text_layer_set_text_alignment(number_of_people_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(number_of_people_layer));
}

static void window_unload(Window *window) {
  // Destroy GBitmap
  gbitmap_destroy(s_logo_bitmap);

  // Destroy BitmapLayer
  bitmap_layer_destroy(s_logo_layer);

  text_layer_destroy(text_layer);
  text_layer_destroy(number_of_people_layer);
}

static void init(void) {
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
