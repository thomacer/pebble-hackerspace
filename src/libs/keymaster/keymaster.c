#include "keymaster.h"

static void KeyMaster_free (KeyMaster* self) {
  if (self->name) {
    free(self->name);
  }

  if (self->irc_nick) {
    free(self->irc_nick);
  }

  if (self->phone) {
    free(self->phone);
  }

  if (self->email) {
    free(self->email);
  }

  if (self->twitter) {
    free(self->twitter);
  }

  free(self);
}

static SimpleMenuItem KeyMaster_menu (KeyMaster* self) {
  char* title = NULL;
  if (self->name) {
    title = self->name;
  } else if (self->irc_nick) {
    title = self->irc_nick;
  }  else if (self->twitter) {
    title = self->twitter;
  }  else if (self->email) {
    title = self->email;
  } else if (self->phone) {
    title = self->phone;
  }

  return (SimpleMenuItem) {
    .icon = get_icon(RESOURCE_ID_KEY_ICON),
    .title = title,
  };
}

static void KeyMaster_draw (Window* window, KeyMaster* self) {
  Layer* window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  self->layers = malloc(sizeof(TextLayer*) * 10);

  int16_t y_offset = 0;

  // Name
  self->layers[0] = text_layer_create(GRect(0, 0, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[0], "Name : ");
  text_layer_set_text_alignment(self->layers[0], GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->layers[0]));

  self->layers[1] = text_layer_create(GRect(bounds.size.w / 2, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[1], self->name);
  text_layer_set_text_alignment(self->layers[1], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[1]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[1]));

  // IRC nick
  self->layers[2] = text_layer_create(GRect(0, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[2], "IRC nickname : ");
  text_layer_set_text_alignment(self->layers[2], GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->layers[2]));

  self->layers[3] = text_layer_create(GRect(bounds.size.w / 2, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[3], self->irc_nick ? self->irc_nick : "Unknown");
  text_layer_set_text_alignment(self->layers[3], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[3]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[3]));

  // Twitter
  self->layers[4] = text_layer_create(GRect(0, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[4], "Twitter : ");
  text_layer_set_text_alignment(self->layers[4], GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(self->layers[4]));

  self->layers[5] = text_layer_create(GRect(bounds.size.w / 2, y_offset, bounds.size.w / 2, bounds.size.h / 6));
  text_layer_set_text(self->layers[5], self->twitter ? self->twitter : "Unknown");
  text_layer_set_text_alignment(self->layers[5], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[5]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[5]));

  // Email
  self->layers[6] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(self->layers[6], "Email : ");
  text_layer_set_text_alignment(self->layers[6], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[6]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[6]));

  self->layers[7] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 4));
  text_layer_set_text(self->layers[7], self->email ? self->email : "Unknown");
  text_layer_set_text_alignment(self->layers[7], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[7]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[7]));

  // Phone
  self->layers[8] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 6));
  text_layer_set_text(self->layers[8], "Phone : ");
  text_layer_set_text_alignment(self->layers[8], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[8]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[8]));

  self->layers[9] = text_layer_create(GRect(0, y_offset, bounds.size.w, bounds.size.h / 4));
  text_layer_set_text(self->layers[9], self->phone ? self->phone : "Unknown");
  text_layer_set_text_alignment(self->layers[9], GTextAlignmentCenter);
  y_offset += text_layer_get_content_size(self->layers[9]).h;
  layer_add_child(window_layer, text_layer_get_layer(self->layers[9]));

#ifdef PBL_ROUND
  uint8_t inset = 4;
  for (uint32_t i = 0; i < 10; ++i) {
    text_layer_enable_screen_text_flow_and_paging(self->layers[i], inset);
  }
#endif
}

static void KeyMaster_destroy (KeyMaster* self) {
  for (uint32_t i = 0; i < 10; ++i) {
    text_layer_destroy(self->layers[i]);
  }
  free(self->layers);
}

KeyMaster* KeyMaster_new (char* name,
    char* nick,
    char* phone,
    char* email,
    char* twitter)
{
  KeyMaster* k = (KeyMaster*) malloc(sizeof(KeyMaster));

  *k = (KeyMaster) {
    .name = NULL,
    .irc_nick = NULL,
    .phone = NULL,
    .email = NULL,
    .twitter = NULL,
    .free = KeyMaster_free,
    .menu = KeyMaster_menu,
    .draw = KeyMaster_draw,
    .destroy = KeyMaster_destroy,
  };

  if (name) {
    size_t length = strlen(name);
    k->name = (char*) malloc(sizeof(char) * length);
    memcpy(k->name, name, length);
  }

  if (nick) {
    size_t length = strlen(nick);
    k->irc_nick = (char*) malloc(sizeof(char) * length);
    memcpy(k->irc_nick, nick, length);
  }

  if (phone) {
    size_t length = strlen(phone);
    k->phone = (char*) malloc(sizeof(char) * length);
    memcpy(k->phone, phone, length);
  }

  if (email) {
    size_t length = strlen(email);
    k->email = (char*) malloc(sizeof(char) * length);
    memcpy(k->email, email, length);
  }

  if (twitter) {
    size_t length = strlen(twitter);
    k->twitter = (char*) malloc(sizeof(char) * length);
    memcpy(k->twitter, twitter, length);
  }

  return k;
}
