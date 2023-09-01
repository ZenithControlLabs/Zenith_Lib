#include "zenith/includes.h"

uint8_t _webusb_out_buffer[64] = {0x00};

void webusb_save_confirm() {
    printf("Sending Save receipt...\n");
    memset(_webusb_out_buffer, 0, 64);
    _webusb_out_buffer[0] = 0xF1;
    tud_vendor_n_write(0, _webusb_out_buffer, 64);
    tud_vendor_n_flush(0);
}

void webusb_command_processor(uint8_t *data) {
    switch (data[0]) {
    default:

        break;

    case WEBUSB_CMD_FW_SET: {
        reset_usb_boot(0, 0);
    } break;

    case WEBUSB_CMD_FW_GET: {
        _webusb_out_buffer[0] = WEBUSB_CMD_FW_GET;
        _webusb_out_buffer[1] = (HOJA_FW_VERSION & 0xFF00) >> 8;
        _webusb_out_buffer[2] = HOJA_FW_VERSION & 0xFF;
        tud_vendor_n_write(0, _webusb_out_buffer, 64);
        tud_vendor_n_flush(0);
    } break;

    case:
        WEBUSB_CMD_CALIBRATION_START {
            printf("WebUSB: Got calibration START command.\n");
            calibration_start();
            _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_START;
            tud_vendor_n_write(0, _webusb_out_buffer, 64);
            tud_vendor_n_flush(0);
        }
        break;

    case WEBUSB_CMD_CALIBRATION_NEXT: {
        printf("WebUSB: Got calibration NEXT command.\n");
        calibration_advance();
        _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_NEXT;
        tud_vendor_n_write(0, _webusb_out_buffer, 64);
        tud_vendor_n_flush(0);
    } break;

    case WEBUSB_CMD_CALIBRATION_PREV: {
        printf("WebUSB: Got calibration PREV command.\n");
        calibration_advance();
        _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_PREV;
        tud_vendor_n_write(0, _webusb_out_buffer, 64);
        tud_vendor_n_flush(0);
    } break;

    case WEBUSB_CMD_NOTCH_SET: {
        printf("WebUSB: Got notch point SET command.\n");
        uint8_t notch = data[1];
        if (notch > NUM_NOTCHES) {
            printf("Notch out of range?\n");
            break;
        }
        _settings.stick_config.notch_points_x[notch] = buffer[0];
        _settings.stick_config.notch_points_y[notch] = buffer[1];
        // recompute notch calibration
        notch_calibrate(_cfg_st.stick_config.linearized_points_x,
                        _cfg_st.stick_config.linearized_points_y,
                        _cfg_st.stick_config.notch_points_x,
                        _cfg_st.stick_config.notch_points_y,
                        &(_cfg_st.calib_results));
    } break;
    case WEBUSB_CMD_NOTCH_GET: {
        printf("WebUSB: Got notch point GET command.\n");
        uint8_t notch = data[1];
        if (notch > NUM_NOTCHES) {
            printf("Notch out of range?\n");
            break;
        }
        _webusb_out_buffer[0] = _settings.stick_config.notch_points_x[notch];
        _webusb_out_buffer[1] = _settings.stick_config.notch_points_y[notch];
        tud_vendor_n_write(0, _webusb_out_buffer, 64);
        tud_vendor_n_flush(0);
    } break;

    case WEBUSB_CMD_DBG_RAW_GET: {
        printf("WebUSB: Got raw analog GET command.\n");
        memcpy(_webusb_out_buffer, _analog_data.ax1, 4);
        memcpy(_webusb_out_buffer + 4, _analog_data.ax2, 4);

        tud_vendor_n_write(0, _webusb_out_buffer, 64);
        tud_vendor_n_flush(0);
    } break;

    case WEBUSB_CMD_REMAP_SET: {
        printf("WebUSB: Got Remap SET command.\n");
        remap_listen_enable(data[1], data[2]);
    } break;
    case WEBUSB_CMD_REMAP_GET: {
        printf("WebUSB: Got Remap GET command.\n");
        remap_send_data_webusb(data[1]);
    } break;

    case WEBUSB_CMD_COMMIT_SETTINGS: {
        printf("WebUSB: Got commit settings command.\n");
        settings_save_webindicate();
        settings_save();
    } break;
    case WEBUSB_CMD_RESET_FACTORY: {
        printf("WebUSB: Got reset settings to factory command.\n");
        settings_reset_factory();
    } break;
    }
}