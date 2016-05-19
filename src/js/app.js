var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
      callback(this.responseText);
    };
  xhr.open(type, url);
  xhr.send();
};

function sendNextItem(items, index) {
    // Build message
    var dict = {};
    dict['KEY_ELEMENT'] = items[index];
    dict['KEY_INDEX'] = index;
    dict['KEY_SIZE'] = items.length;
    dict['KEY_TYPE'] = 1;

    // Send the message
    Pebble.sendAppMessage(dict, function () {
        // Use success callback to increment index
        index++;

        console.log("SENT (list) : " + dict);

        if(index < items.length) {
            // Send next item
            sendNextItem(items, index);
        } else {
            console.log('Last item sent!');
        }
    }, function () {
        console.log('Item transmission failed at index: ' + index);
    });
}

function send_people_present_list (list) {
    var index = 0;
    if (list.length > 0){
        sendNextItem(list, index);
    }
}

function getAPIResult() {
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
            if (!people_presents || people_presents === undefined) {
                people_presents = [];
            }
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
                "KEY_LIST_OF_PEOPLE_PRESENT" : people_presents,

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
