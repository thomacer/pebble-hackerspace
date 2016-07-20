const app = require('./appinfo.js');
const utils = require('./utils.js');
const async = require('async');

class Sensors {
    constructor (sensors) {
        this.obj = sensors; 
    }

    /* @desc : Count the number of sensors object fetched from the spaceAPI.
     */
    _count () {
        const self = this;
        let count = 0;
        for (let obj in self.obj) {
            count += self.obj[obj].length;
        }

        return count;
    }

    /* @desc : Send an object from the "people_now_present" array,
     *      "people_now_present" is more complex because it contain an array 
     *      of Strings itself.
     *
     * @param {obj} : Object from the "people_now_present" array.
     * @param {index} : Index in that array.
     * @param {callback} : function called when done.
     */
    _SendPeopleNowPresentObject (obj, index, length, callback) {
        const self = this;
        async.series([
            (callback) => {
                let formatedObject = {
                    'KEY_TYPE' : app.KEY_SENSOR_PEOPLE_NOW_PRESENT,
                    'KEY_SUBTYPE' : app.KEY_SENSOR_PEOPLE_NOW_PRESENT,
                    'KEY_INDEX' : index,
                    'KEY_LENGTH' : length,
                    'KEY_VALUE' : obj['value'],
                    'KEY_LOCATION' : obj['location'],
                    'KEY_NAME' : obj['name'],
                    'KEY_DESCRIPTION' : obj['description'],
                };
                utils.sendToPebble(formatedObject, callback);
            }, (callback) => {
                if (obj['value'] && obj['names']) {
                    utils.sendListToPebble(obj['names'], (name, arrayIndex) => {
                        return {
                            'KEY_TYPE' : app.KEY_SENSOR_PEOPLE_NOW_PRESENT,
                            'KEY_SUBTYPE' : app.KEY_NAMES,
                            'KEY_INDEX' : index,
                            'KEY_LENGTH' : obj['names'].length,
                            'KEY_SUBINDEX' : arrayIndex,
                            'KEY_NAMES' : name,
                        };
                    }, callback);
                } else {
                    // If no list to send.
                    callback(null);
                }
            }
        ], (err, results) => {
            if (err) {
                console.log(err);
                return;
            } else if (callback) {
                callback();
            }
        });
    }

    /* @desc : Send to the pebble the people now present object from the spaceAPI.
     *
     * @param {array} : Contain object with nested elements of type :
     * @example "people_now_present": [ 
     *     {
     *         "value": 1,
     *         "names": [
     *             "xx:xx:xx:xx:fe:7a"
     *         ]
     *     }
     *  ],
     */
    _people_now_present (array, callback) {
        const self = this;

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                self._SendPeopleNowPresentObject (item.value, item.index, wrapped.length, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }

    /* @desc : Send to the pebble the temperature object from the spaceAPI.
     *
     * @param {array} : Contain temperature objects.
     */
    _temperature (array, callback) {
        const self = this; 

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                utils.sendToPebble({
                    'KEY_TYPE' : app.KEY_SENSOR_TEMPERATURE,
                    'KEY_INDEX' : item.index,
                    'KEY_LENGTH' : wrapped.length,
                    'KEY_VALUE' : item.value['value'],
                    'KEY_LOCATION' : item.value['location'],
                    'KEY_NAME' : item.value['name'],
                    'KEY_DESCRIPTION' : item.value['description'],
                    'KEY_UNIT' : item.value['unit'],
                }, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }

    /* @desc : Send to the pebble the "door_locked" object from the spaceAPI.
     *
     * @param {array} : Contain "door_locked" objects.
     */
    _door_locked(array, callback) {
        const self = this; 

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                utils.sendToPebble({
                    'KEY_TYPE' : app.KEY_SENSOR_DOOR_LOCKED,
                    'KEY_INDEX' : item.index,
                    'KEY_LENGTH' : wrapped.length,
                    'KEY_VALUE' : item.value['value'],
                    'KEY_LOCATION' : item.value['location'],
                    'KEY_NAME' : item.value['name'],
                    'KEY_DESCRIPTION' : item.value['description'],
                }, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }

    /* @desc : Send to the pebble the barometer object from the spaceAPI.
     *
     * @param {array} : Contain barometer objects.
     */
    _barometer (array, callback) {
        const self = this; 

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                utils.sendToPebble({
                    'KEY_TYPE' : app.KEY_SENSOR_BAROMETER,
                    'KEY_INDEX' : item.index,
                    'KEY_LENGTH' : wrapped.length,
                    'KEY_VALUE' : item.value['value'],
                    'KEY_LOCATION' : item.value['location'],
                    'KEY_NAME' : item.value['name'],
                    'KEY_DESCRIPTION' : item.value['description'],
                    'KEY_UNIT' : item.value['unit'],
                }, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }

    /* @desc : Send to the pebble the humidity object from the spaceAPI.
     *
     * @param {array} : Contain humidity objects.
     */
    _humidity (array, callback) {
        const self = this; 

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                utils.sendToPebble({
                    'KEY_TYPE' : app.KEY_SENSOR_HUMIDITY,
                    'KEY_INDEX' : item.index,
                    'KEY_LENGTH' : wrapped.length,
                    'KEY_VALUE' : item.value['value'],
                    'KEY_LOCATION' : item.value['location'],
                    'KEY_NAME' : item.value['name'],
                    'KEY_DESCRIPTION' : item.value['description'],
                    'KEY_UNIT' : item.value['unit'],
                }, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }

    /* @desc : Send to the pebble the power_consumption object from the spaceAPI.
     *
     * @param {array} : Contain power_consumption objects.
     */
    _power_consumption (array, callback) {
        const self = this; 

        // Associating the index to the value.
        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            // Creating the series of function.
            callback(null, (cb) => {
                utils.sendToPebble({
                    'KEY_TYPE' : app.KEY_SENSOR_POWER_CONSUMPTION,
                    'KEY_INDEX' : item.index,
                    'KEY_LENGTH' : wrapped.length,
                    'KEY_VALUE' : item.value['value'],
                    'KEY_LOCATION' : item.value['location'],
                    'KEY_NAME' : item.value['name'],
                    'KEY_DESCRIPTION' : item.value['description'],
                    'KEY_UNIT' : item.value['unit'],
                }, cb);
            });
        }, (err, results) => {
            if (err) {
                console.log(err);
                return;
            }
            async.series(results, callback);
        });
    }



    /* @desc : Send the sensors spaceAPI object to the pebble.
     */
    send (callback) {
        const self = this;

        // const supported_sensors = [{
        //     name : 'people_now_present', 
        //     func : this._people_now_present,
        // }, {
        //     name : 'temperature', 
        //     func : this._temperature,
        // }];


        let functions = [];

        const count = self._count();
        functions.push((cb) => {
            utils.sendToPebble({
                'KEY_TYPE' : app.KEY_SENSOR,
                'KEY_LENGTH' : count,
            }, cb);
        });

        if (self.obj['people_now_present']) {
            functions.push((cb) => {
                self._people_now_present(self.obj['people_now_present']);
                cb();
            });
        }

        if (self.obj['temperature']) {
            functions.push((cb) => {
                self._temperature(self.obj['temperature']);
                cb();
            });
        }

        if (self.obj['door_locked']) {
            functions.push((cb) => {
                self._door_locked(self.obj['door_locked']);
                cb();
            });
        }

        if (self.obj['barometer']) {
            functions.push((cb) => {
                self._barometer(self.obj['barometer']);
                cb();
            });
        }

        if (self.obj['humidity']) {
            functions.push((cb) => {
                self._humidity(self.obj['humidity']);
                cb();
            });
        }

        if (self.obj['power_consumption']) {
            functions.push((cb) => {
                self._power_consumption(self.obj['power_consumption']);
                cb();
            });
        }

        async.series(functions, callback);
    }
}

exports.Sensors = Sensors;
