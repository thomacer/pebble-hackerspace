#include "./people_now_present.h"

PeopleNowPresent* PeopleNowPresent_new (uint32_t value,
    char* location,
    char* name,
    char* description)
{
  PeopleNowPresent* p = malloc(sizeof(PeopleNowPresent));

  *p = (PeopleNowPresent) {
    .type = people_now_present,
    .value = value,
    .location = NULL,
    .name = NULL,
    .names = malloc(value * sizeof(char*)),
    .description = NULL,
    .PeopleNowPresent_free = PeopleNowPresent_free,
    .PeopleNowPresent_draw = PeopleNowPresent_draw,
    .PeopleNowPresent_destroy = PeopleNowPresent_destroy,
    .menu_sections = NULL,
    .menu_items = NULL,
    .menu_layer = NULL,
  };

  for (uint32_t i = 0; i < value; ++i) {
    p->names[i] = NULL;
  }

  if (location) {
    size_t length = strlen(location);
    p->location = malloc(sizeof(char) * length);
    memcpy(p->location, location, length);
  }

  if (name) {
    size_t length = strlen(name);
    p->name = malloc(sizeof(char) * length);
    memcpy(p->name, name, length);
  }

  if (description) {
    size_t length = strlen(description);
    p->description = malloc(sizeof(char) * length);
    memcpy(p->description, description, length);
  }

  return p;
}

void PeopleNowPresent_free(void* s) {
  PeopleNowPresent* self = (PeopleNowPresent*) s;
  for (uint32_t i = 0; i < self->value; ++i) {
    if (self->names[i]) {
      free(self->names[i]);
    }
  }
  free(self->names);

  if (self->location) {
    free(self->location);
  }

  if (self->name) {
    free(self->name);
  }

  if (self->description) {
    free(self->description);
  }

  free(self);
}

void PeopleNowPresent_add_person (PeopleNowPresent* self, uint32_t index, char* name) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Adding name : %s", name);
  size_t length = strlen(name);
  self->names[index] = malloc(length * sizeof(char));
  memcpy(self->names[index], name, length);
}

void PeopleNowPresent_draw (Window* window, void* s) {
  PeopleNowPresent* self = (PeopleNowPresent*) s;
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Drawing people now present");

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);

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

void PeopleNowPresent_destroy (void* s) {
  PeopleNowPresent* self = (PeopleNowPresent*) s;
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
