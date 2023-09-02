#include "zenith/includes.h"

volatile int _cal_step = -1;

/*
Cleaned calibration point array layout:

[
    CENTER,
    RIGHT,
    UPRIGHT,
    UP,
    UPLEFT,
    LEFT,
    DOWNLEFT,
    DOWN,
    DOWNRIGHT
]
*/

void fold_center_points(const float raw_cal_points_x[],
                        const float raw_cal_points_y[],
                        float cleaned_points_x[], float cleaned_points_y[]) {
    cleaned_points_x[0] = 0;
    cleaned_points_y[0] = 0;

    for (int i = 0; i < NUM_NOTCHES; i++) {
        // each origin reading is summed together
        cleaned_points_x[0] += raw_cal_points_x[i * 2];
        cleaned_points_y[0] += raw_cal_points_y[i * 2];

        // for the notches, copy point into cleaned list
        cleaned_points_x[i + 1] = raw_cal_points_x[i * 2 + 1];
        cleaned_points_y[i + 1] = raw_cal_points_y[i * 2 + 1];
    }

    // remove the largest and smallest origin values to remove outliers
    // first, find their indices

    int smallestX = 0;
    int largestX = 0;
    int smallestY = 0;
    int largestY = 0;
    for (int i = 0; i < NUM_NOTCHES; i++) {
        if (raw_cal_points_x[i * 2] < raw_cal_points_x[smallestX]) {
            // record the new smallest index
            smallestX = i * 2;
        } else if (raw_cal_points_x[i * 2] > raw_cal_points_x[largestX]) {
            // record the new largest index
            largestX = i * 2;
        }

        if (raw_cal_points_y[i * 2] < raw_cal_points_y[smallestY]) {
            // record the new smallest index
            smallestY = i * 2;
        } else if (raw_cal_points_y[i * 2] > raw_cal_points_y[largestY]) {
            // record the new largest index
            largestY = i * 2;
        }
    }
    // subtract the smallest and largest values
    cleaned_points_x[0] -= raw_cal_points_x[smallestX];
    cleaned_points_x[0] -= raw_cal_points_x[largestX];
    cleaned_points_y[0] -= raw_cal_points_y[smallestY];
    cleaned_points_y[0] -= raw_cal_points_y[largestY];

    // divide by the total number of calibration steps/2 to get the average
    // origin value except it's minus 4 steps since we removed outliers
    cleaned_points_x[0] = cleaned_points_x[0] / ((float)NUM_NOTCHES - 2);
    cleaned_points_y[0] = cleaned_points_y[0] / ((float)NUM_NOTCHES - 2);
}

void calibration_start(void) {}
void calibration_advance(void) {}
void calibration_undo(void) {}
void calibration_finish(void) {}