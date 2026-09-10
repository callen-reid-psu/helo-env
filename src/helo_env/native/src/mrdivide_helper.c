/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mrdivide_helper.c
 *
 * Code generation for function 'mrdivide_helper'
 *
 */

/* Include files */
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 *
 */
void mrdiv(const double A[9], const double B[9], double Y[9])
{
  __m128d b_r1;
  __m128d r;
  double b_A[9];
  double a21;
  double d;
  double d1;
  double d2;
  double d3;
  double maxval;
  int Y_tmp;
  int r1;
  int r2;
  int r3;
  int rtemp;
  memcpy(&b_A[0], &B[0], 9U * sizeof(double));
  r1 = 0;
  r2 = 1;
  r3 = 2;
  maxval = fabs(B[0]);
  a21 = fabs(B[1]);
  if (a21 > maxval) {
    maxval = a21;
    r1 = 1;
    r2 = 0;
  }
  if (fabs(B[2]) > maxval) {
    r1 = 2;
    r2 = 1;
    r3 = 0;
  }
  b_A[r2] = B[r2] / B[r1];
  b_A[r3] /= b_A[r1];
  b_A[r2 + 3] -= b_A[r2] * b_A[r1 + 3];
  b_A[r3 + 3] -= b_A[r3] * b_A[r1 + 3];
  b_A[r2 + 6] -= b_A[r2] * b_A[r1 + 6];
  b_A[r3 + 6] -= b_A[r3] * b_A[r1 + 6];
  if (fabs(b_A[r3 + 3]) > fabs(b_A[r2 + 3])) {
    rtemp = r2;
    r2 = r3;
    r3 = rtemp;
  }
  b_A[r3 + 3] /= b_A[r2 + 3];
  b_A[r3 + 6] -= b_A[r3 + 3] * b_A[r2 + 6];
  _mm_storeu_pd(&Y[3 * r1],
                _mm_div_pd(_mm_loadu_pd(&A[0]), _mm_set1_pd(b_A[r1])));
  r = _mm_loadu_pd(&Y[3 * r1]);
  maxval = b_A[r1 + 3];
  _mm_storeu_pd(&Y[3 * r2], _mm_sub_pd(_mm_loadu_pd(&A[3]),
                                       _mm_mul_pd(r, _mm_set1_pd(maxval))));
  r = _mm_loadu_pd(&Y[3 * r1]);
  a21 = b_A[r1 + 6];
  _mm_storeu_pd(&Y[3 * r3], _mm_sub_pd(_mm_loadu_pd(&A[6]),
                                       _mm_mul_pd(r, _mm_set1_pd(a21))));
  r = _mm_loadu_pd(&Y[3 * r2]);
  d = b_A[r2 + 3];
  _mm_storeu_pd(&Y[3 * r2], _mm_div_pd(r, _mm_set1_pd(d)));
  r = _mm_loadu_pd(&Y[3 * r2]);
  b_r1 = _mm_loadu_pd(&Y[3 * r3]);
  d1 = b_A[r2 + 6];
  _mm_storeu_pd(&Y[3 * r3], _mm_sub_pd(b_r1, _mm_mul_pd(r, _mm_set1_pd(d1))));
  r = _mm_loadu_pd(&Y[3 * r3]);
  d2 = b_A[r3 + 6];
  _mm_storeu_pd(&Y[3 * r3], _mm_div_pd(r, _mm_set1_pd(d2)));
  r = _mm_loadu_pd(&Y[3 * r3]);
  b_r1 = _mm_loadu_pd(&Y[3 * r2]);
  d3 = b_A[r3 + 3];
  _mm_storeu_pd(&Y[3 * r2], _mm_sub_pd(b_r1, _mm_mul_pd(r, _mm_set1_pd(d3))));
  r = _mm_loadu_pd(&Y[3 * r3]);
  b_r1 = _mm_loadu_pd(&Y[3 * r1]);
  _mm_storeu_pd(&Y[3 * r1],
                _mm_sub_pd(b_r1, _mm_mul_pd(r, _mm_set1_pd(b_A[r3]))));
  r = _mm_loadu_pd(&Y[3 * r2]);
  b_r1 = _mm_loadu_pd(&Y[3 * r1]);
  _mm_storeu_pd(&Y[3 * r1],
                _mm_sub_pd(b_r1, _mm_mul_pd(r, _mm_set1_pd(b_A[r2]))));
  Y_tmp = 3 * r1 + 2;
  Y[Y_tmp] = 0.0 / b_A[r1];
  rtemp = 3 * r2 + 2;
  Y[rtemp] = 0.0 - Y[Y_tmp] * maxval;
  r1 = 3 * r3 + 2;
  Y[r1] = A[8] - Y[Y_tmp] * a21;
  Y[rtemp] /= d;
  Y[r1] -= Y[rtemp] * d1;
  Y[r1] /= d2;
  Y[rtemp] -= Y[r1] * d3;
  Y[Y_tmp] -= Y[r1] * b_A[r3];
  Y[Y_tmp] -= Y[rtemp] * b_A[r2];
}

/* End of code generation (mrdivide_helper.c) */
