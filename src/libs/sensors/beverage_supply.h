#pragma once
#include <pebble.h>
#include "./sensors.h"
#include "./common.h"
#include "./../../icons.h"

/* @desc : BeverageSupply object according to the spaceAPI specification.
 *
 * @param {value} : BeverageSupply unit.
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
    void (*BeverageSupply_free)(void*);
    SimpleMenuItem (*BeverageSupply_menu)(void*);
    void (*BeverageSupply_draw)(Window*, void*);
    void (*BeverageSupply_destroy)(void*);

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
} BeverageSupply;

BeverageSupply* BeverageSupply_new (uint32_t, char*, char*, char*, char*);
void BeverageSupply_free(void*);

/* @desc : Return a simple menu item object formated from a BeverageSupply
 *      object.
 *
 * @param {void*} : A BeverageSupply object to format.
 */
SimpleMenuItem BeverageSupply_menu (void*);

/* @desc : Function used to draw the sensor informations when the window
 *      appear.
 *
 * @param {Window*} : window information.
 * @param {BeverageSupply*} : Sensor informations (defined as a void*
 *      to be polymorphic).
 */
void BeverageSupply_draw (Window*, void*);

/* @desc : Function used to destroy the window when the window disappear.
 *
 * @param {BeverageSupply*} : Sensor informations.
 */
void BeverageSupply_destroy (void*);
