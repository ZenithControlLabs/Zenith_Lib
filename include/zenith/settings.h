#ifndef ZENITH_SETTINGS_H
#define ZENITH_SETTINGS_H

#include "zenith/input/stick.h"

typedef struct {
    calib_results_t calib_results;
    stick_config_t stick_config;
} zenith_settings_t;

extern zenith_settings_t _settings;

// 256k from start of flash
#define FLASH_OFFSET (256 * 1024)

#endif // ZENITH_SETTINGS_H