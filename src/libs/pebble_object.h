#pragma once

#include <pebble.h>

typedef struct {
    void (*free)(void*);
    SimpleMenuItem (*menu)(void*);
    void (*win_draw)(Window*, void*);
    void (*win_destroy)(void*);
} PebbleObject;
