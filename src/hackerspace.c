#include <pebble.h>
#include "./windows/win_main.h"
#include "./globals.h"
#include "./appinfo.h"

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
  switch ((uint32_t) dict_find(iterator, KEY_TYPE)->value->uint32) {
      case KEY_BASIC:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "KEY_BASIC");
        t_space = dict_find(iterator, KEY_SPACE);
        break;
      case KEY_CONTACT:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "KEY_CONTACT");

        t_contact_phone_number = dict_find(iterator, KEY_CONTACT_PHONE_NUMBER);
        t_contact_sip_address = dict_find(iterator, KEY_CONTACT_SIP_ADDRESS);
        t_contact_irc = dict_find(iterator, KEY_CONTACT_IRC);
        t_contact_twitter = dict_find(iterator, KEY_CONTACT_TWITTER);
        t_contact_facebook = dict_find(iterator, KEY_CONTACT_FACEBOOK);
        t_contact_identica = dict_find(iterator, KEY_CONTACT_IDENTICA);
        t_contact_foursquare = dict_find(iterator, KEY_CONTACT_FOURSQUARE);
        t_contact_email = dict_find(iterator, KEY_CONTACT_EMAIL);
        t_contact_mailing_list = dict_find(iterator, KEY_CONTACT_MAILLING_LIST);
        t_contact_jabber = dict_find(iterator, KEY_CONTACT_JABBER);
        t_contact_issue_mail = dict_find(iterator, KEY_CONTACT_ISSUE_MAIL);

        win_main_update();
        break;
      case KEY_SENSOR_PEOPLE_NOW_PRESENT:;
        APP_LOG(APP_LOG_LEVEL_DEBUG, "KEY_SENSOR_PEOPLE_NOW_PRESENT");
        switch ((uint32_t) dict_find(iterator, KEY_SUBTYPE)->value->uint32) {
            case KEY_NAMES: {
                uint32_t index = (uint32_t) dict_find(iterator, KEY_INDEX)->value->uint32;
                uint32_t subindex = (uint32_t) dict_find(iterator, KEY_SUBINDEX)->value->uint32;
                PeopleNowPresent_add_person(
                        sensor_people_now_present->array[index],
                        subindex,
                        (char*) dict_find(iterator, KEY_INDEX)->value->cstring
                );
                break;
            }
            default: {
                if (sensor_people_now_present == NULL) {
                    uint32_t length = (uint32_t) dict_find(iterator, KEY_LENGTH)->value->uint32;
                    create_people_now_present_array(&sensor_people_now_present, length);
                }
                uint32_t index = (uint32_t) dict_find(iterator, KEY_INDEX)->value->uint32;
                uint32_t value = (uint32_t) dict_find(iterator, KEY_VALUE)->value->uint32;
                sensor_people_now_present->array[index] = PeopleNowPresent_new (value);
                break;
            }
        }
        win_main_update();
        break;
      default:
        APP_LOG(APP_LOG_LEVEL_DEBUG, "Default message");

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
