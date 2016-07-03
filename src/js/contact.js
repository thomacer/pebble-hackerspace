const app = require('./appinfo.js');

class Contact {
    constructor (contact) {
        this.obj = contact;
    }

    send (callback) {
        const self = this;

        const formatedObject = {
            'KEY_TYPE' : app.KEY_CONTACT,

            'KEY_CONTACT_PHONE_NUMBER' : self.obj['contact']['phone'],
            'KEY_CONTACT_SIP_ADDRESS' : self.obj['contact']['sip'],
            'KEY_CONTACT_IRC' : self.obj['contact']['irc'],
            'KEY_CONTACT_TWITTER' : self.obj['contact']['twitter'],
            'KEY_CONTACT_FACEBOOK' : self.obj['contact']['facebook'],
            'KEY_CONTACT_IDENTICA' : self.obj['contact']['identica'],
            'KEY_CONTACT_FOURSQUARE' : self.obj['contact']['foursquare'],
            'KEY_CONTACT_EMAIL' : self.obj['contact']['email'],
            'KEY_CONTACT_MAILLING_LIST' : self.obj['contact']['ml'],
            'KEY_CONTACT_JABBER' : self.obj['contact']['jabber'],
            'KEY_CONTACT_ISSUE_MAIL' : self.obj['contact']['issue_mail'],
        };

        Pebble.sendAppMessage(formatedObject, () => {
            console.log('SENT : ' + JSON.stringify(formatedObject));
            if (callback) callback(null);
        }, () => {
            console.log('Contact transmission failed ' + JSON.stringify(formatedObject));
            if (callback) callback('Contact transmission failed ' + JSON.stringify(formatedObject));
        });
    }
}

exports.Contact = Contact;
