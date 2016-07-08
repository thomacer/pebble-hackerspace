#pragma once
#include <pebble.h>
#include "./windows/sensors/people_now_present_array.h"
#include "./libs/contacts.h"

#define BUFFER_SIZE 32

extern Tuple* t_space;

extern PeopleNowPresentArray* sensor_people_now_present;
extern Contacts* contacts_section;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
