#pragma once
#include <pebble.h>
#include "./sensors.h"
#include "./common.h"
#include "../../icons.h"

/* @desc : TotalMemberCount object according to the spaceAPI specification.
 *
 * @param {value} : Number of member.
 * @param {location} : If you use multiple sensor instances for different rooms,
 *      use this field to indicate the location.
 * @param {name} : Give this sensor a name if necessary at all. Use the location
 *      field for the rooms. This field is not intended to be used for names
 *      of hackerspace members. Use the field 'names' instead.
 * @param {description} : An extra field that you can use to attach some
 *      additional information to this sensor instance.
 */
typedef struct {
    void (*TotalMemberCount_free)(void*);
    SimpleMenuItem (*TotalMemberCount_menu)(void*);
    void (*TotalMemberCount_draw)(Window*, void*);
    void (*TotalMemberCount_destroy)(void*);

    // Basic Sensor template.
    t_sensors type;
    uint32_t value;
    char* location;
    char* name;
    char* description;

    // Additional info.
    char formated_value[32];

    TextLayer** layers;
} TotalMemberCount;

TotalMemberCount* TotalMemberCount_new (uint32_t, char*, char*, char*);
void TotalMemberCount_free(void*);

void TotalMemberCount_set_location (TotalMemberCount*, uint32_t, char*);

/* @desc : Draw in a menu format.
 */
SimpleMenuItem TotalMemberCount_menu (void* s);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {TotalMemberCount*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void TotalMemberCount_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {TotalMemberCount*} : Sensor informations.
 */
void TotalMemberCount_destroy (void*);
