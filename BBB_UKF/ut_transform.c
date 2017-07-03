/*
 * File: ut_transform.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "ut_transform.h"
#include "IMU_measurement_model.h"
#include "ut_sigmas.h"
#include "ut_mweights.h"

/* Function Definitions */

/*
 * Apply defaults
 * Arguments    : const float M[18]
 *                const float P[324]
 *                const float g_param1[18]
 *                float g_param2
 *                const float tr_param[3]
 *                float mu[9]
 *                float S[81]
 *                float C[162]
 * Return Type  : void
 */
void ut_transform(const float M[18], const float P[324], const float g_param1[18],
                  float g_param2, const float tr_param[3], float mu[9], float S
                  [81], float C[162])
{
  float WM[37];
  float W[1369];
  float c;
  float X[666];
  float Y[333];
  int i;
  float b_Y[333];
  int i2;
  float b_X[666];
  int i3;
  int i4;

  /* UT_TRANSFORM  Perform unscented transform */
  /*  */
  /*  Syntax: */
  /*    [mu,S,C,X,Y,w] = UT_TRANSFORM(M,P,g,g_param,tr_param) */
  /*  */
  /*  In: */
  /*    M - Random variable mean (Nx1 column vector) */
  /*    P - Random variable covariance (NxN pos.def. matrix) */
  /*    g - Transformation function of the form g(x,param) as */
  /*        matrix, inline function, function name or function reference */
  /*    g_param - Parameters of g               (optional, default empty) */
  /*    tr_param - Parameters of the transformation as:        */
  /*        alpha = tr_param{1} - Transformation parameter      (optional) */
  /*        beta  = tr_param{2} - Transformation parameter      (optional) */
  /*        kappa = tr_param{3} - Transformation parameter      (optional) */
  /*        mat   = tr_param{4} - If 1 uses matrix form         (optional, default 0) */
  /*        X     = tr_param{5} - Sigma points of x */
  /*        w     = tr_param{6} - Weights as cell array {mean-weights,cov-weights,c} */
  /*  */
  /*  Out: */
  /*    mu - Estimated mean of y */
  /*     S - Estimated covariance of y */
  /*     C - Estimated cross-covariance of x and y */
  /*     X - Sigma points of x */
  /*     Y - Sigma points of y */
  /*     w - Weights as cell array {mean-weights,cov-weights,c} */
  /*  */
  /*  Description: */
  /*    ... */
  /*    For default values of parameters, see UT_WEIGHTS. */
  /*  */
  /*  See also */
  /*    UT_WEIGHTS UT_MWEIGHTS UT_SIGMAS */
  /*  Copyright (C) 2006 Simo S�rkk� */
  /*                2010 Jouni Hartikainen */
  /*  */
  /*  $Id: ut_transform.m 482 2010-10-18 07:53:23Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public  */
  /*  Licence (version 2 or later); please refer to the file  */
  /*  Licence.txt, included with the software, for details. */
  /*  */
  /*  Calculate sigma points */
  /*  */
  ut_mweights(tr_param[0], tr_param[1], tr_param[2], WM, W, &c);
  ut_sigmas(M, P, c, X);

  /*  */
  /*  Propagate through the function */
  /*  */
  for (i = 0; i < 37; i++) {
    IMU_measurement_model(*(float (*)[18])&X[18 * i], g_param1, g_param2,
                          *(float (*)[9])&Y[9 * i]);
  }

  for (i2 = 0; i2 < 9; i2++) {
    mu[i2] = 0.0F;
    for (i3 = 0; i3 < 37; i3++) {
      mu[i2] += Y[i2 + 9 * i3] * WM[i3];
      b_Y[i2 + 9 * i3] = 0.0F;
      for (i4 = 0; i4 < 37; i4++) {
        b_Y[i2 + 9 * i3] += Y[i2 + 9 * i4] * W[i4 + 37 * i3];
      }
    }

    for (i3 = 0; i3 < 9; i3++) {
      S[i2 + 9 * i3] = 0.0F;
      for (i4 = 0; i4 < 37; i4++) {
        S[i2 + 9 * i3] += b_Y[i2 + 9 * i4] * Y[i3 + 9 * i4];
      }
    }
  }

  for (i2 = 0; i2 < 18; i2++) {
    for (i3 = 0; i3 < 37; i3++) {
      b_X[i2 + 18 * i3] = 0.0F;
      for (i4 = 0; i4 < 37; i4++) {
        b_X[i2 + 18 * i3] += X[i2 + 18 * i4] * W[i4 + 37 * i3];
      }
    }

    for (i3 = 0; i3 < 9; i3++) {
      C[i2 + 18 * i3] = 0.0F;
      for (i4 = 0; i4 < 37; i4++) {
        C[i2 + 18 * i3] += b_X[i2 + 18 * i4] * Y[i3 + 9 * i4];
      }
    }
  }
}

/*
 * File trailer for ut_transform.c
 *
 * [EOF]
 */
