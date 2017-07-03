/*
 * File: ut_transform.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

#ifndef UT_TRANSFORM_H
#define UT_TRANSFORM_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "UKF_C_types.h"

/* Function Declarations */
extern void ut_transform(const float M[18], const float P[324], const float
  g_param1[18], float g_param2, const float tr_param[3], float mu[9], float S[81],
  float C[162]);

#endif

/*
 * File trailer for ut_transform.h
 *
 * [EOF]
 */
