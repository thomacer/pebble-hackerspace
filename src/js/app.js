var SPACE_INFO_TYPE = 0;
var PEOPLE_PRESENT_LIST_ELEMENT_TYPE = 1;

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
      callback(this.responseText);
    };
  xhr.open(type, url);
  xhr.send();
};


/* @desc : Send a preformated list item to pebble c.
 *
 * @param {item} : Item from a list.
 * @param {index} : Index of the item.
 */
var sendListItem = function (item, index) {
    // Send the message
    Pebble.sendAppMessage(item, function () {
        console.log("SENT (list) : " + JSON.stringify(dict));
    }, function () {
        console.log('Item transmission failed at index ' + index + ' for : ' + items);
    });
}

/* @desc : Send the list of people present in the space to the pebble.
 *
 * @param {list} : List of people present.
 */
var send_people_present_list = function (list) {
    if (!list) {
        console.log("No people info to send.");
        return; 
    }

    var index = 0;

    for (var index = 0; index < list.length; ++i) {
        // Build message
        var item = {
            "KEY_ELEMENT" : list[index],
            "KEY_INDEX" : index,
            "KEY_SIZE" : list.length,
            "KEY_TYPE" : 1,
        };

        sendListItem(item, index);
    }
}

var getAPIResult = function () {
    var url = "http://urlab.be/spaceapi.json";

    console.log("Requesting " + url);

    xhrRequest(url, 'GET', 
        function(responseText) {
            var json = JSON.parse(responseText);

            var result_dict = {
                "KEY_SPACE" : json['space'],
                "KEY_SPACE_URL" : json['url'],

                // ---- Contact section information.               
                "KEY_CONTACT_PHONE_NUMBER" : json['contact']['phone'],
                "KEY_CONTACT_SIP_ADDRESS" : json['contact']['sip'],
                "KEY_CONTACT_IRC" : json['contact']['irc'],
                "KEY_CONTACT_TWITTER" : json['contact']['twitter'],
                "KEY_CONTACT_FACEBOOK" : json['contact']['facebook'],
                "KEY_CONTACT_IDENTICA" : json['contact']['identica'],
                "KEY_CONTACT_FOURSQUARE" : json['contact']['foursquare'],
                "KEY_CONTACT_EMAIL" : json['contact']['email'],
                "KEY_CONTACT_MAILLING_LIST" : json['contact']['ml'],
                "KEY_CONTACT_JABBER" : json['contact']['jabber'],
                "KEY_CONTACT_ISSUE_MAIL" : json['contact']['issue_mail'],

                "KEY_OPEN_STATE" : json['state']['open'],
                "KEY_NUMBER_OF_PEOPLE_PRESENT" : json['sensors']['people_now_present'][0]['value'],

                "KEY_TYPE" : 0,
            };

            console.log("SENDING : " + JSON.stringify(result_dict));

            // Send to Pebble
            Pebble.sendAppMessage(result_dict,
                function (data) {
                    send_people_present_list(json['sensors']['people_now_present'][0]['names']);
                    console.log('API info sent to Pebble successfully!');
                },
                function (data, err) {
                    console.log('Error sending API info to Pebble for ' + JSON.stringify(data) + ' : ' + err);
                }
            );
        }
    );
}

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
