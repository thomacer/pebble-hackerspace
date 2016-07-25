#pragma once
#include <pebble.h>
#include "../globals.h"
#include "./win_sensor.h"

extern SecureArray* sensors_array;

void win_sensor_menu_show(void);
void win_sensor_menu_init(void);
void win_sensor_menu_deinit(void);
