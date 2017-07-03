/*
 * File: UKF_C.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "ut_transform.h"
#include "ukf_predict1.h"

/* Function Definitions */

/*
 * % demo day college tour data Ts
 * Arguments    : const float observation[18]
 *                const float pre_state[18]
 *                const float pre_cov[324]
 *                float state[18]
 *                float cov[324]
 *                float k[162]
 *                float MU[9]
 *                float S[81]
 *                float e[9]
 * Return Type  : void
 */
void UKF_C(const float observation[18], const float pre_state[18], const float
           pre_cov[324], float state[18], float cov[324], float k[162], float
           MU[9], float S[81], float e[9])
{
  float M[18];
  float P[324];
  static const float tr_param[3] = { 0.3F, 2.0F, 0.0F };

  float A[81];
  int b_k;
  signed char ipiv[9];
  float b_S;
  static const float fv0[81] = { 0.962361157F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.962361157F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.962361157F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.09F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.09F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.09F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F,
    0.0F, 0.0F, 0.0F, 0.0F, 0.09F };

  int j;
  int c;
  int kBcol;
  int jp;
  int ix;
  int jAcol;
  float temp;
  float b_observation[9];
  int i;
  float s;
  float c_k[162];

  /* % demo day measurements noise */
  /* % demo day process noise init */
  /*  in radian */
  /* % weighted sigma points parameters */
  /* % UKF */
  memcpy(&M[0], &pre_state[0], 18U * sizeof(float));
  memcpy(&P[0], &pre_cov[0], 324U * sizeof(float));
  ukf_predict1(M, P, *(float (*)[9])&observation[0], 0.3F, 2.0F, 0.0F);

  /*  */
  /*  Do transform and make the update */
  /*  */
  /* UKF_UPDATE1 -  Additive form Unscented Kalman Filter update step */
  /*  */
  /*  Syntax: */
  /*    [M,P,K,MU,S,LH] = UKF_UPDATE1(M,P,Y,h,R,h_param,alpha,beta,kappa,mat) */
  /*  */
  /*  In: */
  /*    M  - Mean state estimate after prediction step */
  /*    P  - State covariance after prediction step */
  /*    Y  - Measurement vector. */
  /*    h  - Measurement model function as a matrix H defining */
  /*         linear function h(x) = H*x, inline function, */
  /*         function handle or name of function in */
  /*         form h(x,param) */
  /*    R  - Measurement covariance. */
  /*    h_param - Parameters of h               (optional, default empty) */
  /*    alpha - Transformation parameter      (optional) */
  /*    beta  - Transformation parameter      (optional) */
  /*    kappa - Transformation parameter      (optional) */
  /*    mat   - If 1 uses matrix form         (optional, default 0) */
  /*  */
  /*  Out: */
  /*    M  - Updated state mean */
  /*    P  - Updated state covariance */
  /*    K  - Computed Kalman gain */
  /*    MU - Predictive mean of Y */
  /*    S  - Predictive covariance Y */
  /*    LH - Predictive probability (likelihood) of measurement. */
  /*     */
  /*  Description: */
  /*    Perform additive form Discrete Unscented Kalman Filter (UKF) */
  /*    measurement update step. Assumes additive measurement */
  /*    noise. */
  /*  */
  /*    Function h should be such that it can be given */
  /*    DxN matrix of N sigma Dx1 points and it returns  */
  /*    the corresponding measurements for each sigma */
  /*    point. This function should also make sure that */
  /*    the returned sigma points are compatible such that */
  /*    there are no 2pi jumps in angles etc. */
  /*  */
  /*  Example: */
  /*    h = inline('atan2(x(2,:)-s(2),x(1,:)-s(1))','x','s'); */
  /*    [M2,P2] = ukf_update(M1,P1,Y,h,R,S); */
  /*  */
  /*  See also: */
  /*    UKF_PREDICT1, UKF_PREDICT2, UKF_UPDATE2, UKF_PREDICT3, UKF_UPDATE3, */
  /*    UT_TRANSFORM, UT_WEIGHTS, UT_MWEIGHTS, UT_SIGMAS */
  /*  */
  /*  History: */
  /*    08.02.2008 JH Fixed a typo in the syntax description.  */
  /*    04.05.2007 JH Made corrections to the description. */
  /*    02.05.2007 JH Fixed a bug in likelihood calculation and added */
  /*               a "See also"-section.  */
  /*    2002-2006  SS Initial version */
  /*     */
  /*   */
  /*  References: */
  /*    [1] Wan, Merwe: The Unscented Kalman Filter */
  /*  Copyright (C) 2002-2006 Simo S�rkk� */
  /*  */
  /*  $Id: ukf_update1.m 480 2010-10-18 07:45:48Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public  */
  /*  Licence (version 2 or later); please refer to the file  */
  /*  Licence.txt, included with the software, for details. */
  ut_transform(M, P, M, 0.07F, tr_param, MU, S, k);
  for (b_k = 0; b_k < 81; b_k++) {
    b_S = S[b_k] + fv0[b_k];
    A[b_k] = b_S;
    S[b_k] = b_S;
  }

  for (b_k = 0; b_k < 9; b_k++) {
    ipiv[b_k] = (signed char)(1 + b_k);
  }

  for (j = 0; j < 8; j++) {
    c = j * 10;
    kBcol = 0;
    ix = c;
    temp = fabsf(A[c]);
    for (b_k = 2; b_k <= 9 - j; b_k++) {
      ix++;
      s = fabsf(A[ix]);
      if (s > temp) {
        kBcol = b_k - 1;
        temp = s;
      }
    }

    if (A[c + kBcol] != 0.0F) {
      if (kBcol != 0) {
        ipiv[j] = (signed char)((j + kBcol) + 1);
        ix = j;
        kBcol += j;
        for (b_k = 0; b_k < 9; b_k++) {
          temp = A[ix];
          A[ix] = A[kBcol];
          A[kBcol] = temp;
          ix += 9;
          kBcol += 9;
        }
      }

      b_k = (c - j) + 9;
      for (i = c + 1; i + 1 <= b_k; i++) {
        A[i] /= A[c];
      }
    }

    jp = c;
    jAcol = c + 9;
    for (kBcol = 1; kBcol <= 8 - j; kBcol++) {
      temp = A[jAcol];
      if (A[jAcol] != 0.0F) {
        ix = c + 1;
        b_k = (jp - j) + 18;
        for (i = 10 + jp; i + 1 <= b_k; i++) {
          A[i] += A[ix] * -temp;
          ix++;
        }
      }

      jAcol += 9;
      jp += 9;
    }
  }

  for (j = 0; j < 9; j++) {
    jp = 18 * j;
    jAcol = 9 * j;
    for (b_k = 1; b_k <= j; b_k++) {
      kBcol = 18 * (b_k - 1);
      if (A[(b_k + jAcol) - 1] != 0.0F) {
        for (i = 0; i < 18; i++) {
          k[i + jp] -= A[(b_k + jAcol) - 1] * k[i + kBcol];
        }
      }
    }

    temp = 1.0F / A[j + jAcol];
    for (i = 0; i < 18; i++) {
      k[i + jp] *= temp;
    }
  }

  for (j = 8; j >= 0; j += -1) {
    jp = 18 * j;
    jAcol = 9 * j - 1;
    for (b_k = j + 2; b_k < 10; b_k++) {
      kBcol = 18 * (b_k - 1);
      if (A[b_k + jAcol] != 0.0F) {
        for (i = 0; i < 18; i++) {
          k[i + jp] -= A[b_k + jAcol] * k[i + kBcol];
        }
      }
    }
  }

  for (kBcol = 7; kBcol >= 0; kBcol += -1) {
    if (ipiv[kBcol] != kBcol + 1) {
      jp = ipiv[kBcol] - 1;
      for (jAcol = 0; jAcol < 18; jAcol++) {
        temp = k[jAcol + 18 * kBcol];
        k[jAcol + 18 * kBcol] = k[jAcol + 18 * jp];
        k[jAcol + 18 * jp] = temp;
      }
    }
  }

  /*    LH = gauss_pdf(Y,MU,S); */
  for (b_k = 0; b_k < 9; b_k++) {
    b_observation[b_k] = observation[9 + b_k] - MU[b_k];
  }

  for (b_k = 0; b_k < 18; b_k++) {
    temp = 0.0F;
    for (kBcol = 0; kBcol < 9; kBcol++) {
      temp += k[b_k + 18 * kBcol] * b_observation[kBcol];
      c_k[b_k + 18 * kBcol] = 0.0F;
      for (jp = 0; jp < 9; jp++) {
        c_k[b_k + 18 * kBcol] += k[b_k + 18 * jp] * S[jp + 9 * kBcol];
      }
    }

    state[b_k] = M[b_k] + temp;
    for (kBcol = 0; kBcol < 18; kBcol++) {
      temp = 0.0F;
      for (jp = 0; jp < 9; jp++) {
        temp += c_k[b_k + 18 * jp] * k[kBcol + 18 * jp];
      }

      cov[b_k + 18 * kBcol] = P[b_k + 18 * kBcol] - temp;
    }
  }

  for (b_k = 0; b_k < 9; b_k++) {
    e[b_k] = observation[9 + b_k] - MU[b_k];
  }
}

/*
 * File trailer for UKF_C.c
 *
 * [EOF]
 */
