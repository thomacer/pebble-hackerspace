#include "./contacts.h"

Contacts* Contacts_new (uint32_t number) {
  Contacts* c = malloc(sizeof(Contacts));
  *c = (Contacts) {
    .number = number,
    .current = 0,
    .array = malloc(sizeof(ContactItem*) * number),
  };

  return c;
}

void Contacts_add (Contacts* self, char* type, char* value) {
  if (self->current < self->number) {
    size_t type_length = strlen(type);
    size_t value_length = strlen(value);

    self->array[self->current] = malloc(sizeof(ContactItem));
    *(self->array[self->current]) = (ContactItem) {
      .type = malloc(sizeof(char) * type_length),
      .value = malloc(sizeof(char) * value_length),
    };

    memcpy(self->array[self->current]->type, type, type_length);
    memcpy(self->array[self->current]->value, value, value_length);

    ++(self->current);
  }
}

void Contacts_free (Contacts* self) {
  for (uint32_t i = 0; i < self->number; ++i) {
    if (self->array[i]) {
      free(self->array[i]->type);
      free(self->array[i]->value);
      free(self->array[i]);
    }
  }
  free(self->array);
  free(self);
}
