#include "common.h"

#define BASIC_TEXT_LAYER_NUMBER 8
TextLayer** draw_basic (Window* window,
    char* title,
    char* value,
    char* name,
    char* location,
    char* description)
{
  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  TextLayer** layers = malloc(sizeof(TextLayer*) * BASIC_TEXT_LAYER_NUMBER);

  int16_t y_offset = 0;

  layers[0] = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(layers[0], title);
  text_layer_set_text_alignment(layers[0], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[0]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[0]));

  layers[1] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(layers[1], value);
  text_layer_set_text_alignment(layers[1], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[1]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[1]));

  // Name
  layers[2] = text_layer_create(GRect(0, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(layers[2], "Name : ");
  text_layer_set_text_alignment(layers[2], GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(layers[2]));

  layers[3] = text_layer_create(GRect(bounds.size.w / 2, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(layers[3], name ? name : "Unknown");
  text_layer_set_text_alignment(layers[3], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[3]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[3]));

  // Location
  layers[4] = text_layer_create(GRect(0, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(layers[4], "Location : ");
  text_layer_set_text_alignment(layers[4], GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(layers[4]));

  layers[5] = text_layer_create(GRect(bounds.size.w / 2, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(layers[5], location ? location : "Unknown");
  text_layer_set_text_alignment(layers[5], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[5]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[5]));

  // Description
  layers[6] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(layers[6], "Description");
  text_layer_set_text_alignment(layers[6], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[6]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[6]));

  layers[7] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 4));
  text_layer_set_text(layers[7], description ? description : "Unknown");
  text_layer_set_text_alignment(layers[7], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(layers[7]).h;
  layer_add_child(window_layer, text_layer_get_layer(layers[7]));

#ifdef PBL_ROUND
  uint8_t inset = 4;
  for (uint32_t i = 0; i < BASIC_TEXT_LAYER_NUMBER; ++i) {
    text_layer_enable_screen_text_flow_and_paging(layers[i], inset);
  }
#endif

  return layers;
}

void free_basic (TextLayer** layers) {
  for (uint32_t i = 0; i < BASIC_TEXT_LAYER_NUMBER; ++i) {
    text_layer_destroy(layers[i]);
  }
  free(layers);
}
