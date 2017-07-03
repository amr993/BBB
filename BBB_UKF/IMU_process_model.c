/*
 * File: IMU_process_model.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "IMU_process_model.h"
#include "rotMat2quatern.h"

/* Function Definitions */

/*
 * this PROCESS MODEL is a 9DOF IMU process model it updates a state vector
 *  of
 *            1) Px : Position in X axis
 *            2) Py : Position in Y axis
 *            3) Pz : Position in Z axis
 *            4) Vx : Velocity in X axis
 *            5) Vy : Velocity in Y axis
 *            6) Vz : Velocity in Z axis
 *            7) roll : rotation angle around X axis
 *            8) pitch: rotation angle around Y axis
 *            9) yaw  : rotation angle around Z axis
 *            10) bias_ax : bias in Accelerometer acceleration in X axis
 *            11) bias_ay : bias in Accelerometer acceleration in Y axis
 *            12) bias_az : bias in Accelerometer acceleration in Z axis
 *            13) bias_wx : bias in Gyroscope angular velocity in X axis
 *            14) bias_wy : bias in Gyroscope angular velocity in Y axis
 *            15) bias_wz : bias in Gyroscope angular velocity in Z axis
 *            16) bias_mx : bias in Magnetometer magnetic field stregth in X axis
 *            17) bias_my : bias in Magnetometer magnetic field stregth in Y axis
 *            18) bias_mz : bias in Magnetometer magnetic field stregth in Z axis
 *
 *  Examples of usage :
 *  IMU Scenario :
 *
 *    process_model(current_state,measurement,Ts,noise,'IMU');
 *
 *    current_state : a vector containing 18 elements
 *                    3 position, 3 velocity, 3 attitude, 3 accelerometer
 *                    biases, 3 Gyroscope biases, 3 Magnetometer Biases
 *    observation : a vector containing 9 elements
 *                  3 accelerometer readings, 3 gyroscope readings,
 *                  3 magnetometer readings
 *    Ts : sampling frequency
 * Arguments    : const float state[18]
 *                const float observation[9]
 *                float updated_state[18]
 * Return Type  : void
 */
void IMU_process_model(const float state[18], const float observation[9], float
  updated_state[18])
{
  float R[9];
  float q[4];
  int k;
  float b[4];
  float ab[4];
  float y;
  float scale;
  float b_q;
  float absxk;
  float t;
  float R_idx_2;
  float b_R[9];
  float b_observation[3];
  float c_R[3];
  float b_state[3];
  int i;

  /* %%%%%%%%%%%%%%%%%% */
  /*  Initializations % */
  /* %%%%%%%%%%%%%%%%%% */
  /*  Position in x, y and z */
  /*  Velocity in x, y and z */
  /*  bias in acceleration */
  /*  bias in angular velocity */
  /*  bias in magnetic field strengths */
  /*  rate of change of bias in acceleration */
  /*  rate of change of bias in angular velocity */
  /*  gravity vector in the NED Frame */
  /*  initialize the updated state vector to zeros */
  memset(&updated_state[0], 0, 18U * sizeof(float));

  /*  acceleration in x, y and z */
  /*  angular velocity in x, y and z */
  /* %%%%%%%%%%%%%%%%%% */
  /*  update attitude % */
  /* %%%%%%%%%%%%%%%%%% */
  /*  previous quaternion from previous euler angles */
  /* EULER2ROTMAT Converts a ZYX Euler angle orientation to a rotation matrix */
  /*  */
  /*    q = euler2rotMat(axis, angle) */
  /*  */
  /*    Converts ZYX Euler angle orientation to a rotation matrix where phi is */
  /*    a rotation around X, theta around Y and psi around Z. */
  /*  */
  /*    For more information see: */
  /*    http://www.x-io.co.uk/node/8#quaternions */
  /*  */
  /* 	Date          Author          Notes */
  /* 	27/09/2011    SOH Madgwick    Initial release */
  R[0] = cosf(state[8]) * cosf(state[7]);
  R[3] = -sinf(state[8]) * cosf(state[6]) + cosf(state[8]) * sinf(state[7]) *
    sinf(state[6]);
  R[6] = sinf(state[8]) * sinf(state[6]) + cosf(state[8]) * sinf(state[7]) *
    cosf(state[6]);
  R[1] = sinf(state[8]) * cosf(state[7]);
  R[4] = cosf(state[8]) * cosf(state[6]) + sinf(state[8]) * sinf(state[7]) *
    sinf(state[6]);
  R[7] = -cosf(state[8]) * sinf(state[6]) + sinf(state[8]) * sinf(state[7]) *
    cosf(state[6]);
  R[2] = -sinf(state[7]);
  R[5] = cosf(state[7]) * sinf(state[6]);
  R[8] = cosf(state[7]) * cosf(state[6]);
  rotMat2quatern(R, q);

  /*  Compute rate of change of quaternion */
  for (k = 0; k < 3; k++) {
    b[k + 1] = observation[3 + k] - state[12 + k];
  }

  /* QUATERNPROD Calculates the quaternion product */
  /*  */
  /*    ab = quaternProd(a, b) */
  /*  */
  /*    Calculates the quaternion product of quaternion a and b. */
  /*  */
  /*    For more information see: */
  /*    http://www.x-io.co.uk/node/8#quaternions */
  /*  */
  /* 	Date          Author          Notes */
  /* 	27/09/2011    SOH Madgwick    Initial release */
  ab[0] = ((0.0F - q[1] * b[1]) - q[2] * b[2]) - q[3] * b[3];
  ab[1] = (q[0] * b[1] + q[2] * b[3]) - q[3] * b[2];
  ab[2] = (q[0] * b[2] - q[1] * b[3]) + q[3] * b[1];
  ab[3] = (q[0] * b[3] + q[1] * b[2]) - q[2] * b[1];

  /*  Integrate to yield quaternion */
  /*  normalize the quaternion */
  y = 0.0F;
  scale = 1.17549435E-38F;
  for (k = 0; k < 4; k++) {
    b_q = q[k] + 0.07F * (0.5F * ab[k]);
    absxk = fabsf(b_q);
    if (absxk > scale) {
      t = scale / absxk;
      y = 1.0F + y * t * t;
      scale = absxk;
    } else {
      t = absxk / scale;
      y += t * t;
    }

    q[k] = b_q;
  }

  y = scale * sqrtf(y);
  for (k = 0; k < 4; k++) {
    q[k] /= y;
  }

  /*  update euler angles in Body frame */
  /* QUATERN2EULER Converts a quaternion orientation to ZYX Euler angles */
  /*  */
  /*    q = quatern2euler(q) */
  /*  */
  /*    Converts a quaternion orientation to ZYX Euler angles where phi is a */
  /*    rotation around X, theta around Y and psi around Z. */
  /*  */
  /*    For more information see: */
  /*    http://www.x-io.co.uk/node/8#quaternions */
  /*  */
  /* 	Date          Author          Notes */
  /* 	27/09/2011    SOH Madgwick    Initial release */
  R_idx_2 = 2.0F * (q[1] * q[3] + q[0] * q[2]);
  updated_state[6] = atan2f(2.0F * (q[2] * q[3] - q[0] * q[1]), (2.0F * (q[0] *
    q[0]) - 1.0F) + 2.0F * (q[3] * q[3]));
  updated_state[7] = -atanf(R_idx_2 / sqrtf(1.0F - R_idx_2 * R_idx_2));
  updated_state[8] = atan2f(2.0F * (q[1] * q[2] - q[0] * q[3]), (2.0F * (q[0] *
    q[0]) - 1.0F) + 2.0F * (q[1] * q[1]));

  /* %%%%%%%%%%%%%%%%%% */
  /*  update velocity % */
  /* %%%%%%%%%%%%%%%%%% */
  /*  updated rotation matrix (from body to NED Frame) */
  /*      R = body2ned_rotMat(quaternConj(q)); */
  /* QUATERN2ROTMAT Converts a quaternion orientation to a rotation matrix */
  /*  */
  /*    R = quatern2rotMat(q) */
  /*  */
  /*    Converts a quaternion orientation to a rotation matrix. */
  /*  */
  /*    For more information see: */
  /*    http://www.x-io.co.uk/node/8#quaternions */
  /*  */
  /* 	Date          Author          Notes */
  /* 	27/09/2011    SOH Madgwick    Initial release */
  b_R[0] = (2.0F * (q[0] * q[0]) - 1.0F) + 2.0F * (q[1] * q[1]);
  b_R[3] = 2.0F * (q[1] * q[2] + q[0] * q[3]);
  b_R[6] = 2.0F * (q[1] * q[3] - q[0] * q[2]);
  b_R[1] = 2.0F * (q[1] * q[2] - q[0] * q[3]);
  b_R[4] = (2.0F * (q[0] * q[0]) - 1.0F) + 2.0F * (q[2] * q[2]);
  b_R[7] = 2.0F * (q[2] * q[3] + q[0] * q[1]);
  b_R[2] = 2.0F * (q[1] * q[3] + q[0] * q[2]);
  b_R[5] = 2.0F * (q[2] * q[3] - q[0] * q[1]);
  b_R[8] = (2.0F * (q[0] * q[0]) - 1.0F) + 2.0F * (q[3] * q[3]);

  /*  update velocity in the NED Frame using integration and updated */
  /*  rotation matrix from body to NED frame */
  for (k = 0; k < 3; k++) {
    b_observation[k] = observation[k] - state[9 + k];
  }

  /* %%%%%%%%%%%%%%%%%% */
  /*  update position % */
  /* %%%%%%%%%%%%%%%%%% */
  /*  updated position in the NED Frame using trapezoidal integration */
  /* %%%%%%%%%%%%%% */
  /*  update bias % */
  /* %%%%%%%%%%%%%% */
  /*  update biases using rate of change in Accelerometer and Gyroscope bias */
  for (i = 0; i < 3; i++) {
    c_R[i] = 0.0F;
    for (k = 0; k < 3; k++) {
      c_R[i] += b_R[i + 3 * k] * b_observation[k];
    }

    updated_state[3 + i] = state[3 + i] + 0.07F * c_R[i];
    b_state[i] = state[i] + 0.035F * (state[3 + i] + updated_state[3 + i]);
    updated_state[i] = b_state[i];
    updated_state[i + 9] = state[i + 9];
    updated_state[i + 12] = state[i + 12];
    updated_state[i + 15] = state[i + 15];
  }

  /*     updated_state(10:18) = [b_acc b_gyr b_mag] ; */
}

/*
 * File trailer for IMU_process_model.c
 *
 * [EOF]
 */
