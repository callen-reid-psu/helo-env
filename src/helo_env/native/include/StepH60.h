/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * StepH60.h
 *
 * Code generation for function 'StepH60'
 *
 */

#ifndef STEPH60_H
#define STEPH60_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void StepH60(const double x[39], const double u[4],
                    const double xdot[39], double dt,
                    const constants_Struct *constants, double xnew[39],
                    double ynew[7], double xdotnew[39]);

void b_StepH60(const double x[39], const double xdot[39],
               const constants_Struct *constants, double xnew[39],
               double ynew[7], double xdotnew[39]);

void c_StepH60(const double x[39], const double u[4], const double xdot[39],
               const constants_Struct *constants, double xnew[39],
               double ynew[7], double xdotnew[39]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (StepH60.h) */
