#include "sensors_array.h"

void free_sensors_array (SensorsArray* self) {
    for (uint32_t i = 0; i < self->length; ++i) {
        if (self->array[i]) {
            ((Sensor*) (self->array[i]))->free(self->array[i]);
        }
    }
    free(self);
}

SensorsArray* SensorsArray_new (uint32_t length) {
    SensorsArray* obj = (SensorsArray*) malloc(sizeof(SensorsArray));
    *obj = (SensorsArray) {
      .length = length,
      .array = (void**) malloc(sizeof(void*) * length),
      .free = free_sensors_array,
    };

    return obj;
}
