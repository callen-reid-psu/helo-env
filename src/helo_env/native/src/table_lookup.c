/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * table_lookup.c
 *
 * Code generation for function 'table_lookup'
 *
 */

/* Include files */
#include "table_lookup.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * function [out] = table_lookup(datin,datout,in)
 */
double b_table_lookup(const double datin[25], const double datout[25],
                      double in)
{
  double out;
  int done;
  int k;
  /* This sub-module is used to do a simple 1-dimensional table look up */
  /* 'table_lookup:5' out=datout(1); */
  out = datout[0];
  /* 'table_lookup:6' if (in<=datin(1)) */
  if (in <= datin[0]) {
    /* 'table_lookup:6' ; */
    /* 'table_lookup:7' done=1; */
    done = 1;
  } else {
    /* 'table_lookup:8' else */
    /* 'table_lookup:9' done=0; */
    done = 0;
  }
  /* 'table_lookup:11' k=1; */
  k = -1;
  /* 'table_lookup:13' while(~done) */
  while (done == 0) {
    double d;
    /* 'table_lookup:13' ; */
    /* 'table_lookup:14' k=k+1; */
    k++;
    /* 'table_lookup:15' if (in<=datin(k)) */
    d = datin[k + 1];
    if (in <= d) {
      /* 'table_lookup:15' ; */
      /* 'table_lookup:16'
       * out=datout(k-1)+(datout(k)-datout(k-1))/(datin(k)-datin(k-1))*(in-datin(k-1));
       */
      out = datout[k] +
            (datout[k + 1] - datout[k]) / (d - datin[k]) * (in - datin[k]);
      /* 'table_lookup:17' done=1; */
      done = 1;
    } else if (k + 2 >= 25) {
      /* 'table_lookup:18' elseif (k>=length(datin)) */
      /* 'table_lookup:18' ; */
      /* 'table_lookup:19' out=datout(k); */
      out = datout[24];
      /* 'table_lookup:20' done=1; */
      done = 1;
    }
  }
  return out;
}

/*
 * function [out] = table_lookup(datin,datout,in)
 */
double table_lookup(const double datin[13], const double datout[13], double in)
{
  double out;
  int done;
  int k;
  /* This sub-module is used to do a simple 1-dimensional table look up */
  /* 'table_lookup:5' out=datout(1); */
  out = datout[0];
  /* 'table_lookup:6' if (in<=datin(1)) */
  if (in <= datin[0]) {
    /* 'table_lookup:6' ; */
    /* 'table_lookup:7' done=1; */
    done = 1;
  } else {
    /* 'table_lookup:8' else */
    /* 'table_lookup:9' done=0; */
    done = 0;
  }
  /* 'table_lookup:11' k=1; */
  k = -1;
  /* 'table_lookup:13' while(~done) */
  while (done == 0) {
    double d;
    /* 'table_lookup:13' ; */
    /* 'table_lookup:14' k=k+1; */
    k++;
    /* 'table_lookup:15' if (in<=datin(k)) */
    d = datin[k + 1];
    if (in <= d) {
      /* 'table_lookup:15' ; */
      /* 'table_lookup:16'
       * out=datout(k-1)+(datout(k)-datout(k-1))/(datin(k)-datin(k-1))*(in-datin(k-1));
       */
      out = datout[k] +
            (datout[k + 1] - datout[k]) / (d - datin[k]) * (in - datin[k]);
      /* 'table_lookup:17' done=1; */
      done = 1;
    } else if (k + 2 >= 13) {
      /* 'table_lookup:18' elseif (k>=length(datin)) */
      /* 'table_lookup:18' ; */
      /* 'table_lookup:19' out=datout(k); */
      out = datout[12];
      /* 'table_lookup:20' done=1; */
      done = 1;
    }
  }
  return out;
}

/* End of code generation (table_lookup.c) */
