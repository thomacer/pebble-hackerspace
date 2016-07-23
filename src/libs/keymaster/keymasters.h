#pragma once

#include <pebble.h>
#include "./keymaster.h"

typedef struct KeyMasters {
    uint32_t length;
    KeyMaster** array;
    void (*free)(struct KeyMasters*);
} KeyMasters;

KeyMasters* KeyMasters_new (uint32_t);
