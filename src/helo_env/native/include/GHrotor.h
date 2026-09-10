/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GHrotor.h
 *
 * Code generation for function 'GHrotor'
 *
 */

#ifndef GHROTOR_H
#define GHROTOR_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void GHrotor(const double x[24], const double u[23], double atmos_rho,
             double atmos_spsnd, const constants_Struct *constants,
             double xdot[24], double y[133]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (GHrotor.h) */
