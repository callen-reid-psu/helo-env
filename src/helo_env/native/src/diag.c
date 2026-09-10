/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * diag.c
 *
 * Code generation for function 'diag'
 *
 */

/* Include files */
#include "diag.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 *
 */
void diag(const double v[3], double d[9])
{
  memset(&d[0], 0, 9U * sizeof(double));
  d[0] = v[0];
  d[4] = v[1];
  d[8] = v[2];
}

/* End of code generation (diag.c) */
