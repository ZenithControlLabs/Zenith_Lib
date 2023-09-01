#include "zenith_includes.h"

btn_data_t _buttons = {0};
btn_data_t _buttons_processed = {0};

analog_data_t _analog_data = {0};
analog_data_t _analog_data_processed = {0};

void zenith_init(void) {
    cb_zenith_init_hardware();
    cb_zenith_app_init();

    settings_init();
}

void zenith_loop_core0(void) {
    for (;;) {
        cb_zenith_read_buttons(&_buttons);
        // remap_task(&_buttons, &_buttons_proceseed);

        usb_task();

        comms_task(&_buttons);

        cb_zenith_core0_inject();
    }
}

void zenith_loop_core1(void) {
    cb_zenith_core1_init();

    for (;;) {
        stick_task();

        cb_zenith_core1_inject();
    }
}

int main() {
    zenith_init();

    multicore_lockout_victim_init();

    multicore_launch_core1(zenith_loop_core1);

    zenith_loop_core0();
}