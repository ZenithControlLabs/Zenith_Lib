#ifndef ZENITH_WEBUSB_H
#define ZENITH_WEBUSB_H

#include <stdint.h>

typedef enum {
    // Set FW update mode
    WEBUSB_CMD_FW_SET = 0x00,
    // Get firmware version
    WEBUSB_CMD_FW_GET = 0xA0,

    WEBUSB_CMD_CALIBRATION_START = 0x01,
    WEBUSB_CMD_CALIBRATION_NEXT = 0x02,
    WEBUSB_CMD_CALIBRATION_PREV = 0x03,
    WEBUSB_CMD_CALIBRATION_STEP_GET = 0xA1,

    WEBUSB_CMD_NOTCH_SET = 0x04,
    WEBUSB_CMD_NOTCH_GET = 0xA4,

    WEBUSB_CMD_DBG_SET = 0x05,
    WEBUSB_CMD_DBG_GET = 0xA5,

    WEBUSB_CMD_REMAP_SET = 0x06,
    WEBUSB_CMD_REMAP_GET = 0xA6,

    WEBUSB_CMD_COMMIT_SETTINGS = 0xF1,
    WEBUSB_CMD_RESET_FACTORY = 0xF2
} webusb_cmd_t;

void webusb_save_confirm();
void webusb_command_processor(uint8_t *data);

#endif // ZENITH_WEBUSB_H