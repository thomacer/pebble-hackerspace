#pragma once
#include <pebble.h>
#include "./sensors.h"

/* @desc : people_now_present object according to the spaceAPI specification.
 *
 * @param {value} : The amount of present people.
 * @param {location} : If you use multiple sensor instances for different rooms,
 *      use this field to indicate the location.
 * @param {name} : Give this sensor a name if necessary at all. Use the location
 *      field for the rooms. This field is not intended to be used for names
 *      of hackerspace members. Use the field 'names' instead.
 * @param {names} : List of hackerspace members that are currently
 *      occupying the space.
 * @param {description} : An extra field that you can use to attach some
 *      additional information to this sensor instance.
 */
typedef struct {
    t_sensors type;
    uint32_t value;
    char* location;
    char* name;
    char* description;
    char** names;
    SimpleMenuSection* menu_sections;
    SimpleMenuItem* menu_items;
    SimpleMenuLayer* menu_layer;
} PeopleNowPresent;

PeopleNowPresent* PeopleNowPresent_new (uint32_t);
void PeopleNowPresent_free(PeopleNowPresent*);

void PeopleNowPresent_set_location (PeopleNowPresent*, uint32_t, char*);
void PeopleNowPresent_add_person (PeopleNowPresent*, uint32_t, char*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {PeopleNowPresent*} : Sensor informations.
 */
void PeopleNowPresent_draw (Window*, PeopleNowPresent*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {Window*} : window information.
 * @param {PeopleNowPresent*} : Sensor informations.
 */
void PeopleNowPresent_destroy (Window*, PeopleNowPresent*);
