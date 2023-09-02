#ifndef ZENITH_CFG_DEF_H
#define ZENITH_CFG_DEF_H

#ifndef ZTH_WEBUSB_URL
#error "Must define ZTH_WEBUSB_URL in zenith_cfg!"
#endif

#ifndef ZTH_MANUFACTURER
#error                                                                         \
    "Must define ZTH_MANUFACTURER in zenith_cfg.h! Will be the USB vendor name"
#endif

#ifndef ZTH_PRODUCT
#error "Must define ZTH_PRODUCT in zenith_cfg! Will be the USB product name"
#endif

#ifndef ZTH_VID
#define ZTH_VID 0x7318
#endif

#ifndef ZTH_PID
#define ZTH_PID 0x0000
#endif

#ifndef ZTH_FW_MAJOR
#define ZTH_FW_MAJOR 0
#endif

#ifndef ZTH_FW_MINOR
#define ZTH_FW_MINOR 0
#endif

#ifndef ZTH_FW_PATCH
#define ZTH_FW_PATCH 0
#endif

#ifndef ZTH_LINEARIZATION_EN
#define ZTH_LINEARIZATION_EN 1
#endif

#endif // ZENITH_CFG_DEF_H