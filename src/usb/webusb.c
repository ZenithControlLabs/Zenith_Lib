#include "zenith/includes.h"

uint8_t _webusb_out_buffer[64] = {0x00};
bool _webusb_output_enabled = false;
int _webusb_output_cnt = 0;

void webusb_save_confirm() {
    printf("Sending Save receipt...\n");
    memset(_webusb_out_buffer, 0, 64);
    _webusb_out_buffer[0] = 0xF1;
    tud_vendor_n_write(0, _webusb_out_buffer, 64);
    tud_vendor_n_flush(0);
}

bool webusb_ready_blocking(int timeout) {
    if (timeout > 0) {
        int internal = timeout;
        while (!tud_vendor_n_write_available(0) && (internal > 0)) {
            sleep_us(100);
            tud_task();
            internal--;
        }

        if (!internal) {
            printf("Disabling webusb output..\n");
            _webusb_output_enabled = false;
            return false;
        }

        return true;
    } else {
        return false;
    }

    return true;
}

void webusb_command_processor(uint8_t *data) {
    _webusb_output_enabled = true;
    switch (data[0]) {
    default:

        break;

    case WEBUSB_CMD_FW_SET: {
        reset_usb_boot(0, 0);
    } break;

    case WEBUSB_CMD_FW_GET: {
        _webusb_out_buffer[0] = WEBUSB_CMD_FW_GET;
        _webusb_out_buffer[1] = (ZTH_FW_MINOR << 8) | (ZTH_FW_PATCH & 0xFF);
        _webusb_out_buffer[2] = ZTH_FW_MAJOR;
        if (webusb_ready_blocking(5000)) {
            tud_vendor_n_write(0, _webusb_out_buffer, 64);
            tud_vendor_n_flush(0);
        }
        _webusb_output_enabled = true;
    } break;

    case WEBUSB_CMD_CALIBRATION_START: {
        printf("WebUSB: Got calibration START command.\n");
        if (_cal_step < 1) {
            _cal_step = 1;
            printf("Starting calibration!\nCalibration Step [%d/%d]\n",
                   _cal_step, CALIBRATION_NUM_STEPS);
        }
        _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_START;

    } break;

    case WEBUSB_CMD_CALIBRATION_ADVANCE: {
        _cal_msg = CALIB_ADVANCE;
        printf("WebUSB: Got calibration ADVANCE command. (msg=%d)\n", _cal_msg);
        _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_ADVANCE;
        if (webusb_ready_blocking(5000)) {
            tud_vendor_n_write(0, _webusb_out_buffer, 64);
            tud_vendor_n_flush(0);
        }
    } break;

    case WEBUSB_CMD_CALIBRATION_UNDO: {
        printf("WebUSB: Got calibration UNDO command.\n");
        _cal_msg = CALIB_UNDO;
        _webusb_out_buffer[0] = WEBUSB_CMD_CALIBRATION_UNDO;
        if (webusb_ready_blocking(5000)) {
            tud_vendor_n_write(0, _webusb_out_buffer, 64);
            tud_vendor_n_flush(0);
        }
    } break;

    case WEBUSB_CMD_NOTCH_SET: {
        printf("WebUSB: Got notch point SET command.\n");
        uint8_t notch = data[1];
        if (notch > NUM_NOTCHES) {
            printf("Notch out of range?\n");
            break;
        }
        _settings.stick_config.notch_points_x[notch] =
            INT_N_TO_AX((int8_t)data[2], 8);
        _settings.stick_config.notch_points_y[notch] =
            INT_N_TO_AX((int8_t)data[3], 8);
        // recompute notch calibration
        notch_calibrate(_settings.stick_config.linearized_points_x,
                        _settings.stick_config.linearized_points_y,
                        _settings.stick_config.notch_points_x,
                        _settings.stick_config.notch_points_y,
                        &(_settings.calib_results));
    } break;
    case WEBUSB_CMD_NOTCHES_GET: {
        printf("WebUSB: Got notch points GET command.\n");
        _webusb_out_buffer[0] = WEBUSB_CMD_NOTCHES_GET;
        for (int i = 0; i < NUM_NOTCHES; i++) {
            _webusb_out_buffer[i * 2 + 1] =
                AX_TO_INT8(_settings.stick_config.notch_points_x[i]);
            _webusb_out_buffer[i * 2 + 2] =
                AX_TO_INT8(_settings.stick_config.notch_points_y[i]);
        }
        if (webusb_ready_blocking(5000)) {
            tud_vendor_n_write(0, _webusb_out_buffer, 64);
            tud_vendor_n_flush(0);
        }
    } break;

    case WEBUSB_CMD_REMAP_SET: {
        printf("WebUSB: Got Remap SET command.\n");
        // remap_listen_enable(data[1], data[2]);
    } break;
    case WEBUSB_CMD_REMAP_GET: {
        printf("WebUSB: Got Remap GET command.\n");
        // remap_send_data_webusb(data[1]);
    } break;

    case WEBUSB_CMD_COMMIT_SETTINGS: {
        printf("WebUSB: Got commit settings command.\n");
        // settings_save_webindicate();
        // settings_save();
    } break;
    case WEBUSB_CMD_RESET_FACTORY: {
        printf("WebUSB: Got reset settings to factory command.\n");
        // settings_reset_factory();
    } break;
    }
}

void webusb_input_report(uint32_t timestamp) {
    uint8_t report_buf[64];
    if (!interval_run(timestamp, ZTH_WEBUSB_INTERVAL))
        return;

    report_buf[0] = WEBUSB_INPUT_REPORT_GET;
    report_buf[1] = AX_TO_INT8(_analog_data_processed.ax1);
    report_buf[2] = AX_TO_INT8(_analog_data_processed.ax2);
    memcpy(report_buf + 4, &_analog_data.ax1, sizeof(ax_t));
    memcpy(report_buf + 4 + sizeof(ax_t), &_analog_data.ax2, sizeof(ax_t));

    if (webusb_ready_blocking(5000)) {
        tud_vendor_n_write(0, report_buf, 64);
        tud_vendor_n_flush(0);
    }
}