/*
 * File: IMU_process_model.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

#ifndef IMU_PROCESS_MODEL_H
#define IMU_PROCESS_MODEL_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "UKF_C_types.h"

/* Function Declarations */
extern void IMU_process_model(const float state[18], const float observation[9],
  float updated_state[18]);

#endif

/*
 * File trailer for IMU_process_model.h
 *
 * [EOF]
 */
