#include "./people_now_present.h"

PeopleNowPresent* PeopleNowPresent_new (uint32_t number) {
    PeopleNowPresent* p = malloc(sizeof(PeopleNowPresent));

    *p = (PeopleNowPresent) {
        .value = number,
        .location = NULL,
        .name = NULL,
        .names = malloc(number * sizeof(char*)),
        .description = NULL,
    };

    return p;
}

void PeopleNowPresent_free(PeopleNowPresent* self) {
    free(self->names);
    free(self);
}

void PeopleNowPresent_set_location (PeopleNowPresent* self, uint32_t index, char* location) {

}

void PeopleNowPresent_add_person (PeopleNowPresent* self, uint32_t index, char* name) {
    self->names[index] = name;
}

void PeopleNowPresent_draw (Window* window, PeopleNowPresent* self) {

}

void PeopleNowPresent_destroy (Window* window, PeopleNowPresent* self) {

}
