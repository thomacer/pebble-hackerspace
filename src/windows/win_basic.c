#include "win_basic.h"

BasicInfo* basic_info = NULL;

static Window* window;

static TextLayer* last_change_info_text_layer = NULL;
static TextLayer* last_change_text_layer = NULL;
static char last_change_buffer[64];

static TextLayer* state_text_layer = NULL;

static void window_appear (Window* window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  if (basic_info == NULL)  {
    return;
  }

  int16_t y_offset = 0;

  state_text_layer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h / 4));
  if (basic_info->state == Closed) {
    text_layer_set_text(state_text_layer, "Your space is closed.\n\n");
  } else if (basic_info->state == Open) {
    text_layer_set_text(state_text_layer, "Your space is open.\n\n");
  } else {
    text_layer_set_text(state_text_layer, "Your space state is unknown.\n\n");
  }

  text_layer_set_text_alignment(state_text_layer, GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(state_text_layer).h;
  layer_add_child(window_layer, text_layer_get_layer(state_text_layer));

  if (basic_info->lastchange) {
    last_change_info_text_layer = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 4));
    text_layer_set_text(last_change_info_text_layer, "The space state changed on : ");
    y_offset += text_layer_get_content_size(last_change_info_text_layer).h;
    layer_add_child(window_layer, text_layer_get_layer(last_change_info_text_layer));

    last_change_text_layer = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 4));
    strftime(last_change_buffer, 64, "%m/%d %H:%M:%S", localtime((time_t*) &(basic_info->lastchange)));
    text_layer_set_text(last_change_text_layer, last_change_buffer);
    text_layer_set_text_alignment(last_change_text_layer, GTextAlignmentCenter);
    y_offset += text_layer_get_content_size(last_change_text_layer).h;
    layer_add_child(window_layer, text_layer_get_layer(last_change_text_layer));
  }
}

static void window_disappear (Window* window) {
  if (state_text_layer) {
    text_layer_destroy(state_text_layer);
    state_text_layer = NULL;
  }

  if (last_change_info_text_layer && last_change_text_layer) {
    text_layer_destroy(last_change_info_text_layer );
    last_change_info_text_layer = NULL;
    text_layer_destroy(state_text_layer);
    state_text_layer = NULL;
  }
}

void win_basic_show(void) {
  window_stack_push(window, true);
}

void win_basic_init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_basic_deinit(void) {
  window_destroy(window);
}
