#pragma once

#include <pebble.h>
#include "./libs/sensors/sensors_array.h"
#include "./libs/contacts.h"
#include "./libs/basic/basic.h"

#define BUFFER_SIZE 32

extern Tuple* t_space;

extern SensorsArray* sensors_array;
extern Contacts* contacts_section;

extern SpaceState open_state;

extern BasicInfo* basic_info;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
