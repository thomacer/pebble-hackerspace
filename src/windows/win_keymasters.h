#pragma once

#include <pebble.h>
#include "../globals.h"
#include "../libs/keymaster/keymaster.h"
#include "../libs/functionnal.h"
#include "../libs/secure_array.h"

extern SecureArray* key_masters;

void win_keymasters_show(void);
void win_keymasters_init(void);
void win_keymasters_deinit(void);
