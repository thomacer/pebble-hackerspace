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

#define BUFFER_SIZE 32

extern Tuple* t_space;
extern Tuple* t_number;
extern Tuple* t_email;
extern Tuple* t_irc;
extern Tuple* t_facebook;
extern Tuple* t_twitter;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;

#endif
