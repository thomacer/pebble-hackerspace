#include "people_now_present_array.h"

void free_people_now_present_array (PeopleNowPresentArray** array) {
    for (uint32_t i = 0; i < (*array)->length; ++i) {
        if ((*array)->array[i]) {
            PeopleNowPresent_free ((*array)->array[i]);
        }
    }
    free(*array);
}

void create_people_now_present_array (PeopleNowPresentArray** array, uint32_t length) {
    *array = (PeopleNowPresentArray*) malloc(sizeof(PeopleNowPresentArray));
    (*array)->array = (PeopleNowPresent**) malloc(sizeof(PeopleNowPresent*) * length);
    (*array)->length = length;
}
