#include "win_about.h"

static Window* window;

static GBitmap* s_logo_bitmap;
static Layer* image_layer;

static TextLayer* text_layer;
static char* about_text = "Built at the UrLab hackerspace in Brussels.";

static void image_layer_update (Layer* layer, GContext* ctx) {
  graphics_draw_bitmap_in_rect(ctx, s_logo_bitmap, gbitmap_get_bounds(s_logo_bitmap));
}

static void window_load(Window *window) {
  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  s_logo_bitmap = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);
  GRect image_bound = gbitmap_get_bounds(s_logo_bitmap);
  image_layer = layer_create(image_bound);
  layer_add_child(window_layer, image_layer);
  layer_set_update_proc(image_layer, image_layer_update);

  text_layer = text_layer_create(GRect(0, image_bound.size.h, bounds.size.w , bounds.size.h / 2));
  text_layer_set_text (text_layer, about_text);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  layer_destroy(image_layer);
  text_layer_destroy(text_layer);
}

void win_about_show(void) {
  window_stack_push(window, true);
}

void win_about_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
}

void win_about_deinit(void) {
  window_destroy(window);
}
