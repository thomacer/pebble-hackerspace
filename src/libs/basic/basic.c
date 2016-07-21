#include "basic.h"

BasicInfo* BasicInfo_new (char* name,
    char* url,
    uint32_t lastchange,
    SpaceState state)
{
  BasicInfo* result = malloc(sizeof(BasicInfo));

  *result = (BasicInfo) {
    .name = NULL,
    .url = NULL,
    .lastchange = lastchange,
    .state = state,
    .free = BasicInfo_free,
  };

  if (name) {
    size_t length = strlen(name);
    result->name = (char*) malloc(length * sizeof(char));
    memcpy(result->name, name, length);
  }

  if (url) {
    size_t length = strlen(url);
    result->url = (char*) malloc(length * sizeof(char));
    memcpy(result->url, url, length);
  }

  return result;
}

void BasicInfo_free (BasicInfo* self) {
  if (self->name) {
    free(self->name);
  }

  if (self->url) {
    free(self->url);
  }

  free(self);
}
