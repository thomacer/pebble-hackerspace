#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "pebble.h"

#define KEY_SPACE 0

/* Used in the contact section */
#define KEY_EMAIL 1
#define KEY_IRC 2
#define KEY_FACEBOOK 3
#define KEY_TWITTER 4

/* Used in the state section. */
#define KEY_OPEN_STATE 5
#define KEY_NUMBER_OF_PEOPLE_PRESENT 6
#define KEY_LIST_OF_PEOPLE_PRESENT 7

static Tuple* t_space = NULL;
static Tuple* t_number = NULL;
static Tuple* t_email = NULL;
static Tuple* t_irc = NULL;
static Tuple* t_facebook = NULL;
static Tuple* t_twitter = NULL;

/* Keep track of the hackerspace name */
static char space_name_buffer[32];

#endif
