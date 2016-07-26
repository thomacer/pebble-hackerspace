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
    .icon = lightning_icon,
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

  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  self->title_layer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(self->title_layer, "Your space power consumption is : ");
  text_layer_set_text_alignment(self->title_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->title_layer));

  self->power_layer = text_layer_create(GRect(0, bounds.size.h / 6, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(self->power_layer, self->formated_value);
  text_layer_set_text_alignment(self->power_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->power_layer));

  // Name
  self->info_name_layer = text_layer_create(GRect(0, 2 * bounds.size.h / 6, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->info_name_layer, "Name : ");
  text_layer_set_text_alignment(self->info_name_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->info_name_layer));

  self->name_layer = text_layer_create(GRect(bounds.size.w / 2, 2 * bounds.size.h / 6, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->name_layer, self->name ? self->name : "Unknown");
  text_layer_set_text_alignment(self->name_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->name_layer));

  // Location
  self->info_location_layer = text_layer_create(GRect(0, 3 * bounds.size.h / 6, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->info_location_layer, "Location : ");
  text_layer_set_text_alignment(self->info_location_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->info_location_layer));

  self->location_layer = text_layer_create(GRect(bounds.size.w / 2, 3 * bounds.size.h / 6, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->location_layer, self->location ? self->location : "Unknown");
  text_layer_set_text_alignment(self->location_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->location_layer));
}

void PowerConsumption_destroy (void* s) {
  PowerConsumption* self = s;

  text_layer_destroy(self->title_layer);
  text_layer_destroy(self->power_layer);
  text_layer_destroy(self->info_name_layer);
  text_layer_destroy(self->name_layer);
  text_layer_destroy(self->info_location_layer);
  text_layer_destroy(self->location_layer);
}
