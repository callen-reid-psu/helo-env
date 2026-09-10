/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * RunRevs.h
 *
 * Code generation for function 'RunRevs'
 *
 */

#ifndef RUNREVS_H
#define RUNREVS_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void RunRevs(double x0[39], const double u0[4], double xdot0[39],
             const constants_Struct *constants, double xdotav[12],
             double yav[7]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (RunRevs.h) */
