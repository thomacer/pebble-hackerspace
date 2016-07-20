#pragma once
#include <pebble.h>
#include "./sensors.h"

/* @desc : PowerConsumption object according to the spaceAPI specification.
 *
 * @param {value} : PowerConsumption unit.
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
    void (*PowerConsumption_free)(void*);
    SimpleMenuItem (*PowerConsumption_menu)(void*);
    void (*PowerConsumption_draw)(Window*, void*);
    void (*PowerConsumption_destroy)(void*);

    // Additional info.
    char* unit;
    char formated_value[32];
} PowerConsumption;

PowerConsumption* PowerConsumption_new (uint32_t, char*, char*, char*, char*);
void PowerConsumption_free(void*);

/* @desc : Return a simple menu item object formated from a PowerConsumption
 *      object.
 *
 * @param {void*} : A PowerConsumption object to format.
 */
SimpleMenuItem PowerConsumption_menu (void*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {PowerConsumption*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void PowerConsumption_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {PowerConsumption*} : Sensor informations.
 */
void PowerConsumption_destroy (void*);
