#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define MY_UUID { 0x6D, 0x57, 0xBE, 0xFA, 0x8B, 0x81, 0x4B, 0xF4, 0x81, 0xE3, 0xAB, 0x14, 0x20, 0x70, 0xAB, 0xCD }
PBL_APP_INFO(MY_UUID,
             "Memento Mori", "Little Hiccup",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

TextLayer text_header_layer;
TextLayer text_test_layer;

void handle_second_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;

  static char time_text[] = "00:00:00"; // Needs to be static because it's used by the system later.

  PblTm current_time;
  get_time(&current_time);

  int years_left = 

  string_format_time(time_text, sizeof(time_text), "%T", &current_time);
  text_layer_set_text(&text_test_layer, time_text);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Memento Mori");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&APP_RESOURCES);

  // 


  // create our header
  static char header_text[] = "I love you Ashley";
  text_layer_init(&text_header_layer, window.layer.frame);
  text_layer_set_text_color(&text_header_layer, GColorWhite);
  text_layer_set_background_color(&text_header_layer, GColorClear);
  layer_set_frame(&text_header_layer.layer, GRect(8, 0, 144-8, 168-16));
  text_layer_set_font(&text_header_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_ITALIC_14)));
  layer_add_child(&window.layer, &text_header_layer.layer);
  text_layer_set_text(&text_header_layer, header_text);

  // text test layer
  text_layer_init(&text_test_layer, GRect(29, 54, 144-40 /* width */, 168-54 /* height */));
  text_layer_set_text_color(&text_test_layer, GColorWhite);
  text_layer_set_background_color(&text_test_layer, GColorClear);
  text_layer_set_font(&text_test_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_BOLD_16)));
  handle_second_tick(ctx, NULL); // update immediately
  layer_add_child(&window.layer, &text_test_layer.layer);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    // Handle time updates
    .tick_info = {
      .tick_handler = &handle_second_tick,
      .tick_units = SECOND_UNIT
    }

  };
  app_event_loop(params, &handlers);
}
