#pragma once

#include "./sensors.h"

typedef struct SensorsArray {
    void** array;
    uint32_t length;
    void (*free)(struct SensorsArray*);
} SensorsArray;

void free_sensors_array (SensorsArray*);
SensorsArray* SensorsArray_new (uint32_t);
