#include "./account_balance.h"

AccountBalance* AccountBalance_new (uint32_t value,
    char* unit,
    char* location,
    char* name,
    char* description)
{
  AccountBalance* t = malloc(sizeof(AccountBalance));

  *t = (AccountBalance) {
    .type = humidity,
    .value = value,
    .unit = NULL,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .AccountBalance_free = AccountBalance_free,
    .AccountBalance_menu = AccountBalance_menu,
    .AccountBalance_draw = AccountBalance_draw,
    .AccountBalance_destroy = AccountBalance_destroy,
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

void AccountBalance_free(void* s) {
  AccountBalance* self = (AccountBalance*) s;
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

SimpleMenuItem AccountBalance_menu (void* s) {
  AccountBalance* t = (AccountBalance*) s;
  SimpleMenuItem result = {
    .title = "Account Balance",
    .subtitle = t->formated_value,
    .icon = get_icon(RESOURCE_ID_MONEY_ICON),
    .callback = NULL,
  };

  if (t->name) {
    result.title = t->name;
  } else if (t->location) {
    result.title = t->location;
  }

  return result;
}

void AccountBalance_draw (Window* window, void* s) {
  AccountBalance* self = (AccountBalance*) s;

  self->layers = draw_basic(window,
    "Your space account balance : ",
    self->formated_value,
    self->name,
    self->location,
    self->description);
}

void AccountBalance_destroy (void* s) {
  free_basic(((AccountBalance*) s)->layers);
}
