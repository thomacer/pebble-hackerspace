#include "people_now_present.h"

PeopleNowPresent* PeopleNowPresent_new (uint32_t number) {
    PeopleNowPresent* p = malloc(sizeof(PeopleNowPresent));

    *p = (PeopleNowPresent) {
        value = number,
        location = NULL,
        name = NULL,
        names = malloc(number * sizeof(char*)),
        description = NULL,
    };

    return p;
}

void PeopleNowPresent_free(PeopleNowPresent* self) {
    free(self->names);
    free(self);
}

void PeopleNowPresent_add_person (PeopleNowPresent* self, uint32_t index, char* name) {
    self->names[index] = name;
}

void PeopleNowPresent_draw (PeopleNowPresent* self) {
}
