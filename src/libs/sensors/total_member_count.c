#include "./total_member_count.h"

TotalMemberCount* TotalMemberCount_new (uint32_t value,
    char* location,
    char* name,
    char* description)
{
  TotalMemberCount* d = malloc(sizeof(TotalMemberCount));

  *d = (TotalMemberCount) {
    .type = door_locked,
    .value = value,
    .location = NULL,
    .name = NULL,
    .description = NULL,
    .TotalMemberCount_free = TotalMemberCount_free,
    .TotalMemberCount_menu = TotalMemberCount_menu,
    .TotalMemberCount_draw = TotalMemberCount_draw,
    .TotalMemberCount_destroy = TotalMemberCount_destroy,
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

void TotalMemberCount_free(void* s) {
  TotalMemberCount* self = (TotalMemberCount*) s;

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

SimpleMenuItem TotalMemberCount_menu (void* s) {
  TotalMemberCount* self = (TotalMemberCount*) s;
  SimpleMenuItem result = {
    .title = "Total member count",
    .subtitle = self->formated_value,
    .icon = get_icon(RESOURCE_ID_PERSON_ICON),
    .callback = NULL,
  };

  if (self->name) {
    result.title = self->name;
  } else if (self->location) {
    result.title = self->location;
  }

  return result;
}

void TotalMemberCount_draw (Window* window, void* s) { }

void TotalMemberCount_destroy (void* s) { }
