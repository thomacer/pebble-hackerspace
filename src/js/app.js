var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
      callback(this.responseText);
    };
  xhr.open(type, url);
  xhr.send();
};


function getAPIResult() {
    var url = "http://urlab.be/spaceapi.json";

    console.log("Requesting " + url);

    xhrRequest(url, 'GET', 
        function(responseText) {
            var json = JSON.parse(responseText);

            var space = json["space"];

            var email = json["contact"]["email"];

            var irc = json["contact"]["irc"];

            var facebook = json["contact"]["facebook"];

            var twitter = json["contact"]["twitter"];

            var openstate = json["state"]["open"];

            var number_of_peoples = json["sensors"]["people_now_present"][0]["value"];
            console.log('There is ' + number_of_peoples + ' persons in the hackerspace');

            var people_presents = json["sensors"]["people_now_present"][0]["names"];
            console.log('Names are : ' + people_presents);

            result_dict = {
                "KEY_SPACE" : space,
                "KEY_EMAIL" : email,
                "KEY_IRC" : irc,
                "KEY_FACEBOOK" : facebook,
                "KEY_TWITTER" : twitter,
                "KEY_OPEN_STATE" : openstate
                "KEY_NUMBER_OF_PEOPLE_PRESENT" : number_of_peoples,
                "KEY_LIST_OF_PEOPLE_PRESENT" : people_presents
            };

            // Send to Pebble
            Pebble.sendAppMessage(result_dict,
                function(e) {
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
