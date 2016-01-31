#include <pebble.h>
#include "square_grid.h"

static Window *window;
static SquareGrid * grid;
static uint8_t flipper = 0xFF;
struct tm * curr_time = 0;

#define BUFFER_SIZE 20

static inline uint8_t char_to_uint(char c) {
    if (c >= '0' && c <= '9') {
        return (uint8_t) (c - '0');
    } else {
        return 0;
    }
}

static inline void time_string(char * buffer, size_t n) {
    if (clock_is_24h_style()) {
        strftime(buffer, n, "%H%M", curr_time);
    } else {
        strftime(buffer, n, "%l%M", curr_time);
    }    
}

static void update_time() {
    if (!curr_time) return;
    char buffer[BUFFER_SIZE];
    uint8_t vbuffer[GRID_ROW_COUNT];

    time_string(buffer, BUFFER_SIZE);

    for (uint8_t i = 0; i < GRID_ROW_COUNT; i++) {
        vbuffer[i] = char_to_uint(buffer[i]);
    }

    square_grid_set_values(grid, &vbuffer);
}

static void tick_handler(struct tm * tick_time, TimeUnits units_changed) {
    if (units_changed == SECOND_UNIT)
        tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    curr_time = tick_time;
    update_time();
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
    // flipper = ~flipper;
    // update_time();
}

static void window_load(Window *window) {
    window_set_background_color(window, GColorBlack);
    tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
    accel_tap_service_subscribe(tap_handler);
}

static void window_unload(Window *window) {

}

static void init(void) {
    window = window_create();
    window_set_window_handlers(window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    const bool animated = true;
    window_stack_push(window, animated);

    grid = square_grid_create();
    square_grid_add_parent(grid, window_get_root_layer(window));
}

static void deinit(void) {
    square_grid_destroy(grid);
    grid = NULL;
    window_destroy(window);
}

int main(void) {
    init();

    APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

    app_event_loop();
    deinit();
}
