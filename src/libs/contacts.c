#include "./contacts.h"

static void ContactItem_free (void* s) {
  ContactItem* self = s;

  free(self->type);
  free(self->value);
  free(self);
}

static SimpleMenuItem ContactItem_menu (void* s) {
  ContactItem* self = s;

  return (SimpleMenuItem) {
    .title = self->type,
    .subtitle = self->value,
  };
}

ContactItem* ContactItem_new (char* type, char* value) {
  ContactItem* r = malloc(sizeof(ContactItem));

  *r = (ContactItem) {
    .free = ContactItem_free,
    .menu = ContactItem_menu,
    .win_draw = NULL,
    .win_destroy = NULL,
    .type = NULL,
    .value = NULL,
  };

  if (type) {
    size_t length = strlen(type);
    r->type = malloc(sizeof(char) * length);
    memcpy(r->type, type, length);
  }

  if (value) {
    size_t length = strlen(value);
    r->value = malloc(sizeof(char) * length);
    memcpy(r->value, value, length);
  }

  return r;
}
