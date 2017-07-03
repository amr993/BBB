/*
 * File: xzlanhs.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "xzlanhs.h"

/* Function Definitions */

/*
 * Arguments    : const creal32_T A[16]
 *                int ilo
 *                int ihi
 * Return Type  : float
 */
float xzlanhs(const creal32_T A[16], int ilo, int ihi)
{
  float f;
  float scale;
  float sumsq;
  boolean_T firstNonZero;
  int j;
  int i1;
  int i;
  float reAij;
  float imAij;
  float temp2;
  f = 0.0F;
  if (ilo > ihi) {
  } else {
    scale = 0.0F;
    sumsq = 0.0F;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      i1 = j + 1;
      if (ihi < j + 1) {
        i1 = ihi;
      }

      for (i = ilo; i <= i1; i++) {
        reAij = A[(i + ((j - 1) << 2)) - 1].re;
        imAij = A[(i + ((j - 1) << 2)) - 1].im;
        if (reAij != 0.0F) {
          reAij = fabsf(reAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = reAij;
            firstNonZero = false;
          } else if (scale < reAij) {
            temp2 = scale / reAij;
            sumsq = 1.0F + sumsq * temp2 * temp2;
            scale = reAij;
          } else {
            temp2 = reAij / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0F) {
          reAij = fabsf(imAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = reAij;
            firstNonZero = false;
          } else if (scale < reAij) {
            temp2 = scale / reAij;
            sumsq = 1.0F + sumsq * temp2 * temp2;
            scale = reAij;
          } else {
            temp2 = reAij / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    f = scale * sqrtf(sumsq);
  }

  return f;
}

/*
 * File trailer for xzlanhs.c
 *
 * [EOF]
 */
