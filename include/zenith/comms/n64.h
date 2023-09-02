#ifndef ZENITH_N64_H
#define ZENITH_N64_H

#include "zenith/utilities/interval.h"
#include <stdint.h>

typedef struct {
    union {
        struct {
            uint8_t dpad_right : 1;
            uint8_t dpad_left : 1;
            uint8_t dpad_down : 1;
            uint8_t dpad_up : 1;
            uint8_t button_start : 1;
            uint8_t button_z : 1;
            uint8_t button_b : 1;
            uint8_t button_a : 1;
        };
        uint8_t buttons_1;
    };

    union {
        struct {
            uint8_t cpad_right : 1;
            uint8_t cpad_left : 1;
            uint8_t cpad_down : 1;
            uint8_t cpad_up : 1;
            uint8_t button_r : 1;
            uint8_t button_l : 1;
            uint8_t reserved : 1;
            uint8_t reset : 1;
        };
        uint8_t buttons_2;
    };

    int8_t stick_x;
    int8_t stick_y;
} __attribute__((packed)) n64_input_t;

void n64_comms_task(uint32_t timestamp, btn_data_t *buttons,
                    analog_data_t *analog);

#endif // ZENITH_N64_H