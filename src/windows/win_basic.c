#include "win_basic.h"

BasicInfo* basic_info = NULL;

static Window* window;

static TextLayer* last_change_text_layer = NULL;
static char last_change_buffer[64];

static TextLayer* state_text_layer = NULL;
static char state_buffer[32];

static void window_appear (Window* window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  if (basic_info == NULL)  {
    return;
  }

  state_text_layer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h / 2));
  if (basic_info->state == Closed) {
    snprintf(state_buffer, 32, "Your space is closed.");
  } else if (basic_info->state == Open) {
    snprintf(state_buffer, 32, "Your space is open.");
  } else {
    snprintf(state_buffer, 32, "Your space state is unknown.");
  }

  text_layer_set_text(state_text_layer, state_buffer);
  text_layer_set_text_alignment(state_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(state_text_layer));

  if (basic_info->lastchange) {
    last_change_text_layer = text_layer_create(GRect(0, bounds.size.h / 2, bounds.size.w, bounds.size.h / 2));
    snprintf(last_change_buffer, 64, "The space state last changed : %ld", basic_info->lastchange);
    text_layer_set_text(last_change_text_layer, last_change_buffer);
    text_layer_set_text_alignment(last_change_text_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(last_change_text_layer));
  }
}

static void window_disappear (Window* window) {
  if (state_text_layer) {
    text_layer_destroy(state_text_layer);
    state_text_layer = NULL;
  }

  if (last_change_text_layer) {
    text_layer_destroy(last_change_text_layer);
    last_change_text_layer = NULL;
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
