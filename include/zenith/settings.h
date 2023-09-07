#ifndef ZENITH_SETTINGS_H
#define ZENITH_SETTINGS_H

#include "zenith/comms/comms.h"
#include "zenith/input/btn_remap.h"
#include "zenith/input/stick.h"

// 512k from start of flash
#define FLASH_OFFSET (512 * 1024)

// Not in the userland-accessible zenith_cfg.h file because
// we control the settings struct.
static const uint32_t SETTINGS_VER = 0x5001;

typedef struct {
    uint32_t settings_ver;
    comms_mode_t comms_mode;
    calib_results_t calib_results;
    stick_config_t stick_config;
    btn_remap_profile_t btn_remap_profile_n64;
    btn_remap_profile_t btn_remap_profile_gamecube;
} zenith_settings_t;

typedef enum { SETTINGS_NONE, SETTINGS_COMMIT, SETTINGS_RESET } settings_cmd_t;

extern zenith_settings_t _settings;
extern _Atomic volatile settings_cmd_t _settings_cmd;

void settings_core1_handle_commit();
void settings_load();
void settings_reset_to_factory();
void settings_inform_commit();

#endif // ZENITH_SETTINGS_H
