/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * QSInflowComp.c
 *
 * Code generation for function 'QSInflowComp'
 *
 */

/* Include files */
#include "QSInflowComp.h"
#include "H60Sim_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * function [lambda0_qs,NoConverge] = QSInflowComp(CT,muzs,mu,Kge)
 */
double QSInflowComp(double CT, double muzs, double mu, double Kge,
                    double *NoConverge)
{
  double a;
  double d;
  double delta_lambda;
  double lambda0_qs;
  double lambdah2;
  int iter;
  /*  Iteration to solve for quasi-steady lambda0 */
  /* 'QSInflowComp:4' delta_lambda=10.; */
  delta_lambda = 10.0;
  /* 'QSInflowComp:5' iter=0; */
  iter = 0;
  /* 'QSInflowComp:6' itermax=70; */
  /*  check if we should use iterative apporach or approximation for VRS/TWS */
  /*  Rotorcraft Aeromechanics p.126, Eq 5.10-5.14 */
  /* 'QSInflowComp:10' if(CT < 0) */
  if (CT < 0.0) {
    /*  flip the values of CT and muzs, instead of reverse thrust, we are */
    /*  doing steep descent */
    /* 'QSInflowComp:13' CT = -CT; */
    CT = -CT;
    /* 'QSInflowComp:14' muzs = -muzs; */
    muzs = -muzs;
    /*  shouldn't need to flip mu since it only appears as a squared term */
  }
  /* 'QSInflowComp:17' lambdah2 = CT/2; */
  lambdah2 = CT / 2.0;
  /* 'QSInflowComp:18' lambdah = sqrt(lambdah2); */
  lambda0_qs = sqrt(lambdah2);
  /* 'QSInflowComp:19' lambda0_qs=lambdah; */
  /* 'QSInflowComp:20' inflowCond = 1.5*(mu^2)+(-2*muzs+3*(lambdah))^2 -
   * lambdah2; */
  a = -2.0 * muzs + 3.0 * lambda0_qs;
  /*  use newton-raphson iteration in climb and windmill brake state */
  /* 'QSInflowComp:23' if inflowCond >= 0 */
  d = mu * mu;
  if ((1.5 * d + a * a) - lambdah2 >= 0.0) {
    /* 'QSInflowComp:24' while( (abs(delta_lambda)>1e-9) && (iter<itermax) ) */
    while ((fabs(delta_lambda) > 1.0E-9) && (iter < 70)) {
      /*  Newton-Raphson method */
      /* 'QSInflowComp:26' Lambda = mu^2+(lambda0_qs-muzs)^2; */
      delta_lambda = lambda0_qs - muzs;
      delta_lambda = d + delta_lambda * delta_lambda;
      /* 'QSInflowComp:27' delta_lambda =
       * -(2*lambda0_qs*Lambda^0.5-Kge*CT)*Lambda/(2*Lambda^1.5-Kge*CT*(muzs-lambda0_qs));
       */
      lambdah2 = Kge * CT;
      delta_lambda = -(2.0 * lambda0_qs * sqrt(delta_lambda) - lambdah2) *
                     delta_lambda /
                     (2.0 * rt_powd_snf(delta_lambda, 1.5) -
                      lambdah2 * (muzs - lambda0_qs));
      /* 'QSInflowComp:28' lambda0_qs = lambda0_qs+0.5*delta_lambda; */
      lambda0_qs += 0.5 * delta_lambda;
      /* 'QSInflowComp:29' iter=iter+1; */
      iter++;
    }
  } else {
    /* 'QSInflowComp:31' else */
    /*  use the approximation for vortex ring state / turbulent wake state */
    /* 'QSInflowComp:33' delta_lambda = 0; */
    /* 'QSInflowComp:34' iter = -1; */
    iter = -1;
    /* 'QSInflowComp:35' lambda0_qs = -muzs * ((0.373*muzs^2 +
     * 0.598*mu^2)/(lambdah2) - 0.991)  + muzs; */
    lambda0_qs =
        -muzs * ((0.373 * (muzs * muzs) + 0.598 * d) / lambdah2 - 0.991) + muzs;
  }
  /* 'QSInflowComp:38' if (iter>=itermax) */
  if (iter >= 70) {
    /* 'QSInflowComp:39' NoConverge=1; */
    *NoConverge = 1.0;
  } else {
    /* 'QSInflowComp:40' else */
    /* 'QSInflowComp:41' NoConverge=0; */
    *NoConverge = 0.0;
  }
  return lambda0_qs;
}

/* End of code generation (QSInflowComp.c) */
