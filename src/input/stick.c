#include "zenith/includes.h"

/*
This method is SUPER important because it captures the signal chain of the stick
reports. Look here to find the sauce
*/
void process_stick(analog_data_t *in, analog_data_t *out,
                   const calib_results_t *calib_results) {

    float linearized_x = linearize(in->ax1, calib_results->fit_coeffs_x);
    float linearized_y = linearize(in->ax2, calib_results->fit_coeffs_y);

    float remapped_x, remapped_y;
    notch_remap(linearized_x, linearized_y, &remapped_x, &remapped_y,
                calib_results);

    out->ax2 = fmin(1.0, fmax(-1.0, remapped_x));
    out->ax1 = fmin(1.0, fmax(-1.0, remapped_y));
}

void stick_task(analog_data_t *in, analog_data_t *out) {
    cb_zenith_read_analog(in);

    process_stick(in, out, &(_settings.calib_results));
}