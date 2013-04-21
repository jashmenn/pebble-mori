#include <stdio.h>
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "xprintf.h"
#include "num2words-en.h"
#include "rand.h"

#define BUFFER_SIZE 256

#define MY_UUID { 0x6D, 0x57, 0xBE, 0xFA, 0x8B, 0x81, 0x4B, 0xF4, 0x81, 0xE3, 0xAB, 0x14, 0x20, 0x70, 0xAB, 0xCD }
PBL_APP_INFO(MY_UUID,
             "Memento Mori", "Little Hiccup",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

TextLayer text_header_layer;
TextLayer text_test_layer;

// Minutes since January 1st 1970 in some timezone, w/o rt leap years
// We use minutes because I plan on living longer than 2038
time_t get_pebble_time_t() {
    PblTm t;
    get_time(&t);
    time_t minutes = t.tm_min;
    minutes += t.tm_hour * 60;
    minutes += t.tm_yday * 1440;
    minutes += ((t.tm_year + 1900) - 1970) * 525600; // t.tm_year is an integer from 1900
    return minutes;
}

// Time in minutes since January 1st 1970 when you're going to die
time_t get_death_time_t() {
  // Configure when you're going to die right here
  // Will make this a setting when Pebble exposes settings to watchfaces
  time_t minutes = 14;
  minutes += 14 * 60;
  minutes += 44 * 1440;
  minutes += (2065 - 1970) * 525600;
  return minutes;
}

time_t get_time_left_t() {
  return get_death_time_t() - get_pebble_time_t();
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *t) {
  (void)t;
  (void)ctx;

  PblTm current_time;
  get_time(&current_time);

  // set time left to words
  static char time_text[BUFFER_SIZE];
  number_to_words(get_time_left_t(), time_text, BUFFER_SIZE);
  append_string(time_text, BUFFER_SIZE, " minutes to live");
  text_layer_set_text(&text_test_layer, time_text);
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, "Memento Mori");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);

  resource_init_current_app(&APP_RESOURCES);

  // create our header
  static char header_text[] = "You have:";

  text_layer_init(&text_header_layer, window.layer.frame);
  text_layer_set_text_color(&text_header_layer, GColorWhite);
  text_layer_set_background_color(&text_header_layer, GColorClear);
  layer_set_frame(&text_header_layer.layer, GRect(8, 0, 144-8, 168-16));
  text_layer_set_font(&text_header_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_ITALIC_14)));
  layer_add_child(&window.layer, &text_header_layer.layer);
  text_layer_set_text(&text_header_layer, header_text);

  // text test layer
  text_layer_init(&text_test_layer, GRect(10, 20, 144-10 /* width */, 168-20 /* height */));
  text_layer_set_text_color(&text_test_layer, GColorWhite);
  text_layer_set_background_color(&text_test_layer, GColorClear);
  text_layer_set_font(&text_test_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_OPENSANS_BOLD_16)));
  handle_tick(ctx, NULL); // update immediately
  layer_add_child(&window.layer, &text_test_layer.layer);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,

    // Handle time updates
    .tick_info = {
      .tick_handler = &handle_tick,
      .tick_units = MINUTE_UNIT
    }

  };
  app_event_loop(params, &handlers);
}


