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

let api_address = localStorage.getItem('api_address');

const getAPIResult = function () {
    console.log('Requesting ' + api_address);

    xhrRequest(api_address ? api_address : 'http://urlab.be/spaceapi.json', 'GET', 
        function(responseText) {
            const json = JSON.parse(responseText);

            async.series([
                (callback) => {
                    utils.sendToPebble({
                        'KEY_TYPE' : app.KEY_BASIC,
                        'KEY_SPACE' : json['space'],
                        'KEY_SPACE_URL' : json['url'],
                        'KEY_OPEN_STATE' : json['state']['open'],
                        'KEY_LAST_CHANGE' : json['state']['lastchange'],
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

Pebble.addEventListener('showConfiguration', () => {
  const url = 'https://rawgit.com/thomacer/pebble-hackerspace/master/config/index.html';

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', (e) => {
  // Decode the user's preferences
  if (e.response) {
    api_address = JSON.parse(decodeURIComponent(e.response)).api_address;
    console.log('Received : ' + api_address);
    localStorage.setItem('api_address', api_address);
  }
});

