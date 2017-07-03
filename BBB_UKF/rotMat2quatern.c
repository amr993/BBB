/*
 * File: rotMat2quatern.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "rotMat2quatern.h"
#include "xzggev.h"

/* Function Definitions */

/*
 * ROTMAT2QUATERN Converts a rotation matrix orientation to a quaternion
 *
 *    q = axisAngle2quatern(axis, angle)
 *
 *    Converts a rotation matrix orientation to a quaternion.
 *
 *    For more information see:
 *    http://www.x-io.co.uk/node/8#quaternions
 *
 *  Date          Author          Notes
 *  27/09/2011    SOH Madgwick    Initial release
 * Arguments    : const float R[9]
 *                float q[4]
 * Return Type  : void
 */
void rotMat2quatern(const float R[9], float q[4])
{
  float K[16];
  creal32_T At[16];
  int info;
  creal32_T alpha1[4];
  creal32_T beta1[4];
  creal32_T V[16];
  int coltop;
  float colnorm;
  float scale;
  float fcnOutput[4];
  float absxk;
  float t;
  K[0] = 0.333333343F * ((R[0] - R[4]) - R[8]);
  K[4] = 0.333333343F * (R[1] + R[3]);
  K[8] = 0.333333343F * (R[2] + R[6]);
  K[12] = 0.333333343F * (R[7] - R[5]);
  K[1] = 0.333333343F * (R[1] + R[3]);
  K[5] = 0.333333343F * ((R[4] - R[0]) - R[8]);
  K[9] = 0.333333343F * (R[5] + R[7]);
  K[13] = 0.333333343F * (R[2] - R[6]);
  K[2] = 0.333333343F * (R[2] + R[6]);
  K[6] = 0.333333343F * (R[5] + R[7]);
  K[10] = 0.333333343F * ((R[8] - R[0]) - R[4]);
  K[14] = 0.333333343F * (R[3] - R[1]);
  K[3] = 0.333333343F * (R[7] - R[5]);
  K[7] = 0.333333343F * (R[2] - R[6]);
  K[11] = 0.333333343F * (R[3] - R[1]);
  K[15] = 0.333333343F * ((R[0] + R[4]) + R[8]);
  for (info = 0; info < 16; info++) {
    At[info].re = K[info];
    At[info].im = 0.0F;
  }

  xzggev(At, &info, alpha1, beta1, V);
  for (coltop = 0; coltop <= 13; coltop += 4) {
    colnorm = 0.0F;
    scale = 1.17549435E-38F;
    for (info = coltop; info + 1 <= coltop + 4; info++) {
      absxk = fabsf(V[info].re);
      if (absxk > scale) {
        t = scale / absxk;
        colnorm = 1.0F + colnorm * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        colnorm += t * t;
      }

      absxk = fabsf(V[info].im);
      if (absxk > scale) {
        t = scale / absxk;
        colnorm = 1.0F + colnorm * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        colnorm += t * t;
      }
    }

    colnorm = scale * sqrtf(colnorm);
    for (info = coltop; info + 1 <= coltop + 4; info++) {
      if (V[info].im == 0.0F) {
        V[info].re /= colnorm;
        V[info].im = 0.0F;
      } else if (V[info].re == 0.0F) {
        V[info].re = 0.0F;
        V[info].im /= colnorm;
      } else {
        V[info].re /= colnorm;
        V[info].im /= colnorm;
      }
    }
  }

  /* p = find(max(D)); */
  /* q = V(:,p)'; */
  for (info = 0; info < 4; info++) {
    fcnOutput[info] = V[12 + info].re;
  }

  q[0] = fcnOutput[3];
  q[1] = fcnOutput[0];
  q[2] = fcnOutput[1];
  q[3] = fcnOutput[2];
}

/*
 * File trailer for rotMat2quatern.c
 *
 * [EOF]
 */
