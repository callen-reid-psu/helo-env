/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * StepH60.c
 *
 * Code generation for function 'StepH60'
 *
 */

/* Include files */
#include "StepH60.h"
#include "H60.h"
#include "H60Sim_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * function [xnew,ynew,xdotnew]= StepH60(x,u,xdot,dt,constants)
 */
void StepH60(const double x[39], const double u[4], const double xdot[39],
             double dt, const constants_Struct *constants, double xnew[39],
             double ynew[7], double xdotnew[39])
{
  __m128d r;
  __m128d r1;
  double k2[39];
  double k3[39];
  double k4[39];
  double d;
  int i;
  /* Performs one 4th order Runge-Kutta Integration Step of H-60 Simulation */
  /* 'StepH60:5' [xd,~]=H60(x,u,xdot,constants); */
  b_H60(x, u, xdot, constants, xnew, ynew);
  /* 'StepH60:6' k1=dt*xd; */
  /* 'StepH60:7' [xd,~]=H60(x+0.5*k1,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&xnew[i]);
    r = _mm_mul_pd(_mm_set1_pd(dt), r);
    _mm_storeu_pd(&xnew[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = dt * xnew[38];
  xnew[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  b_H60(xdotnew, u, xdot, constants, k2, ynew);
  /* 'StepH60:8' k2=dt*xd; */
  /* 'StepH60:9' [xd,~]=H60(x+0.5*k2,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k2[i]);
    r = _mm_mul_pd(_mm_set1_pd(dt), r);
    _mm_storeu_pd(&k2[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = dt * k2[38];
  k2[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  b_H60(xdotnew, u, xdot, constants, k3, ynew);
  /* 'StepH60:10' k3=dt*xd; */
  /* 'StepH60:11' [xd,~]=H60(x+k3,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k3[i]);
    r = _mm_mul_pd(_mm_set1_pd(dt), r);
    _mm_storeu_pd(&k3[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]), r));
  }
  d = dt * k3[38];
  k3[38] = d;
  xdotnew[38] = x[38] + d;
  b_H60(xdotnew, u, xdot, constants, k4, ynew);
  /* 'StepH60:12' k4=dt*xd; */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(&k4[i], _mm_mul_pd(_mm_set1_pd(dt), r));
  }
  k4[38] *= dt;
  /* 'StepH60:13' if (constants.IFREEZE == 1) */
  if (constants->IFREEZE == 1.0) {
    /*  Don't update fuselage states in freeze mode */
    /* 'StepH60:15' k1(1:12)=0; */
    /* 'StepH60:16' k2(1:12)=0; */
    /* 'StepH60:17' k3(1:12)=0; */
    /* 'StepH60:18' k4(1:12)=0; */
    memset(&xnew[0], 0, 12U * sizeof(double));
    memset(&k2[0], 0, 12U * sizeof(double));
    memset(&k3[0], 0, 12U * sizeof(double));
    memset(&k4[0], 0, 12U * sizeof(double));
  }
  /* 'StepH60:20' xnew=x+k1/6+k2/3+k3/3+k4/6; */
  r = _mm_set1_pd(3.0);
  r1 = _mm_set1_pd(6.0);
  for (i = 0; i <= 36; i += 2) {
    __m128d r2;
    __m128d r3;
    __m128d r4;
    __m128d r5;
    r2 = _mm_loadu_pd(&xnew[i]);
    r3 = _mm_loadu_pd(&k2[i]);
    r4 = _mm_loadu_pd(&k3[i]);
    r5 = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(
        &xnew[i],
        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_loadu_pd(&x[i]),
                                                    _mm_div_pd(r2, r1)),
                                         _mm_div_pd(r3, r)),
                              _mm_div_pd(r4, r)),
                   _mm_div_pd(r5, r1)));
  }
  xnew[38] =
      (((x[38] + xnew[38] / 6.0) + k2[38] / 3.0) + k3[38] / 3.0) + k4[38] / 6.0;
  /* 'StepH60:22' [xdotnew,ynew]=H60(xnew,u,xdot,constants); */
  b_H60(xnew, u, xdot, constants, xdotnew, ynew);
}

/*
 * function [xnew,ynew,xdotnew]= StepH60(x,u,xdot,dt,constants)
 */
void b_StepH60(const double x[39], const double xdot[39],
               const constants_Struct *constants, double xnew[39],
               double ynew[7], double xdotnew[39])
{
  __m128d r;
  __m128d r1;
  double k2[39];
  double k3[39];
  double k4[39];
  double d;
  int i;
  /* Performs one 4th order Runge-Kutta Integration Step of H-60 Simulation */
  /* 'StepH60:5' [xd,~]=H60(x,u,xdot,constants); */
  H60(x, xdot, constants, xnew, ynew);
  /* 'StepH60:6' k1=dt*xd; */
  /* 'StepH60:7' [xd,~]=H60(x+0.5*k1,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&xnew[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&xnew[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = 0.006464182414793813 * xnew[38];
  xnew[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  H60(xdotnew, xdot, constants, k2, ynew);
  /* 'StepH60:8' k2=dt*xd; */
  /* 'StepH60:9' [xd,~]=H60(x+0.5*k2,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k2[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&k2[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = 0.006464182414793813 * k2[38];
  k2[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  H60(xdotnew, xdot, constants, k3, ynew);
  /* 'StepH60:10' k3=dt*xd; */
  /* 'StepH60:11' [xd,~]=H60(x+k3,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k3[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&k3[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]), r));
  }
  d = 0.006464182414793813 * k3[38];
  k3[38] = d;
  xdotnew[38] = x[38] + d;
  H60(xdotnew, xdot, constants, k4, ynew);
  /* 'StepH60:12' k4=dt*xd; */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(&k4[i], _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r));
  }
  k4[38] *= 0.006464182414793813;
  /* 'StepH60:13' if (constants.IFREEZE == 1) */
  /*  Don't update fuselage states in freeze mode */
  /* 'StepH60:15' k1(1:12)=0; */
  /* 'StepH60:16' k2(1:12)=0; */
  /* 'StepH60:17' k3(1:12)=0; */
  /* 'StepH60:18' k4(1:12)=0; */
  memset(&xnew[0], 0, 12U * sizeof(double));
  memset(&k2[0], 0, 12U * sizeof(double));
  memset(&k3[0], 0, 12U * sizeof(double));
  memset(&k4[0], 0, 12U * sizeof(double));
  /* 'StepH60:20' xnew=x+k1/6+k2/3+k3/3+k4/6; */
  r = _mm_set1_pd(3.0);
  r1 = _mm_set1_pd(6.0);
  for (i = 0; i <= 36; i += 2) {
    __m128d r2;
    __m128d r3;
    __m128d r4;
    __m128d r5;
    r2 = _mm_loadu_pd(&xnew[i]);
    r3 = _mm_loadu_pd(&k2[i]);
    r4 = _mm_loadu_pd(&k3[i]);
    r5 = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(
        &xnew[i],
        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_loadu_pd(&x[i]),
                                                    _mm_div_pd(r2, r1)),
                                         _mm_div_pd(r3, r)),
                              _mm_div_pd(r4, r)),
                   _mm_div_pd(r5, r1)));
  }
  xnew[38] =
      (((x[38] + xnew[38] / 6.0) + k2[38] / 3.0) + k3[38] / 3.0) + k4[38] / 6.0;
  /* 'StepH60:22' [xdotnew,ynew]=H60(xnew,u,xdot,constants); */
  H60(xnew, xdot, constants, xdotnew, ynew);
}

/*
 * function [xnew,ynew,xdotnew]= StepH60(x,u,xdot,dt,constants)
 */
void c_StepH60(const double x[39], const double u[4], const double xdot[39],
               const constants_Struct *constants, double xnew[39],
               double ynew[7], double xdotnew[39])
{
  __m128d r;
  __m128d r1;
  double k2[39];
  double k3[39];
  double k4[39];
  double d;
  int i;
  /* Performs one 4th order Runge-Kutta Integration Step of H-60 Simulation */
  /* 'StepH60:5' [xd,~]=H60(x,u,xdot,constants); */
  b_H60(x, u, xdot, constants, xnew, ynew);
  /* 'StepH60:6' k1=dt*xd; */
  /* 'StepH60:7' [xd,~]=H60(x+0.5*k1,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&xnew[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&xnew[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = 0.006464182414793813 * xnew[38];
  xnew[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  b_H60(xdotnew, u, xdot, constants, k2, ynew);
  /* 'StepH60:8' k2=dt*xd; */
  /* 'StepH60:9' [xd,~]=H60(x+0.5*k2,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k2[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&k2[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]),
                                          _mm_mul_pd(_mm_set1_pd(0.5), r)));
  }
  d = 0.006464182414793813 * k2[38];
  k2[38] = d;
  xdotnew[38] = x[38] + 0.5 * d;
  b_H60(xdotnew, u, xdot, constants, k3, ynew);
  /* 'StepH60:10' k3=dt*xd; */
  /* 'StepH60:11' [xd,~]=H60(x+k3,u,xdot,constants); */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k3[i]);
    r = _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r);
    _mm_storeu_pd(&k3[i], r);
    _mm_storeu_pd(&xdotnew[i], _mm_add_pd(_mm_loadu_pd(&x[i]), r));
  }
  d = 0.006464182414793813 * k3[38];
  k3[38] = d;
  xdotnew[38] = x[38] + d;
  b_H60(xdotnew, u, xdot, constants, k4, ynew);
  /* 'StepH60:12' k4=dt*xd; */
  for (i = 0; i <= 36; i += 2) {
    r = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(&k4[i], _mm_mul_pd(_mm_set1_pd(0.006464182414793813), r));
  }
  k4[38] *= 0.006464182414793813;
  /* 'StepH60:13' if (constants.IFREEZE == 1) */
  /*  Don't update fuselage states in freeze mode */
  /* 'StepH60:15' k1(1:12)=0; */
  /* 'StepH60:16' k2(1:12)=0; */
  /* 'StepH60:17' k3(1:12)=0; */
  /* 'StepH60:18' k4(1:12)=0; */
  memset(&xnew[0], 0, 12U * sizeof(double));
  memset(&k2[0], 0, 12U * sizeof(double));
  memset(&k3[0], 0, 12U * sizeof(double));
  memset(&k4[0], 0, 12U * sizeof(double));
  /* 'StepH60:20' xnew=x+k1/6+k2/3+k3/3+k4/6; */
  r = _mm_set1_pd(3.0);
  r1 = _mm_set1_pd(6.0);
  for (i = 0; i <= 36; i += 2) {
    __m128d r2;
    __m128d r3;
    __m128d r4;
    __m128d r5;
    r2 = _mm_loadu_pd(&xnew[i]);
    r3 = _mm_loadu_pd(&k2[i]);
    r4 = _mm_loadu_pd(&k3[i]);
    r5 = _mm_loadu_pd(&k4[i]);
    _mm_storeu_pd(
        &xnew[i],
        _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_loadu_pd(&x[i]),
                                                    _mm_div_pd(r2, r1)),
                                         _mm_div_pd(r3, r)),
                              _mm_div_pd(r4, r)),
                   _mm_div_pd(r5, r1)));
  }
  xnew[38] =
      (((x[38] + xnew[38] / 6.0) + k2[38] / 3.0) + k3[38] / 3.0) + k4[38] / 6.0;
  /* 'StepH60:22' [xdotnew,ynew]=H60(xnew,u,xdot,constants); */
  b_H60(xnew, u, xdot, constants, xdotnew, ynew);
}

/* End of code generation (StepH60.c) */
