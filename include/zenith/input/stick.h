#ifndef ZENITH_STICK_H
#define ZENITH_STICK_H

#include <stdint.h>

#define NUM_NOTCHES 8
#define FIT_ORDER 3

typedef struct {
    bool calibrated;
    float fit_coeffs_x[FIT_ORDER + 1];
    float fit_coeffs_y[FIT_ORDER + 1];

    float affine_coeffs[NUM_NOTCHES][4];
    float boundary_angles[NUM_NOTCHES];

    ax_t notch_points_x_in[NUM_NOTCHES];
    ax_t notch_points_y_in[NUM_NOTCHES];
} calib_results_t;

typedef struct {
    ax_t notch_points_x[NUM_NOTCHES];
    ax_t notch_points_y[NUM_NOTCHES];
} stick_config_t;

void process_stick(analog_data_t *in, analog_data_t *out,
                   const calib_results_t *calib_results);

void stick_task(analog_data_t *in, analog_data_t *out);

#endif // ZENITH_STICK_H