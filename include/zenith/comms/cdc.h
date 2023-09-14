#ifndef ZENITH_CDC_H
#define ZENITH_CDC_H

#include <stdint.h>

void cdc_comms_task(uint32_t timestamp, btn_data_t *buttons,
                    analog_data_t *analog);

#endif // ZENITH_CDC_H