/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RunRevs.c
 *
 * Code generation for function 'RunRevs'
 *
 */

/* Include files */
#include "RunRevs.h"
#include "H60Sim_types.h"
#include "StepH60.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * function [xdotav, x, xdot, yav] = RunRevs(x0,u0,xdot0,dt,constants)
 */
void RunRevs(double x0[39], const double u0[4], double xdot0[39],
             const constants_Struct *constants, double xdotav[12],
             double yav[7])
{
  __m128d r;
  double b_x0[39];
  double b_xdot0[39];
  double a__1[7];
  int b_i;
  int i;
  /* 'RunRevs:3' x = x0; */
  /* 'RunRevs:4' u = u0; */
  /* 'RunRevs:5' xdot = xdot0; */
  /* Run revolutions to convergence */
  /* 'RunRevs:8' for istep = 1:constants.NREVSTEP*constants.NREVCONV */
  for (i = 0; i < 72; i++) {
    /* 'RunRevs:9' [x,~,xdot] = StepH60(x,u,xdot,dt,constants); */
    memcpy(&b_x0[0], &x0[0], 39U * sizeof(double));
    memcpy(&b_xdot0[0], &xdot0[0], 39U * sizeof(double));
    c_StepH60(b_x0, u0, b_xdot0, constants, x0, a__1, xdot0);
  }
  /* Run revolutions to average */
  /* 'RunRevs:13' Navg = constants.NREVSTEP*constants.NREVAVERAGE; */
  /* 'RunRevs:14' xdotav = zeros(SizeConstants.NFSTATES,1); */
  memset(&xdotav[0], 0, 12U * sizeof(double));
  /* 'RunRevs:15' yav = zeros(SizeConstants.NOUT,1); */
  for (i = 0; i < 7; i++) {
    yav[i] = 0.0;
  }
  /* 'RunRevs:16' for istep = 1:Navg */
  r = _mm_set1_pd(36.0);
  for (i = 0; i < 36; i++) {
    __m128d r1;
    /* 'RunRevs:17' [x,y,xdot] = StepH60(x,u,xdot,dt,constants); */
    memcpy(&b_x0[0], &x0[0], 39U * sizeof(double));
    memcpy(&b_xdot0[0], &xdot0[0], 39U * sizeof(double));
    c_StepH60(b_x0, u0, b_xdot0, constants, x0, a__1, xdot0);
    /* 'RunRevs:18' xdotav = xdotav + xdot(SizeConstants.IDXF)/Navg; */
    for (b_i = 0; b_i <= 10; b_i += 2) {
      r1 = _mm_loadu_pd(&xdotav[b_i]);
      _mm_storeu_pd(&xdotav[b_i],
                    _mm_add_pd(r1, _mm_div_pd(_mm_loadu_pd(&xdot0[b_i]),
                                              _mm_set1_pd(36.0))));
    }
    __m128d r2;
    /* 'RunRevs:19' yav = yav + y/Navg; */
    r1 = _mm_loadu_pd(&a__1[0]);
    r2 = _mm_loadu_pd(&yav[0]);
    _mm_storeu_pd(&yav[0], _mm_add_pd(r2, _mm_div_pd(r1, r)));
    r1 = _mm_loadu_pd(&a__1[2]);
    r2 = _mm_loadu_pd(&yav[2]);
    _mm_storeu_pd(&yav[2], _mm_add_pd(r2, _mm_div_pd(r1, r)));
    r1 = _mm_loadu_pd(&a__1[4]);
    r2 = _mm_loadu_pd(&yav[4]);
    _mm_storeu_pd(&yav[4], _mm_add_pd(r2, _mm_div_pd(r1, r)));
    yav[6] += a__1[6] / 36.0;
  }
}

/* End of code generation (RunRevs.c) */
