#include "icons.h"

GBitmap* urlab_logo = NULL;
GBitmap* door_icon = NULL;
GBitmap* thermometer_icon = NULL;
GBitmap* person_icon = NULL;
GBitmap* humidity_icon = NULL;
GBitmap* lightning_icon = NULL;

void load_icons () {
  urlab_logo = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);
  door_icon = gbitmap_create_with_resource(RESOURCE_ID_KEY_ICON);
  thermometer_icon = gbitmap_create_with_resource(RESOURCE_ID_THERMOMETER_ICON);
  person_icon = gbitmap_create_with_resource(RESOURCE_ID_PERSON_ICON);
  humidity_icon = gbitmap_create_with_resource(RESOURCE_ID_HUMIDITY_ICON);
  lightning_icon = gbitmap_create_with_resource(RESOURCE_ID_LIGHTNING_ICON);
}

void free_icons () {
  gbitmap_destroy(urlab_logo);
  gbitmap_destroy(door_icon);
  gbitmap_destroy(thermometer_icon);
  gbitmap_destroy(person_icon);
}
