#pragma once

#include <pebble.h>

typedef enum {
  Closed = 0,
  Open = 1,
  Undefined = 2,
} SpaceState;

typedef struct BasicInfo {
  char* name;
  char* url;
  uint32_t lastchange;
  SpaceState state;
  void (*free)(struct BasicInfo*);
} BasicInfo;

BasicInfo* BasicInfo_new (char*, char*, uint32_t, SpaceState);
void BasicInfo_free (BasicInfo*);
