/*
 * File: ukf_predict1.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

#ifndef UKF_PREDICT1_H
#define UKF_PREDICT1_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "UKF_C_types.h"

/* Function Declarations */
extern void ukf_predict1(float M[18], float P[324], const float f_param1[9],
  float alpha, float beta, float kappa);

#endif

/*
 * File trailer for ukf_predict1.h
 *
 * [EOF]
 */
