#ifndef ZENITH_NOTCH_REMAP_H
#define ZENITH_NOTCH_REMAP_H

#include "zenith/input/stick.h"

void notch_remap(const float x_in, const float y_in, float *x_out, float *y_out,
                 const calib_results_t *calib_results);

void notch_calibrate(const float in_points_x[], const float in_points_y[],
                     const int8_t notch_points_x[],
                     const int8_t notch_points_y[],
                     calib_results_t *calib_results);

#endif // ZENITH_NOTCH_REMAP_H