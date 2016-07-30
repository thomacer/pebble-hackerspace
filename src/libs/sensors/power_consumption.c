#include "./power_consumption.h"

PowerConsumption* PowerConsumption_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  PowerConsumption* t = malloc(sizeof(PowerConsumption));

  *t = (PowerConsumption) {
    .type = power_consumption,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .PowerConsumption_free = PowerConsumption_free,
    .PowerConsumption_menu = PowerConsumption_menu,
    .PowerConsumption_draw = PowerConsumption_draw,
    .PowerConsumption_destroy = PowerConsumption_destroy,
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

void PowerConsumption_free(void* s) {
  PowerConsumption* self = (PowerConsumption*) s;
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

SimpleMenuItem PowerConsumption_menu (void* s) {
  PowerConsumption* t = (PowerConsumption*) s;
  SimpleMenuItem result = {
    .title = "Power Consumption",
    .subtitle = t->formated_value,
    .icon = get_icon(RESOURCE_ID_LIGHTNING_ICON),
    .callback = NULL,
  };

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  }

  return result;
}

void PowerConsumption_draw (Window* window, void* s) {
  PowerConsumption* self = s;

  self->layers = draw_basic (window,
    "Your space power consumption is : ",
    self->formated_value,
    self->name,
    self->location,
    self->description);
}

void PowerConsumption_destroy (void* s) {
  PowerConsumption* self = s;

  free_basic (self->layers);
}
