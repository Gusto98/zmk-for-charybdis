#include <device.h>
#include <drivers/gpio.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>

#define DPI_LEVELS 3

struct dpi_cycle_behavior_config {
    // You can add config options here if needed later
};

struct dpi_cycle_behavior_data {
    uint8_t current_level;
};

static int dpi_cycle_behavior_init(const struct device *dev) {
    struct dpi_cycle_behavior_data *data = dev->data;
    data->current_level = 0; // start at level 0
    return 0;
}

static int dpi_cycle_behavior_on_press(const struct device *dev, struct zmk_behavior_binding *binding,
                                       struct zmk_behavior_binding_event event) {
    struct dpi_cycle_behavior_data *data = dev->data;

    // Cycle through DPI levels 0,1,2
    data->current_level = (data->current_level + 1) % DPI_LEVELS;

    // Here you send the appropriate keycode or command for the new DPI level.
    // For example, send a consumer control or HID report.
    // This is where you'll need to tie in your actual DPI change commands, e.g.:

    switch (data->current_level) {
        case 0:
            // send DPI level 1 keycode
            // zmk_hid_keyboard_press(REPORT_ID, KEYCODE_DPI_1);
            break;
        case 1:
            // send DPI level 2 keycode
            break;
        case 2:
            // send DPI level 3 keycode
            break;
    }

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct zmk_behavior_driver_api dpi_cycle_behavior_driver_api = {
    .binding_pressed = dpi_cycle_behavior_on_press,
};

ZMK_BEHAVIOR_DRIVER(dpi_cycle_behavior, dpi_cycle_behavior_driver_api, dpi_cycle_behavior_init,
                    struct dpi_cycle_behavior_config, struct dpi_cycle_behavior_data);
