#include "./humidity.h"

Humidity* Humidity_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  Humidity* t = malloc(sizeof(Humidity));

  *t = (Humidity) {
    .type = humidity,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .Humidity_free = Humidity_free,
    .Humidity_menu = Humidity_menu,
    .Humidity_draw = Humidity_draw,
    .Humidity_destroy = Humidity_destroy,
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

void Humidity_free(void* s) {
  Humidity* self = (Humidity*) s;
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

SimpleMenuItem Humidity_menu (void* s) {
  Humidity* t = (Humidity*) s;
  SimpleMenuItem result = {
    .title = "Humidity",
    .subtitle = t->formated_value,
    .icon = get_icon(RESOURCE_ID_HUMIDITY_ICON),
    .callback = NULL,
  };

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  }

  return result;
}

void Humidity_draw (Window* window, void* s) {
  Humidity* self = (Humidity*) s;

  self->layers = draw_basic(window,
    "humidity in the space : ",
    self->formated_value,
    self->name,
    self->location,
    self->description);
}

void Humidity_destroy (void* s) {
  free_basic(((Humidity*) s)->layers);
}
