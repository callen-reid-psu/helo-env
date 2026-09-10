/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * interp1.h
 *
 * Code generation for function 'interp1'
 *
 */

#ifndef INTERP1_H
#define INTERP1_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_interp1(const double varargin_1[181], const double varargin_2[181],
               const double varargin_3[40], double Vq[40]);

double c_interp1(const double varargin_1[4], const double varargin_2[4],
                 double varargin_3);

void interp1(const double varargin_1[21], const double varargin_2[21],
             const double varargin_3[10], double Vq[10]);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (interp1.h) */
