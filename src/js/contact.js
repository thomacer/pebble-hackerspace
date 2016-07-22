const app = require('./appinfo.js');
const async = require('async');
const utils = require('./utils.js');

class Contact {
    constructor (contact) {
        this.obj = contact;
    }

    /* @desc : Send the contact info from the SpaceAPI.
     *
     * @param {callback} : Function executed at the end of the function.
     */
    _links (obj, callback) {
        const self = this;

        // List of the currently supported part of the SpaceAPI contact section.
         const supported = ['phone', 'sip', 'irc', 'twitter', 'facebook',
             'identica', 'foursquare', 'email', 'ml', 'jabber', 'issue_mail'
         ];

         let number = 0; // Number of present contact section sent to your pebble
         for (let i = 0; i < supported.length; ++i) {
             if (self.obj[supported[i]]) {
                 ++number;
             }
         }
        

        utils.sendToPebble ({
            'KEY_TYPE' : app.KEY_CONTACT,
            'KEY_LENGTH' : number,

            'KEY_CONTACT_PHONE_NUMBER' : obj['phone'],
            'KEY_CONTACT_SIP_ADDRESS' : obj['sip'],
            'KEY_CONTACT_IRC' : obj['irc'],
            'KEY_CONTACT_TWITTER' : obj['twitter'],
            'KEY_CONTACT_FACEBOOK' : obj['facebook'],
            'KEY_CONTACT_IDENTICA' : obj['identica'],
            'KEY_CONTACT_FOURSQUARE' : obj['foursquare'],
            'KEY_CONTACT_EMAIL' : obj['email'],
            'KEY_CONTACT_MAILLING_LIST' : obj['ml'],
            'KEY_CONTACT_JABBER' : obj['jabber'],
            'KEY_CONTACT_ISSUE_MAIL' : obj['issue_mail'],
        }, callback);
    }

    /* @desc : The keymasters is a special object and need to send an array.
     *
     * @param {callback} : Function executed at the end of the function.
     */
    _keymasters (keymasters, callback) {
        const self = this;

        const length = keymasters.length;
        utils.sendListToPebble(self.obj['keymasters'], (keymaster, index) => {
            return {
                'KEY_TYPE' : app.KEY_CONTACT_KEYMASTER,
                'KEY_INDEX' : index,
                'KEY_LENGTH' : length,
                'KEY_NAME' : keymaster['name'],
                'KEY_NICK' : keymaster['irc_nick'],
                'KEY_PHONE' : keymaster['phone'],
                'KEY_EMAIL' : keymaster['email'],
                'KEY_TWITTER' : keymaster['twitter'],
            };
        }, callback);
    }

    send (callback) {
        const self = this;

        if (!self.obj) {
            callback(null, null);
        }

        let functions = [];

        functions.push((cb) => {
            self._links(self.obj, cb);
        });


        if (self.obj['keymasters']) {
            functions.push((cb) => {
                self._keymasters(self.obj['beverage_supply'], cb);
            });
        }

        async.series(functions, callback);
    }
}

exports.Contact = Contact;
