#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x6D, 0x57, 0xBE, 0xFA, 0x8B, 0x81, 0x4B, 0xF4, 0x81, 0xE3, 0xAB, 0x14, 0x20, 0x70, 0xAB, 0xCD }
PBL_APP_INFO(MY_UUID,
             "Memento Mori", "Little Hiccup",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
