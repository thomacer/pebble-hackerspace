#include "./beverage_supply.h"

BeverageSupply* BeverageSupply_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  BeverageSupply* t = malloc(sizeof(BeverageSupply));

  *t = (BeverageSupply) {
    .type = humidity,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .BeverageSupply_free = BeverageSupply_free,
    .BeverageSupply_menu = BeverageSupply_menu,
    .BeverageSupply_draw = BeverageSupply_draw,
    .BeverageSupply_destroy = BeverageSupply_destroy,
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

void BeverageSupply_free(void* s) {
  BeverageSupply* self = (BeverageSupply*) s;
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

SimpleMenuItem BeverageSupply_menu (void* s) {
  BeverageSupply* t = (BeverageSupply*) s;
  SimpleMenuItem result = {
    .title = "Beverage Supply",
    .subtitle = t->formated_value,
    .icon = drink_icon,
    .callback = NULL,
  };

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  }

  return result;
}

void BeverageSupply_draw (Window* window, void* s) { }

void BeverageSupply_destroy (void* s) { }
