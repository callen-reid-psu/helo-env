/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sum.c
 *
 * Code generation for function 'sum'
 *
 */

/* Include files */
#include "sum.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 *
 */
void sum(const double x[40], double y[4])
{
  int k;
  y[0] = x[0];
  y[1] = x[1];
  y[2] = x[2];
  y[3] = x[3];
  for (k = 0; k < 9; k++) {
    __m128d r;
    int xoffset;
    xoffset = (k + 1) << 2;
    r = _mm_loadu_pd(&y[0]);
    _mm_storeu_pd(&y[0], _mm_add_pd(r, _mm_loadu_pd(&x[xoffset])));
    r = _mm_loadu_pd(&y[2]);
    _mm_storeu_pd(&y[2], _mm_add_pd(r, _mm_loadu_pd(&x[xoffset + 2])));
  }
}

/* End of code generation (sum.c) */
