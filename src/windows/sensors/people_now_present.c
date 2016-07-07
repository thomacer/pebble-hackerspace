#include "./people_now_present.h"

PeopleNowPresent* PeopleNowPresent_new (uint32_t value) {
  PeopleNowPresent* p = malloc(sizeof(PeopleNowPresent));

  *p = (PeopleNowPresent) {
    .type = people_now_present,
    .value = value,
    .location = NULL,
    .name = NULL,
    .names = malloc(value * sizeof(char*)),
    .description = NULL,
    .menu_sections = NULL,
    .menu_items = NULL,
    .menu_layer = NULL,
  };

  for (uint32_t i = 0; i < value; ++i) {
    p->names[i] = NULL;
  }

  return p;
}

void PeopleNowPresent_free(PeopleNowPresent* self) {
  for (uint32_t i = 0; i < self->value; ++i) {
    if (self->names[i]) {
      free(self->names[i]);
    }
  }
  free(self->names);
  free(self);
}

void PeopleNowPresent_set_location (PeopleNowPresent* self, uint32_t index, char* location) {

}

void PeopleNowPresent_add_person (PeopleNowPresent* self, uint32_t index, char* name) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Adding name : %s", name);
  size_t length = strlen(name);
  self->names[index] = malloc(length * sizeof(char));
  memcpy(self->names[index], name, length);
}

/* @desc : Format the names to be represented in a scroll_layer.
 *
 * @param {PeopleNowPresent*} : Struct to add the result to.
 */
/* static void format_names_to_text (PeopleNowPresent* self) { */
/*   // Finding the size for the buffer. */
/*   size_t length = 0; */
/*   for (uint32_t i = 0; i < self->value; ++i) { */
/*     if (self->names[i]) { */
/*       length += strlen(self->names[i]); */
/*     } */
/*   } */
/*   self->text_displayed = malloc(length * sizeof(char)); */

/*   for (uint32_t i = 0; i < self->value; ++i) { */
/*     if (self->names[i]) { */
/*       APP_LOG(APP_LOG_LEVEL_DEBUG, "Concat name : %s", self->names[i]); */
/*       strcat(self->text_displayed, self->names[i]); */
/*       strcat(self->text_displayed, "\n"); */
/*     } */
/*   } */
/*   APP_LOG(APP_LOG_LEVEL_DEBUG, "Concatened names : %s", self->text_displayed); */
/* } */

void PeopleNowPresent_draw (Window* window, PeopleNowPresent* self) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Drawing people now present");

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

  /* self->scroll_layer = scroll_layer_create(bounds); */
  /* scroll_layer_set_click_config_onto_window(self->scroll_layer, window); */

  /* #ifdef PBL_ROUND */
  /* scroll_layer_set_paging(self->scroll_layer, true); */
  /* #endif */

  /* GRect max_text_bounds = GRect(0, 0, bounds.size.w, 2000); */
  /* self->text_layer = text_layer_create(max_text_bounds); */
  /* format_names_to_text (self); */
  /* text_layer_set_text(self->text_layer, self->text_displayed); */

  /* scroll_layer_add_child(self->scroll_layer, text_layer_get_layer(self->text_layer)); */
  /* layer_add_child(window_layer, scroll_layer_get_layer(self->scroll_layer)); */
  self->menu_sections = malloc(sizeof(SimpleMenuSection) * 1);
  self->menu_items = malloc(sizeof(SimpleMenuItem) * self->value);

  for (uint32_t i = 0; i < self->value; ++i) {
    self->menu_items[i] = (SimpleMenuItem) {
      .title = self->names[i],
    };
  }

  self->menu_sections[0] = (SimpleMenuSection) {
    .title = "People now present",
    .num_items = self->value,
    .items = self->menu_items,
  };

  self->menu_layer = simple_menu_layer_create(bounds, window, self->menu_sections, 1, NULL);
  layer_add_child(window_layer, simple_menu_layer_get_layer(self->menu_layer));
}

void PeopleNowPresent_destroy (Window* window, PeopleNowPresent* self) {
  if (self->menu_sections != NULL) {
    free(self->menu_sections);
  }
  if (self->menu_items != NULL) {
    free(self->menu_items);
  }
  if (self->menu_layer != NULL) {
    simple_menu_layer_destroy(self->menu_layer);
  }
}
