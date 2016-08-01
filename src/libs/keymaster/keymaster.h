#pragma once

#include <pebble.h>
#include "./../../icons.h"
#include "../log.h"

typedef struct KeyMaster {
    void (*free)(struct KeyMaster*);
    SimpleMenuItem (*menu)(struct KeyMaster*);
    void (*draw)(Window*, struct KeyMaster*);
    void (*destroy)(struct KeyMaster*);

    char* name;
    char* irc_nick;
    char* phone;
    char* email;
    char* twitter;

    TextLayer** layers;
} KeyMaster;

KeyMaster* KeyMaster_new (char*, char*, char*, char*, char*);
