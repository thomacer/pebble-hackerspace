#pragma once

#include <pebble.h>

/* @desc : Representation for an item of the contact section.
 *
 * @param {type} : Describe what it is.
 * @param {value} : What it contain, typically an adress.
 */
typedef struct {
  char* type;
  char* value;
} ContactItem;

/* @desc : Datastructure containing the contact info of the SpaceAPI.
 *
 * @param {number} : Max number of SpaceAPI info.
 * @param {current} : Current number of added contact info.
 * @param {array} : Array of the contact info.
 */
typedef struct {
  uint32_t number;
  uint32_t current;
  ContactItem** array;
} Contacts;

/* @desc : Create a new "Contacts" struct.
 *
 * @param {uint32_t} : Max number of contact info.
 *
 * @return {Contacts*} : The newly created struct.
 */
Contacts* Contacts_new (uint32_t);

/* @desc : Add a "ContactInfo" to a Contact struct
 *
 * @param {Contact*} : Where to save the data.
 * @param {char*} : String describing the type.
 * @param {char*} : String for the value.
 */
void Contacts_add (Contacts*, char*, char*);

/* @desc : Free a "Contacts" struct.
 *
 * @param {Contacts*} : Struct to free.
 */
void Contacts_free (Contacts*);


