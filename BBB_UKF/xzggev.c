/*
 * File: xzggev.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 24-Jun-2017 16:50:47
 */

/* Include Files */
#include "UKF_C.h"
#include "xzggev.h"
#include "xztgevc.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "xzlangeM.h"

/* Function Definitions */

/*
 * Arguments    : creal32_T A[16]
 *                int *info
 *                creal32_T alpha1[4]
 *                creal32_T beta1[4]
 *                creal32_T V[16]
 * Return Type  : void
 */
void xzggev(creal32_T A[16], int *info, creal32_T alpha1[4], creal32_T beta1[4],
            creal32_T V[16])
{
  float anrm;
  boolean_T ilascl;
  float anrmto;
  float cfromc;
  int rscale[4];
  float ctoc;
  int i;
  boolean_T notdone;
  int ilo;
  int ihi;
  float cfrom1;
  float stemp_re;
  int exitg2;
  float stemp_im;
  int j;
  int ii;
  int nzcount;
  boolean_T exitg5;
  int jj;
  creal32_T atmp;
  boolean_T exitg6;
  int exitg1;
  signed char I[16];
  boolean_T guard2 = false;
  boolean_T exitg3;
  boolean_T exitg4;
  boolean_T guard1 = false;
  anrm = xzlangeM(A);
  ilascl = false;
  anrmto = anrm;
  if ((anrm > 0.0F) && (anrm < 9.09494702E-13F)) {
    anrmto = 9.09494702E-13F;
    ilascl = true;
  } else {
    if (anrm > 1.09951163E+12F) {
      anrmto = 1.09951163E+12F;
      ilascl = true;
    }
  }

  if (ilascl) {
    cfromc = anrm;
    ctoc = anrmto;
    notdone = true;
    while (notdone) {
      cfrom1 = cfromc * 1.97215226E-31F;
      stemp_re = ctoc / 5.0706024E+30F;
      if ((fabsf(cfrom1) > fabsf(ctoc)) && (ctoc != 0.0F)) {
        stemp_im = 1.97215226E-31F;
        cfromc = cfrom1;
      } else if (fabsf(stemp_re) > fabsf(cfromc)) {
        stemp_im = 5.0706024E+30F;
        ctoc = stemp_re;
      } else {
        stemp_im = ctoc / cfromc;
        notdone = false;
      }

      for (nzcount = 0; nzcount < 16; nzcount++) {
        A[nzcount].re *= stemp_im;
        A[nzcount].im *= stemp_im;
      }
    }
  }

  for (i = 0; i < 4; i++) {
    rscale[i] = 1;
  }

  ilo = 0;
  ihi = 4;
  do {
    exitg2 = 0;
    i = 0;
    j = 0;
    notdone = false;
    ii = ihi;
    exitg5 = false;
    while ((!exitg5) && (ii > 0)) {
      nzcount = 0;
      i = ii;
      j = ihi;
      jj = 1;
      exitg6 = false;
      while ((!exitg6) && (jj <= ihi)) {
        guard2 = false;
        if ((A[(ii + ((jj - 1) << 2)) - 1].re != 0.0F) || (A[(ii + ((jj - 1) <<
               2)) - 1].im != 0.0F) || (ii == jj)) {
          if (nzcount == 0) {
            j = jj;
            nzcount = 1;
            guard2 = true;
          } else {
            nzcount = 2;
            exitg6 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          jj++;
        }
      }

      if (nzcount < 2) {
        notdone = true;
        exitg5 = true;
      } else {
        ii--;
      }
    }

    if (!notdone) {
      exitg2 = 2;
    } else {
      if (i != ihi) {
        for (nzcount = 0; nzcount < 4; nzcount++) {
          atmp = A[(i + (nzcount << 2)) - 1];
          A[(i + (nzcount << 2)) - 1] = A[(ihi + (nzcount << 2)) - 1];
          A[(ihi + (nzcount << 2)) - 1] = atmp;
        }
      }

      if (j != ihi) {
        for (nzcount = 0; nzcount + 1 <= ihi; nzcount++) {
          atmp = A[nzcount + ((j - 1) << 2)];
          A[nzcount + ((j - 1) << 2)] = A[nzcount + ((ihi - 1) << 2)];
          A[nzcount + ((ihi - 1) << 2)] = atmp;
        }
      }

      rscale[ihi - 1] = j;
      ihi--;
      if (ihi == 1) {
        rscale[0] = 1;
        exitg2 = 1;
      }
    }
  } while (exitg2 == 0);

  if (exitg2 == 1) {
  } else {
    do {
      exitg1 = 0;
      i = 0;
      j = 0;
      notdone = false;
      jj = ilo + 1;
      exitg3 = false;
      while ((!exitg3) && (jj <= ihi)) {
        nzcount = 0;
        i = ihi;
        j = jj;
        ii = ilo + 1;
        exitg4 = false;
        while ((!exitg4) && (ii <= ihi)) {
          guard1 = false;
          if ((A[(ii + ((jj - 1) << 2)) - 1].re != 0.0F) || (A[(ii + ((jj - 1) <<
                 2)) - 1].im != 0.0F) || (ii == jj)) {
            if (nzcount == 0) {
              i = ii;
              nzcount = 1;
              guard1 = true;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            ii++;
          }
        }

        if (nzcount < 2) {
          notdone = true;
          exitg3 = true;
        } else {
          jj++;
        }
      }

      if (!notdone) {
        exitg1 = 1;
      } else {
        if (i != ilo + 1) {
          for (nzcount = ilo; nzcount + 1 < 5; nzcount++) {
            atmp = A[(i + (nzcount << 2)) - 1];
            A[(i + (nzcount << 2)) - 1] = A[ilo + (nzcount << 2)];
            A[ilo + (nzcount << 2)] = atmp;
          }
        }

        if (j != ilo + 1) {
          for (nzcount = 0; nzcount + 1 <= ihi; nzcount++) {
            atmp = A[nzcount + ((j - 1) << 2)];
            A[nzcount + ((j - 1) << 2)] = A[nzcount + (ilo << 2)];
            A[nzcount + (ilo << 2)] = atmp;
          }
        }

        rscale[ilo] = j;
        ilo++;
        if (ilo + 1 == ihi) {
          rscale[ilo] = ilo + 1;
          exitg1 = 1;
        }
      }
    } while (exitg1 == 0);
  }

  for (nzcount = 0; nzcount < 16; nzcount++) {
    I[nzcount] = 0;
  }

  for (nzcount = 0; nzcount < 4; nzcount++) {
    I[nzcount + (nzcount << 2)] = 1;
  }

  for (nzcount = 0; nzcount < 16; nzcount++) {
    V[nzcount].re = I[nzcount];
    V[nzcount].im = 0.0F;
  }

  if (ihi < ilo + 3) {
  } else {
    for (ii = ilo; ii + 1 < ihi - 1; ii++) {
      for (nzcount = ihi - 1; nzcount + 1 > ii + 2; nzcount--) {
        xzlartg(A[(nzcount + (ii << 2)) - 1], A[nzcount + (ii << 2)], &cfrom1,
                &atmp, &A[(nzcount + (ii << 2)) - 1]);
        A[nzcount + (ii << 2)].re = 0.0F;
        A[nzcount + (ii << 2)].im = 0.0F;
        for (j = ii + 1; j + 1 < 5; j++) {
          stemp_re = cfrom1 * A[(nzcount + (j << 2)) - 1].re + (atmp.re *
            A[nzcount + (j << 2)].re - atmp.im * A[nzcount + (j << 2)].im);
          stemp_im = cfrom1 * A[(nzcount + (j << 2)) - 1].im + (atmp.re *
            A[nzcount + (j << 2)].im + atmp.im * A[nzcount + (j << 2)].re);
          cfromc = A[(nzcount + (j << 2)) - 1].im;
          ctoc = A[(nzcount + (j << 2)) - 1].re;
          A[nzcount + (j << 2)].re = cfrom1 * A[nzcount + (j << 2)].re -
            (atmp.re * A[(nzcount + (j << 2)) - 1].re + atmp.im * A[(nzcount +
              (j << 2)) - 1].im);
          A[nzcount + (j << 2)].im = cfrom1 * A[nzcount + (j << 2)].im -
            (atmp.re * cfromc - atmp.im * ctoc);
          A[(nzcount + (j << 2)) - 1].re = stemp_re;
          A[(nzcount + (j << 2)) - 1].im = stemp_im;
        }

        atmp.re = -atmp.re;
        atmp.im = -atmp.im;
        for (i = 0; i + 1 <= ihi; i++) {
          stemp_re = cfrom1 * A[i + (nzcount << 2)].re + (atmp.re * A[i +
            ((nzcount - 1) << 2)].re - atmp.im * A[i + ((nzcount - 1) << 2)].im);
          stemp_im = cfrom1 * A[i + (nzcount << 2)].im + (atmp.re * A[i +
            ((nzcount - 1) << 2)].im + atmp.im * A[i + ((nzcount - 1) << 2)].re);
          cfromc = A[i + (nzcount << 2)].im;
          ctoc = A[i + (nzcount << 2)].re;
          A[i + ((nzcount - 1) << 2)].re = cfrom1 * A[i + ((nzcount - 1) << 2)].
            re - (atmp.re * A[i + (nzcount << 2)].re + atmp.im * A[i + (nzcount <<
                   2)].im);
          A[i + ((nzcount - 1) << 2)].im = cfrom1 * A[i + ((nzcount - 1) << 2)].
            im - (atmp.re * cfromc - atmp.im * ctoc);
          A[i + (nzcount << 2)].re = stemp_re;
          A[i + (nzcount << 2)].im = stemp_im;
        }

        for (i = 0; i < 4; i++) {
          stemp_re = cfrom1 * V[i + (nzcount << 2)].re + (atmp.re * V[i +
            ((nzcount - 1) << 2)].re - atmp.im * V[i + ((nzcount - 1) << 2)].im);
          stemp_im = cfrom1 * V[i + (nzcount << 2)].im + (atmp.re * V[i +
            ((nzcount - 1) << 2)].im + atmp.im * V[i + ((nzcount - 1) << 2)].re);
          cfromc = V[i + (nzcount << 2)].re;
          V[i + ((nzcount - 1) << 2)].re = cfrom1 * V[i + ((nzcount - 1) << 2)].
            re - (atmp.re * V[i + (nzcount << 2)].re + atmp.im * V[i + (nzcount <<
                   2)].im);
          V[i + ((nzcount - 1) << 2)].im = cfrom1 * V[i + ((nzcount - 1) << 2)].
            im - (atmp.re * V[i + (nzcount << 2)].im - atmp.im * cfromc);
          V[i + (nzcount << 2)].re = stemp_re;
          V[i + (nzcount << 2)].im = stemp_im;
        }
      }
    }
  }

  xzhgeqz(A, ilo + 1, ihi, V, info, alpha1, beta1);
  if (*info != 0) {
  } else {
    xztgevc(A, V);
    if (ilo + 1 > 1) {
      for (i = ilo - 1; i + 1 >= 1; i--) {
        nzcount = rscale[i] - 1;
        if (rscale[i] != i + 1) {
          for (j = 0; j < 4; j++) {
            atmp = V[i + (j << 2)];
            V[i + (j << 2)] = V[nzcount + (j << 2)];
            V[nzcount + (j << 2)] = atmp;
          }
        }
      }
    }

    if (ihi < 4) {
      while (ihi + 1 < 5) {
        nzcount = rscale[ihi] - 1;
        if (rscale[ihi] != ihi + 1) {
          for (j = 0; j < 4; j++) {
            atmp = V[ihi + (j << 2)];
            V[ihi + (j << 2)] = V[nzcount + (j << 2)];
            V[nzcount + (j << 2)] = atmp;
          }
        }

        ihi++;
      }
    }

    for (nzcount = 0; nzcount < 4; nzcount++) {
      cfromc = fabsf(V[nzcount << 2].re) + fabsf(V[nzcount << 2].im);
      for (ii = 0; ii < 3; ii++) {
        ctoc = fabsf(V[(ii + (nzcount << 2)) + 1].re) + fabsf(V[(ii + (nzcount <<
          2)) + 1].im);
        if (ctoc > cfromc) {
          cfromc = ctoc;
        }
      }

      if (cfromc >= 9.09494702E-13F) {
        cfromc = 1.0F / cfromc;
        for (ii = 0; ii < 4; ii++) {
          V[ii + (nzcount << 2)].re *= cfromc;
          V[ii + (nzcount << 2)].im *= cfromc;
        }
      }
    }

    if (ilascl) {
      notdone = true;
      while (notdone) {
        cfrom1 = anrmto * 1.97215226E-31F;
        stemp_re = anrm / 5.0706024E+30F;
        if ((fabsf(cfrom1) > fabsf(anrm)) && (anrm != 0.0F)) {
          stemp_im = 1.97215226E-31F;
          anrmto = cfrom1;
        } else if (fabsf(stemp_re) > fabsf(anrmto)) {
          stemp_im = 5.0706024E+30F;
          anrm = stemp_re;
        } else {
          stemp_im = anrm / anrmto;
          notdone = false;
        }

        for (nzcount = 0; nzcount < 4; nzcount++) {
          alpha1[nzcount].re *= stemp_im;
          alpha1[nzcount].im *= stemp_im;
        }
      }
    }
  }
}

/*
 * File trailer for xzggev.c
 *
 * [EOF]
 */
