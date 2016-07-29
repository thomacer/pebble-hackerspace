#pragma once

#include <pebble.h>
#include "./../../icons.h"

typedef struct KeyMaster {
    char* name;
    char* irc_nick;
    char* phone;
    char* email;
    char* twitter;

    void (*free)(struct KeyMaster*);
    SimpleMenuItem (*menu)(struct KeyMaster*);
    void (*draw)(Window*, struct KeyMaster*);
    void (*destroy)(struct KeyMaster*);
} KeyMaster;

KeyMaster* KeyMaster_new (char*, char*, char*, char*, char*);
