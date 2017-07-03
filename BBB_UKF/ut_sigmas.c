/*
 * File: ut_sigmas.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "ut_sigmas.h"

/* Function Definitions */

/*
 * size(P)
 * Arguments    : const float M[18]
 *                const float P[324]
 *                float c
 *                float X[666]
 * Return Type  : void
 */
void ut_sigmas(const float M[18], const float P[324], float c, float X[666])
{
  float A[324];
  int i;
  int j;
  float x;
  float b[666];
  int jtilecol;
  float s;
  int k;
  float fv1[666];
  int ibtile;

  /* UT_SIGMAS - Generate Sigma Points for Unscented Transformation */
  /*  */
  /*  Syntax: */
  /*    X = ut_sigmas(M,P,c); */
  /*  */
  /*  In: */
  /*    M - Initial state mean (Nx1 column vector) */
  /*    P - Initial state covariance */
  /*    c - Parameter returned by UT_WEIGHTS */
  /*  */
  /*  Out: */
  /*    X - Matrix where 2N+1 sigma points are as columns */
  /*  */
  /*  Description: */
  /*    Generates sigma points and associated weights for Gaussian */
  /*    initial distribution N(M,P). For default values of parameters */
  /*    alpha, beta and kappa see UT_WEIGHTS. */
  /*  */
  /*  See also UT_WEIGHTS UT_TRANSFORM UT_SIGMAS */
  /*  */
  /*  Copyright (C) 2006 Simo Särkkä */
  /*  */
  /*  $Id: ut_sigmas.m 109 2007-09-04 08:32:58Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public */
  /*  Licence (version 2 or later); please refer to the file */
  /*  Licence.txt, included with the software, for details. */
  /* SCHOL  Cholesky factorization for positive semidefinite matrices */
  /*  */
  /*  Syntax: */
  /*    [L,def] = schol(A) */
  /*  */
  /*  In: */
  /*    A - Symmetric pos.semi.def matrix to be factorized */
  /*  */
  /*  Out: */
  /*    L   - Lower triangular matrix such that A=L*L' if def>=0. */
  /*    def - Value 1,0,-1 denoting that A was positive definite, */
  /*          positive semidefinite or negative definite, respectively. */
  /*  */
  /*  Description: */
  /*    Compute lower triangular Cholesky factor L of symmetric positive */
  /*    semidefinite matrix A such that */
  /*  */
  /*      A = L*L' */
  /*  */
  /*  See also */
  /*    CHOL */
  /*  Copyright (C) 2006 Simo Särkkä */
  /*  */
  /*  $Id: schol.m 111 2007-09-04 12:09:23Z ssarkka $ */
  /*  */
  /*  This software is distributed under the GNU General Public  */
  /*  Licence (version 2 or later); please refer to the file  */
  /*  Licence.txt, included with the software, for details. */
  memset(&A[0], 0, 324U * sizeof(float));
  for (i = 0; i < 18; i++) {
    for (j = 0; j <= i; j++) {
      s = P[i + 18 * j];
      for (k = 0; k < j; k++) {
        s -= A[i + 18 * k] * A[j + 18 * k];
      }

      if (1 + j < 1 + i) {
        if (A[j + 18 * j] > 2.22044605E-16F) {
          A[i + 18 * j] = s / A[j + 18 * j];
        } else {
          A[i + 18 * j] = 0.0F;
        }
      } else {
        if (s < -2.22044605E-16F) {
          s = 0.0F;
        } else {
          if (s < 2.22044605E-16F) {
            s = 0.0F;
          }
        }

        A[j + 18 * j] = sqrtf(s);
      }
    }
  }

  /*   A = chol(P)'; */
  x = sqrtf(c);
  for (jtilecol = 0; jtilecol < 37; jtilecol++) {
    ibtile = jtilecol * 18;
    memcpy(&b[ibtile], &M[0], 18U * sizeof(float));
  }

  for (jtilecol = 0; jtilecol < 18; jtilecol++) {
    fv1[jtilecol] = 0.0F;
    for (ibtile = 0; ibtile < 18; ibtile++) {
      fv1[ibtile + 18 * (jtilecol + 1)] = A[ibtile + 18 * jtilecol];
      fv1[ibtile + 18 * (jtilecol + 19)] = -A[ibtile + 18 * jtilecol];
    }
  }

  for (jtilecol = 0; jtilecol < 37; jtilecol++) {
    for (ibtile = 0; ibtile < 18; ibtile++) {
      X[ibtile + 18 * jtilecol] = x * fv1[ibtile + 18 * jtilecol] + b[ibtile +
        18 * jtilecol];
    }
  }
}

/*
 * File trailer for ut_sigmas.c
 *
 * [EOF]
 */
