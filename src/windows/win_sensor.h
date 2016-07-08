#pragma once
#include <pebble.h>
#include "../libs/pebble-assist.h"
#include "../appinfo.h"
#include "../libs/sensors/people_now_present.h"
#include "../libs/sensors/sensors.h"

void win_sensor_show (void*);
void win_sensor_init (void);
void win_sensor_deinit (void);
