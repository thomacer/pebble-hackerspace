#include "secure_array.h"

/* @desc : Get the first item of the array who result non zero return by
 *      the function "func" passed in parameter.
 *
 * @param {SecureArray*} : The array of sensor to get the object from.
 * @param {func} : Function to verify the data.
 */
static void* SecureArray_get (SecureArray* self, int (*func)(void*)) {
    for (uint32_t i = 0; i < self->current; ++i) {
        if (func(self->array[i])) {
            return self->array[i];
        }
    }

    return NULL;
}

/* @desc : Add a sensor to the array.
 *
 * @param {SecureArray*} : The array to add the object in.
 * @param {void*} : The object to add.
 */
static void SecureArray_add (SecureArray* self, void* sensor) {
    if (self->current >= self->length) {
        return;
    }

    self->array[self->current] = sensor;

    ++self->current;
}

/* @desc : Free the content of the array.
 *
 * @param {SecureArray*} : Array to free.
 * @param {free_func} : The way to free the content of the array (can be NULL).
 */
static void SecureArray_free (SecureArray* self, void (*free_func)(void*)) {
    if (free_func) {
        for (uint32_t i = 0; i < self->current; ++i) {
            free_func(self->array[i]);
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
      .get = SecureArray_get,
      .free = SecureArray_free,
    };

    for (uint32_t i = 0; i < length; ++i) {
        obj->array[i] = NULL;
    }

    return obj;
}
