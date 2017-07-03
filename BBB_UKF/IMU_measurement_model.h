/*
 * File: IMU_measurement_model.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

#ifndef IMU_MEASUREMENT_MODEL_H
#define IMU_MEASUREMENT_MODEL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "UKF_C_types.h"

/* Function Declarations */
extern void IMU_measurement_model(const float pre_state[18], const float state
  [18], float Ts, float measurement[9]);

#endif

/*
 * File trailer for IMU_measurement_model.h
 *
 * [EOF]
 */
