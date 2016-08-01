#pragma once

#include <pebble.h>

/* @desc : Representation for an item of the contact section.
 *
 * @param {type} : Describe what it is.
 * @param {value} : What it contain, typically an adress.
 */
typedef struct {
  void (*free)(void*);
  SimpleMenuItem (*menu)(void*);
  void (*win_draw)(Window*, void*);
  void (*win_destroy)(void*);

  char* type;
  char* value;
} ContactItem;

ContactItem* ContactItem_new (char*, char*);
