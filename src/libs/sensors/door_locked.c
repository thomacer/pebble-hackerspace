#include "./door_locked.h"

DoorLocked* DoorLocked_new (uint32_t value,
    char* location,
    char* name,
    char* description)
{
  DoorLocked* d = malloc(sizeof(DoorLocked));

  *d = (DoorLocked) {
    .type = door_locked,
    .value = value,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .DoorLocked_free = DoorLocked_free,
    .DoorLocked_menu = DoorLocked_menu,
    .DoorLocked_draw = DoorLocked_draw,
    .DoorLocked_destroy = DoorLocked_destroy,
  };

  if (location) {
    size_t length = strlen(location);
    d->location = malloc(sizeof(char) * length);
    memcpy(d->location, location, length);
  }

  if (name) {
    size_t length = strlen(name);
    d->name = malloc(sizeof(char) * length);
    memcpy(d->name, name, length);
  }

  if (description) {
    size_t length = strlen(description);
    d->description = malloc(sizeof(char) * length);
    memcpy(d->description, description, length);
  }

  return d;
}

void DoorLocked_free(void* s) {
  DoorLocked* self = (DoorLocked*) s;

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

SimpleMenuItem DoorLocked_menu (void* s) {
  DoorLocked* self = (DoorLocked*) s;
  SimpleMenuItem result = {};

  /* TODO result.icon = */

  if (self->name) {
    result.title = self->name;

  } else if (self->location) {
    result.title = self->location;
  } else {
    result.title = "Door locked";
  }

  result.subtitle = self->formated_value;

  return result;
}

void DoorLocked_draw (Window* window, void* s) { }

void DoorLocked_destroy (void* s) { }
