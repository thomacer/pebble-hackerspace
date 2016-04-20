#ifndef _GLOBALS_H
#define _GLOBALS_H
#include "pebble.h"

/* Type used for communication */
#define SPACE_INFO 0
#define LIST 1

#define KEY_TYPE 99

/* Global info used by every sections. */
#define KEY_SPACE 100
/* Used in the contact section */
#define KEY_CONTACT_PHONE_NUMBER 101
#define KEY_CONTACT_SIP_ADDRESS 102
#define KEY_CONTACT_IRC 103
#define KEY_CONTACT_TWITTER 104
#define KEY_CONTACT_FACEBOOK 105
#define KEY_CONTACT_IDENTICA 106
#define KEY_CONTACT_FOURSQUARE 107
#define KEY_CONTACT_EMAIL 108
#define KEY_CONTACT_MAILLING_LIST 109
#define KEY_CONTACT_JABBER 110
#define KEY_CONTACT_ISSUE_MAIL 111
/* Used in the state section. */
#define KEY_OPEN_STATE 112
#define KEY_NUMBER_OF_PEOPLE_PRESENT 113

/* Definition to transmit list. */
#define KEY_ELEMENT 200
#define KEY_INDEX 201
#define KEY_SIZE 202

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

extern Tuple** t_present_person;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
#endif
