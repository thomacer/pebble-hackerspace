#include "./win_keymasters.h"

SecureArray* key_masters = NULL;

static Window* s_window = NULL;
static SimpleMenuLayer* s_menu_layer = NULL;

static SimpleMenuItem* key_item = NULL;
static SimpleMenuSection menu_section[1];

static void draw_keymaster (int index, void* context) {
  /* win_keymaster_show((void*) key_masters->array[index]); */
}

static void window_appear (Window* window) {
  key_item = malloc(sizeof(SimpleMenuItem) * key_masters->current);

  uint32_t count = 0;
  for (uint32_t i = 0; i < key_masters->current; ++i) {
    if (key_masters->array[i] == NULL) {
      continue;
    }

    KeyMaster* tmp = (KeyMaster*) key_masters->array[i];
    key_item[i] = tmp->menu(key_masters->array[i]);
    key_item[i].callback = draw_keymaster;
    ++count;
  }

  menu_section[0] = (SimpleMenuSection) {
    .title = PBL_IF_RECT_ELSE(
        count > 1 ? "Key masters" : "Key master",
        NULL),
    .num_items = count,
    .items = key_item,
  };

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  s_menu_layer = simple_menu_layer_create(bounds, window, menu_section, 1, NULL);

  layer_add_child(window_layer, simple_menu_layer_get_layer(s_menu_layer));
}

static void window_disappear (Window* window) {
  simple_menu_layer_destroy(s_menu_layer);
  free(key_item);
  key_item = NULL;
}

void win_keymasters_show(void) {
  window_stack_push(s_window, true);
}

void win_keymasters_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_keymasters_deinit(void) {
  if (key_masters) {
    key_masters->free(key_masters, lambda(void, (void* s) {
      KeyMaster* self = (KeyMaster*) s;
      self->free(self);
    }));
  }

  window_destroy(s_window);
}
