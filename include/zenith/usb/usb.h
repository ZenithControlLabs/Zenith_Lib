#ifndef ZENITH_USB_H
#define ZENITH_USB_H

#define HID_REPORT_GAMEPAD 4

extern bool _usb_busy;

int usb_init(void);

void usb_task(uint32_t timestamp, btn_data_t *buttons, analog_data_t *analog);

#endif // ZENITH_USB_H