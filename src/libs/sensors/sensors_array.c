#include "sensors_array.h"

SensorsArray* SensorsArray_new (uint32_t length) {
    SensorsArray* obj = (SensorsArray*) malloc(sizeof(SensorsArray));
    *obj = (SensorsArray) {
      .length = length,
      .array = (void**) malloc(sizeof(void*) * length),
      .add = SensorsArray_add,
      .free = SensorsArray_free,
    };

    for (uint32_t i = 0; i < length; ++i) {
        obj->array[i] = NULL;
    }

    return obj;
}

void SensorsArray_add (SensorsArray* self, void* sensor) {
    if (self->current >= self->length) {
        return;
    }

    self->array[self->current] = sensor;

    ++self->current;
}

void SensorsArray_free (SensorsArray* self) {
    for (uint32_t i = 0; i < self->length; ++i) {
        if (self->array[i]) {
            ((Sensor*) (self->array[i]))->free(self->array[i]);
        }
    }
    free(self);
}


