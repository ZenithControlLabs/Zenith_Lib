#include "zenith/includes.h"

void cdc_comms_task(uint32_t timestamp, btn_data_t *buttons,
                    analog_data_t *analog) {
    uint8_t input_disp_buf[33];
    input_disp_buf[0] = buttons->s.b1;
    input_disp_buf[1] = buttons->s.b2;
    input_disp_buf[2] = buttons->s.b10;
    input_disp_buf[3] = buttons->s.b7;
    input_disp_buf[4] = buttons->s.b14;
    input_disp_buf[5] = buttons->s.b11;
    input_disp_buf[6] = buttons->s.b12;
    input_disp_buf[7] = buttons->s.b13;
    input_disp_buf[8] = 0;
    input_disp_buf[9] = 0;
    input_disp_buf[10] = buttons->s.b8;
    input_disp_buf[11] = buttons->s.b9;
    input_disp_buf[12] = buttons->s.b3;
    input_disp_buf[13] = buttons->s.b4;
    input_disp_buf[14] = buttons->s.b5;
    input_disp_buf[15] = buttons->s.b6;
    int8_t ax1_int8 = AX_TO_INT8(analog->ax1);
    int8_t ax2_int8 = AX_TO_INT8(analog->ax2);
    for (int i = 0; i < 8; i++) {
        input_disp_buf[16 + i] = (ax1_int8 >> i) & 0x1;
    }
    for (int i = 0; i < 8; i++) {
        input_disp_buf[24 + i] = (ax2_int8 >> i) & 0x1;
    }
    input_disp_buf[33] = '\n';

    if (tud_cdc_connected()) {
        tud_cdc_write(input_disp_buf, 32);
        tud_cdc_write_flush();
    }
}

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf) { (void)itf; }