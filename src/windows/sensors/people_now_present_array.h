#pragma once
#include "people_now_present.h"

typedef struct {
    PeopleNowPresent** array;
    uint32_t length;
} PeopleNowPresentArray;

void free_people_now_present_array ();
void create_people_now_present_array (PeopleNowPresentArray**, uint32_t);
