/*
Public-facing API for Zenith.
*/

#ifndef ZENITH_H
#define ZENITH_H

#include "zenith/types.h"

// hardware callbacks
void cb_zenith_init_hardware(void);
void cb_zenith_read_buttons(btn_data_t *buttons);
void cb_zenith_read_analog(analog_data_t *analog_data);

// app callbacks
void cb_zenith_app_init(void);
void cb_zenith_core1_init(void);
void cb_zenith_core0_inject(void);
void cb_zenith_core1_inject(void);

#endif // ZENITH_H