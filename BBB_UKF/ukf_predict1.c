/*
 * File: ukf_predict1.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "ukf_predict1.h"
#include "IMU_process_model.h"
#include "ut_sigmas.h"
#include "ut_mweights.h"

/* Function Definitions */

/*
 * Do transform
 *  and add process noise
 * Arguments    : float M[18]
 *                float P[324]
 *                const float f_param1[9]
 *                float alpha
 *                float beta
 *                float kappa
 * Return Type  : void
 */
void ukf_predict1(float M[18], float P[324], const float f_param1[9], float
                  alpha, float beta, float kappa)
{
  float WM[37];
  float W[1369];
  float c;
  float X[666];
  float Y[666];
  int i;
  float b_Y[666];
  int i7;
  int i8;
  float f0;
  int i9;

  /* UKF_PREDICT1  Nonaugmented (Additive) UKF prediction step */
  /*  */
  /*  Syntax: */
  /*    [M,P] = UKF_PREDICT1(M,P,f,Q,f_param,alpha,beta,kappa,mat) */
  /*  */
  /*  In: */
  /*    M - Nx1 mean state estimate of previous step */
  /*    P - NxN state covariance of previous step */
  /*    f - Dynamic model function as a matrix A defining */
  /*        linear function a(x) = A*x, inline function, */
  /*        function handle or name of function in */
  /*        form a(x,param)                   (optional, default eye()) */
  /*    Q - Process noise of discrete model   (optional, default zero) */
  /*    f_param - Parameters of f               (optional, default empty) */
  /*    alpha - Transformation parameter      (optional) */
  /*    beta  - Transformation parameter      (optional) */
  /*    kappa - Transformation parameter      (optional) */
  /*    mat   - If 1 uses matrix form         (optional, default 0) */
  /*  */
  /*  Out: */
  /*    M - Updated state mean */
  /*    P - Updated state covariance */
  /*  */
  /*  Description: */
  /*    Perform additive form Unscented Kalman Filter prediction step. */
  /*  */
  /*    Function a should be such that it can be given */
  /*    DxN matrix of N sigma Dx1 points and it returns  */
  /*    the corresponding predictions for each sigma */
  /*    point.  */
  /*  */
  /*  See also: */
  /*    UKF_UPDATE1, UKF_PREDICT2, UKF_UPDATE2, UKF_PREDICT3, UKF_UPDATE3, */
  /*    UT_TRANSFORM, UT_WEIGHTS, UT_MWEIGHTS, UT_SIGMAS */
  /*  Copyright (C) 2003-2006 Simo S�rkk� */
  /*  */
  /*  $Id: ukf_predict1.m 483 2010-10-18 08:54:19Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public */
  /*  Licence (version 2 or later); please refer to the file */
  /*  Licence.txt, included with the software, for details. */
  /*  */
  /*  Apply defaults */
  /*  */
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
  ut_mweights(alpha, beta, kappa, WM, W, &c);
  ut_sigmas(M, P, c, X);

  /*  */
  /*  Propagate through the function */
  /*  */
  for (i = 0; i < 37; i++) {
    IMU_process_model(*(float (*)[18])&X[18 * i], f_param1, *(float (*)[18])&Y
                      [18 * i]);
  }

  for (i7 = 0; i7 < 18; i7++) {
    M[i7] = 0.0F;
    for (i8 = 0; i8 < 37; i8++) {
      M[i7] += Y[i7 + 18 * i8] * WM[i8];
      b_Y[i7 + 18 * i8] = 0.0F;
      for (i9 = 0; i9 < 37; i9++) {
        b_Y[i7 + 18 * i8] += Y[i7 + 18 * i9] * W[i9 + 37 * i8];
      }
    }

    for (i8 = 0; i8 < 18; i8++) {
      f0 = 0.0F;
      for (i9 = 0; i9 < 37; i9++) {
        f0 += b_Y[i7 + 18 * i9] * Y[i8 + 18 * i9];
      }

      P[i7 + 18 * i8] = f0;
    }
  }
}

/*
 * File trailer for ukf_predict1.c
 *
 * [EOF]
 */
