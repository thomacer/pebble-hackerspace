#pragma once
#include <pebble.h>
#include "./libs/sensors/sensors_array.h"
#include "./libs/contacts.h"

#define BUFFER_SIZE 32

extern Tuple* t_space;

extern SensorsArray* sensors_array;
extern Contacts* contacts_section;

typedef enum {
  Closed = 0,
  Open = 1,
  Undefined = 2,
} SpaceState;
extern SpaceState open_state;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
