#include "./barometer.h"

Barometer* Barometer_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  Barometer* t = malloc(sizeof(Barometer));

  *t = (Barometer) {
    .type = barometer,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .Barometer_free = Barometer_free,
    .Barometer_menu = Barometer_menu,
    .Barometer_draw = Barometer_draw,
    .Barometer_destroy = Barometer_destroy,
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

void Barometer_free(void* s) {
  Barometer* self = (Barometer*) s;
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

SimpleMenuItem Barometer_menu (void* s) {
  Barometer* t = (Barometer*) s;
  SimpleMenuItem result = {
    .title = "Barometer",
    .subtitle = t->formated_value,
    .icon = NULL,
    .callback = NULL,
  };

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  }

  return result;
}

void Barometer_draw (Window* window, void* s) {
  Barometer* self = (Barometer*) s;

  self->layers = draw_basic(window,
    "Barometer value : ",
    self->formated_value,
    self->name,
    self->location,
    self->description);

}

void Barometer_destroy (void* s) {
  free_basic(((Barometer*) s)->layers);
}
