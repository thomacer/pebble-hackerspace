#include "icons.h"

GBitmap* urlab_logo = NULL;
GBitmap* door_icon = NULL;
GBitmap* thermometer_icon = NULL;
GBitmap* person_icon = NULL;
GBitmap* humidity_icon = NULL;
GBitmap* lightning_icon = NULL;
GBitmap* money_icon = NULL;
GBitmap* drink_icon = NULL;
GBitmap* alpha_icon = NULL;
GBitmap* beta_icon = NULL;
GBitmap* gamma_icon = NULL;
GBitmap* betagamma_icon = NULL;


void load_icons () {
  urlab_logo = gbitmap_create_with_resource(RESOURCE_ID_URLAB_LOGO);
  door_icon = gbitmap_create_with_resource(RESOURCE_ID_KEY_ICON);
  thermometer_icon = gbitmap_create_with_resource(RESOURCE_ID_THERMOMETER_ICON);
  person_icon = gbitmap_create_with_resource(RESOURCE_ID_PERSON_ICON);
  humidity_icon = gbitmap_create_with_resource(RESOURCE_ID_HUMIDITY_ICON);
  lightning_icon = gbitmap_create_with_resource(RESOURCE_ID_LIGHTNING_ICON);
  money_icon = gbitmap_create_with_resource(RESOURCE_ID_MONEY_ICON);
  drink_icon = gbitmap_create_with_resource(RESOURCE_ID_DRINK_ICON);
  alpha_icon = gbitmap_create_with_resource(RESOURCE_ID_ALPHA_ICON);
  beta_icon = gbitmap_create_with_resource(RESOURCE_ID_BETA_ICON);
  gamma_icon = gbitmap_create_with_resource(RESOURCE_ID_GAMMA_ICON);
  betagamma_icon = gbitmap_create_with_resource(RESOURCE_ID_BETAGAMMA_ICON);
}

void free_icons () {
  gbitmap_destroy(urlab_logo);
  gbitmap_destroy(door_icon);
  gbitmap_destroy(thermometer_icon);
  gbitmap_destroy(person_icon);
  gbitmap_destroy(humidity_icon);
  gbitmap_destroy(lightning_icon);
  gbitmap_destroy(money_icon);
  gbitmap_destroy(drink_icon);
  gbitmap_destroy(alpha_icon);
  gbitmap_destroy(beta_icon);
  gbitmap_destroy(gamma_icon);
  gbitmap_destroy(betagamma_icon);
}
