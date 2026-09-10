/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * InitFcnH60.h
 *
 * Code generation for function 'InitFcnH60'
 *
 */

#ifndef INITFCNH60_H
#define INITFCNH60_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void InitFcnH60(FlightConditions_Struct *FlightConditions, double x0[39],
                       double u0[4], double xdot0[39], double b_y0[7],
                       double *itrim, constants_Struct *constants);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (InitFcnH60.h) */
