#pragma once

#include <pebble.h>
#include "./libs/secure_array.h"
#include "./libs/contacts.h"
#include "./libs/basic/basic.h"

#define BUFFER_SIZE 32

/* Defined in the win_keymasters file. */
extern SecureArray* key_masters;

/* Defined in the win_sensor_menu file. */
extern SecureArray* sensors_array;

/* Defined in the win_contact file. */
extern Contacts* contacts_section;

/* Defined in the win_basic file. */
extern BasicInfo* basic_info;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
