const Contact = require('./contact.js').Contact;
const Sensors = require('./sensors.js').Sensors;
const utils = require('./utils.js');
const async = require('async');
const app = require('./appinfo.js');

const xhrRequest = function (url, type, callback) {
  const xhr = new XMLHttpRequest();
  xhr.onload = function () {
      callback(this.responseText);
    };
  xhr.open(type, url);
  xhr.send();
};

const getAPIResult = function () {
    const url = 'http://urlab.be/spaceapi.json';

    console.log('Requesting ' + url);

    xhrRequest(url, 'GET', 
        function(responseText) {
            const json = JSON.parse(responseText);

            async.series([
                (callback) => {
                    utils.sendToPebble({
                        'KEY_TYPE' : app.KEY_BASIC,
                        'KEY_SPACE' : json['space'],
                        'KEY_SPACE_URL' : json['url'],
                        'KEY_OPEN_STATE' : json['state']['open'],
                    }, callback);
                }, (callback) => {
                    let tmp = new Sensors(json['sensors']);
                    tmp.send(callback);
                }, (callback) => {
                    let tmp = new Contact(json['contact']);
                    tmp.send(callback);
                }
            ]);
        }
    );
};

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
    function(e) {
        console.log('PebbleKit JS ready!');
        getAPIResult();
    }
);

Pebble.addEventListener('appmessage',
    function(e) {
        console.log('AppMessage received!');
        getAPIResult();
    }                     
);
