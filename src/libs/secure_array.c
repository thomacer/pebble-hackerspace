#include "secure_array.h"

/* @desc : Add a sensor to the array.
 *
 * @param {SecureArray*} : The array of sensor to add the sensor in.
 * @param {void*} : The sensor to add.
 */
static void SecureArray_add (SecureArray* self, void* sensor) {
    if (self->current >= self->length) {
        return;
    }

    self->array[self->current] = sensor;

    ++self->current;
}

/* @desc : Free the content of the sensor array.
 *
 * @param {SecureArray*} : Array to free.
 */
static void SecureArray_free (SecureArray* self) {
    for (uint32_t i = 0; i < self->length; ++i) {
        if (self->array[i]) {
            ((Sensor*) (self->array[i]))->free(self->array[i]);
        }
    }
    free(self);
}

SecureArray* SecureArray_new (uint32_t length) {
    SecureArray* obj = (SecureArray*) malloc(sizeof(SecureArray));
    *obj = (SecureArray) {
      .length = length,
      .array = (void**) malloc(sizeof(void*) * length),
      .add = SecureArray_add,
      .free = SecureArray_free,
    };

    for (uint32_t i = 0; i < length; ++i) {
        obj->array[i] = NULL;
    }

    return obj;
}


