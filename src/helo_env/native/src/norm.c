/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * norm.c
 *
 * Code generation for function 'norm'
 *
 */

/* Include files */
#include "norm.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 *
 */
double b_norm(const double x[12])
{
  double scale;
  double y;
  int k;
  boolean_T b;
  y = 0.0;
  scale = 3.312168642111238E-170;
  for (k = 0; k < 12; k++) {
    double absxk;
    absxk = fabs(x[k]);
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
    b_k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (b_k < 12) {
        if (rtIsNaN(x[b_k])) {
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

/* End of code generation (norm.c) */
