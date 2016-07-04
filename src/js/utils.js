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



