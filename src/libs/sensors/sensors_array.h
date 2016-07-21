#pragma once

#include "./sensors.h"

typedef struct SensorsArray {
    void** array;
    uint32_t current;
    uint32_t length;
    void (*add)(struct SensorsArray*, void*);
    void (*free)(struct SensorsArray*);
} SensorsArray;

/* @desc : Create a new sensor array.
 *
 * @param {uint32_t} : length of the array.
 */
SensorsArray* SensorsArray_new (uint32_t);

/* @desc : Add a sensor to the array.
 *
 * @param {SensorsArray*} : The array of sensor to add the sensor in.
 * @param {void*} : The sensor to add.
 */
void SensorsArray_add(SensorsArray*, void*);

/* @desc : Free the content of the sensor array.
 *
 * @param {SensorsArray*} : Array to free.
 */
void SensorsArray_free (SensorsArray*);

