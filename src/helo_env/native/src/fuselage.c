/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * fuselage.c
 *
 * Code generation for function 'fuselage'
 *
 */

/* Include files */
#include "fuselage.h"
#include "H60Sim_types.h"
#include "rt_nonfinite.h"
#include "table_lookup.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * function [Ff,Mf,pfusNED] = fuselage(xf,VextF,rotor_if,atmos,constants)
 */
void fuselage(const double xf[12], const double rotor_if[8], double atmos_rho,
              const constants_Struct *constants, double Ff[3], double Mf[3],
              double pfusNED[3])
{
  __m128d r;
  __m128d r1;
  __m128d r2;
  double TNED2body[9];
  double Tbw[9];
  double dv[9];
  double ALFWF;
  double BWT;
  double CALFWF;
  double FWT;
  double VXWF;
  double VYWF;
  double WWT;
  double cphi;
  double cpsi;
  double cthe;
  double sphi;
  double spsi;
  double sthe;
  int i;
  /* Fuselage Aerodynamics Model for UH-60A Black Hawk */
  /* Converted from GENHEL AFUSE.F90 code. Converted by Ilker Oruc 2/2016. */
  /* Inputs: Fuselage state, xf */
  /*         rotor_if: Rotor interference - rotor_if(1:2) = [Vz, Vx]'; */
  /*         Constants (parameter) */
  /* 'fuselage:8' R2D = 180./pi; */
  /* 'fuselage:9' RHO = atmos.rho; */
  /* location of Fuselage rel. to CG (in) - manual */
  /* 'fuselage:12' FSWF = constants.FSfus; */
  /* [in] */
  /* 'fuselage:13' WLWF = constants.WLfus; */
  /* [in] */
  /* 'fuselage:14' BLWF = constants.BLfus; */
  /* [in] */
  /* location of CG (in) - manual */
  /* 'fuselage:16' FSCGB = constants.FSCG; */
  /* [in] */
  /* 'fuselage:17' WLCGB = constants.WLCG; */
  /* [in] */
  /* 'fuselage:18' BLCGB = constants.BLCG; */
  /* [in] */
  /* Geometry */
  /* 'fuselage:22' FWT = (FSCGB-FSWF)/12; */
  FWT = (constants->FSCG - constants->FSfus) / 12.0;
  /* [ft] */
  /* 'fuselage:23' WWT = (WLCGB-WLWF)/12; */
  WWT = (constants->WLCG - constants->WLfus) / 12.0;
  /*  [ft] */
  /* 'fuselage:24' BWT = (BLCGB-BLWF)/12; */
  BWT = (constants->BLCG - constants->BLfus) / 12.0;
  /*  [ft] */
  /* Gust velocities */
  /* 'fuselage:27' VXGWF = 0.0; */
  /* 'fuselage:28' VYGWF = 0.0; */
  /* 'fuselage:29' VZGWF = 0.0; */
  /* NED to Body transformation */
  /* 'fuselage:32' sphi=sin(xf(7)); */
  sphi = sin(xf[6]);
  /* 'fuselage:33' cphi=cos(xf(7)); */
  cphi = cos(xf[6]);
  /* 'fuselage:34' sthe=sin(xf(8)); */
  sthe = sin(xf[7]);
  /* 'fuselage:35' cthe=cos(xf(8)); */
  cthe = cos(xf[7]);
  /* 'fuselage:36' spsi=sin(xf(9)); */
  spsi = sin(xf[8]);
  /* 'fuselage:37' cpsi=cos(xf(9)); */
  cpsi = cos(xf[8]);
  /* 'fuselage:38' TNED2body=[            cthe*cpsi               cthe*spsi
   * -sthe; ... */
  /* 'fuselage:39'             (sphi*sthe*cpsi-cphi*spsi)
   * (sphi*sthe*spsi+cphi*cpsi)  sphi*cthe; ... */
  /* 'fuselage:40'             (cphi*sthe*cpsi+sphi*spsi)
   * (cphi*sthe*spsi-sphi*cpsi)  cphi*cthe]; */
  TNED2body[0] = cthe * cpsi;
  TNED2body[3] = cthe * spsi;
  TNED2body[6] = -sthe;
  VXWF = sphi * sthe;
  TNED2body[1] = VXWF * cpsi - cphi * spsi;
  TNED2body[4] = VXWF * spsi + cphi * cpsi;
  TNED2body[7] = sphi * cthe;
  sthe *= cphi;
  TNED2body[2] = sthe * cpsi + sphi * spsi;
  TNED2body[5] = sthe * spsi - sphi * cpsi;
  TNED2body[8] = cphi * cthe;
  /* External velocities in body coordinates */
  /* 'fuselage:42' Vextb=TNED2body*VextF; */
  memset(&pfusNED[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&TNED2body[0]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  r2 = _mm_set1_pd(0.0);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  pfusNED[2] += TNED2body[2] * 0.0;
  r = _mm_loadu_pd(&TNED2body[3]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  pfusNED[2] += TNED2body[5] * 0.0;
  r = _mm_loadu_pd(&TNED2body[6]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  pfusNED[2] += TNED2body[8] * 0.0;
  /* Interference velocities */
  /* 'fuselage:45' VXIWF = rotor_if(2)+Vextb(1); */
  /*  [ft/s] */
  /* 'fuselage:46' VYIWF = 0.0+Vextb(2); */
  /*  [ft/s] */
  /* 'fuselage:47' VZIWF = rotor_if(1)+Vextb(3); */
  /*  [ft/s] */
  /* Air velocity inputs */
  /* 'fuselage:50' VXB=xf(1); */
  /* 'fuselage:51' VYB=xf(2); */
  /* 'fuselage:52' VZB=xf(3); */
  /*  Fuselage velocities in body axes */
  /*  All velocity components in body-fixed coordinate system */
  /*  V*WF   - total velocity at fuselage */
  /*  V*B     - motion velocity of helicopter CG */
  /*  V*GWF   - gust velocity at the fuselage */
  /*  V*IWF   - rotor wash interference on the fuselage */
  /* 'fuselage:60' VXWF = VXB+VXGWF+VXIWF; */
  VXWF = xf[0] + (pfusNED[0] + rotor_if[1]);
  /*  [ft/s] */
  /* 'fuselage:61' VYWF = VYB+VYGWF+VYIWF; */
  VYWF = xf[1] + pfusNED[1];
  /*  [ft/s] */
  /* 'fuselage:62' VZWF = VZB+VZGWF+VZIWF; */
  sphi = xf[2] + (rotor_if[0] + pfusNED[2]);
  /*  [ft/s] */
  /* Angles of attack and sideslip */
  /* 'fuselage:65' AVXWF=abs(VXWF); */
  sthe = fabs(VXWF);
  /* [ft/s] */
  /* 'fuselage:66' if(AVXWF < 0.000001) */
  if (sthe < 1.0E-6) {
    /* 'fuselage:67' AVXWF = 0.000001; */
    sthe = 1.0E-6;
    /* [ft/s] */
  }
  /* 'fuselage:69' ALFWFR = atan(VZWF/AVXWF); */
  /* [rad] */
  /* 'fuselage:70' ALFWF = R2D*ALFWFR; */
  ALFWF = 57.29577951308232 * atan(sphi / sthe);
  /* [deg] */
  /* 'fuselage:72' FVTERM = (VXWF^2)+(VZWF^2); */
  spsi = VXWF * VXWF + sphi * sphi;
  /* [ft^2/s^2] */
  /* 'fuselage:73' if (FVTERM < 0.000001) */
  if (spsi < 1.0E-6) {
    /* 'fuselage:74' FVTERM = 0.000001; */
    spsi = 1.0E-6;
  }
  /* 'fuselage:76' RVTERM = 1/sqrt(FVTERM); */
  sthe = 1.0 / sqrt(spsi);
  /* [s/ft] */
  /* 'fuselage:78' CALFWF = VXWF*RVTERM; */
  CALFWF = VXWF * sthe;
  /* 'fuselage:79' SALFWF = VZWF*RVTERM; */
  cpsi = sphi * sthe;
  /* 'fuselage:81' BETWFR = atan(VYWF*RVTERM); */
  sthe = atan(VYWF * sthe);
  /* [rad] */
  /* 'fuselage:82' BETWF  = R2D*BETWFR; */
  cphi = 57.29577951308232 * sthe;
  /* [deg] */
  /* 'fuselage:83' SBETWF = sin(BETWFR); */
  cthe = sin(sthe);
  /* 'fuselage:84' CBETWF = cos(BETWFR); */
  sphi = cos(sthe);
  /* 'fuselage:86' PSIWF = -BETWF; */
  /* [deg] */
  /* Dynamic pressure */
  /* 'fuselage:89' QWF = 0.5*RHO*(VYWF^2 + FVTERM); */
  sthe = 0.5 * atmos_rho * (VYWF * VYWF + spsi);
  /* [lb/ft^2] */
  /* Fuselage aerodyanmic loading coefficients */
  /* AALFWF = abs(ALFWF); %[deg] */
  /* 'fuselage:93' APSIWF = abs(PSIWF); */
  VXWF = fabs(-cphi);
  /* [deg] */
  /* SGNPSI = sign(PSIWF); */
  /* 'fuselage:96' CDA = table_lookup(constants.FUSEAOA,constants.FUSEDA,ALFWF);
   */
  /* 'fuselage:97' CLA = table_lookup(constants.FUSEAOA,constants.FUSELA,ALFWF);
   */
  /* 'fuselage:98' CMA = table_lookup(constants.FUSEAOA,constants.FUSEMA,ALFWF);
   */
  /* Functions of sideslip angle */
  /* 'fuselage:101' CLB =
   * table_lookup(constants.FUSEBETA,constants.FUSELB,PSIWF); */
  /* 'fuselage:102' CMB =
   * table_lookup(constants.FUSEABETA,constants.FUSEMB,APSIWF); */
  /* 'fuselage:103' CDB =
   * table_lookup(constants.FUSEABETA,constants.FUSEDB,APSIWF); */
  /* 'fuselage:104' CYB =
   * table_lookup(constants.FUSEBETA,constants.FUSEYB,PSIWF); */
  /* 'fuselage:105' CRB =
   * table_lookup(constants.FUSEBETA,constants.FUSERB,PSIWF); */
  /* 'fuselage:106' CNB =
   * table_lookup(constants.FUSEBETA,constants.FUSENB,PSIWF); */
  /* 'fuselage:108' CDTOT = CDA + CDB; */
  /* 'fuselage:109' CLTOT = CLA + CLB; */
  /* 'fuselage:110' CYTOT = CYB; */
  /* 'fuselage:112' CRTOT = CRB; */
  /* 'fuselage:113' CMTOT = CMA + CMB; */
  /* 'fuselage:114' CNTOT = CNB; */
  /* Transform forces and moments from wind axes to body axes */
  /* 'fuselage:118' Tbw=[CALFWF*CBETWF CALFWF*SBETWF -SALFWF; ... */
  /* 'fuselage:119'         SBETWF        -CBETWF        0.; .... */
  /* 'fuselage:120'      SALFWF*CBETWF  SALFWF*SBETWF  CALFWF]; */
  Tbw[0] = CALFWF * sphi;
  Tbw[3] = CALFWF * cthe;
  Tbw[6] = -cpsi;
  Tbw[1] = cthe;
  Tbw[4] = -sphi;
  Tbw[7] = 0.0;
  Tbw[2] = cpsi * sphi;
  Tbw[5] = cpsi * cthe;
  Tbw[8] = CALFWF;
  /* . */
  /* 'fuselage:122' Ffw=-QWF*[CDTOT;CYTOT;CLTOT]; */
  /* 'fuselage:123' Ff=Tbw*Ffw; */
  pfusNED[0] =
      -sthe * (b_table_lookup(constants->FUSEAOA, constants->FUSEDA, ALFWF) +
               table_lookup(constants->FUSEABETA, constants->FUSEDB, VXWF));
  pfusNED[1] =
      -sthe * b_table_lookup(constants->FUSEBETA, constants->FUSEYB, -cphi);
  pfusNED[2] =
      -sthe * (b_table_lookup(constants->FUSEAOA, constants->FUSELA, ALFWF) +
               b_table_lookup(constants->FUSEBETA, constants->FUSELB, -cphi));
  memset(&Ff[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Tbw[0]);
  r1 = _mm_loadu_pd(&Ff[0]);
  _mm_storeu_pd(&Ff[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(pfusNED[0]))));
  Ff[2] += pfusNED[0] * Tbw[2];
  r = _mm_loadu_pd(&Tbw[3]);
  r1 = _mm_loadu_pd(&Ff[0]);
  _mm_storeu_pd(&Ff[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(pfusNED[1]))));
  Ff[2] += pfusNED[1] * Tbw[5];
  r = _mm_loadu_pd(&Tbw[6]);
  r1 = _mm_loadu_pd(&Ff[0]);
  _mm_storeu_pd(&Ff[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(pfusNED[2]))));
  Ff[2] += pfusNED[2] * CALFWF;
  /* 'fuselage:124' Mf=Tbw*QWF*[CRTOT;-CMTOT;CNTOT]+[0. -WWT  BWT; WWT 0. -FWT;
   * -BWT FWT 0.]*Ff; */
  pfusNED[0] = b_table_lookup(constants->FUSEBETA, constants->FUSERB, -cphi);
  pfusNED[1] = -(b_table_lookup(constants->FUSEAOA, constants->FUSEMA, ALFWF) +
                 table_lookup(constants->FUSEABETA, constants->FUSEMB, VXWF));
  pfusNED[2] = b_table_lookup(constants->FUSEBETA, constants->FUSENB, -cphi);
  dv[0] = 0.0;
  dv[3] = -WWT;
  dv[6] = BWT;
  dv[1] = WWT;
  dv[4] = 0.0;
  dv[7] = -FWT;
  dv[2] = -BWT;
  dv[5] = FWT;
  dv[8] = 0.0;
  memset(&Mf[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Tbw[0]);
  r1 = _mm_loadu_pd(&Mf[0]);
  r2 = _mm_set1_pd(sthe);
  _mm_storeu_pd(&Mf[0], _mm_add_pd(r1, _mm_mul_pd(_mm_mul_pd(r, r2),
                                                  _mm_set1_pd(pfusNED[0]))));
  Mf[2] += Tbw[2] * sthe * pfusNED[0];
  r = _mm_loadu_pd(&Tbw[3]);
  r1 = _mm_loadu_pd(&Mf[0]);
  _mm_storeu_pd(&Mf[0], _mm_add_pd(r1, _mm_mul_pd(_mm_mul_pd(r, r2),
                                                  _mm_set1_pd(pfusNED[1]))));
  Mf[2] += Tbw[5] * sthe * pfusNED[1];
  r = _mm_loadu_pd(&Tbw[6]);
  r1 = _mm_loadu_pd(&Mf[0]);
  _mm_storeu_pd(&Mf[0], _mm_add_pd(r1, _mm_mul_pd(_mm_mul_pd(r, r2),
                                                  _mm_set1_pd(pfusNED[2]))));
  Mf[2] += CALFWF * sthe * pfusNED[2];
  memset(&pfusNED[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&dv[0]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Ff[0]))));
  pfusNED[2] += Ff[0] * -BWT;
  r = _mm_loadu_pd(&dv[3]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Ff[1]))));
  pfusNED[2] += Ff[1] * FWT;
  r = _mm_loadu_pd(&dv[6]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&pfusNED[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Ff[2]))));
  pfusNED[2] += 0.0 * Ff[2];
  r = _mm_loadu_pd(&Mf[0]);
  r1 = _mm_loadu_pd(&pfusNED[0]);
  _mm_storeu_pd(&Mf[0], _mm_add_pd(r, r1));
  Mf[2] += pfusNED[2];
  /* 'fuselage:126' pfusNED=xf(10:12)+TNED2body'*[FWT;BWT;WWT]; */
  for (i = 0; i < 3; i++) {
    pfusNED[i] =
        xf[i + 9] + ((TNED2body[3 * i] * FWT + TNED2body[3 * i + 1] * BWT) +
                     TNED2body[3 * i + 2] * WWT);
  }
}

/* End of code generation (fuselage.c) */
