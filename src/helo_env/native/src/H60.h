/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * H60.h
 *
 * Code generation for function 'H60'
 *
 */

#ifndef H60_H
#define H60_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void H60(const double x[39], const double xdot[39],
         const constants_Struct *constants, double x_dot[39], double y[7]);

void b_H60(const double x[39], const double u[4], const double xdot[39],
           const constants_Struct *constants, double x_dot[39], double y[7]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (H60.h) */
