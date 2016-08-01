#include "./win_objects_menu.h"

static SecureArray* objects_array = NULL;
static char* header = NULL;

static Window* s_window = NULL;
static SimpleMenuLayer* s_menu_layer = NULL;

static SimpleMenuItem* object_items = NULL;
static SimpleMenuSection menu_section[1];

static void window_appear (Window* window) {
  MEM_STATE("appearing");
  object_items = malloc(sizeof(SimpleMenuItem) * objects_array->current);

  uint32_t count = 0;
  for (uint32_t i = 0; i < objects_array->current; ++i) {
    if (objects_array->array[i] == NULL) {
      continue;
    }

    PebbleObject* tmp = objects_array->array[i];
    object_items[i] = tmp->menu(tmp);
    object_items[i].callback = lambda(void, (int index, void* context) {
      win_object_show((void*) objects_array->array[index]);
    });

    ++count;
  }

  menu_section[0] = (SimpleMenuSection) {
    .title = PBL_IF_RECT_ELSE(
        header,
        NULL),
    .num_items = count,
    .items = object_items,
  };

  if (!s_menu_layer) {
    // If it's still on the window stack this part won't be executed.
    DEBUG ("Win not on the win stack allocating s_menu_layer");
    Layer* window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_frame(window_layer);

    s_menu_layer = simple_menu_layer_create(bounds, window, menu_section, 1, NULL);

    layer_add_child(window_layer, simple_menu_layer_get_layer(s_menu_layer));
  }
  MEM_STATE("appeared");
}

static void window_disappear (Window* window) {
  MEM_STATE("disappearing");

  if (!window_stack_contains_window(window)) {
    /* Not freeing the simple menu layer when is disappearing
     * and still on the stack, it can cause app fault sometime.
     */
    simple_menu_layer_destroy(s_menu_layer);
    s_menu_layer = NULL;
  }

  free(object_items);
  object_items = NULL;

  MEM_STATE("disappeared");
}

void win_objects_menu_show(SecureArray* array, char* h) {
  objects_array = array;
  header = h;
  window_stack_push(s_window, true);
}

void win_objects_menu_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .appear = window_appear,
    .disappear = window_disappear,
  });
}

void win_objects_menu_deinit(void) {
  /* if (objects_array) { */
  /*   objects_array->free(objects_array, lambda(void, (void* s) { */
  /*     KeyMaster* self = (KeyMaster*) s; */
  /*     self->free(self); */
  /*   })); */
  /* } */

  window_destroy(s_window);
}
