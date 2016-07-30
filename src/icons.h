#pragma once

#include <pebble.h>

extern GBitmap* RESOURCE_ID_THERMOMETER_ICON_VAR;
extern GBitmap* RESOURCE_ID_KEY_ICON_VAR;
extern GBitmap* RESOURCE_ID_PERSON_ICON_VAR;
extern GBitmap* RESOURCE_ID_HUMIDITY_ICON_VAR;
extern GBitmap* RESOURCE_ID_LIGHTNING_ICON_VAR;
extern GBitmap* RESOURCE_ID_MONEY_ICON_VAR;
extern GBitmap* RESOURCE_ID_DRINK_ICON_VAR;
extern GBitmap* RESOURCE_ID_ALPHA_ICON_VAR;
extern GBitmap* RESOURCE_ID_BETA_ICON_VAR;
extern GBitmap* RESOURCE_ID_GAMMA_ICON_VAR;
extern GBitmap* RESOURCE_ID_BETAGAMMA_ICON_VAR;

#define get_icon(id) id ## _VAR ? id ## _VAR : gbitmap_create_with_resource(id)

void free_icons();
