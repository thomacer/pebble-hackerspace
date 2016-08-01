#pragma once
#include <pebble.h>
#include "./sensors.h"
#include "./common.h"

/* @desc : Barometer object according to the spaceAPI specification.
 *
 * @param {value} : Barometer unit.
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
    void (*Barometer_free)(void*);
    SimpleMenuItem (*Barometer_menu)(void*);
    void (*Barometer_draw)(Window*, void*);
    void (*Barometer_destroy)(void*);

    // Basic Sensor template.
    t_sensors type;
    uint32_t value;
    char* location;
    char* name;
    char* description;

    // Additional info.
    char* unit;
    char formated_value[32];

    TextLayer** layers;
} Barometer;

Barometer* Barometer_new (uint32_t, char*, char*, char*, char*);
void Barometer_free(void*);

/* @desc : Return a simple menu item object formated from a Barometer
 *      object.
 *
 * @param {void*} : A Barometer object to format.
 */
SimpleMenuItem Barometer_menu (void*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {Barometer*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void Barometer_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {Barometer*} : Sensor informations.
 */
void Barometer_destroy (void*);
