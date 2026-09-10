/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pinv.c
 *
 * Code generation for function 'pinv'
 *
 */

/* Include files */
#include "pinv.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 *
 */
void pinv(const double A[144], double X[144])
{
  double V[144];
  double absx;
  int b_k;
  int ic;
  int k;
  int vcol;
  boolean_T p;
  p = true;
  for (k = 0; k < 144; k++) {
    X[k] = 0.0;
    if (p) {
      absx = A[k];
      if (rtIsInf(absx) || rtIsNaN(absx)) {
        p = false;
      }
    } else {
      p = false;
    }
  }
  if (!p) {
    for (k = 0; k < 144; k++) {
      X[k] = rtNaN;
    }
  } else {
    double U[144];
    double s[12];
    int r;
    boolean_T exitg1;
    svd(A, U, s, V);
    absx = fabs(s[0]);
    if (rtIsInf(absx) || rtIsNaN(absx)) {
      absx = rtNaN;
    } else if (absx < 4.450147717014403E-308) {
      absx = 5.0E-324;
    } else {
      frexp(absx, &vcol);
      absx = ldexp(1.0, vcol - 53);
    }
    absx *= 12.0;
    vcol = 0;
    exitg1 = false;
    while (!exitg1 && (vcol < 12)) {
      if (rtIsInf(s[vcol]) || rtIsNaN(s[vcol])) {
        absx = 1.7976931348623157E+308;
        exitg1 = true;
      } else {
        vcol++;
      }
    }
    r = -1;
    vcol = 0;
    while ((vcol < 12) && (s[vcol] > absx)) {
      r++;
      vcol++;
    }
    if (r + 1 > 0) {
      __m128d b_r;
      int ar;
      int vectorUB;
      vcol = 1;
      for (k = 0; k <= r; k++) {
        absx = 1.0 / s[k];
        ar = vcol + 12;
        vectorUB = vcol + 10;
        for (b_k = vcol; b_k <= vectorUB; b_k += 2) {
          b_r = _mm_loadu_pd(&V[b_k - 1]);
          _mm_storeu_pd(&V[b_k - 1], _mm_mul_pd(_mm_set1_pd(absx), b_r));
        }
        for (b_k = ar; b_k <= vcol + 11; b_k++) {
          V[b_k - 1] *= absx;
        }
        vcol += 12;
      }
      for (k = 0; k <= 132; k += 12) {
        memset(&X[k], 0, 12U * sizeof(double));
      }
      vcol = 0;
      for (k = 0; k <= 132; k += 12) {
        ar = -1;
        vcol++;
        vectorUB = vcol + 12 * r;
        for (b_k = vcol; b_k <= vectorUB; b_k += 12) {
          int b_vectorUB;
          int scalarLB;
          scalarLB = k + 13;
          b_vectorUB = k + 11;
          for (ic = k + 1; ic <= b_vectorUB; ic += 2) {
            __m128d r1;
            b_r = _mm_loadu_pd(&V[(ar + ic) - k]);
            r1 = _mm_loadu_pd(&X[ic - 1]);
            _mm_storeu_pd(
                &X[ic - 1],
                _mm_add_pd(r1, _mm_mul_pd(_mm_set1_pd(U[b_k - 1]), b_r)));
          }
          for (ic = scalarLB; ic <= k + 12; ic++) {
            X[ic - 1] += U[b_k - 1] * V[(ar + ic) - k];
          }
          ar += 12;
        }
      }
    }
  }
}

/* End of code generation (pinv.c) */
