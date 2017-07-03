/*
 * File: xzlangeM.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "xzlangeM.h"

/* Function Definitions */

/*
 * Arguments    : const creal32_T x[16]
 * Return Type  : float
 */
float xzlangeM(const creal32_T x[16])
{
  float y;
  int k;
  float absxk;
  y = 0.0F;
  for (k = 0; k < 16; k++) {
    absxk = hypotf(x[k].re, x[k].im);
    if (absxk > y) {
      y = absxk;
    }
  }

  return y;
}

/*
 * File trailer for xzlangeM.c
 *
 * [EOF]
 */
