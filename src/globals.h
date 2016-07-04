#pragma once
#include "pebble.h"
#include "./windows/sensors/people_now_present_array.h"

#define BUFFER_SIZE 32

extern Tuple* t_space;

extern Tuple* t_contact_phone_number;
extern Tuple* t_contact_sip_address;
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

extern PeopleNowPresentArray* sensor_people_now_present;

/* Keep track of the hackerspace name */
extern char* space_name_buffer;
