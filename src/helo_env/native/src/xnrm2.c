/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xnrm2.c
 *
 * Code generation for function 'xnrm2'
 *
 */

/* Include files */
#include "xnrm2.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 *
 */
double b_xnrm2(int n, const double x[12], int ix0)
{
  double scale;
  double y;
  int k;
  int kend;
  boolean_T b;
  y = 0.0;
  scale = 3.312168642111238E-170;
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }
  y = scale * sqrt(y);
  b = rtIsNaN(y);
  if (b) {
    int b_k;
    b_k = ix0;
    int exitg1;
    do {
      exitg1 = 0;
      if (b_k <= kend - 1) {
        if (rtIsNaN(x[b_k - 1])) {
          exitg1 = 1;
        } else {
          b_k++;
        }
      } else {
        y = rtInf;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return y;
}

/*
 *
 */
double xnrm2(int n, const double x[144], int ix0)
{
  double scale;
  double y;
  int k;
  int kend;
  boolean_T b;
  y = 0.0;
  scale = 3.312168642111238E-170;
  kend = ix0 + n;
  for (k = ix0; k < kend; k++) {
    double absxk;
    absxk = fabs(x[k - 1]);
    if (absxk > scale) {
      double t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      double t;
      t = absxk / scale;
      y += t * t;
    }
  }
  y = scale * sqrt(y);
  b = rtIsNaN(y);
  if (b) {
    int b_k;
    b_k = ix0;
    int exitg1;
    do {
      exitg1 = 0;
      if (b_k <= kend - 1) {
        if (rtIsNaN(x[b_k - 1])) {
          exitg1 = 1;
        } else {
          b_k++;
        }
      } else {
        y = rtInf;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  return y;
}

/* End of code generation (xnrm2.c) */
