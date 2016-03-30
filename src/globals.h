#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "pebble.h"

#define KEY_SPACE 0

/* Used in the contact section */
#define KEY_CONTACT_PHONE_NUMBER 1
#define KEY_CONTACT_SIP_ADDRESS 2
#define KEY_CONTACT_IRC 3
#define KEY_CONTACT_TWITTER 4
#define KEY_CONTACT_FACEBOOK 5
#define KEY_CONTACT_IDENTICA 6
#define KEY_CONTACT_FOURSQUARE 7
#define KEY_CONTACT_EMAIL 8
#define KEY_CONTACT_MAILLING_LIST 9
#define KEY_CONTACT_JABBER 10
#define KEY_CONTACT_ISSUE_MAIL 11

/* Used in the state section. */
#define KEY_OPEN_STATE 12
#define KEY_NUMBER_OF_PEOPLE_PRESENT 13
#define KEY_LIST_OF_PEOPLE_PRESENT 14

#define BUFFER_SIZE 32

extern Tuple* t_space;

extern Tuple* t_contact_phone_number;
extern Tuple* t_contact_sip_adress;
extern Tuple* t_contact_irc;
extern Tuple* t_contact_twitter;
extern Tuple* t_contact_facebook;
extern Tuple* t_contact_identica;
extern Tuple* t_contact_foursquare;
extern Tuple* t_contact_email;
extern Tuple* t_contact_mailing_list;
extern Tuple* t_contact_jabber;
extern Tuple* t_contact_issue_mail;

extern Tuple* t_number;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;

#endif
