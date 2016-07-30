#pragma once

#include <pebble.h>

TextLayer** draw_basic (Window*, char*, char*, char*, char*, char*);
void free_basic (TextLayer**);
