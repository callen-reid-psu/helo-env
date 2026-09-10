/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * table_lookup.h
 *
 * Code generation for function 'table_lookup'
 *
 */

#ifndef TABLE_LOOKUP_H
#define TABLE_LOOKUP_H

/* Include files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double b_table_lookup(const double datin[25], const double datout[25],
                      double in);

double table_lookup(const double datin[13], const double datout[13], double in);

#ifdef __cplusplus
}
#endif

#endif
/* End of code generation (table_lookup.h) */
