/*
 * File: xztgevc.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "xztgevc.h"

/* Function Definitions */

/*
 * Arguments    : const creal32_T A[16]
 *                creal32_T V[16]
 * Return Type  : void
 */
void xztgevc(const creal32_T A[16], creal32_T V[16])
{
  float rworka[4];
  int jc;
  float anorm;
  int j;
  float xmx;
  float ascale;
  float d_re;
  int je;
  float temp;
  float salpha_re;
  float salpha_im;
  float acoeff;
  boolean_T b0;
  boolean_T b1;
  float scale;
  float acoefa;
  creal32_T work1[4];
  int jr;
  float dmin;
  creal32_T work2[4];
  float d_im;
  float work1_re;
  for (jc = 0; jc < 4; jc++) {
    rworka[jc] = 0.0F;
  }

  anorm = fabsf(A[0].re) + fabsf(A[0].im);
  for (j = 0; j < 3; j++) {
    for (jc = 0; jc <= j; jc++) {
      rworka[j + 1] += fabsf(A[jc + ((j + 1) << 2)].re) + fabsf(A[jc + ((j + 1) <<
        2)].im);
    }

    d_re = rworka[j + 1] + (fabsf(A[(j + ((j + 1) << 2)) + 1].re) + fabsf(A[(j +
      ((j + 1) << 2)) + 1].im));
    if (d_re > anorm) {
      anorm = d_re;
    }
  }

  xmx = anorm;
  if (1.17549435E-38F > anorm) {
    xmx = 1.17549435E-38F;
  }

  ascale = 1.0F / xmx;
  for (je = 0; je < 4; je++) {
    xmx = (fabsf(A[(((3 - je) << 2) - je) + 3].re) + fabsf(A[(((3 - je) << 2) -
             je) + 3].im)) * ascale;
    if (1.0F > xmx) {
      xmx = 1.0F;
    }

    temp = 1.0F / xmx;
    salpha_re = ascale * (temp * A[(((3 - je) << 2) - je) + 3].re);
    salpha_im = ascale * (temp * A[(((3 - je) << 2) - je) + 3].im);
    acoeff = temp * ascale;
    if ((fabsf(temp) >= 1.17549435E-38F) && (fabsf(acoeff) < 3.94430453E-31F)) {
      b0 = true;
    } else {
      b0 = false;
    }

    if ((fabsf(salpha_re) + fabsf(salpha_im) >= 1.17549435E-38F) && (fabsf
         (salpha_re) + fabsf(salpha_im) < 3.94430453E-31F)) {
      b1 = true;
    } else {
      b1 = false;
    }

    scale = 1.0F;
    if (b0) {
      xmx = anorm;
      if (2.5353012E+30F < anorm) {
        xmx = 2.5353012E+30F;
      }

      scale = 3.94430453E-31F / fabsf(temp) * xmx;
    }

    if (b1) {
      xmx = 3.94430453E-31F / (fabsf(salpha_re) + fabsf(salpha_im));
      if (xmx > scale) {
        scale = xmx;
      }
    }

    if (b0 || b1) {
      xmx = fabsf(acoeff);
      d_re = fabsf(salpha_re) + fabsf(salpha_im);
      if (1.0F > xmx) {
        xmx = 1.0F;
      }

      if (d_re > xmx) {
        xmx = d_re;
      }

      d_re = 1.0F / (1.17549435E-38F * xmx);
      if (d_re < scale) {
        scale = d_re;
      }

      if (b0) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      if (b1) {
        salpha_re *= scale;
        salpha_im *= scale;
      } else {
        salpha_re *= scale;
        salpha_im *= scale;
      }
    }

    acoefa = fabsf(acoeff);
    for (jr = 0; jr < 4; jr++) {
      work1[jr].re = 0.0F;
      work1[jr].im = 0.0F;
    }

    work1[3 - je].re = 1.0F;
    work1[3 - je].im = 0.0F;
    xmx = 1.1920929E-7F * (fabsf(salpha_re) + fabsf(salpha_im));
    dmin = 1.1920929E-7F * acoefa * anorm;
    if (xmx > dmin) {
      dmin = xmx;
    }

    if (1.17549435E-38F > dmin) {
      dmin = 1.17549435E-38F;
    }

    for (jr = 0; jr <= 2 - je; jr++) {
      work1[jr].re = acoeff * A[jr + ((3 - je) << 2)].re;
      work1[jr].im = acoeff * A[jr + ((3 - je) << 2)].im;
    }

    work1[3 - je].re = 1.0F;
    work1[3 - je].im = 0.0F;
    for (j = 0; j <= 2 - je; j++) {
      jc = (-je - j) + 2;
      d_re = acoeff * A[jc + (jc << 2)].re - salpha_re;
      d_im = acoeff * A[jc + (jc << 2)].im - salpha_im;
      if (fabsf(d_re) + fabsf(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0F;
      }

      if ((fabsf(d_re) + fabsf(d_im) < 1.0F) && (fabsf(work1[jc].re) + fabsf
           (work1[jc].im) >= 2.12676479E+37F * (fabsf(d_re) + fabsf(d_im)))) {
        temp = 1.0F / (fabsf(work1[jc].re) + fabsf(work1[jc].im));
        for (jr = 0; jr <= 3 - je; jr++) {
          work1[jr].re *= temp;
          work1[jr].im *= temp;
        }
      }

      work1_re = -work1[jc].re;
      if (d_im == 0.0F) {
        if (-work1[jc].im == 0.0F) {
          work1[jc].re = -work1[jc].re / d_re;
          work1[jc].im = 0.0F;
        } else if (-work1[jc].re == 0.0F) {
          work1[jc].re = 0.0F;
          work1[jc].im = -work1[jc].im / d_re;
        } else {
          work1[jc].re = -work1[jc].re / d_re;
          work1[jc].im = -work1[jc].im / d_re;
        }
      } else if (d_re == 0.0F) {
        if (-work1[jc].re == 0.0F) {
          work1[jc].re = -work1[jc].im / d_im;
          work1[jc].im = 0.0F;
        } else if (-work1[jc].im == 0.0F) {
          work1[jc].re = 0.0F;
          work1[jc].im = -(work1_re / d_im);
        } else {
          work1[jc].re = -work1[jc].im / d_im;
          work1[jc].im = -(work1_re / d_im);
        }
      } else {
        temp = fabsf(d_re);
        xmx = fabsf(d_im);
        if (temp > xmx) {
          scale = d_im / d_re;
          xmx = d_re + scale * d_im;
          work1[jc].re = (-work1[jc].re + scale * -work1[jc].im) / xmx;
          work1[jc].im = (-work1[jc].im - scale * work1_re) / xmx;
        } else if (xmx == temp) {
          if (d_re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (d_im > 0.0F) {
            xmx = 0.5F;
          } else {
            xmx = -0.5F;
          }

          work1[jc].re = (-work1[jc].re * scale + -work1[jc].im * xmx) / temp;
          work1[jc].im = (-work1[jc].im * scale - work1_re * xmx) / temp;
        } else {
          scale = d_re / d_im;
          xmx = d_im + scale * d_re;
          work1[jc].re = (scale * -work1[jc].re + -work1[jc].im) / xmx;
          work1[jc].im = (scale * -work1[jc].im - work1_re) / xmx;
        }
      }

      if (jc + 1 > 1) {
        if (fabsf(work1[jc].re) + fabsf(work1[jc].im) > 1.0F) {
          temp = 1.0F / (fabsf(work1[jc].re) + fabsf(work1[jc].im));
          if (acoefa * rworka[jc] >= 2.12676479E+37F * temp) {
            for (jr = 0; jr <= 3 - je; jr++) {
              work1[jr].re *= temp;
              work1[jr].im *= temp;
            }
          }
        }

        d_re = acoeff * work1[jc].re;
        d_im = acoeff * work1[jc].im;
        for (jr = 0; jr < jc; jr++) {
          work1[jr].re += d_re * A[jr + (jc << 2)].re - d_im * A[jr + (jc << 2)]
            .im;
          work1[jr].im += d_re * A[jr + (jc << 2)].im + d_im * A[jr + (jc << 2)]
            .re;
        }
      }
    }

    for (jr = 0; jr < 4; jr++) {
      work2[jr].re = 0.0F;
      work2[jr].im = 0.0F;
    }

    for (jc = 0; jc <= 3 - je; jc++) {
      for (jr = 0; jr < 4; jr++) {
        work2[jr].re += V[jr + (jc << 2)].re * work1[jc].re - V[jr + (jc << 2)].
          im * work1[jc].im;
        work2[jr].im += V[jr + (jc << 2)].re * work1[jc].im + V[jr + (jc << 2)].
          im * work1[jc].re;
      }
    }

    xmx = fabsf(work2[0].re) + fabsf(work2[0].im);
    for (jr = 0; jr < 3; jr++) {
      d_re = fabsf(work2[jr + 1].re) + fabsf(work2[jr + 1].im);
      if (d_re > xmx) {
        xmx = d_re;
      }
    }

    if (xmx > 1.17549435E-38F) {
      temp = 1.0F / xmx;
      for (jr = 0; jr < 4; jr++) {
        V[jr + ((3 - je) << 2)].re = temp * work2[jr].re;
        V[jr + ((3 - je) << 2)].im = temp * work2[jr].im;
      }
    } else {
      for (jr = 0; jr < 4; jr++) {
        V[jr + ((3 - je) << 2)].re = 0.0F;
        V[jr + ((3 - je) << 2)].im = 0.0F;
      }
    }
  }
}

/*
 * File trailer for xztgevc.c
 *
 * [EOF]
 */
