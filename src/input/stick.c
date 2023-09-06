#include "zenith/includes.h"

void process_stick(analog_data_t *in, analog_data_t *out,
                   const calib_results_t *calib_results) {

#if ZTH_LINEARIZATION_EN
    ax_t notch_remap_in_x = linearize(in->ax1, calib_results->fit_coeffs_x);
    ax_t notch_remap_in_y = linearize(in->ax2, calib_results->fit_coeffs_y);
#else
    ax_t notch_remap_in_x = in->ax1;
    ax_t notch_remap_in_y = in->ax2;
#endif

    ax_t remapped_x, remapped_y;
    notch_remap(notch_remap_in_x, notch_remap_in_y, &remapped_x, &remapped_y,
                calib_results);

    out->ax1 = fmin(1.0, fmax(-1.0, remapped_x));
    out->ax2 = fmin(1.0, fmax(-1.0, remapped_y));
}

void stick_task(analog_data_t *in, analog_data_t *out) {
    cb_zenith_read_analog(in);

    if (_cal_step > 0) {
        // The WebUSB task sends us a message through this variable
        // indicating when we will advance or undo a calibration step
        // We read and then clear the message flag to indicate that it is read.
        switch (_cal_msg) {
        case CALIB_ADVANCE: {
            _cal_msg = CALIB_NONE;
#if ZTH_SEPARATE_CAL_READ
            cb_zenith_read_analog_cal(in);
#endif
            calibration_advance(in);
            break;
        }
        case CALIB_UNDO: {
            _cal_msg = CALIB_NONE;
            calibration_undo();
            break;
        }
        default:
            break;
        }
    } else {
        process_stick(in, out, &(_settings.calib_results));
    }
}