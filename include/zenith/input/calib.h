#ifndef ZENITH_CALIB_H
#define ZENITH_CALIB_H

extern int _cal_step;

void calibration_start(void);

void calibration_advance(void);

void calibration_undo(void);

void calibration_finish(void);

#endif // ZENITH_CALIB_H