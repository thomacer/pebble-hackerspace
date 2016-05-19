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

            var space = json['space'];
            console.log('HackerSpace name is ' + space);

            var website_url = json['url'];
            console.log('HackerSpace url is ' + website_url);

            // ---- Contact section information.
            var phone_number = json['contact']['phone'];
            console.log('HackerSpace phone number is ' + phone_number);

            var sip_address = json['contact']['sip'];
            console.log('HackerSpace sip adress is ' + sip_address);

            // TODO var keymasters = json['contact']['keymasters'];

            var irc = json['contact']['irc'];
            console.log('HackerSpace irc is ' + irc);

            var twitter = json['contact']['twitter'];
            console.log('HackerSpace twitter is ' + twitter);

            var facebook = json['contact']['facebook'];
            console.log('HackerSpace facebook is ' + facebook);

            // TODO var google = json['contact']['google'];

            var identica = json['contact']['identica'];
            console.log('HackerSpace identica is ' + identica);

            var foursquare_id = json['contact']['foursquare'];
            console.log('HackerSpace foursquare ID is ' + foursquare_id);

            var email = json['contact']['email'];
            console.log('HackerSpace mail is ' + email);

            var mailing_list = json['contact']['ml'];
            console.log('HackerSpace mailing list address is ' + mailing_list);

            var jabber = json['contact']['jabber'];
            console.log('HackerSpace jabber chatroom address is ' + jabber);

            var mail_issue = json['contact']['issue_mail'];
            console.log('HackerSpace mail for issues is ' + mail_issue);
            // -----------------------------------------------------------------

            // ---- State of the Hackerspace section.
            var openstate = json['state']['open'];
            console.log('Is HackerSpace open ? : ' + openstate);

            var number_of_peoples = json['sensors']['people_now_present'][0]['value'];
            console.log('There is ' + number_of_peoples + ' persons in the hackerspace');

            var people_presents = json['sensors']['people_now_present'][0]['names'];
            console.log('Names are : ' + people_presents);
            // -----------------------------------------------------------------

            var result_dict = {
                "KEY_SPACE" : space,
                
                "KEY_CONTACT_PHONE_NUMBER" : phone_number,
                "KEY_CONTACT_SIP_ADDRESS" : sip_address,
                "KEY_CONTACT_IRC" : irc,
                "KEY_CONTACT_TWITTER" : twitter,
                "KEY_CONTACT_FACEBOOK" : facebook,
                "KEY_CONTACT_IDENTICA" : identica,
                "KEY_CONTACT_FOURSQUARE" : foursquare_id,
                "KEY_CONTACT_EMAIL" : email,
                "KEY_CONTACT_MAILLING_LIST" : mailing_list,
                "KEY_CONTACT_JABBER" : jabber,
                "KEY_CONTACT_ISSUE_MAIL" : mail_issue,

                "KEY_OPEN_STATE" : openstate,
                "KEY_NUMBER_OF_PEOPLE_PRESENT" : number_of_peoples,
                // "KEY_LIST_OF_PEOPLE_PRESENT" : people_presents,

                "KEY_TYPE" : 0,
            };

            // Send to Pebble
            Pebble.sendAppMessage(result_dict,
                function(e) {
                    send_people_present_list(people_presents);
                    console.log('API info sent to Pebble successfully!');
                },
                function(e) {
                    console.log('Error sending API info to Pebble!');
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
