#pragma once
#include <pebble.h>
#include "./sensors.h"
#include "./common.h"
#include "../../icons.h"

/* @desc : temperature object according to the spaceAPI specification.
 *
 * @param {value} : tmeperature in the "unit" unit.
 * @param {unit} : unit of the sensor value.
 * @param {location} : If you use multiple sensor instances for different rooms,
 *      use this field to indicate the location.
 * @param {name} : Give this sensor a name if necessary at all. Use the location
 *      field for the rooms. This field is not intended to be used for names
 *      of hackerspace members. Use the field 'names' instead.
 * @param {description} : An extra field that you can use to attach some
 *      additional information to this sensor instance.
 */
typedef struct {
    // Basic Sensor template.
    t_sensors type;
    uint32_t value;
    char* location;
    char* name;
    char* description;
    void (*Temperature_free)(void*);
    SimpleMenuItem (*Temperature_menu)(void*);
    void (*Temperature_draw)(Window*, void*);
    void (*Temperature_destroy)(void*);

    // Additional info.
    char* unit;
    char formated_value[32];

    TextLayer** layers;
} Temperature;

Temperature* Temperature_new (uint32_t, char*, char*, char*, char*);
void Temperature_free(void*);

/* @desc : Return a simple menu item object formated from a Temperature
 *      object.
 *
 * @param {void*} : A temperature object to format.
 */
SimpleMenuItem Temperature_menu (void*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {Temperature*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void Temperature_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {Temperature*} : Sensor informations.
 */
void Temperature_destroy (void*);
