#include <pebble.h>
#include "./windows/win_main.h"
#include "./globals.h"

/* ------------------------------------------------------------------------
 *                      Partie communication avec l'API.
 * ------------------------------------------------------------------------
 */

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void inbox_connected_person_callback(DictionaryIterator *iterator, void *context) {
  switch ((int) dict_find(iterator, KEY_TYPE)->value->int32) {
      case SPACE_INFO_TYPE:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Received space info in pebble.");
        /* Get the name of the hackerspace. */
        t_space = dict_find(iterator, KEY_SPACE);

        t_contact_phone_number = dict_find(iterator, KEY_CONTACT_PHONE_NUMBER);
        t_contact_sip_adress = dict_find(iterator, KEY_CONTACT_SIP_ADDRESS);
        t_contact_irc = dict_find(iterator, KEY_CONTACT_IRC);
        t_contact_twitter = dict_find(iterator, KEY_CONTACT_TWITTER);
        t_contact_facebook = dict_find(iterator, KEY_CONTACT_FACEBOOK);
        t_contact_identica = dict_find(iterator, KEY_CONTACT_IDENTICA);
        t_contact_foursquare = dict_find(iterator, KEY_CONTACT_FOURSQUARE);
        t_contact_email = dict_find(iterator, KEY_CONTACT_EMAIL);
        t_contact_mailing_list = dict_find(iterator, KEY_CONTACT_MAILLING_LIST);
        t_contact_jabber = dict_find(iterator, KEY_CONTACT_JABBER);
        t_contact_issue_mail = dict_find(iterator, KEY_CONTACT_ISSUE_MAIL);

        t_number = dict_find(iterator, KEY_NUMBER_OF_PEOPLE_PRESENT);

        win_main_update();
        break;
      case PEOPLE_PRESENT_LIST_ELEMENT_TYPE:;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Received list in pebble.");
        int32_t index = dict_find(iterator, KEY_INDEX)->value->int32;
        int32_t size = dict_find(iterator, KEY_SIZE)->value->int32;
        if (index == 0) {
            APP_LOG(APP_LOG_LEVEL_DEBUG, "Initiating the new array list of size %ld.", size);
            t_present_person = malloc(sizeof(Tuple*) * size);
        }

        APP_LOG(APP_LOG_LEVEL_DEBUG, "Element is %s.", dict_find(iterator, KEY_ELEMENT)->value->cstring);
        t_present_person[index] = dict_find(iterator, KEY_ELEMENT);
        // TODO Also update the "state" page.
        break;
  }
}

int main(void) {
  win_main_init();

  // Register callbacks
  app_message_register_inbox_received(inbox_connected_person_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);

  /* app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum()); */
  app_message_open(1024, 1024);

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed main window");

  app_event_loop();

  win_main_deinit();
}
