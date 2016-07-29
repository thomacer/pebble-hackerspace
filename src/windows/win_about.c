#include "win_about.h"

static Window* window;

static GBitmap* urlab_logo;

static ScrollLayer* scroll_layer;

static Layer* image_layer;

static TextLayer* text_layer;
static char* about_text = "Built at the UrLab hackerspace in Brussels.";

static void image_layer_update (Layer* layer, GContext* ctx) {
  graphics_draw_bitmap_in_rect(ctx, urlab_logo, gbitmap_get_bounds(urlab_logo));
}

static void window_appear(Window* window) {
  urlab_logo = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  scroll_layer = scroll_layer_create(bounds);
  scroll_layer_set_click_config_onto_window(scroll_layer, window);

#ifdef PBL_ROUND
  scroll_layer_set_paging(scroll_layer, true);
#endif

  GRect image_bound = gbitmap_get_bounds(urlab_logo);
  image_layer = layer_create(image_bound);
  layer_add_child(window_layer, image_layer);
  layer_set_update_proc(image_layer, image_layer_update);

  scroll_layer_add_child(scroll_layer, image_layer);

  text_layer = text_layer_create(GRect(0, image_bound.size.h, bounds.size.w , bounds.size.h / 2));
  text_layer_set_text (text_layer, about_text);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
#ifdef PBL_ROUND
  uint8_t inset = 4;
  text_layer_enable_screen_text_flow_and_paging(text_layer, inset);
#endif
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  scroll_layer_add_child(scroll_layer, text_layer_get_layer(text_layer));

  layer_add_child(window_layer, scroll_layer_get_layer(scroll_layer));

  scroll_layer_set_content_size(scroll_layer, GSize(bounds.size.w, image_bound.size.h + bounds.size.h / 2));
}

static void window_disappear(Window *window) {
  gbitmap_destroy(urlab_logo);
  layer_destroy(image_layer);
  text_layer_destroy(text_layer);
  scroll_layer_destroy(scroll_layer);
}

void win_about_show(void) {
  window_stack_push(window, true);
}

void win_about_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_about_deinit(void) {
  window_destroy(window);
}
