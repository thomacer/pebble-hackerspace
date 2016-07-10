#pragma once
#include <pebble.h>
#include "../libs/pebble-assist.h"
#include "../globals.h"

extern Contacts* contacts_section;

void win_contact_init(void);
void win_contact_show(void);
void win_contact_deinit(void);
