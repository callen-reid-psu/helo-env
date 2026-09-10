/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * interp2.c
 *
 * Code generation for function 'interp2'
 *
 */

/* Include files */
#include "interp2.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 *
 */
void b_interp2(const double varargin_1[33], const double varargin_2[11],
               const double varargin_3[363], const double varargin_4[40],
               const double varargin_5[40], double Vq[40])
{
  int k;
  for (k = 0; k < 40; k++) {
    double ry;
    ry = varargin_4[k];
    if ((ry >= varargin_1[0]) && (ry <= varargin_1[32]) &&
        (varargin_5[k] >= varargin_2[0]) && (varargin_5[k] <= varargin_2[10])) {
      double qx1;
      double qx2;
      double rx;
      int b_low_i;
      int high_i;
      int low_i;
      int low_ip1;
      int mid_i;
      low_i = 0;
      low_ip1 = 2;
      high_i = 33;
      while (high_i > low_ip1) {
        mid_i = ((low_i + high_i) + 1) >> 1;
        if (varargin_4[k] >= varargin_1[mid_i - 1]) {
          low_i = mid_i - 1;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      b_low_i = 1;
      low_ip1 = 2;
      high_i = 11;
      while (high_i > low_ip1) {
        mid_i = (b_low_i + high_i) >> 1;
        if (varargin_5[k] >= varargin_2[mid_i - 1]) {
          b_low_i = mid_i;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }
      ry = varargin_4[k];
      if (ry == varargin_1[low_i]) {
        low_ip1 = b_low_i + 11 * low_i;
        qx1 = varargin_3[low_ip1 - 1];
        qx2 = varargin_3[low_ip1];
      } else if (ry == varargin_1[low_i + 1]) {
        low_ip1 = b_low_i + 11 * (low_i + 1);
        qx1 = varargin_3[low_ip1 - 1];
        qx2 = varargin_3[low_ip1];
      } else {
        rx = (ry - varargin_1[low_i]) /
             (varargin_1[low_i + 1] - varargin_1[low_i]);
        high_i = b_low_i + 11 * low_i;
        qx1 = varargin_3[high_i - 1];
        low_ip1 = b_low_i + 11 * (low_i + 1);
        ry = varargin_3[low_ip1 - 1];
        if (!(qx1 == ry)) {
          qx1 = (1.0 - rx) * qx1 + rx * ry;
        }
        qx2 = varargin_3[high_i];
        ry = varargin_3[low_ip1];
        if (!(qx2 == ry)) {
          qx2 = (1.0 - rx) * qx2 + rx * ry;
        }
      }
      ry = varargin_2[b_low_i - 1];
      rx = varargin_5[k];
      if ((rx == ry) || (qx1 == qx2)) {
        Vq[k] = qx1;
      } else if (rx == varargin_2[b_low_i]) {
        Vq[k] = qx2;
      } else {
        ry = (rx - ry) / (varargin_2[b_low_i] - ry);
        Vq[k] = (1.0 - ry) * qx1 + ry * qx2;
      }
    } else {
      Vq[k] = rtNaN;
    }
  }
}

/*
 *
 */
double interp2(const double varargin_1[11], const double varargin_2[3],
               const double varargin_3[33], double varargin_4,
               double varargin_5)
{
  double Vq;
  if ((varargin_4 >= varargin_1[0]) && (varargin_4 <= varargin_1[10]) &&
      (varargin_5 >= varargin_2[0]) && (varargin_5 <= varargin_2[2])) {
    double qx2;
    double ry;
    int high_i;
    int low_i;
    int low_ip1;
    int mid_i;
    low_i = 0;
    low_ip1 = 2;
    high_i = 11;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (varargin_4 >= varargin_1[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }
    mid_i = 0;
    if (varargin_5 >= varargin_2[1]) {
      mid_i = 1;
    }
    if (varargin_4 == varargin_1[low_i]) {
      low_ip1 = mid_i + 3 * low_i;
      Vq = varargin_3[low_ip1];
      qx2 = varargin_3[low_ip1 + 1];
    } else if (varargin_4 == varargin_1[low_i + 1]) {
      low_ip1 = mid_i + 3 * (low_i + 1);
      Vq = varargin_3[low_ip1];
      qx2 = varargin_3[low_ip1 + 1];
    } else {
      double rx;
      rx = (varargin_4 - varargin_1[low_i]) /
           (varargin_1[low_i + 1] - varargin_1[low_i]);
      high_i = mid_i + 3 * low_i;
      Vq = varargin_3[high_i];
      low_ip1 = mid_i + 3 * (low_i + 1);
      ry = varargin_3[low_ip1];
      if (!(Vq == ry)) {
        Vq = (1.0 - rx) * Vq + rx * ry;
      }
      qx2 = varargin_3[high_i + 1];
      ry = varargin_3[low_ip1 + 1];
      if (!(qx2 == ry)) {
        qx2 = (1.0 - rx) * qx2 + rx * ry;
      }
    }
    if (!(varargin_5 == varargin_2[mid_i]) && !(Vq == qx2)) {
      ry = varargin_2[mid_i + 1];
      if (varargin_5 == ry) {
        Vq = qx2;
      } else {
        ry = (varargin_5 - varargin_2[mid_i]) / (ry - varargin_2[mid_i]);
        Vq = (1.0 - ry) * Vq + ry * qx2;
      }
    }
  } else {
    Vq = rtNaN;
  }
  return Vq;
}

/* End of code generation (interp2.c) */
