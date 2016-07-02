const app = require('./appinfo.js');
const async = require('async');

class Sensors {
    constructor (sensors) {
        this.obj = sensors; 
    }

    _sendListItemToPebble (array, index, format, callback) {
        Pebble.sendAppMessage(format ? format(array[index], index) : array[index], () => {
            console.log('SENT : ' + JSON.stringify(array[index]));
            if (array.length < (index + 1)) {
                this._sendPebbleItem(array, index + 1);
            } else if (callback) {
                callback(null);
            }
        }, function () {
            if (callback) callback('Item transmission failed at index ' + index + ' for : ' + array);
        });
    }

    /* @desc : Send a list of item to your pebble.
     *
     * @param {items} : List to send.
     * @param {format} : Way items are sent.
     * @param {callback} : Executed function when it's done.
     */
    _sendListToPebble (array, format, callback) {
        this._sendListItemToPebble(array, 0, format, callback);
    }

    /* @desc : Send properly formated object to the pebble smartwatch.
     *
     * @param {obj} : Object sent.
     * @param {callback} : Function called when done.
     */
    _sendToPebble (obj, callback) {
         Pebble.sendAppMessage(obj, () => {

            console.log('SENT : ' + JSON.stringify(obj));
            if (callback) callback(null);
        }, () => {
            if (callback) {
                callback('Item transmission failed ' + JSON.stringify(obj));
            } else {
                console.log('Item transmission failed ' + JSON.stringify(obj));
            
            }
        });
    }

    /* @desc : Send an object from the "people_now_present" array,
     *      "people_now_present" is more complex because it contain an array 
     *      of Strings itself.
     *
     * @param {obj} : Object from the "people_now_present" array.
     * @param {index} : Index in that array.
     * @param {callback} : function called when done.
     */
    _SendPeopleNowPresentObject (obj, index, callback) {
        const self = this;
        async.series([
            (callback) => {
                let formatedObject = {
                    'KEY_TYPE' : app.KEY_SENSOR,
                    'KEY_INDEX' : index,
                    'KEY_VALUE' : obj['value'],
                    'KEY_LOCATION' : obj['location'],
                    'KEY_NAME' : obj['name']
                };
                self._sendToPebble (formatedObject, callback);
            }, (callback) => {
                self._sendListToPebble(obj['names'], (name, index) => {
                    return {
                        'KEY_TYPE' : app.KEY_SENSOR,
                        'KEY_SUBTYPE' : app.KEY_NAMES,
                        'KEY_INDEX' : index,
                        'KEY_NAMES' : name,
                    };
                }, callback);
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

        const wrapped = array.map(function (value, index) {
          return {index: index, value: value};
        });

        async.map(wrapped, (item, callback) => {
            callback(null, (cb) => {
                self._SendPeopleNowPresent (item.value, item.index, cb);
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
