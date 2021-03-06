const async = require('async');

/* @desc : Send properly formated object to the pebble smartwatch.
 *
 * @param {obj} : Object sent.
 * @param {callback} : Function called when done.
 */
exports.sendToPebble = (obj, callback) => {
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
};

const _sendListItemToPebble = (array, index, format, callback) => {
    const toSend = format ? format(array[index], index) : array[index];
    Pebble.sendAppMessage(toSend, () => {
        console.log('SENT : ' + JSON.stringify(toSend));
        if ((index + 1) < array.length) {
            _sendListItemToPebble (array, index + 1, format, callback);
        } else if (callback) {
            callback(null);
        }
    }, function () {
        if (callback) callback('Item transmission failed at index ' + index + ' for : ' + array);
    });
};

/* @desc : Send a list of item to your pebble.
 *
 * @param {items} : List to send.
 * @param {format} : Way items are sent.
 * @param {callback} : Executed function when it's done.
 */
exports.sendListToPebble = (array, format, callback) => {
    _sendListItemToPebble(array, 0, format, callback);
};

/* @desc : Associate the value of an element to its index.
 *
 * @param {array} : Array to wrap.
 */
const wrap = (array) => {
    return array.map((value, index) => {
        return {index: index, value: value};
    });
};
exports.wrap = wrap;

/* @desc : Mix between a map and a series, execute in serie
 *  the same function for every member of an array.
 *
 * @param {array} : The array of object to execute de "func".
 * @param {func} : A function that executed by every member of the "array". The map
 *      pass the arguments :
 *        - value,   // The current value of the array.
 *        - index,   // The current index of the array.
 *        - array,   // The whole array.
 *        - callback // The function to execute when it's done.
 * @param {callback} : Function to call when its done passing the parameters :
 *   - err
 *   - result
 */
exports.mapSerie = (array, func, callback) => {
    const wrapped = wrap(array);

    async.map(wrapped, (item, callback) => {
        // Creating the series of function.
        callback(null, (cb) => {
            func (item.value, item.index, array, cb);
        });
    }, (err, results) => {
        if (err) {
            console.log(err);
            return;
        }
        async.series(results, callback);
    });
};
