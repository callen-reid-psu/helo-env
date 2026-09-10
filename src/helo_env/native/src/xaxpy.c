/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.c
 *
 * Code generation for function 'xaxpy'
 *
 */

/* Include files */
#include "xaxpy.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 *
 */
void b_xaxpy(int n, double a, const double x[144], int ix0, double y[12],
             int iy0)
{
  int k;
  if (!(a == 0.0)) {
    int scalarLB;
    int vectorUB;
    scalarLB = (n / 2) << 1;
    vectorUB = scalarLB - 2;
    for (k = 0; k <= vectorUB; k += 2) {
      int i;
      i = (iy0 + k) - 1;
      _mm_storeu_pd(&y[i],
                    _mm_add_pd(_mm_loadu_pd(&y[i]),
                               _mm_mul_pd(_mm_set1_pd(a),
                                          _mm_loadu_pd(&x[(ix0 + k) - 1]))));
    }
    for (k = scalarLB; k < n; k++) {
      vectorUB = (iy0 + k) - 1;
      y[vectorUB] += a * x[(ix0 + k) - 1];
    }
  }
}

/*
 *
 */
void c_xaxpy(int n, double a, const double x[12], int ix0, double y[144],
             int iy0)
{
  int k;
  if (!(a == 0.0)) {
    int scalarLB;
    int vectorUB;
    scalarLB = n / 2 * 2;
    vectorUB = scalarLB - 2;
    for (k = 0; k <= vectorUB; k += 2) {
      __m128d r;
      __m128d r1;
      int i;
      i = (iy0 + k) - 1;
      r = _mm_loadu_pd(&x[(ix0 + k) - 1]);
      r = _mm_mul_pd(_mm_set1_pd(a), r);
      r1 = _mm_loadu_pd(&y[i]);
      r = _mm_add_pd(r1, r);
      _mm_storeu_pd(&y[i], r);
    }
    for (k = scalarLB; k < n; k++) {
      vectorUB = (iy0 + k) - 1;
      y[vectorUB] += a * x[(ix0 + k) - 1];
    }
  }
}

/*
 *
 */
void xaxpy(int n, double a, int ix0, double y[144], int iy0)
{
  int k;
  if (!(a == 0.0)) {
    for (k = 0; k < n; k++) {
      int i;
      i = (iy0 + k) - 1;
      y[i] += a * y[(ix0 + k) - 1];
    }
  }
}

/* End of code generation (xaxpy.c) */
