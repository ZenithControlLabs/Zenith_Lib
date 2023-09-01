#include "zenith/includes.h"

/*
This method is SUPER important because it captures the signal chain of the stick
reports. Look here to find the sauce
*/
void process_stick(raw_stick_t *raw, const calib_results_t *calib_results,
                   processed_stick_t *stick_out) {

    float linearized_x =
        linearize(raw->stick_x_raw, calib_results->fit_coeffs_x);
    float linearized_y =
        linearize(raw->stick_y_raw, calib_results->fit_coeffs_y);
    raw->stick_x_lin = linearized_x;
    raw->stick_y_lin = linearized_y;

    float remapped_x, remapped_y;
    notch_remap(linearized_x, linearized_y, &remapped_x, &remapped_y,
                calib_results);

    float clamped_x = fmin(127, fmax(-128, remapped_x));
    float clamped_y = fmin(127, fmax(-128, remapped_y));

    stick_out->x = (int8_t)(clamped_x);
    stick_out->y = (int8_t)(clamped_y);
}