const app = require('./appinfo.js');
const utils = require('./utils.js');
const async = require('async');

class Sensors {
    constructor (sensors) {
        this.obj = sensors; 
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
                    'KEY_NAME' : obj['name']
                };
                utils.sendToPebble (formatedObject, callback);
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

    /* @desc : Send to the pebble the people now present object form the spaceAPI.
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

    /* @desc : Send the sensors spaceAPI object to the pebble.
     */
    send (callback) {
        if (this.obj['people_now_present']) {
            this._people_now_present(this.obj['people_now_present'], callback);
        }
    }
}

exports.Sensors = Sensors;
