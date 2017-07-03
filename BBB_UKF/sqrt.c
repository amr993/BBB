/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : creal32_T *x
 * Return Type  : void
 */
void b_sqrt(creal32_T *x)
{
  float absxr;
  float absxi;
  if (x->im == 0.0F) {
    if (x->re < 0.0F) {
      absxi = 0.0F;
      absxr = sqrtf(fabsf(x->re));
    } else {
      absxi = sqrtf(x->re);
      absxr = 0.0F;
    }
  } else if (x->re == 0.0F) {
    if (x->im < 0.0F) {
      absxi = sqrtf(-x->im / 2.0F);
      absxr = -absxi;
    } else {
      absxi = sqrtf(x->im / 2.0F);
      absxr = absxi;
    }
  } else {
    absxr = fabsf(x->re);
    absxi = fabsf(x->im);
    if ((absxr > 8.50705867E+37F) || (absxi > 8.50705867E+37F)) {
      absxr *= 0.5F;
      absxi *= 0.5F;
      absxi = hypotf(absxr, absxi);
      if (absxi > absxr) {
        absxi = sqrtf(absxi) * sqrtf(1.0F + absxr / absxi);
      } else {
        absxi = sqrtf(absxi) * 1.41421354F;
      }
    } else {
      absxi = sqrtf((hypotf(absxr, absxi) + absxr) * 0.5F);
    }

    if (x->re > 0.0F) {
      absxr = 0.5F * (x->im / absxi);
    } else {
      if (x->im < 0.0F) {
        absxr = -absxi;
      } else {
        absxr = absxi;
      }

      absxi = 0.5F * (x->im / absxr);
    }
  }

  x->re = absxi;
  x->im = absxr;
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */
