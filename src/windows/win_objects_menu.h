#pragma once

#include <pebble.h>
#include "../globals.h"
#include "./win_object.h"
#include "../libs/pebble_object.h"
#include "../libs/functionnal.h"
#include "../libs/secure_array.h"
#include "../libs/log.h"

void win_objects_menu_show(SecureArray*, char*);
void win_objects_menu_init(void);
void win_objects_menu_deinit(void);
