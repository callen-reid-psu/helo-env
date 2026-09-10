/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * interp1.c
 *
 * Code generation for function 'interp1'
 *
 */

/* Include files */
#include "interp1.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 *
 */
void b_interp1(const double varargin_1[181], const double varargin_2[181],
               const double varargin_3[40], double Vq[40])
{
  double x[181];
  double y[181];
  double xtmp;
  int b_j1;
  memcpy(&y[0], &varargin_2[0], 181U * sizeof(double));
  memcpy(&x[0], &varargin_1[0], 181U * sizeof(double));
  if (varargin_1[1] < varargin_1[0]) {
    for (b_j1 = 0; b_j1 < 90; b_j1++) {
      xtmp = x[b_j1];
      x[b_j1] = x[180 - b_j1];
      x[180 - b_j1] = xtmp;
      xtmp = y[b_j1];
      y[b_j1] = y[180 - b_j1];
      y[180 - b_j1] = xtmp;
    }
  }
  for (b_j1 = 0; b_j1 < 40; b_j1++) {
    Vq[b_j1] = rtNaN;
    xtmp = varargin_3[b_j1];
    if (rtIsNaN(xtmp)) {
      Vq[b_j1] = rtNaN;
    } else if (!(xtmp > x[180]) && !(xtmp < x[0])) {
      int high_i;
      int low_i;
      int low_ip1;
      low_i = 1;
      low_ip1 = 2;
      high_i = 181;
      while (high_i > low_ip1) {
        int mid_i;
        mid_i = (low_i + high_i) >> 1;
        if (varargin_3[b_j1] >= x[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      xtmp = x[low_i - 1];
      xtmp = (varargin_3[b_j1] - xtmp) / (x[low_i] - xtmp);
      if (xtmp == 0.0) {
        Vq[b_j1] = y[low_i - 1];
      } else if (xtmp == 1.0) {
        Vq[b_j1] = y[low_i];
      } else if (y[low_i - 1] == y[low_i]) {
        Vq[b_j1] = y[low_i - 1];
      } else {
        Vq[b_j1] = (1.0 - xtmp) * y[low_i - 1] + xtmp * y[low_i];
      }
    }
  }
}

/*
 *
 */
double c_interp1(const double varargin_1[4], const double varargin_2[4],
                 double varargin_3)
{
  double x[4];
  double y[4];
  double Vq;
  y[0] = varargin_2[0];
  x[0] = varargin_1[0];
  y[1] = varargin_2[1];
  x[1] = varargin_1[1];
  y[2] = varargin_2[2];
  x[2] = varargin_1[2];
  y[3] = varargin_2[3];
  x[3] = varargin_1[3];
  if (varargin_1[1] < varargin_1[0]) {
    x[0] = varargin_1[3];
    x[3] = varargin_1[0];
    y[0] = varargin_2[3];
    y[3] = varargin_2[0];
    x[1] = varargin_1[2];
    x[2] = varargin_1[1];
    y[1] = varargin_2[2];
    y[2] = varargin_2[1];
  }
  Vq = rtNaN;
  if (!rtIsNaN(varargin_3) && !(varargin_3 > x[3]) && !(varargin_3 < x[0])) {
    double r;
    int high_i;
    int low_i;
    int low_ip1;
    low_i = 1;
    low_ip1 = 2;
    high_i = 4;
    while (high_i > low_ip1) {
      int mid_i;
      mid_i = (low_i + high_i) >> 1;
      if (varargin_3 >= x[mid_i - 1]) {
        low_i = mid_i;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }
    Vq = x[low_i - 1];
    r = (varargin_3 - Vq) / (x[low_i] - Vq);
    if (r == 0.0) {
      Vq = y[low_i - 1];
    } else if (r == 1.0) {
      Vq = y[low_i];
    } else {
      Vq = y[low_i - 1];
      if (!(Vq == y[low_i])) {
        Vq = (1.0 - r) * Vq + r * y[low_i];
      }
    }
  }
  return Vq;
}

/*
 *
 */
void interp1(const double varargin_1[21], const double varargin_2[21],
             const double varargin_3[10], double Vq[10])
{
  double x[21];
  double y[21];
  double xtmp;
  int b_j1;
  memcpy(&y[0], &varargin_2[0], 21U * sizeof(double));
  memcpy(&x[0], &varargin_1[0], 21U * sizeof(double));
  if (varargin_1[1] < varargin_1[0]) {
    for (b_j1 = 0; b_j1 < 10; b_j1++) {
      xtmp = x[b_j1];
      x[b_j1] = x[20 - b_j1];
      x[20 - b_j1] = xtmp;
      xtmp = y[b_j1];
      y[b_j1] = y[20 - b_j1];
      y[20 - b_j1] = xtmp;
    }
  }
  for (b_j1 = 0; b_j1 < 10; b_j1++) {
    Vq[b_j1] = rtNaN;
    xtmp = varargin_3[b_j1];
    if (rtIsNaN(xtmp)) {
      Vq[b_j1] = rtNaN;
    } else if (!(xtmp > x[20]) && !(xtmp < x[0])) {
      int high_i;
      int low_i;
      int low_ip1;
      low_i = 1;
      low_ip1 = 2;
      high_i = 21;
      while (high_i > low_ip1) {
        int mid_i;
        mid_i = (low_i + high_i) >> 1;
        if (varargin_3[b_j1] >= x[mid_i - 1]) {
          low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      xtmp = x[low_i - 1];
      xtmp = (varargin_3[b_j1] - xtmp) / (x[low_i] - xtmp);
      if (xtmp == 0.0) {
        Vq[b_j1] = y[low_i - 1];
      } else if (xtmp == 1.0) {
        Vq[b_j1] = y[low_i];
      } else if (y[low_i - 1] == y[low_i]) {
        Vq[b_j1] = y[low_i - 1];
      } else {
        Vq[b_j1] = (1.0 - xtmp) * y[low_i - 1] + xtmp * y[low_i];
      }
    }
  }
}

/* End of code generation (interp1.c) */
