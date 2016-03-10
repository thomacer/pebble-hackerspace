#include <pebble.h>
#include "./windows/win_main.h"

int main(void) {
  win_main_init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed main window");

  app_event_loop();

  win_main_deinit();
}
