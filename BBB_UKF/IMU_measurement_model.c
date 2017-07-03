/*
 * File: IMU_measurement_model.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "IMU_measurement_model.h"
#include "rotMat2quatern.h"

/* Function Definitions */

/*
 * Authors: Ahmed Mohamed Ayman & Amr Mohamed Taha
 * % This Measurment MODEL of the 9DOF IMU
 * % Measurment_model Summary of this function goes here
 *  % %
 *  % % This function used to transform the input state matrix from
 *  % % the NED frame to the body frame and calculate the acceleration,
 *  % % aangular velocity, & magnetic fields.
 *  % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % % %
 *    Detailed explanation goes here
 *  % % % % % % % % Outputs % % % % % % % % % %
 *  %  measurment  :
 *  %         m = |a_x  a_y  a_z  w_x  w_y  w_z  m_x  m_y  m_z|
 *
 *  % % % % % % % % Inputs % % % % % % % % % %
 *  %  pre_state :
 *  %             x_t-1 = |p_x  p_y  p_z  v_x  v_y  v_z  roll  pitch  yaw  b_ax  b_ay  b_az  b_wx  b_wy  b_wz  b_mx  b_my  b_mz|
 *
 *  %  state :
 *  %              x_t  = |p_x  p_y  p_z  v_x  v_y  v_z  roll  pitch  yaw  b_ax  b_ay  b_az  b_wx  b_wy  b_wz  b_mx  b_my  b_mz|
 *
 *  % Ts : Sampling time form sensors
 *  %
 *
 *
 *                |
 *  %  source :
 *  %
 *
 *   note :
 *
 *
 * % Initializations
 *  %    D  : A term used for derivative.
 *  % mag_e : The magnetic field of the earth in our region.
 *  % V_xyz : Velocity in xyz-axis.
 *  % roll  : rotation angle about x-axis.
 *  % pitch : rotation angle about y-axis.
 *  % yaw   : rotation angle about z-axis.
 *  % pre_Euler_angles : roll, pitch & yaw angles from the previous state.
 *  % pre_V_xyz : Velocity in xyz-axis from the previous state.
 * Arguments    : const float pre_state[18]
 *                const float state[18]
 *                float Ts
 *                float measurement[9]
 * Return Type  : void
 */
void IMU_measurement_model(const float pre_state[18], const float state[18],
  float Ts, float measurement[9])
{
  float D;
  float R[9];
  float q[4];
  float R_1[9];
  float R_2[9];
  float q_1[4];
  float q_2[4];
  float c;
  int i5;
  float w[4];
  float fv2[9];
  float fv3[9];
  float b_state[3];
  float b_pre_state[3];
  int i6;
  static const float y[3] = { 0.0309475F, 0.0023484F, 0.0305581987F };

  D = 1.0F / Ts;

  /*  from nT to gauss e-5 */
  /*  Euler_angles = state(7:9); */
  /* % %%%%%%%%%%%%%%%%%% */
  /*     IMU_model   % */
  /* %%%%%%%%%%%%%%%%% */
  /*  % % % % % % % % % % % % Obtain acceleration from velocity  */
  /* UNTITLED Summary of this function goes here */
  /*    Detailed explanation goes here */
  /* UNTITLED Summary of this function goes here */
  /*    Detailed explanation goes here */
  /* + bias_a ; */
  /*  % % % % % % % % % % % % Obtain magnetometer from euler angles */
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

  /*  %%adding bias to the magnetometer. */
  /* + bias_m; */
  /*  % % % % % % % % % % % Obtain angular velocity from euler angles % % % % */
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
  R_1[0] = cosf(pre_state[8]) * cosf(pre_state[7]);
  R_1[3] = -sinf(pre_state[8]) * cosf(pre_state[6]) + cosf(pre_state[8]) * sinf
    (pre_state[7]) * sinf(pre_state[6]);
  R_1[6] = sinf(pre_state[8]) * sinf(pre_state[6]) + cosf(pre_state[8]) * sinf
    (pre_state[7]) * cosf(pre_state[6]);
  R_1[1] = sinf(pre_state[8]) * cosf(pre_state[7]);
  R_1[4] = cosf(pre_state[8]) * cosf(pre_state[6]) + sinf(pre_state[8]) * sinf
    (pre_state[7]) * sinf(pre_state[6]);
  R_1[7] = -cosf(pre_state[8]) * sinf(pre_state[6]) + sinf(pre_state[8]) * sinf
    (pre_state[7]) * cosf(pre_state[6]);
  R_1[2] = -sinf(pre_state[7]);
  R_1[5] = cosf(pre_state[7]) * sinf(pre_state[6]);
  R_1[8] = cosf(pre_state[7]) * cosf(pre_state[6]);

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
  R_2[0] = cosf(state[8]) * cosf(state[7]);
  R_2[3] = -sinf(state[8]) * cosf(state[6]) + cosf(state[8]) * sinf(state[7]) *
    sinf(state[6]);
  R_2[6] = sinf(state[8]) * sinf(state[6]) + cosf(state[8]) * sinf(state[7]) *
    cosf(state[6]);
  R_2[1] = sinf(state[8]) * cosf(state[7]);
  R_2[4] = cosf(state[8]) * cosf(state[6]) + sinf(state[8]) * sinf(state[7]) *
    sinf(state[6]);
  R_2[7] = -cosf(state[8]) * sinf(state[6]) + sinf(state[8]) * sinf(state[7]) *
    cosf(state[6]);
  R_2[2] = -sinf(state[7]);
  R_2[5] = cosf(state[7]) * sinf(state[6]);
  R_2[8] = cosf(state[7]) * cosf(state[6]);
  rotMat2quatern(R_1, q_1);
  rotMat2quatern(R_2, q_2);

  /* QUATERN2ROTMAT Converts a quaternion to its conjugate */
  /*  */
  /*    qConj = quaternConj(q) */
  /*  */
  /*    Converts a quaternion to its conjugate. */
  /*  */
  /*    For more information see: */
  /*    http://www.x-io.co.uk/node/8#quaternions */
  /*  */
  /* 	Date          Author          Notes */
  /* 	27/09/2011    SOH Madgwick    Initial release */
  c = 2.0F * D;
  for (i5 = 0; i5 < 4; i5++) {
    q_2[i5] = c * (q_2[i5] - q_1[i5]);
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
  w[0] = ((q_1[0] * q_2[0] - -q_1[1] * q_2[1]) - -q_1[2] * q_2[2]) - -q_1[3] *
    q_2[3];
  w[1] = ((q_1[0] * q_2[1] + -q_1[1] * q_2[0]) + -q_1[2] * q_2[3]) - -q_1[3] *
    q_2[2];
  w[2] = ((q_1[0] * q_2[2] - -q_1[1] * q_2[3]) + -q_1[2] * q_2[0]) + -q_1[3] *
    q_2[1];
  w[3] = ((q_1[0] * q_2[3] + -q_1[1] * q_2[2]) - -q_1[2] * q_2[1]) + -q_1[3] *
    q_2[0];

  /* %%%%%%%%%%%%%%%%%%%%%%% */
  /*     IMU_Case _Output  % */
  /* %%%%%%%%%%%%%%%%%%%%%%% */
  fv2[0] = cosf(state[7]) * cosf(state[8]);
  fv2[3] = cosf(state[7]) * sinf(state[8]);
  fv2[6] = -sinf(state[7]);
  fv2[1] = sinf(state[6]) * sinf(state[7]) * cosf(state[8]) - cosf(state[6]) *
    sinf(state[8]);
  fv2[4] = sinf(state[6]) * sinf(state[7]) * sinf(state[8]) + cosf(state[6]) *
    cosf(state[8]);
  fv2[7] = sinf(state[6]) * cosf(state[7]);
  fv2[2] = cosf(state[6]) * sinf(state[7]) * cosf(state[8]) + sinf(state[6]) *
    sinf(state[8]);
  fv2[5] = cosf(state[6]) * sinf(state[7]) * sinf(state[8]) - sinf(state[6]) *
    cosf(state[8]);
  fv2[8] = cosf(state[6]) * cosf(state[7]);
  fv3[0] = cosf(state[7]) * cosf(state[8]);
  fv3[3] = cosf(state[7]) * sinf(state[8]);
  fv3[6] = -sinf(state[7]);
  fv3[1] = sinf(state[6]) * sinf(state[7]) * cosf(state[8]) - cosf(state[6]) *
    sinf(state[8]);
  fv3[4] = sinf(state[6]) * sinf(state[7]) * sinf(state[8]) + cosf(state[6]) *
    cosf(state[8]);
  fv3[7] = sinf(state[6]) * cosf(state[7]);
  fv3[2] = cosf(state[6]) * sinf(state[7]) * cosf(state[8]) + sinf(state[6]) *
    sinf(state[8]);
  fv3[5] = cosf(state[6]) * sinf(state[7]) * sinf(state[8]) - sinf(state[6]) *
    cosf(state[8]);
  fv3[8] = cosf(state[6]) * cosf(state[7]);
  for (i5 = 0; i5 < 3; i5++) {
    b_state[i5] = 0.0F;
    b_pre_state[i5] = 0.0F;
    for (i6 = 0; i6 < 3; i6++) {
      b_state[i5] += state[3 + i6] * fv2[i6 + 3 * i5];
      b_pre_state[i5] += pre_state[3 + i6] * fv3[i6 + 3 * i5];
    }

    measurement[i5] = (b_state[i5] - b_pre_state[i5]) / D;
    measurement[i5 + 3] = w[1 + i5] + state[12 + i5];
    measurement[i5 + 6] = q[1 + i5] / y[i5];
  }
}

/*
 * File trailer for IMU_measurement_model.c
 *
 * [EOF]
 */
