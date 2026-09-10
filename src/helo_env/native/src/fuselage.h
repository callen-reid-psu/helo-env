/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fuselage.h
 *
 * Code generation for function 'fuselage'
 *
 */

#ifndef FUSELAGE_H
#define FUSELAGE_H

/* Include files */
#include "H60Sim_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void fuselage(const double xf[12], const double rotor_if[8], double atmos_rho,
              const constants_Struct *constants, double Ff[3], double Mf[3],
              double pfusNED[3]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (fuselage.h) */
