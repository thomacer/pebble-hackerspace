#include "./temperature.h"

Temperature* Temperature_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  Temperature* t = malloc(sizeof(Temperature));

  *t = (Temperature) {
    .type = temperature,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .Temperature_free = Temperature_free,
    .Temperature_menu = Temperature_menu,
    .Temperature_draw = Temperature_draw,
    .Temperature_destroy = Temperature_destroy,
    .menu_sections = NULL,
    .menu_items = NULL,
    .menu_layer = NULL,
  };

  if (unit) {
    size_t length = strlen(unit);
    t->unit = malloc(sizeof(char) * length);
    memcpy(t->unit, unit, length);

    snprintf(t->formated_value, 32, "%ld %s", t->value, t->unit);
  } else {
    snprintf(t->formated_value, 32, "%ld", t->value);
  }

  if (location) {
    size_t length = strlen(location);
    t->location = malloc(sizeof(char) * length);
    memcpy(t->location, location, length);
  }

  if (name) {
    size_t length = strlen(name);
    t->name = malloc(sizeof(char) * length);
    memcpy(t->name, name, length);
  }

  if (description) {
    size_t length = strlen(description);
    t->description = malloc(sizeof(char) * length);
    memcpy(t->description, description, length);
  }

  return t;
}

void Temperature_free(void* s) {
  Temperature* self = (Temperature*) s;
  if (self->unit) {
    free(self->unit);
  }

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

SimpleMenuItem Temperature_menu (void* s) {
  Temperature* t = (Temperature*) s;
  SimpleMenuItem result = {};

  /* TODO result.icon = */

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  } else {
    result.title = "Temperature";
  }

  result.subtitle = t->formated_value;

  return result;
}

void Temperature_draw (Window* window, void* s) { }

void Temperature_destroy (void* s) { }
