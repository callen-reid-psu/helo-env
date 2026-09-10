/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzlascl.c
 *
 * Code generation for function 'xzlascl'
 *
 */

/* Include files */
#include "xzlascl.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 *
 */
void b_xzlascl(double cfrom, double cto, double A[12])
{
  double cfromc;
  double ctoc;
  int i;
  boolean_T notdone;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.004168360008973E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
      mul = 2.004168360008973E-292;
      cfromc = cfrom1;
    } else if (cto1 > cfromc) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }
    for (i = 0; i <= 10; i += 2) {
      _mm_storeu_pd(&A[i], _mm_mul_pd(_mm_loadu_pd(&A[i]), _mm_set1_pd(mul)));
    }
  }
}

/*
 *
 */
void xzlascl(double cfrom, double cto, double A[144])
{
  double cfromc;
  double ctoc;
  int i;
  boolean_T notdone;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    double cfrom1;
    double cto1;
    double mul;
    cfrom1 = cfromc * 2.004168360008973E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
      mul = 2.004168360008973E-292;
      cfromc = cfrom1;
    } else if (cto1 > cfromc) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }
    for (i = 0; i <= 142; i += 2) {
      __m128d r;
      r = _mm_loadu_pd(&A[i]);
      r = _mm_mul_pd(r, _mm_set1_pd(mul));
      _mm_storeu_pd(&A[i], r);
    }
  }
}

/* End of code generation (xzlascl.c) */
