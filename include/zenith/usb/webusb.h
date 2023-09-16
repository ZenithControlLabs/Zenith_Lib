#ifndef ZENITH_WEBUSB_H
#define ZENITH_WEBUSB_H

#include <stdint.h>

extern bool _webusb_output_enabled;

typedef enum {
    // Get firmware version
    WEBUSB_CMD_FW_GET = 0xA1,

    WEBUSB_CMD_CALIBRATION_START = 0x01,
    WEBUSB_CMD_CALIBRATION_ADVANCE = 0x02,
    WEBUSB_CMD_CALIBRATION_UNDO = 0x03,
    WEBUSB_CMD_CALIBRATION_STEP_GET = 0xA2,

    WEBUSB_CMD_NOTCH_SET = 0x04,
    WEBUSB_CMD_NOTCHES_GET = 0xA4,

    WEBUSB_CMD_REMAP_SET = 0x05,
    WEBUSB_CMD_REMAP_GET = 0xA5,

    WEBUSB_CMD_UPDATE_FW = 0xF1,
    WEBUSB_CMD_COMMIT_SETTINGS = 0xF2,
    WEBUSB_CMD_RESET_SETTINGS = 0xF3
} webusb_cmd_t;

#define WEBUSB_CMD_USER_MASK 0b01100000

// defining for access to stick data through WebUSB
extern analog_data_t _analog_data;
extern analog_data_t _analog_data_processed;

// The WebUSB interface will send output reports separately over the USB.
// But it doesn't need to be sending that when the controller is just being used
// for HID, so it will disable itself after this many reports sent without a
// confirm on the JS side.
#define WEBUSB_OE_CONFIRM_THRESHOLD 1

void webusb_save_confirm();
void webusb_command_processor(uint8_t *data);
// It's called input report, but this is from the perspective of the USB host.
// This is an output of the controller.
void webusb_input_report();

#endif // ZENITH_WEBUSB_H