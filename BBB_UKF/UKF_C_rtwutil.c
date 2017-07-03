/*
 * File: UKF_C_rtwutil.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 14:31:22
 */

/* Include Files */
#include "UKF_C.h"
#include "UKF_C_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
float rt_hypotf(float u0, float u1)
{
  float y;
  float a;
  float b;
  a = (float)fabs(u0);
  b = (float)fabs(u1);
  if (a < b) {
    a /= b;
    y = b * (float)sqrt(a * a + 1.0F);
  } else if (a > b) {
    b /= a;
    y = a * (float)sqrt(b * b + 1.0F);
  } else {
    y = a * 1.41421354F;
  }

  return y;
}

/*
 * File trailer for UKF_C_rtwutil.c
 *
 * [EOF]
 */
