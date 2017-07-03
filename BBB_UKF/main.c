/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 14:31:22
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "UKF_C.h"
#include "main.h"
#include "UKF_C_terminate.h"
#include "UKF_C_initialize.h"

/* Function Declarations */
static void argInit_18x18_real32_T(float result[324]);
static void argInit_18x1_real32_T(float result[18]);
static void argInit_9x2_real32_T(float result[18]);
static float argInit_real32_T(void);
static void main_UKF_C(void);

/* Function Definitions */

/*
 * Arguments    : float result[324]
 * Return Type  : void
 */
static void argInit_18x18_real32_T(float result[324])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 18; idx0++) {
    for (idx1 = 0; idx1 < 18; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 18 * idx1] = argInit_real32_T();
    }
  }
}

/*
 * Arguments    : float result[18]
 * Return Type  : void
 */
static void argInit_18x1_real32_T(float result[18])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 18; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real32_T();
  }
}

/*
 * Arguments    : float result[18]
 * Return Type  : void
 */
static void argInit_9x2_real32_T(float result[18])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 9; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + 9 * idx1] = 0.5;
    		  /*argInit_real32_T();*/
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_UKF_C(void)
{
  float fv4[18];
  float fv5[18];
  float fv6[324];
  float state[18];
  float cov[324];
  float k[162];
  float MU[9];
  float S[81];
  float e[9];
  char i;
  /* Initialize function 'UKF_C' input arguments. */
  /* Initialize function input argument 'observation'. */
  /* Initialize function input argument 'pre_state'. */
  /* Initialize function input argument 'pre_cov'. */
  /* Call the entry-point 'UKF_C'. */
  argInit_9x2_real32_T(fv4);
  argInit_18x1_real32_T(fv5);
  argInit_18x18_real32_T(fv6);
  UKF_C(fv4, fv5, fv6, state, cov, k, MU, S, e);
  for(i=0;i<18;i++){
  printf("State: %f\n",state[i]);
  }
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
	char j;
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  ///UKF_C_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
for(j=0;j<2;j++){
  main_UKF_C();
  printf("Hello\n");
}
  /* Terminate the application.
     You do not need to do this more than one time. */
  //UKF_C_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
