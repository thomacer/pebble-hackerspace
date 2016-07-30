#include "./radiation.h"

Radiation* Radiation_new (uint32_t type,
    uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description,
    uint32_t dead_time,
    uint32_t conversion_factor)
{
  Radiation* t = malloc(sizeof(Radiation));

  *t = (Radiation) {
    .type = radiation,
    .subtype = type,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .dead_time = dead_time,
    .conversion_factor = conversion_factor,
    .Radiation_free = Radiation_free,
    .Radiation_menu = Radiation_menu,
    .Radiation_draw = Radiation_draw,
    .Radiation_destroy = Radiation_destroy,
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

void Radiation_free(void* s) {
  Radiation* self = (Radiation*) s;
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

SimpleMenuItem Radiation_menu (void* s) {
  Radiation* self = (Radiation*) s;
  SimpleMenuItem result = {
    .title = "Radiation",
    .subtitle = self->formated_value,
    .icon = NULL,
    .callback = NULL,
  };

  switch (self->subtype) {
    case KEY_SENSOR_RADIATION_ALPHA:
      result.icon = get_icon(RESOURCE_ID_ALPHA_ICON);
      break;
    case KEY_SENSOR_RADIATION_BETA:
      result.icon = get_icon(RESOURCE_ID_BETA_ICON);
      break;
    case KEY_SENSOR_RADIATION_GAMMA:
      result.icon = get_icon(RESOURCE_ID_GAMMA_ICON);
      break;
    case KEY_SENSOR_RADIATION_BETAGAMMA:
      result.icon = get_icon(RESOURCE_ID_BETAGAMMA_ICON);
      break;
    default:
      break;
  }

  if (self->name) {
    result.title = self->name;
  } else if (self->location) {
    result.title = self->location;
  }

  return result;
}

void Radiation_draw (Window* window, void* s) { }

void Radiation_destroy (void* s) { }
