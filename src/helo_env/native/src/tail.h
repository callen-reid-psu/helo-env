/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tail.h
 *
 * Code generation for function 'tail'
 *
 */

#ifndef TAIL_H
#define TAIL_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void tail(const double xf[12], double elev, const double rotor_if[8],
          double idxtail, double atmos_rho, const constants_Struct *constants,
          double Ft[3], double Mt[3], double ptNED[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (tail.h) */
