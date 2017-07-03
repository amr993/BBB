/*
 * File: xzhgeqz.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "sqrt.h"
#include "mod.h"
#include "xzlanhs.h"

/* Function Definitions */

/*
 * Arguments    : creal32_T A[16]
 *                int ilo
 *                int ihi
 *                creal32_T Z[16]
 *                int *info
 *                creal32_T alpha1[4]
 *                creal32_T beta1[4]
 * Return Type  : void
 */
void xzhgeqz(creal32_T A[16], int ilo, int ihi, creal32_T Z[16], int *info,
             creal32_T alpha1[4], creal32_T beta1[4])
{
  int jp1;
  float eshift_re;
  float eshift_im;
  float ctemp_re;
  float ctemp_im;
  float anorm;
  float temp2;
  float b_atol;
  float d;
  float ascale;
  boolean_T failed;
  int j;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int ifirst;
  int istart;
  int ilast;
  int ilastm1;
  int iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int jiter;
  int exitg1;
  boolean_T exitg3;
  boolean_T ilazro;
  boolean_T b_guard1 = false;
  float ad22_re;
  float ad22_im;
  creal32_T shift;
  float c;
  float t1_re;
  boolean_T exitg2;
  float t1_im;
  boolean_T guard3 = false;
  float tempr;
  int x;
  *info = 0;
  for (jp1 = 0; jp1 < 4; jp1++) {
    alpha1[jp1].re = 0.0F;
    alpha1[jp1].im = 0.0F;
    beta1[jp1].re = 1.0F;
    beta1[jp1].im = 0.0F;
  }

  eshift_re = 0.0F;
  eshift_im = 0.0F;
  ctemp_re = 0.0F;
  ctemp_im = 0.0F;
  anorm = xzlanhs(A, ilo, ihi);
  temp2 = 1.1920929E-7F * anorm;
  b_atol = 1.17549435E-38F;
  if (temp2 > 1.17549435E-38F) {
    b_atol = temp2;
  }

  d = 1.17549435E-38F;
  if (anorm > 1.17549435E-38F) {
    d = anorm;
  }

  ascale = 1.0F / d;
  failed = true;
  for (j = ihi; j + 1 < 5; j++) {
    alpha1[j] = A[j + (j << 2)];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1)) {
        if (ilast + 1 == ilo) {
          goto60 = true;
        } else if (fabsf(A[ilast + (ilastm1 << 2)].re) + fabsf(A[ilast +
                    (ilastm1 << 2)].im) <= b_atol) {
          A[ilast + (ilastm1 << 2)].re = 0.0F;
          A[ilast + (ilastm1 << 2)].im = 0.0F;
          goto60 = true;
        } else {
          j = ilastm1;
          exitg3 = false;
          while ((!exitg3) && (j + 1 >= ilo)) {
            if (j + 1 == ilo) {
              ilazro = true;
            } else if (fabsf(A[j + ((j - 1) << 2)].re) + fabsf(A[j + ((j - 1) <<
              2)].im) <= b_atol) {
              A[j + ((j - 1) << 2)].re = 0.0F;
              A[j + ((j - 1) << 2)].im = 0.0F;
              ilazro = true;
            } else {
              ilazro = false;
            }

            if (ilazro) {
              ifirst = j + 1;
              goto70 = true;
              exitg3 = true;
            } else {
              j--;
            }
          }
        }

        if (goto60 || goto70) {
          ilazro = true;
        } else {
          ilazro = false;
        }

        if (!ilazro) {
          for (jp1 = 0; jp1 < 4; jp1++) {
            alpha1[jp1].re = 0.0F;
            alpha1[jp1].im = 0.0F;
            beta1[jp1].re = 0.0F;
            beta1[jp1].im = 0.0F;
          }

          for (jp1 = 0; jp1 < 16; jp1++) {
            Z[jp1].re = 0.0F;
            Z[jp1].im = 0.0F;
          }

          *info = 1;
          exitg1 = 1;
        } else {
          b_guard1 = false;
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + (ilast << 2)];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0F;
              eshift_im = 0.0F;
              b_guard1 = true;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              if (b_mod(iiter) != 0) {
                anorm = ascale * A[ilastm1 + (ilastm1 << 2)].re;
                temp2 = ascale * A[ilastm1 + (ilastm1 << 2)].im;
                if (temp2 == 0.0F) {
                  shift.re = anorm / 0.5F;
                  shift.im = 0.0F;
                } else if (anorm == 0.0F) {
                  shift.re = 0.0F;
                  shift.im = temp2 / 0.5F;
                } else {
                  shift.re = anorm / 0.5F;
                  shift.im = temp2 / 0.5F;
                }

                anorm = ascale * A[ilast + (ilast << 2)].re;
                temp2 = ascale * A[ilast + (ilast << 2)].im;
                if (temp2 == 0.0F) {
                  ad22_re = anorm / 0.5F;
                  ad22_im = 0.0F;
                } else if (anorm == 0.0F) {
                  ad22_re = 0.0F;
                  ad22_im = temp2 / 0.5F;
                } else {
                  ad22_re = anorm / 0.5F;
                  ad22_im = temp2 / 0.5F;
                }

                t1_re = 0.5F * (shift.re + ad22_re);
                t1_im = 0.5F * (shift.im + ad22_im);
                anorm = ascale * A[ilastm1 + (ilast << 2)].re;
                temp2 = ascale * A[ilastm1 + (ilast << 2)].im;
                if (temp2 == 0.0F) {
                  d = anorm / 0.5F;
                  c = 0.0F;
                } else if (anorm == 0.0F) {
                  d = 0.0F;
                  c = temp2 / 0.5F;
                } else {
                  d = anorm / 0.5F;
                  c = temp2 / 0.5F;
                }

                anorm = ascale * A[ilast + (ilastm1 << 2)].re;
                temp2 = ascale * A[ilast + (ilastm1 << 2)].im;
                if (temp2 == 0.0F) {
                  tempr = anorm / 0.5F;
                  anorm = 0.0F;
                } else if (anorm == 0.0F) {
                  tempr = 0.0F;
                  anorm = temp2 / 0.5F;
                } else {
                  tempr = anorm / 0.5F;
                  anorm = temp2 / 0.5F;
                }

                temp2 = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) + (d * tempr - c *
                  anorm)) - (shift.re * ad22_re - shift.im * ad22_im);
                shift.im = ((t1_re * t1_im + t1_im * t1_re) + (d * anorm + c *
                  tempr)) - temp2;
                b_sqrt(&shift);
                if ((t1_re - ad22_re) * shift.re + (t1_im - ad22_im) * shift.im <=
                    0.0F) {
                  shift.re += t1_re;
                  shift.im += t1_im;
                } else {
                  shift.re = t1_re - shift.re;
                  shift.im = t1_im - shift.im;
                }
              } else {
                anorm = ascale * A[ilast + (ilastm1 << 2)].re;
                temp2 = ascale * A[ilast + (ilastm1 << 2)].im;
                if (temp2 == 0.0F) {
                  d = anorm / 0.5F;
                  c = 0.0F;
                } else if (anorm == 0.0F) {
                  d = 0.0F;
                  c = temp2 / 0.5F;
                } else {
                  d = anorm / 0.5F;
                  c = temp2 / 0.5F;
                }

                eshift_re += d;
                eshift_im += c;
                shift.re = eshift_re;
                shift.im = eshift_im;
              }

              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                ctemp_re = ascale * A[j + (j << 2)].re - shift.re * 0.5F;
                ctemp_im = ascale * A[j + (j << 2)].im - shift.im * 0.5F;
                anorm = fabsf(ctemp_re) + fabsf(ctemp_im);
                temp2 = ascale * (fabsf(A[jp1 + (j << 2)].re) + fabsf(A[jp1 + (j
                  << 2)].im));
                tempr = anorm;
                if (temp2 > anorm) {
                  tempr = temp2;
                }

                if ((tempr < 1.0F) && (tempr != 0.0F)) {
                  anorm /= tempr;
                  temp2 /= tempr;
                }

                if ((fabsf(A[j + ((j - 1) << 2)].re) + fabsf(A[j + ((j - 1) << 2)]
                      .im)) * temp2 <= anorm * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = j;
                  j--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                ctemp_re = ascale * A[(ifirst + ((ifirst - 1) << 2)) - 1].re -
                  shift.re * 0.5F;
                ctemp_im = ascale * A[(ifirst + ((ifirst - 1) << 2)) - 1].im -
                  shift.im * 0.5F;
                goto90 = true;
              }
            }

            if (goto90) {
              goto90 = false;
              ad22_re = ascale * A[istart + ((istart - 1) << 2)].re;
              ad22_im = ascale * A[istart + ((istart - 1) << 2)].im;
              anorm = fabsf(ctemp_re);
              temp2 = fabsf(ctemp_im);
              if (temp2 > anorm) {
                anorm = temp2;
              }

              d = fabsf(ad22_re);
              temp2 = fabsf(ad22_im);
              if (temp2 > d) {
                d = temp2;
              }

              if (d > anorm) {
                anorm = d;
              }

              shift.re = ctemp_re;
              shift.im = ctemp_im;
              guard3 = false;
              if (anorm >= 5.49755814E+11F) {
                do {
                  shift.re *= 1.8189894E-12F;
                  shift.im *= 1.8189894E-12F;
                  ad22_re *= 1.8189894E-12F;
                  ad22_im *= 1.8189894E-12F;
                  anorm *= 1.8189894E-12F;
                } while (!(anorm < 5.49755814E+11F));

                guard3 = true;
              } else if (anorm <= 1.8189894E-12F) {
                if ((ad22_re == 0.0F) && (ad22_im == 0.0F)) {
                  c = 1.0F;
                  shift.re = 0.0F;
                  shift.im = 0.0F;
                } else {
                  do {
                    shift.re *= 5.49755814E+11F;
                    shift.im *= 5.49755814E+11F;
                    ad22_re *= 5.49755814E+11F;
                    ad22_im *= 5.49755814E+11F;
                    anorm *= 5.49755814E+11F;
                  } while (!(anorm > 1.8189894E-12F));

                  guard3 = true;
                }
              } else {
                guard3 = true;
              }

              if (guard3) {
                anorm = shift.re * shift.re + shift.im * shift.im;
                temp2 = ad22_re * ad22_re + ad22_im * ad22_im;
                d = temp2;
                if (1.0F > temp2) {
                  d = 1.0F;
                }

                if (anorm <= d * 1.97215226E-31F) {
                  if ((ctemp_re == 0.0F) && (ctemp_im == 0.0F)) {
                    c = 0.0F;
                    d = hypotf(ad22_re, ad22_im);
                    shift.re = ad22_re / d;
                    shift.im = -ad22_im / d;
                  } else {
                    tempr = sqrtf(temp2);
                    c = hypotf(shift.re, shift.im) / tempr;
                    d = fabsf(ctemp_re);
                    temp2 = fabsf(ctemp_im);
                    if (temp2 > d) {
                      d = temp2;
                    }

                    if (d > 1.0F) {
                      d = hypotf(ctemp_re, ctemp_im);
                      shift.re = ctemp_re / d;
                      shift.im = ctemp_im / d;
                    } else {
                      anorm = 5.49755814E+11F * ctemp_re;
                      temp2 = 5.49755814E+11F * ctemp_im;
                      d = hypotf(anorm, temp2);
                      shift.re = anorm / d;
                      shift.im = temp2 / d;
                    }

                    ad22_re /= tempr;
                    ad22_im = -ad22_im / tempr;
                    anorm = shift.re;
                    shift.re = shift.re * ad22_re - shift.im * ad22_im;
                    shift.im = anorm * ad22_im + shift.im * ad22_re;
                  }
                } else {
                  tempr = sqrtf(1.0F + temp2 / anorm);
                  c = 1.0F / tempr;
                  d = anorm + temp2;
                  anorm = tempr * shift.re / d;
                  temp2 = tempr * shift.im / d;
                  shift.re = anorm * ad22_re - temp2 * -ad22_im;
                  shift.im = anorm * -ad22_im + temp2 * ad22_re;
                }
              }

              j = istart;
              jp1 = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  xzlartg(A[(j + (jp1 << 2)) - 1], A[j + (jp1 << 2)], &c, &shift,
                          &A[(j + (jp1 << 2)) - 1]);
                  A[j + (jp1 << 2)].re = 0.0F;
                  A[j + (jp1 << 2)].im = 0.0F;
                }

                for (jp1 = j - 1; jp1 + 1 < 5; jp1++) {
                  ad22_re = c * A[(j + (jp1 << 2)) - 1].re + (shift.re * A[j +
                    (jp1 << 2)].re - shift.im * A[j + (jp1 << 2)].im);
                  ad22_im = c * A[(j + (jp1 << 2)) - 1].im + (shift.re * A[j +
                    (jp1 << 2)].im + shift.im * A[j + (jp1 << 2)].re);
                  anorm = A[(j + (jp1 << 2)) - 1].im;
                  temp2 = A[(j + (jp1 << 2)) - 1].re;
                  A[j + (jp1 << 2)].re = c * A[j + (jp1 << 2)].re - (shift.re *
                    A[(j + (jp1 << 2)) - 1].re + shift.im * A[(j + (jp1 << 2)) -
                    1].im);
                  A[j + (jp1 << 2)].im = c * A[j + (jp1 << 2)].im - (shift.re *
                    anorm - shift.im * temp2);
                  A[(j + (jp1 << 2)) - 1].re = ad22_re;
                  A[(j + (jp1 << 2)) - 1].im = ad22_im;
                }

                shift.re = -shift.re;
                shift.im = -shift.im;
                x = j;
                if (ilast + 1 < j + 2) {
                  x = ilast - 1;
                }

                for (jp1 = 0; jp1 + 1 <= x + 2; jp1++) {
                  ad22_re = c * A[jp1 + (j << 2)].re + (shift.re * A[jp1 + ((j -
                    1) << 2)].re - shift.im * A[jp1 + ((j - 1) << 2)].im);
                  ad22_im = c * A[jp1 + (j << 2)].im + (shift.re * A[jp1 + ((j -
                    1) << 2)].im + shift.im * A[jp1 + ((j - 1) << 2)].re);
                  anorm = A[jp1 + (j << 2)].im;
                  temp2 = A[jp1 + (j << 2)].re;
                  A[jp1 + ((j - 1) << 2)].re = c * A[jp1 + ((j - 1) << 2)].re -
                    (shift.re * A[jp1 + (j << 2)].re + shift.im * A[jp1 + (j <<
                      2)].im);
                  A[jp1 + ((j - 1) << 2)].im = c * A[jp1 + ((j - 1) << 2)].im -
                    (shift.re * anorm - shift.im * temp2);
                  A[jp1 + (j << 2)].re = ad22_re;
                  A[jp1 + (j << 2)].im = ad22_im;
                }

                for (jp1 = 0; jp1 < 4; jp1++) {
                  ad22_re = c * Z[jp1 + (j << 2)].re + (shift.re * Z[jp1 + ((j -
                    1) << 2)].re - shift.im * Z[jp1 + ((j - 1) << 2)].im);
                  ad22_im = c * Z[jp1 + (j << 2)].im + (shift.re * Z[jp1 + ((j -
                    1) << 2)].im + shift.im * Z[jp1 + ((j - 1) << 2)].re);
                  anorm = Z[jp1 + (j << 2)].im;
                  temp2 = Z[jp1 + (j << 2)].re;
                  Z[jp1 + ((j - 1) << 2)].re = c * Z[jp1 + ((j - 1) << 2)].re -
                    (shift.re * Z[jp1 + (j << 2)].re + shift.im * Z[jp1 + (j <<
                      2)].im);
                  Z[jp1 + ((j - 1) << 2)].im = c * Z[jp1 + ((j - 1) << 2)].im -
                    (shift.re * anorm - shift.im * temp2);
                  Z[jp1 + (j << 2)].re = ad22_re;
                  Z[jp1 + (j << 2)].im = ad22_im;
                }

                jp1 = j - 1;
                j++;
              }
            }

            b_guard1 = true;
          }

          if (b_guard1) {
            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 + 1 <= ilast + 1; jp1++) {
        alpha1[jp1].re = 0.0F;
        alpha1[jp1].im = 0.0F;
        beta1[jp1].re = 0.0F;
        beta1[jp1].im = 0.0F;
      }

      for (jp1 = 0; jp1 < 16; jp1++) {
        Z[jp1].re = 0.0F;
        Z[jp1].im = 0.0F;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j + 1 < ilo; j++) {
      alpha1[j] = A[j + (j << 2)];
    }
  }
}

/*
 * File trailer for xzhgeqz.c
 *
 * [EOF]
 */
