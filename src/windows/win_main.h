#pragma once

#include <pebble.h>
#include "../libs/log.h"
#include "./win_basic.h"
#include "./win_sensor_menu.h"
#include "./win_contact.h"
#include "./win_about.h"
#include "./win_keymasters.h"
#include "../globals.h"
#include "../icons.h"

void win_main_update(void);
void win_main_init(void);
void win_main_deinit(void);
