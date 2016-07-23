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
    .icon = door_icon,
    .title = title,
  };
}

static void KeyMaster_draw (Window* window, KeyMaster* self) {
}

static void KeyMaster_destroy (KeyMaster* self) {
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
