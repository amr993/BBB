/*
 * File: ut_mweights.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "ut_mweights.h"

/* Function Definitions */

/*
 * Check which arguments are there
 * Arguments    : float alpha
 *                float beta
 *                float kappa
 *                float WM[37]
 *                float W[1369]
 *                float *c
 * Return Type  : void
 */
void ut_mweights(float alpha, float beta, float kappa, float WM[37], float W
                 [1369], float *c)
{
  float WC[37];
  int j;
  float wm;
  int jtilecol;
  float wc;
  float d[1369];
  int ibtile;
  static const signed char iv0[1369] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1 };

  float b_W[1369];
  float c_W[1369];
  int i0;

  /* UT_MWEIGHTS - Generate matrix form unscented transformation weights */
  /*  */
  /*  Syntax: */
  /*    [WM,W,c] = ut_mweights(n,alpha,beta,kappa) */
  /*  */
  /*  In: */
  /*    n     - Dimensionality of random variable */
  /*    alpha - Transformation parameter  (optional, default 0.5) */
  /*    beta  - Transformation parameter  (optional, default 2) */
  /*    kappa - Transformation parameter  (optional, default 3-size(X,1)) */
  /*  */
  /*  Out: */
  /*    WM - Weight vector for mean calculation */
  /*     W - Weight matrix for covariance calculation */
  /*     c - Scaling constant */
  /*  */
  /*  Description: */
  /*    Computes matrix form unscented transformation weights. */
  /*  */
  /*  Copyright (C) 2006 Simo Särkkä */
  /*  */
  /*  $Id: ut_mweights.m 109 2007-09-04 08:32:58Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public  */
  /*  Licence (version 2 or later); please refer to the file  */
  /*  Licence.txt, included with the software, for details. */
  /*  */
  /*  Check which arguments are there */
  /*  */
  /* UT_WEIGHTS - Generate unscented transformation weights */
  /*  */
  /*  Syntax: */
  /*    [WM,WC,c] = ut_weights(n,alpha,beta,kappa) */
  /*  */
  /*  In: */
  /*    n     - Dimensionality of random variable */
  /*    alpha - Transformation parameter  (optional, default 0.5) */
  /*    beta  - Transformation parameter  (optional, default 2) */
  /*    kappa - Transformation parameter  (optional, default 3-n) */
  /*  */
  /*  Out: */
  /*    WM - Weights for mean calculation */
  /*    WC - Weights for covariance calculation */
  /*     c - Scaling constant */
  /*  */
  /*  Description: */
  /*    Computes unscented transformation weights. */
  /*  */
  /*  See also UT_MWEIGHTS UT_TRANSFORM UT_SIGMAS */
  /*   */
  /*  Copyright (C) 2006 Simo Sï¿½rkkï¿½ */
  /*  */
  /*  $Id: ut_weights.m 467 2010-10-12 09:30:14Z jmjharti $ */
  /*  */
  /*  This software is distributed under the GNU General Public  */
  /*  Licence (version 2 or later); please refer to the file  */
  /*  Licence.txt, included with the software, for details. */
  /*  */
  /*  Apply default values */
  /*  */
  /*  */
  /*  Compute the normal weights  */
  /*  */
  *c = alpha * alpha * (18.0F + kappa);
  for (j = 0; j < 37; j++) {
    if (1 + j == 1) {
      wm = (*c - 18.0F) / (18.0F + (*c - 18.0F));
      wc = (*c - 18.0F) / (18.0F + (*c - 18.0F)) + ((1.0F - alpha * alpha) +
        beta);
    } else {
      wm = 1.0F / (2.0F * (18.0F + (*c - 18.0F)));
      wc = wm;
    }

    WM[j] = wm;
    WC[j] = wc;
  }

  *c = 18.0F + (*c - 18.0F);
  for (jtilecol = 0; jtilecol < 37; jtilecol++) {
    ibtile = jtilecol * 37;
    memcpy(&W[ibtile], &WM[0], 37U * sizeof(float));
  }

  for (jtilecol = 0; jtilecol < 1369; jtilecol++) {
    d[jtilecol] = 0.0F;
    W[jtilecol] = (float)iv0[jtilecol] - W[jtilecol];
  }

  for (j = 0; j < 37; j++) {
    d[j + 37 * j] = WC[j];
  }

  for (jtilecol = 0; jtilecol < 37; jtilecol++) {
    for (ibtile = 0; ibtile < 37; ibtile++) {
      b_W[jtilecol + 37 * ibtile] = 0.0F;
      for (i0 = 0; i0 < 37; i0++) {
        b_W[jtilecol + 37 * ibtile] += W[jtilecol + 37 * i0] * d[i0 + 37 *
          ibtile];
      }
    }

    for (ibtile = 0; ibtile < 37; ibtile++) {
      c_W[jtilecol + 37 * ibtile] = 0.0F;
      for (i0 = 0; i0 < 37; i0++) {
        c_W[jtilecol + 37 * ibtile] += b_W[jtilecol + 37 * i0] * W[ibtile + 37 *
          i0];
      }
    }
  }

  for (jtilecol = 0; jtilecol < 37; jtilecol++) {
    memcpy(&W[jtilecol * 37], &c_W[jtilecol * 37], 37U * sizeof(float));
  }
}

/*
 * File trailer for ut_mweights.c
 *
 * [EOF]
 */
