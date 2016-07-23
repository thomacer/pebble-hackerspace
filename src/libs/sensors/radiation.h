#pragma once

#include <pebble.h>
#include "./sensors.h"
#include "./../../icons.h"

/* @desc : Radiation object according to the spaceAPI specification.
 *
 * @param {type} : Alpha, beta, gamma, beta gamma.
 * @param {value} : Radiation unit.
 * @param {unit} : unit of the sensor value.
 * @param {location} : If you use multiple sensor instances for different rooms,
 *      use this field to indicate the location.
 * @param {name} : Give this sensor a name if necessary at all. Use the location
 *      field for the rooms. This field is not intended to be used for names
 *      of hackerspace members. Use the field 'names' instead.
 * @param {description} : An extra field that you can use to attach some
 *      additional information to this sensor instance.
 * @param {dead_time} : The dead time in µs. See the description of the value
 *      field to see how to use the dead time.
 * @param {conversion_factor} : The conversion from the cpm unit to another
 *      unit hardly depends on your tube type. See the description of
 *      the value field to see how to use the conversion factor.
 */
typedef struct {
    // Basic Sensor template.
    t_sensors type;
    uint32_t value;
    char* location;
    char* name;
    char* description;
    void (*Radiation_free)(void*);
    SimpleMenuItem (*Radiation_menu)(void*);
    void (*Radiation_draw)(Window*, void*);
    void (*Radiation_destroy)(void*);

    // Additional info.
    char* unit;
    uint32_t dead_time;
    uint32_t conversion_factor;

    char formated_value[32];
} Radiation;

Radiation* Radiation_new (uint32_t, uint32_t, char*, char*, char*, char*, uint32_t, uint32_t);
void Radiation_free(void*);

/* @desc : Return a simple menu item object formated from a Radiation
 *      object.
 *
 * @param {void*} : A Radiation object to format.
 */
SimpleMenuItem Radiation_menu (void*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {Radiation*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void Radiation_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {Radiation*} : Sensor informations.
 */
void Radiation_destroy (void*);
