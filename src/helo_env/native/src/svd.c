/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.c
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "svd.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include "xzlangeM.h"
#include "xzlascl.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 *
 */
void svd(const double A[144], double U[144], double s[12], double V[144])
{
  __m128d r;
  double b_A[144];
  double e[12];
  double work[12];
  double anrm;
  double b;
  double cscale;
  double f;
  double nrm;
  double rt;
  double sm;
  double snorm;
  double sqds;
  int b_k;
  int k;
  int m;
  int q;
  int qjj;
  int qp1;
  int qp1jj;
  int qq;
  int qq_tmp;
  int vectorUB;
  boolean_T doscale;
  memcpy(&b_A[0], &A[0], 144U * sizeof(double));
  memset(&s[0], 0, 12U * sizeof(double));
  memset(&e[0], 0, 12U * sizeof(double));
  memset(&work[0], 0, 12U * sizeof(double));
  memset(&U[0], 0, 144U * sizeof(double));
  memset(&V[0], 0, 144U * sizeof(double));
  doscale = false;
  anrm = xzlangeM(A);
  cscale = anrm;
  if ((anrm > 0.0) && (anrm < 6.717876107567089E-139)) {
    doscale = true;
    cscale = 6.717876107567089E-139;
    xzlascl(anrm, cscale, b_A);
  } else if (anrm > 1.488565707357403E+138) {
    doscale = true;
    cscale = 1.488565707357403E+138;
    xzlascl(anrm, cscale, b_A);
  }
  for (q = 0; q < 11; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    qq_tmp = q + 12 * q;
    qq = qq_tmp + 1;
    apply_transform = false;
    nrm = xnrm2(12 - q, b_A, qq_tmp + 1);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq_tmp] < 0.0) {
        nrm = -nrm;
      }
      s[q] = nrm;
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qjj = (qq_tmp - q) + 12;
        qp1jj = ((((qjj - qq_tmp) / 2) << 1) + qq_tmp) + 1;
        vectorUB = qp1jj - 2;
        for (b_k = qq; b_k <= vectorUB; b_k += 2) {
          r = _mm_loadu_pd(&b_A[b_k - 1]);
          _mm_storeu_pd(&b_A[b_k - 1], _mm_mul_pd(_mm_set1_pd(nrm), r));
        }
        for (b_k = qp1jj; b_k <= qjj; b_k++) {
          b_A[b_k - 1] *= nrm;
        }
      } else {
        qjj = (qq_tmp - q) + 12;
        qp1jj = ((((qjj - qq_tmp) / 2) << 1) + qq_tmp) + 1;
        vectorUB = qp1jj - 2;
        for (k = qq; k <= vectorUB; k += 2) {
          r = _mm_loadu_pd(&b_A[k - 1]);
          _mm_storeu_pd(&b_A[k - 1], _mm_div_pd(r, _mm_set1_pd(s[q])));
        }
        for (k = qp1jj; k <= qjj; k++) {
          b_A[k - 1] /= s[q];
        }
      }
      b_A[qq_tmp]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0;
    }
    for (b_k = qp1; b_k < 13; b_k++) {
      qjj = q + 12 * (b_k - 1);
      if (apply_transform) {
        xaxpy(12 - q,
              -(xdotc(12 - q, b_A, qq_tmp + 1, b_A, qjj + 1) / b_A[qq_tmp]),
              qq_tmp + 1, b_A, qjj + 1);
      }
      e[b_k - 1] = b_A[qjj];
    }
    for (b_k = q + 1; b_k < 13; b_k++) {
      qjj = (b_k + 12 * q) - 1;
      U[qjj] = b_A[qjj];
    }
    if (q + 1 <= 10) {
      nrm = b_xnrm2(11 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }
        nrm = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          qjj = ((((11 - q) / 2) << 1) + q) + 2;
          qp1jj = qjj - 2;
          for (b_k = qp1; b_k <= qp1jj; b_k += 2) {
            r = _mm_loadu_pd(&e[b_k - 1]);
            _mm_storeu_pd(&e[b_k - 1], _mm_mul_pd(_mm_set1_pd(nrm), r));
          }
          for (b_k = qjj; b_k < 13; b_k++) {
            e[b_k - 1] *= nrm;
          }
        } else {
          qjj = ((((11 - q) / 2) << 1) + q) + 2;
          qp1jj = qjj - 2;
          for (b_k = qp1; b_k <= qp1jj; b_k += 2) {
            r = _mm_loadu_pd(&e[b_k - 1]);
            _mm_storeu_pd(&e[b_k - 1], _mm_div_pd(r, _mm_set1_pd(nrm)));
          }
          for (b_k = qjj; b_k < 13; b_k++) {
            e[b_k - 1] /= nrm;
          }
        }
        e[q + 1]++;
        e[q] = -e[q];
        for (b_k = qp1; b_k < 13; b_k++) {
          work[b_k - 1] = 0.0;
        }
        for (b_k = qp1; b_k < 13; b_k++) {
          b_xaxpy(11 - q, e[b_k - 1], b_A, (q + 12 * (b_k - 1)) + 2, work,
                  q + 2);
        }
        for (b_k = qp1; b_k < 13; b_k++) {
          c_xaxpy(11 - q, -e[b_k - 1] / e[q + 1], work, q + 2, b_A,
                  (q + 12 * (b_k - 1)) + 2);
        }
      }
      for (b_k = qp1; b_k < 13; b_k++) {
        V[(b_k + 12 * q) - 1] = e[b_k - 1];
      }
    }
  }
  m = 11;
  s[11] = b_A[143];
  e[10] = b_A[142];
  e[11] = 0.0;
  memset(&U[132], 0, 12U * sizeof(double));
  U[143] = 1.0;
  for (k = 10; k >= 0; k--) {
    qq = k + 12 * k;
    if (s[k] != 0.0) {
      for (b_k = k + 2; b_k < 13; b_k++) {
        qjj = (k + 12 * (b_k - 1)) + 1;
        xaxpy(12 - k, -(xdotc(12 - k, U, qq + 1, U, qjj) / U[qq]), qq + 1, U,
              qjj);
      }
      vectorUB = ((((12 - k) / 2) << 1) + k) + 1;
      qjj = vectorUB - 2;
      for (b_k = k + 1; b_k <= qjj; b_k += 2) {
        qp1jj = (b_k + 12 * k) - 1;
        r = _mm_loadu_pd(&U[qp1jj]);
        _mm_storeu_pd(&U[qp1jj], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
      }
      for (b_k = vectorUB; b_k < 13; b_k++) {
        qjj = (b_k + 12 * k) - 1;
        U[qjj] = -U[qjj];
      }
      U[qq]++;
      for (b_k = 0; b_k < k; b_k++) {
        U[b_k + 12 * k] = 0.0;
      }
    } else {
      memset(&U[k * 12], 0, 12U * sizeof(double));
      U[qq] = 1.0;
    }
  }
  for (b_k = 11; b_k >= 0; b_k--) {
    if ((b_k + 1 <= 10) && (e[b_k] != 0.0)) {
      qjj = (b_k + 12 * b_k) + 2;
      for (k = b_k + 2; k < 13; k++) {
        qp1jj = (b_k + 12 * (k - 1)) + 2;
        xaxpy(11 - b_k, -(xdotc(11 - b_k, V, qjj, V, qp1jj) / V[qjj - 1]), qjj,
              V, qp1jj);
      }
    }
    memset(&V[b_k * 12], 0, 12U * sizeof(double));
    V[b_k + 12 * b_k] = 1.0;
  }
  qq = 0;
  snorm = 0.0;
  for (k = 0; k < 12; k++) {
    nrm = s[k];
    if (nrm != 0.0) {
      rt = fabs(nrm);
      nrm /= rt;
      s[k] = rt;
      if (k + 1 < 12) {
        e[k] /= nrm;
      }
      qjj = 12 * k + 1;
      qp1jj = qjj + 12;
      vectorUB = qjj + 10;
      for (b_k = qjj; b_k <= vectorUB; b_k += 2) {
        r = _mm_loadu_pd(&U[b_k - 1]);
        _mm_storeu_pd(&U[b_k - 1], _mm_mul_pd(_mm_set1_pd(nrm), r));
      }
      for (b_k = qp1jj; b_k <= qjj + 11; b_k++) {
        U[b_k - 1] *= nrm;
      }
    }
    if (k + 1 < 12) {
      nrm = e[k];
      if (nrm != 0.0) {
        rt = fabs(nrm);
        nrm = rt / nrm;
        e[k] = rt;
        s[k + 1] *= nrm;
        qjj = 12 * (k + 1) + 1;
        qp1jj = qjj + 12;
        vectorUB = qjj + 10;
        for (b_k = qjj; b_k <= vectorUB; b_k += 2) {
          r = _mm_loadu_pd(&V[b_k - 1]);
          _mm_storeu_pd(&V[b_k - 1], _mm_mul_pd(_mm_set1_pd(nrm), r));
        }
        for (b_k = qp1jj; b_k <= qjj + 11; b_k++) {
          V[b_k - 1] *= nrm;
        }
      }
    }
    snorm = fmax(snorm, fmax(fabs(s[k]), fabs(e[k])));
  }
  while ((m + 1 > 0) && (qq < 75)) {
    boolean_T exitg1;
    qq_tmp = m;
    exitg1 = false;
    while (!(exitg1 || (qq_tmp == 0))) {
      nrm = fabs(e[qq_tmp - 1]);
      if ((nrm <=
           2.220446049250313E-16 * (fabs(s[qq_tmp - 1]) + fabs(s[qq_tmp]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((qq > 20) && (nrm <= 2.220446049250313E-16 * snorm))) {
        e[qq_tmp - 1] = 0.0;
        exitg1 = true;
      } else {
        qq_tmp--;
      }
    }
    if (qq_tmp == m) {
      qjj = 4;
    } else {
      qp1jj = m + 1;
      qjj = m + 1;
      exitg1 = false;
      while (!exitg1 && (qjj >= qq_tmp)) {
        qp1jj = qjj;
        if (qjj == qq_tmp) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 1) {
            nrm = fabs(e[qjj - 1]);
          }
          if (qjj > qq_tmp + 1) {
            nrm += fabs(e[qjj - 2]);
          }
          rt = fabs(s[qjj - 1]);
          if ((rt <= 2.220446049250313E-16 * nrm) ||
              (rt <= 1.0020841800044864E-292)) {
            s[qjj - 1] = 0.0;
            exitg1 = true;
          } else {
            qjj--;
          }
        }
      }
      if (qp1jj == qq_tmp) {
        qjj = 3;
      } else if (qp1jj == m + 1) {
        qjj = 1;
      } else {
        qjj = 2;
        qq_tmp = qp1jj;
      }
    }
    switch (qjj) {
    case 1:
      f = e[m - 1];
      e[m - 1] = 0.0;
      for (b_k = m; b_k >= qq_tmp + 1; b_k--) {
        rt = xrotg(&s[b_k - 1], &f, &nrm);
        if (b_k > qq_tmp + 1) {
          b = e[b_k - 2];
          f = -nrm * b;
          e[b_k - 2] = b * rt;
        }
        xrot(V, 12 * (b_k - 1) + 1, 12 * m + 1, rt, nrm);
      }
      break;
    case 2:
      f = e[qq_tmp - 1];
      e[qq_tmp - 1] = 0.0;
      for (b_k = qq_tmp + 1; b_k <= m + 1; b_k++) {
        rt = xrotg(&s[b_k - 1], &f, &nrm);
        b = e[b_k - 1];
        f = -nrm * b;
        e[b_k - 1] = b * rt;
        xrot(U, 12 * (b_k - 1) + 1, 12 * (qq_tmp - 1) + 1, rt, nrm);
      }
      break;
    case 3: {
      double scale;
      nrm = s[m - 1];
      rt = e[m - 1];
      scale = fmax(
          fmax(fmax(fmax(fabs(s[m]), fabs(nrm)), fabs(rt)), fabs(s[qq_tmp])),
          fabs(e[qq_tmp]));
      sm = s[m] / scale;
      nrm /= scale;
      rt /= scale;
      sqds = s[qq_tmp] / scale;
      b = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
      nrm = sm * rt;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }
        rt = nrm / (b + rt);
      } else {
        rt = 0.0;
      }
      f = (sqds + sm) * (sqds - sm) + rt;
      nrm = sqds * (e[qq_tmp] / scale);
      for (b_k = qq_tmp + 1; b_k <= m; b_k++) {
        b = xrotg(&f, &nrm, &sm);
        if (b_k > qq_tmp + 1) {
          e[b_k - 2] = f;
        }
        nrm = e[b_k - 1];
        rt = s[b_k - 1];
        e[b_k - 1] = b * nrm - sm * rt;
        sqds = sm * s[b_k];
        s[b_k] *= b;
        qjj = 12 * (b_k - 1) + 1;
        qp1jj = 12 * b_k + 1;
        xrot(V, qjj, qp1jj, b, sm);
        s[b_k - 1] = b * rt + sm * nrm;
        rt = xrotg(&s[b_k - 1], &sqds, &b);
        nrm = e[b_k - 1];
        f = rt * nrm + b * s[b_k];
        s[b_k] = -b * nrm + rt * s[b_k];
        nrm = b * e[b_k];
        e[b_k] *= rt;
        xrot(U, qjj, qp1jj, rt, b);
      }
      e[m - 1] = f;
      qq++;
    } break;
    default:
      if (s[qq_tmp] < 0.0) {
        s[qq_tmp] = -s[qq_tmp];
        qjj = 12 * qq_tmp + 1;
        qp1jj = qjj + 12;
        vectorUB = qjj + 10;
        for (b_k = qjj; b_k <= vectorUB; b_k += 2) {
          r = _mm_loadu_pd(&V[b_k - 1]);
          _mm_storeu_pd(&V[b_k - 1], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
        }
        for (b_k = qp1jj; b_k <= qjj + 11; b_k++) {
          V[b_k - 1] = -V[b_k - 1];
        }
      }
      qp1 = qq_tmp + 1;
      while ((qq_tmp + 1 < 12) && (s[qq_tmp] < s[qp1])) {
        rt = s[qq_tmp];
        s[qq_tmp] = s[qp1];
        s[qp1] = rt;
        qp1jj = 12 * qq_tmp + 1;
        qjj = 12 * (qq_tmp + 1) + 1;
        xswap(V, qp1jj, qjj);
        xswap(U, qp1jj, qjj);
        qq_tmp = qp1;
        qp1++;
      }
      qq = 0;
      m--;
      break;
    }
  }
  if (doscale) {
    b_xzlascl(cscale, anrm, s);
  }
}

/* End of code generation (svd.c) */
