/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eqnmot.h
 *
 * Code generation for function 'eqnmot'
 *
 */

#ifndef EQNMOT_H
#define EQNMOT_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void eqnmot(const double xf[12], const double Ftot[3], const double Mtot[3],
            double constants_g, double constants_MASS, double constants_IX,
            double constants_IY, double constants_IZ, double constants_IXZ,
            double xf_dot[12]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (eqnmot.h) */
