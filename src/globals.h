#pragma once

#include <pebble.h>
#include "./libs/sensors/sensors_array.h"
#include "./libs/contacts.h"
#include "./libs/basic/basic.h"

#define BUFFER_SIZE 32

/* Defined in the win_sensor_menu file.  */
extern SensorsArray* sensors_array;

/* Defined in the win_contact file.  */
extern Contacts* contacts_section;

/* Defined in the win_basic file.  */
extern BasicInfo* basic_info;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
