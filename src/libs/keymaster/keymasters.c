#include "keymasters.h"

static void KeyMasters_free (KeyMasters* self) {
  for (uint32_t i = 0; i < self->length; ++i) {
    if (self->array[i]) {
      self->array[i]->free(self->array[i]);
    }
  }

  free(self->array);
  free(self);
}

KeyMasters* KeyMasters_new (uint32_t size) {
  KeyMasters* k = malloc(sizeof(KeyMasters));

  *k = (KeyMasters) {
    .length = size,
    .array = (KeyMaster**) malloc(sizeof(KeyMaster*) * size),
    .free = KeyMasters_free,
  };

  return k;
}
