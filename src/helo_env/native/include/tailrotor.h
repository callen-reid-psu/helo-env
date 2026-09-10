/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tailrotor.h
 *
 * Code generation for function 'tailrotor'
 *
 */

#ifndef TAILROTOR_H
#define TAILROTOR_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double tailrotor(double xtr, const double xf[12], const double controls[4],
                 const double rotor_if[8], double omega, double atmos_rho,
                 const constants_Struct *constants, double Ftr[3],
                 double Mtr[3], double *Qtr, double ptrNED[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (tailrotor.h) */
