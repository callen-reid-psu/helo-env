/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mod.c
 *
 * Code generation for function 'mod'
 *
 */

/* Include files */
#include "mod.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 *
 */
void b_mod(const double x[4], double r[4])
{
  int k;
  for (k = 0; k < 4; k++) {
    double b_r;
    b_r = x[k];
    if (rtIsNaN(b_r) || rtIsInf(b_r)) {
      b_r = rtNaN;
    } else {
      double q;
      q = fabs(b_r / 6.283185307179586);
      if (fabs(q - floor(q + 0.5)) > 2.220446049250313E-16 * q) {
        b_r = fmod(b_r, 6.283185307179586);
      } else {
        b_r = 0.0;
      }
      if (b_r == 0.0) {
        b_r = 0.0;
      } else if (b_r < 0.0) {
        b_r += 6.283185307179586;
      }
    }
    r[k] = b_r;
  }
}

/* End of code generation (mod.c) */
