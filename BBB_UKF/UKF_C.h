/*
 * File: UKF_C.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

#ifndef UKF_C_H
#define UKF_C_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "UKF_C_types.h"

/* Function Declarations */
extern void UKF_C(const float observation[18], const float pre_state[18], const
                  float pre_cov[324], float state[18], float cov[324], float k
                  [162], float MU[9], float S[81], float e[9]);

#endif

/*
 * File trailer for UKF_C.h
 *
 * [EOF]
 */
