/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * GHrotor.c
 *
 * Code generation for function 'GHrotor'
 *
 */

/* Include files */
#include "GHrotor.h"
#include "H60Sim_rtwutil.h"
#include "H60Sim_types.h"
#include "QSInflowComp.h"
#include "atan2.h"
#include "diag.h"
#include "interp1.h"
#include "interp2.h"
#include "mod.h"
#include "mrdivide_helper.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Definitions */
/*
 * function [xdot,y] = GHrotor(x,u,atmos,constants)
 */
void GHrotor(const double x[24], const double u[23], double atmos_rho,
             double atmos_spsnd, const constants_Struct *constants,
             double xdot[24], double y[133])
{
  static const double b[9] = {1.8407769454627694, 0.0, 0.0, 0.0,
                              8.835729338221293,  0.0, 0.0, 0.0,
                              8.835729338221293};
  static const signed char iv[4] = {-1, 1, -1, 1};
  __m128d r;
  __m128d r1;
  __m128d r10;
  __m128d r11;
  __m128d r12;
  __m128d r13;
  __m128d r14;
  __m128d r15;
  __m128d r16;
  __m128d r17;
  __m128d r18;
  __m128d r2;
  __m128d r3;
  __m128d r4;
  __m128d r5;
  __m128d r6;
  __m128d r7;
  __m128d r8;
  __m128d r9;
  double b_Ur_tmp[120];
  double b_y_tmp[120];
  double d_Tbody2NED[120];
  double CL[40];
  double Mach[40];
  double Machtab[40];
  double Up[40];
  double Ur[40];
  double Ut[40];
  double acosgam[40];
  double alphay[40];
  double atrans0[40];
  double atransBtab[40];
  double atrans_tmp[40];
  double b_Fpb[40];
  double b_cbeta[40];
  double cosgam[40];
  double theta[40];
  double LIBC2MBCddot[16];
  double LMBC2IBC[16];
  double LMBC2IBCdot[16];
  double xdot_tmp[16];
  double dv1[10];
  double Tbody2NED[9];
  double Ts2w[9];
  double b_Tbody2NED[9];
  double b_Ts2w[9];
  double delL1[9];
  double delL2[9];
  double delL3[9];
  double y_tmp[9];
  double Fld[4];
  double Fpb[4];
  double Frb[4];
  double Ftb[4];
  double Fxa_tmp[4];
  double Fxt[4];
  double Fyt[4];
  double LIBC2MBCdot_tmp[4];
  double Mf_aero[4];
  double Up_tmp[4];
  double Ur_tmp[4];
  double b_Fxa_tmp[4];
  double b_y[4];
  double beta[4];
  double beta_ddot[4];
  double beta_dot[4];
  double c_y[4];
  double cbeta[4];
  double cpsi[4];
  double cpsizeta[4];
  double czeta[4];
  double psi[4];
  double sbeta[4];
  double spsi[4];
  double spsizeta[4];
  double szeta[4];
  double thetab[4];
  double xld_tmp_tmp[4];
  double zeta[4];
  double zeta_ddot[4];
  double zeta_dot[4];
  double c_Tbody2NED[3];
  double lambda_dot[3];
  double temp[3];
  double dv[2];
  double CTa;
  double CTa_tmp;
  double Hforce;
  double KR;
  double Lhub;
  double Mhub;
  double Tbody2NED_tmp;
  double Veq;
  double Vxsdot;
  double Vysdot;
  double Vzsdot;
  double Xh;
  double Yh;
  double Zh;
  double a;
  double b_a;
  double b_beta_ddot_tmp_idx_0;
  double b_beta_ddot_tmp_idx_1;
  double b_beta_ddot_tmp_idx_2;
  double b_beta_ddot_tmp_idx_3;
  double b_y_idx_0;
  double b_y_idx_1;
  double b_y_idx_2;
  double b_zeta_ddot_tmp_idx_1;
  double b_zeta_ddot_tmp_idx_2;
  double beta_ddot_tmp_idx_0;
  double beta_ddot_tmp_idx_1;
  double beta_ddot_tmp_idx_2;
  double beta_ddot_tmp_idx_3;
  double c;
  double c_a;
  double c_beta_ddot_tmp_idx_0;
  double c_beta_ddot_tmp_idx_1;
  double c_beta_ddot_tmp_idx_2;
  double c_beta_ddot_tmp_idx_3;
  double cbetawind;
  double cphi;
  double cpsiE;
  double cthe;
  double d;
  double d1;
  double d10;
  double d2;
  double d3;
  double d4;
  double d5;
  double d6;
  double d7;
  double d8;
  double d9;
  double d_y;
  double daxld_idx_0;
  double daxld_idx_1;
  double daxld_idx_2;
  double e;
  double e_y;
  double mu;
  double mutot;
  double muxs;
  double muzs;
  double psdot;
  double qsdot;
  double rminusO;
  double rsdot;
  double rsdotmomd;
  double sbetawind;
  double sphi;
  double spsiE;
  double sthe;
  double thetab_dot_idx_0;
  double thetab_dot_idx_1;
  double thetab_dot_idx_2;
  double y_idx_0;
  double y_idx_1;
  double y_idx_2;
  double yld_idx_0;
  double yld_idx_1;
  double yld_idx_2;
  double yld_tmp_idx_0;
  double yld_tmp_idx_1;
  double yld_tmp_idx_2;
  double yld_tmp_idx_3;
  double zeta_ddot_tmp_idx_0;
  double zeta_ddot_tmp_idx_1;
  double zeta_ddot_tmp_idx_2;
  double zeta_ddot_tmp_idx_3;
  double zld_idx_0;
  double zld_idx_1;
  double zld_idx_2;
  double zld_tmp_idx_0;
  double zld_tmp_idx_1;
  double zld_tmp_idx_2;
  double zld_tmp_idx_3;
  int LMBC2IBCdot_tmp;
  int i;
  int k;
  /* Map constants to local variable names */
  /* FtLb_s2Hp=constants.FtLb_s2Hp; */
  /* 'GHrotor:6' RHO=atmos.rho; */
  /* OMEGA=constants.OMEGA; */
  /* 'GHrotor:8' R=constants.R; */
  /* 'GHrotor:9' CHORD=constants.CHORD; */
  /* 'GHrotor:10' DELSP=constants.DELSP; */
  /* 'GHrotor:11' NSEG=SizeConstants.NSEG; */
  /* 'GHrotor:12' NB=SizeConstants.NB; */
  /* 'GHrotor:13' MBETA=constants.MBETA; */
  /* 'GHrotor:14' IBETA=constants.IBETA; */
  /* 'GHrotor:15' WBLADE=constants.WBLADE; */
  /* 'GHrotor:16' G=constants.G; */
  /* 'GHrotor:17' VSOUND=atmos.spsnd; */
  /* WEIGHT=constants.WEIGHT; */
  /* WEIGHTNR=constants.WEIGHTNR; */
  /* 'GHrotor:20' CLAG=constants.CLAG; */
  /* 'GHrotor:21' KLAG=constants.KLAG; */
  /* 'GHrotor:22' ZETA0=constants.ZETA0; */
  /* 'GHrotor:23' THETALDGEO=constants.THETALDGEO; */
  /* SPAR=constants.SPAR; */
  /* 'GHrotor:25' HOFFSET=constants.HOFFSET; */
  /* 'GHrotor:26' ALD=constants.ALD; */
  /* 'GHrotor:27' BLD=constants.BLD; */
  /* 'GHrotor:28' CLD=constants.CLD; */
  /* 'GHrotor:29' DLD=constants.DLD; */
  /* 'GHrotor:30' RLD=constants.RLD; */
  /* 'GHrotor:31' DELTA3=constants.DELTA3; */
  /* 'GHrotor:32' FSCGB=constants.FSCGB; */
  /* 'GHrotor:33' WLCGB=constants.WLCGB; */
  /* 'GHrotor:34' BLCGB=constants.BLCGB; */
  /* 'GHrotor:35' FSMR=constants.FSMR; */
  /* 'GHrotor:36' WLMR=constants.WLMR; */
  /* 'GHrotor:37' BLMR=constants.BLMR; */
  /* 'GHrotor:38' OMEGAT=constants.OMEGAT; */
  /* D2R=constants.D2R; */
  /* AOATAB=constants.MRAOATAB; */
  /* CLTAB=constants.MRCLTAB; */
  /* CDTAB=constants.MRCDTAB; */
  /* 'GHrotor:43' ACL1=constants.ACL1; */
  /* 'GHrotor:44' ACL2=constants.ACL2; */
  /* 'GHrotor:45' ACL3=constants.ACL3; */
  /* 'GHrotor:46' ACL4=constants.ACL4; */
  /* 'GHrotor:48' rseg=constants.RSEG; */
  /* 'GHrotor:49' delseg=constants.DELSEG; */
  /* 'GHrotor:51' e=HOFFSET/R; */
  e = constants->HOFFSET / constants->R;
  /* eprime=SPAR/R; %not used */
  /* Define blade twist at blade elements */
  /* 'GHrotor:55'
   * twist=interp1(constants.TWISTTABR,constants.TWISTTABTHET,rseg); */
  /* Rotor states */
  /*  X = [MBC flapping angles; MBC flapping rates; MBC lag angles; MBC lag
   * rates; PP inflow states; azimuth of */
  /*  rotor; loading state for dynamic twist model; PH Inflow states] */
  /* Map to local variables names  */
  /* 'GHrotor:64' lambda0=x(17); */
  /* Keep Pitt Peters states even for inflow = 2 for interference model */
  /* 'GHrotor:65' lambda1s=x(18); */
  /* 'GHrotor:66' lambda1c=x(19); */
  /* 'GHrotor:68' psi1=x(20); */
  /* Blade azimuths */
  /* 'GHrotor:71' psi=psi1+(0:(NB-1))*(2*pi/NB); */
  /* 'GHrotor:72' psi=mod(psi',2*pi); */
  dv[0] = 0.0;
  dv[1] = 1.0;
  r = _mm_loadu_pd(&dv[0]);
  r1 = _mm_set1_pd(x[19]);
  r2 = _mm_set1_pd(1.5707963267948966);
  _mm_storeu_pd(&Ftb[0], _mm_add_pd(r1, _mm_mul_pd(r2, r)));
  dv[0] = 2.0;
  dv[1] = 3.0;
  r = _mm_loadu_pd(&dv[0]);
  _mm_storeu_pd(&Ftb[2], _mm_add_pd(r1, _mm_mul_pd(r2, r)));
  b_mod(Ftb, psi);
  /* 'GHrotor:74' cpsi=cos(psi); */
  /* 'GHrotor:75' spsi=sin(psi); */
  /* Convert from IBC to MBC */
  /* 'GHrotor:78' LMBC2IBC=[ones(4,1),(-1).^(1:NB)',cpsi,spsi]; */
  d = cos(psi[0]);
  cpsi[0] = d;
  d1 = sin(psi[0]);
  spsi[0] = d1;
  LMBC2IBC[0] = 1.0;
  LMBC2IBC[4] = -1.0;
  LMBC2IBC[8] = d;
  LMBC2IBC[12] = d1;
  d = cos(psi[1]);
  cpsi[1] = d;
  d1 = sin(psi[1]);
  spsi[1] = d1;
  LMBC2IBC[1] = 1.0;
  LMBC2IBC[5] = 1.0;
  LMBC2IBC[9] = d;
  LMBC2IBC[13] = d1;
  d = cos(psi[2]);
  cpsi[2] = d;
  d1 = sin(psi[2]);
  spsi[2] = d1;
  LMBC2IBC[2] = 1.0;
  LMBC2IBC[6] = -1.0;
  LMBC2IBC[10] = d;
  LMBC2IBC[14] = d1;
  d = cos(psi[3]);
  cpsi[3] = d;
  d1 = sin(psi[3]);
  spsi[3] = d1;
  LMBC2IBC[3] = 1.0;
  LMBC2IBC[7] = 1.0;
  LMBC2IBC[11] = d;
  LMBC2IBC[15] = d1;
  /* 'GHrotor:79' LMBC2IBCdot=OMEGAT*[zeros(4,2),-spsi,cpsi]; */
  spsiE = constants->OMEGAT * 0.0;
  for (k = 0; k < 2; k++) {
    LMBC2IBCdot_tmp = k << 2;
    LMBC2IBCdot[LMBC2IBCdot_tmp] = spsiE;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 1] = spsiE;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 2] = spsiE;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 3] = spsiE;
  }
  /* 'GHrotor:80' beta=LMBC2IBC*x(1:NB); */
  memset(&beta[0], 0, sizeof(double) << 2);
  /* 'GHrotor:81' beta_dot=LMBC2IBC*x(NB+1:2*NB)+LMBC2IBCdot*x(1:NB); */
  memset(&beta_dot[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot[k + 8] = constants->OMEGAT * -spsi[k];
    LMBC2IBCdot[k + 12] = constants->OMEGAT * cpsi[k];
    LMBC2IBCdot_tmp = k << 2;
    r1 = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r = _mm_loadu_pd(&beta[0]);
    r2 = _mm_set1_pd(x[k]);
    _mm_storeu_pd(&beta[0], _mm_add_pd(r, _mm_mul_pd(r1, r2)));
    r = _mm_loadu_pd(&beta_dot[0]);
    r3 = _mm_set1_pd(x[k + 4]);
    _mm_storeu_pd(&beta_dot[0], _mm_add_pd(r, _mm_mul_pd(r1, r3)));
    r1 = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r = _mm_loadu_pd(&beta[2]);
    _mm_storeu_pd(&beta[2], _mm_add_pd(r, _mm_mul_pd(r1, r2)));
    r = _mm_loadu_pd(&beta_dot[2]);
    _mm_storeu_pd(&beta_dot[2], _mm_add_pd(r, _mm_mul_pd(r1, r3)));
  }
  memset(&Ftb[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Ftb[0]);
    r2 = _mm_set1_pd(x[k]);
    _mm_storeu_pd(&Ftb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Ftb[2]);
    _mm_storeu_pd(&Ftb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  }
  /* 'GHrotor:82' zeta=LMBC2IBC*x(2*NB+1:3*NB); */
  memset(&zeta[0], 0, sizeof(double) << 2);
  /* 'GHrotor:83' zeta_dot=LMBC2IBC*x(3*NB+1:4*NB)+LMBC2IBCdot*x(2*NB+1:3*NB);
   */
  memset(&zeta_dot[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    beta_dot[k] += Ftb[k];
    LMBC2IBCdot_tmp = k << 2;
    r1 = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r = _mm_loadu_pd(&zeta[0]);
    r2 = _mm_set1_pd(x[k + 8]);
    _mm_storeu_pd(&zeta[0], _mm_add_pd(r, _mm_mul_pd(r1, r2)));
    r = _mm_loadu_pd(&zeta_dot[0]);
    r3 = _mm_set1_pd(x[k + 12]);
    _mm_storeu_pd(&zeta_dot[0], _mm_add_pd(r, _mm_mul_pd(r1, r3)));
    r1 = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r = _mm_loadu_pd(&zeta[2]);
    _mm_storeu_pd(&zeta[2], _mm_add_pd(r, _mm_mul_pd(r1, r2)));
    r = _mm_loadu_pd(&zeta_dot[2]);
    _mm_storeu_pd(&zeta_dot[2], _mm_add_pd(r, _mm_mul_pd(r1, r3)));
  }
  memset(&Ftb[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Ftb[0]);
    r2 = _mm_set1_pd(x[k + 8]);
    _mm_storeu_pd(&Ftb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Ftb[2]);
    _mm_storeu_pd(&Ftb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  }
  /* 'GHrotor:85' LIBC2MBC=1/NB*[ones(1,4);(-1).^(1:NB);2*cpsi';2*spsi']; */
  /* 'GHrotor:86' LIBC2MBCdot=OMEGAT/NB*[zeros(2,4);-2*spsi';2*cpsi']; */
  a = constants->OMEGAT / 4.0;
  /* 'GHrotor:87'
   * LIBC2MBCddot=(OMEGAT*OMEGAT)/NB*[zeros(2,4);-2*cpsi';-2*spsi']; */
  b_a = constants->OMEGAT * constants->OMEGAT / 4.0;
  /* Save commonly used cosine /sine values */
  /* 'GHrotor:90' cbeta=cos(beta); */
  /* 'GHrotor:91' sbeta=sin(beta); */
  /* 'GHrotor:92' czeta=cos(zeta); */
  /* 'GHrotor:93' szeta=sin(zeta); */
  /* 'GHrotor:94' cpsizeta=cos(psi+zeta); */
  /* 'GHrotor:95' spsizeta=sin(psi+zeta); */
  KR = a * 0.0;
  sphi = b_a * 0.0;
  for (k = 0; k < 4; k++) {
    zeta_dot[k] += Ftb[k];
    cpsiE = cpsi[k];
    Tbody2NED_tmp = 2.0 * cpsiE;
    LMBC2IBCdot_tmp = k << 2;
    LMBC2IBC[LMBC2IBCdot_tmp] = 0.25;
    LMBC2IBC[LMBC2IBCdot_tmp + 1] = 0.25 * (double)iv[k];
    LMBC2IBC[LMBC2IBCdot_tmp + 2] = 0.25 * Tbody2NED_tmp;
    spsiE = spsi[k];
    LMBC2IBC[LMBC2IBCdot_tmp + 3] = 0.25 * (2.0 * spsiE);
    spsiE *= -2.0;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 2] = a * spsiE;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 3] = a * Tbody2NED_tmp;
    LMBC2IBCdot[LMBC2IBCdot_tmp] = KR;
    LIBC2MBCddot[LMBC2IBCdot_tmp] = sphi;
    LMBC2IBCdot[LMBC2IBCdot_tmp + 1] = KR;
    LIBC2MBCddot[LMBC2IBCdot_tmp + 1] = sphi;
    LIBC2MBCddot[LMBC2IBCdot_tmp + 2] = b_a * (-2.0 * cpsiE);
    LIBC2MBCddot[LMBC2IBCdot_tmp + 3] = b_a * spsiE;
    spsiE = beta[k];
    cbeta[k] = cos(spsiE);
    sbeta[k] = sin(spsiE);
    spsiE = zeta[k];
    czeta[k] = cos(spsiE);
    szeta[k] = sin(spsiE);
    spsiE += psi[k];
    cpsizeta[k] = cos(spsiE);
    spsiE = sin(spsiE);
    spsizeta[k] = spsiE;
  }
  /* Inputs to Rotor Module */
  /*  U = [Rotor controls (lat cyc, long cyc, collective); Air velocities in */
  /*  body frame; angular rates in body  frame; roll and pitch attitude; */
  /*  accelerations in frame; angular accel in body frame; wind gusts in body
   * frame] */
  /* Control inputs */
  /* 'GHrotor:104' theta1c=u(1); */
  /* 'GHrotor:105' theta1s=u(2); */
  /* 'GHrotor:106' theta0=u(3); */
  /* Air velocity inputs */
  /* 'GHrotor:109' Vxb=u(4); */
  /* 'GHrotor:110' Vyb=u(5); */
  /* 'GHrotor:111' Vzb=u(6); */
  /* Angular rate inputs */
  /* 'GHrotor:113' p=u(7); */
  /* 'GHrotor:114' q=u(8); */
  /* 'GHrotor:115' r=u(9); */
  /* Euler Angles */
  /* 'GHrotor:117' sphi=sin(u(10)); */
  sphi = sin(u[9]);
  /* 'GHrotor:118' cphi=cos(u(10)); */
  cphi = cos(u[9]);
  /* 'GHrotor:119' sthe=sin(u(11)); */
  sthe = sin(u[10]);
  /* 'GHrotor:120' cthe=cos(u(11)); */
  cthe = cos(u[10]);
  /* 'GHrotor:121' spsiE=sin(u(12)); */
  spsiE = sin(u[11]);
  /* 'GHrotor:122' cpsiE=cos(u(12)); */
  cpsiE = cos(u[11]);
  /* 'GHrotor:124' Tbody2NED=[cthe*cpsiE (sphi*sthe*cpsiE-cphi*spsiE)
   * (cphi*sthe*cpsiE+sphi*spsiE); ... */
  /* 'GHrotor:125'            cthe*spsiE (sphi*sthe*spsiE+cphi*cpsiE)
   * (cphi*sthe*spsiE-sphi*cpsiE); ... */
  /* 'GHrotor:126'            -sthe                  sphi*cthe cphi*cthe]; */
  Tbody2NED[0] = cthe * cpsiE;
  Tbody2NED_tmp = sphi * sthe;
  Tbody2NED[3] = Tbody2NED_tmp * cpsiE - cphi * spsiE;
  a = cphi * sthe;
  Tbody2NED[6] = a * cpsiE + sphi * spsiE;
  Tbody2NED[1] = cthe * spsiE;
  Tbody2NED[4] = Tbody2NED_tmp * spsiE + cphi * cpsiE;
  Tbody2NED[7] = a * spsiE - sphi * cpsiE;
  Tbody2NED[2] = -sthe;
  Tbody2NED[5] = sphi * cthe;
  Tbody2NED[8] = cphi * cthe;
  /* CG location */
  /* 'GHrotor:128' xcg=u(13); */
  /* 'GHrotor:129' ycg=u(14); */
  /* 'GHrotor:130' zcg=u(15); */
  /* Linear Acceleration Inputs */
  /* 'GHrotor:133' Vxbdot=u(16); */
  /* 'GHrotor:134' Vybdot=u(17); */
  /* 'GHrotor:135' Vzbdot=u(18); */
  /* Angular Acceleration inputs */
  /* 'GHrotor:137' pdot=u(19); */
  /* 'GHrotor:138' qdot=u(20); */
  /* 'GHrotor:139' rdot=u(21); */
  /* Rotor speed */
  /* 'GHrotor:142' OMEGA=u(22); */
  /* Rotor accel */
  /* 'GHrotor:145' Omega_dot=u(23); */
  /* Wind gusts (Not using here) */
  /* VgNED=reshape(u(24:23+NB*NSEG*3),3,NB*NSEG); */
  /* Coupling gain to fade out inflow model */
  /* InflowFade=u(23+NB*NSEG*3+1); */
  /* Convert gusts to shaft axes */
  /* Vgs=constants.Tshaft*Tbody2NED'*VgNED; */
  /* Vgxs=reshape(Vgs(1,:)',NSEG,NB)'; */
  /* Vgys=reshape(Vgs(2,:)',NSEG,NB)'; */
  /* Vgzs=reshape(Vgs(3,:)',NSEG,NB)'; */
  /* Get average of gust velocities to determine the effective advance ration of
   * the rotor */
  /* Vgxsavg=mean(mean(Vgxs)); */
  /* Vgysavg=mean(mean(Vgys)); */
  /* Vgzsavg=mean(mean(Vgzs)); */
  /* mugxs=Vgxsavg/(OMEGAT*R); */
  /* mugys=Vgysavg/(OMEGAT*R); */
  /* mugzs=Vgzsavg/(OMEGAT*R); */
  /* Then calculate perturbation froma average for adding into blade elements */
  /* dVgxs=Vgxs-Vgxsavg; */
  /* dVgys=Vgys-Vgysavg; */
  /* dVgzs=Vgzs-Vgzsavg; */
  /* Accelerations at Rotor Hub */
  /* 'GHrotor:172' gx=G*sthe; */
  /* 'GHrotor:173' gy=-G*sphi*cthe; */
  /* 'GHrotor:174' gz=-G*cphi*cthe; */
  /*  Calculate moment arms from fuselage CG to main rotor hub */
  /* 'GHrotor:177' Xh=(FSCGB-FSMR)/12.; */
  Xh = (constants->FSCGB - constants->FSMR) / 12.0;
  /* 'GHrotor:178' Yh=(BLCGB-BLMR)/12.; */
  Yh = (constants->BLCGB - constants->BLMR) / 12.0;
  /* 'GHrotor:179' Zh=(WLCGB-WLMR)/12.; */
  Zh = (constants->WLCGB - constants->WLMR) / 12.0;
  /* Acceleration of the hub */
  /* 'GHrotor:182'
   * Vxhdot=Vxbdot-r*Vyb+q*Vzb-Xh*(q^2+r^2)+Yh*(p*q-rdot)+Zh*(p*r+qdot)+gx; */
  /* 'GHrotor:183'
   * Vyhdot=Vybdot-p*Vzb+r*Vxb+Xh*(p*q+rdot)-Yh*(p^2+r^2)+Zh*(q*r-pdot)+gy; */
  /* 'GHrotor:184'
   * Vzhdot=Vzbdot+p*Vyb-q*Vxb+Xh*(p*r-qdot)+Yh*(q*r+pdot)-Zh*(p^2+q^2)+gz; */
  /* Non-dimensional advance ratios */
  /* 'GHrotor:187' muxh=(Vxb+q*Zh-r*Yh)/(OMEGAT*R); */
  /* 'GHrotor:188' muyh=(Vyb+r*Xh-p*Zh)/(OMEGAT*R); */
  /* 'GHrotor:189' muzh=(Vzb-q*Xh+p*Yh)/(OMEGAT*R); */
  /* muxhdot=(Vxbdot+qdot*Zh-rdot*Yh)/(OMEGAT*R); */
  /* muyhdot=(Vybdot+rdot*Xh-pdot*Zh)/(OMEGAT*R); */
  /* muzhdot=(Vzbdot-qdot*Xh+pdot*Yh)/(OMEGAT*R); */
  /* Shaft axes transformations */
  /* 'GHrotor:197' temp=constants.Tshaft*[Vxhdot;Vyhdot;Vzhdot]; */
  spsiE = u[6] * u[7];
  cpsiE = u[8] * u[8];
  Tbody2NED_tmp = u[6] * u[8];
  a = u[7] * u[7];
  muxs = (((((u[15] - u[4] * u[8]) + u[5] * u[7]) - Xh * (a + cpsiE)) +
           Yh * (spsiE - u[20])) +
          Zh * (Tbody2NED_tmp + u[19])) +
         constants->G * sthe;
  b_a = u[7] * u[8];
  KR = u[6] * u[6];
  sphi = (((((u[16] - u[5] * u[6]) + u[3] * u[8]) + Xh * (spsiE + u[20])) -
           Yh * (KR + cpsiE)) +
          Zh * (b_a - u[18])) +
         -constants->G * sphi * cthe;
  a = (((((u[17] + u[4] * u[6]) - u[3] * u[7]) + Xh * (Tbody2NED_tmp - u[19])) +
        Yh * (b_a + u[18])) -
       Zh * (KR + a)) +
      -constants->G * cphi * cthe;
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[0]),
                                         _mm_set1_pd(muxs))));
  temp[2] += constants->Tshaft[2] * muxs;
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[3]),
                                         _mm_set1_pd(sphi))));
  temp[2] += constants->Tshaft[5] * sphi;
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[6]),
                                         _mm_set1_pd(a))));
  temp[2] += constants->Tshaft[8] * a;
  /* 'GHrotor:198' Vxsdot=temp(1); */
  Vxsdot = temp[0];
  /* 'GHrotor:199' Vysdot=temp(2); */
  Vysdot = temp[1];
  /* 'GHrotor:200' Vzsdot=temp(3); */
  Vzsdot = temp[2];
  /* 'GHrotor:201' temp=constants.Tshaft*[pdot;qdot;rdot]; */
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[0]),
                                         _mm_set1_pd(u[18]))));
  temp[2] += constants->Tshaft[2] * u[18];
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[3]),
                                         _mm_set1_pd(u[19]))));
  temp[2] += constants->Tshaft[5] * u[19];
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[6]),
                                         _mm_set1_pd(u[20]))));
  temp[2] += constants->Tshaft[8] * u[20];
  /* 'GHrotor:202' psdot=temp(1); */
  psdot = temp[0];
  /* 'GHrotor:203' qsdot=temp(2); */
  qsdot = temp[1];
  /* 'GHrotor:204' rsdot=temp(3); */
  rsdot = temp[2];
  /* 'GHrotor:205' rsdotmomd=rsdot-Omega_dot; */
  rsdotmomd = temp[2] - u[22];
  /* 'GHrotor:207' temp=constants.Tshaft*[muxh;muyh;muzh]; */
  spsiE = constants->OMEGAT * constants->R;
  muxs = ((u[3] + u[7] * Zh) - u[8] * Yh) / spsiE;
  sphi = ((u[4] + u[8] * Xh) - u[6] * Zh) / spsiE;
  a = ((u[5] - u[7] * Xh) + u[6] * Yh) / spsiE;
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[0]),
                                         _mm_set1_pd(muxs))));
  temp[2] += constants->Tshaft[2] * muxs;
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[3]),
                                         _mm_set1_pd(sphi))));
  temp[2] += constants->Tshaft[5] * sphi;
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[6]),
                                         _mm_set1_pd(a))));
  temp[2] += constants->Tshaft[8] * a;
  /* Add in the average gust */
  /* muxs=temp(1)+mugxs; */
  /* muys=temp(2)+mugys; */
  /* muzs=temp(3)+mugzs; */
  /* 'GHrotor:212' muxs=temp(1); */
  /* 'GHrotor:213' muys=temp(2); */
  /* 'GHrotor:214' muzs=temp(3); */
  muzs = temp[2];
  /* 'GHrotor:216' betawind = atan2(muys, muxs); */
  spsiE = b_atan2(temp[1], temp[0]);
  /* 'GHrotor:217' mu=max(sqrt(muxs^2+muys^2),1e-5); */
  mu = fmax(sqrt(temp[0] * temp[0] + temp[1] * temp[1]), 1.0E-5);
  /* 'GHrotor:218' cbetawind=cos(betawind); */
  cbetawind = cos(spsiE);
  /* 'GHrotor:219' sbetawind=sin(betawind); */
  sbetawind = sin(spsiE);
  /* 'GHrotor:220' muxs=mu*cbetawind; */
  muxs = mu * cbetawind;
  /* 'GHrotor:221' muys=mu*sbetawind; */
  /* temp=constants.Tshaft*[muxhdot;muyhdot;muzhdot]; */
  /* Note that we currently ignore time rate of change of gust on mu dot  */
  /* muxsdot=temp(1); */
  /* muysdot=temp(2); */
  /* muzsdot=temp(3); */
  /* betawind_dot=(cbetawind*muysdot-sbetawind*muxsdot)/mu; */
  /* betawind_dot=min(abs(betawind_dot),10.)*sign(betawind_dot); */
  /* 'GHrotor:231' temp=constants.Tshaft*[p;q;r]; */
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[0]),
                                         _mm_set1_pd(u[6]))));
  temp[2] += constants->Tshaft[2] * u[6];
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[3]),
                                         _mm_set1_pd(u[7]))));
  temp[2] += constants->Tshaft[5] * u[7];
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[6]),
                                         _mm_set1_pd(u[8]))));
  temp[2] += constants->Tshaft[8] * u[8];
  /* 'GHrotor:232' ps=temp(1); */
  /* 'GHrotor:233' qs=temp(2); */
  /* 'GHrotor:234' rs=temp(3); */
  /* 'GHrotor:235' rminusO=rs-OMEGA; */
  rminusO = temp[2] - u[21];
  /* Blade pitch */
  /* 'GHrotor:238'
   * thetab=theta0+theta1c*cos(psi+DELSP)+theta1s*sin(psi+DELSP)-tan(DELTA3)*beta;
   */
  spsiE = tan(constants->DELTA3);
  /* 'GHrotor:239'
   * thetab_dot=-theta1c*OMEGA*sin(psi+DELSP)+theta1s*OMEGA*cos(psi+DELSP); */
  cpsiE = -u[0] * u[21];
  Tbody2NED_tmp = u[1] * u[21];
  a = psi[0] + constants->DELSP;
  zeta_ddot_tmp_idx_3 = sin(a);
  a = cos(a);
  thetab[0] =
      ((u[2] + u[0] * a) + u[1] * zeta_ddot_tmp_idx_3) - spsiE * beta[0];
  zeta_ddot_tmp_idx_3 = cpsiE * zeta_ddot_tmp_idx_3 + Tbody2NED_tmp * a;
  thetab_dot_idx_0 = zeta_ddot_tmp_idx_3;
  a = psi[1] + constants->DELSP;
  zeta_ddot_tmp_idx_3 = sin(a);
  a = cos(a);
  thetab[1] =
      ((u[2] + u[0] * a) + u[1] * zeta_ddot_tmp_idx_3) - spsiE * beta[1];
  zeta_ddot_tmp_idx_3 = cpsiE * zeta_ddot_tmp_idx_3 + Tbody2NED_tmp * a;
  thetab_dot_idx_1 = zeta_ddot_tmp_idx_3;
  a = psi[2] + constants->DELSP;
  zeta_ddot_tmp_idx_3 = sin(a);
  a = cos(a);
  thetab[2] =
      ((u[2] + u[0] * a) + u[1] * zeta_ddot_tmp_idx_3) - spsiE * beta[2];
  zeta_ddot_tmp_idx_3 = cpsiE * zeta_ddot_tmp_idx_3 + Tbody2NED_tmp * a;
  thetab_dot_idx_2 = zeta_ddot_tmp_idx_3;
  a = psi[3] + constants->DELSP;
  zeta_ddot_tmp_idx_3 = sin(a);
  a = cos(a);
  thetab[3] =
      ((u[2] + u[0] * a) + u[1] * zeta_ddot_tmp_idx_3) - spsiE * beta[3];
  zeta_ddot_tmp_idx_3 = cpsiE * zeta_ddot_tmp_idx_3 + Tbody2NED_tmp * a;
  /* Dynamic Twist Component */
  /* 'GHrotor:242'
   * Veq=sqrt(atmos.rho/constants.rhoSLSTD)*sqrt(Vxb^2+Vyb^2+Vzb^2)/1.688; */
  Veq = sqrt(atmos_rho / constants->rhoSLSTD) *
        sqrt((u[3] * u[3] + u[4] * u[4]) + u[5] * u[5]) / 1.688;
  /* 'GHrotor:243' KVDT=min(max(1.4e-4-(4.4e-6*Veq),-0.00052),-0.0003); */
  /* 'GHrotor:244' theta_DTtip=KVDT*x(21); */
  KR = fmin(fmax(0.00014 - 4.4E-6 * Veq, -0.00052), -0.0003) * x[20];
  /* x(21); */
  /* 'GHrotor:245'
   * theta_DT=ones(4,1)*theta_DTtip*constants.DynTwistMode*pi/180.; */
  /* Segment pitch */
  /* 'GHrotor:249' theta=thetab*ones(1,NSEG)+ones(NB,1)*twist*pi/180+theta_DT;
   */
  interp1(constants->TWISTTABR, constants->TWISTTABTHET, constants->RSEG, dv1);
  /*  */
  /* Gust velocities, transform to blade system */
  /* JFH 16MAT19 now use perturbation gusts  */
  /* Utg=1/(OMEGA*R)*( (spsizeta*ones(1,NSEG)).*dVgxs +
   * (cpsizeta*ones(1,NSEG)).*dVgys); */
  /* Urg=1/(OMEGA*R)*( ((-cpsizeta.*cbeta)*ones(1,NSEG)).*dVgxs +
   * ((spsizeta.*cbeta)*ones(1,NSEG)).*dVgys - (sbeta*ones(1,NSEG)).*dVgzs ); */
  /* Upg=1/(OMEGA*R)*( ((-cpsizeta.*sbeta)*ones(1,NSEG)).*dVgxs +
   * ((spsizeta.*sbeta)*ones(1,NSEG)).*dVgys + (cbeta*ones(1,NSEG)).*dVgzs ); */
  /* NOT USING GUST PENENTRATION, WILL REPLACE WITH STEADY WIND MODEL */
  /* Pitt-Peters Inflow Model */
  /* 'GHrotor:259' Upd_pp=(-lambda0*cbeta*ones(1,NSEG)
   * -lambda1c*(e*cbeta.*cpsi*ones(1,NSEG)+cbeta.*cpsizeta*rseg) ... */
  /* 'GHrotor:260' -lambda1s*(e*cbeta.*spsi*ones(1,NSEG)+cbeta.*spsizeta*rseg)
   * ); */
  /* *(1-InflowFade); */
  /* 'GHrotor:262' Urd_pp=(-lambda0*sbeta*ones(1,NSEG)
   * -lambda1c*(e*sbeta.*cpsi*ones(1,NSEG)+sbeta.*cpsizeta*rseg) ... */
  /* 'GHrotor:263' -lambda1s*(e*sbeta.*spsi*ones(1,NSEG)+sbeta.*spsizeta*rseg)
   * ); */
  /* *(1-InflowFade); */
  /* Blade segment velocities */
  /* 'GHrotor:267'
   * Up=(-muxs*sbeta.*cpsizeta+muys*sbeta.*spsizeta+muzs*cbeta)*ones(1,NSEG) +
   * ... */
  /* 'GHrotor:268'
   * +(e/OMEGA)*(cbeta.*(qs*cpsi+ps*spsi)-sbeta.*szeta*rminusO)*ones(1,NSEG) +
   * ... */
  /* 'GHrotor:269'     (-beta_dot+qs*cpsizeta+ps*spsizeta)*rseg/OMEGA + ... */
  /* 'GHrotor:270'     Upd_pp; */
  r4 = _mm_loadu_pd(&cbeta[0]);
  r5 = _mm_set1_pd(e);
  _mm_storeu_pd(&Fpb[0], _mm_mul_pd(r5, r4));
  r6 = _mm_loadu_pd(&sbeta[0]);
  _mm_storeu_pd(&LIBC2MBCdot_tmp[0], _mm_mul_pd(r5, r6));
  r = _mm_loadu_pd(&cpsi[0]);
  r1 = _mm_loadu_pd(&spsi[0]);
  r7 = _mm_set1_pd(temp[1]);
  r8 = _mm_set1_pd(temp[0]);
  r3 = _mm_add_pd(_mm_mul_pd(r7, r), _mm_mul_pd(r8, r1));
  _mm_storeu_pd(&Up_tmp[0], r3);
  r = _mm_loadu_pd(&szeta[0]);
  r = _mm_mul_pd(r6, r);
  _mm_storeu_pd(&Fxt[0], r);
  r1 = _mm_loadu_pd(&cpsizeta[0]);
  r2 = _mm_loadu_pd(&spsizeta[0]);
  r9 = _mm_set1_pd(-muxs);
  r10 = _mm_set1_pd(mu * sbetawind);
  r11 = _mm_set1_pd(muzs);
  _mm_storeu_pd(&Frb[0],
                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_mul_pd(r9, r6), r1),
                                      _mm_mul_pd(_mm_mul_pd(r10, r6), r2)),
                           _mm_mul_pd(r11, r4)));
  r12 = _mm_set1_pd(e / u[21]);
  r13 = _mm_set1_pd(rminusO);
  _mm_storeu_pd(&Ftb[0], _mm_mul_pd(r12, _mm_sub_pd(_mm_mul_pd(r4, r3),
                                                    _mm_mul_pd(r, r13))));
  r4 = _mm_loadu_pd(&cbeta[2]);
  _mm_storeu_pd(&Fpb[2], _mm_mul_pd(r5, r4));
  r6 = _mm_loadu_pd(&sbeta[2]);
  _mm_storeu_pd(&LIBC2MBCdot_tmp[2], _mm_mul_pd(r5, r6));
  r = _mm_loadu_pd(&cpsi[2]);
  r1 = _mm_loadu_pd(&spsi[2]);
  r3 = _mm_add_pd(_mm_mul_pd(r7, r), _mm_mul_pd(r8, r1));
  _mm_storeu_pd(&Up_tmp[2], r3);
  r = _mm_loadu_pd(&szeta[2]);
  r = _mm_mul_pd(r6, r);
  _mm_storeu_pd(&Fxt[2], r);
  r1 = _mm_loadu_pd(&cpsizeta[2]);
  r2 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&Frb[2],
                _mm_add_pd(_mm_add_pd(_mm_mul_pd(_mm_mul_pd(r9, r6), r1),
                                      _mm_mul_pd(_mm_mul_pd(r10, r6), r2)),
                           _mm_mul_pd(r11, r4)));
  _mm_storeu_pd(&Ftb[2], _mm_mul_pd(r12, _mm_sub_pd(_mm_mul_pd(r4, r3),
                                                    _mm_mul_pd(r, r13))));
  spsiE = Frb[0];
  cpsiE = Frb[1];
  Tbody2NED_tmp = Frb[2];
  a = Frb[3];
  b_a = Ftb[0];
  sphi = Ftb[1];
  cphi = Ftb[2];
  cthe = Ftb[3];
  r = _mm_set1_pd(0.0);
  for (k = 0; k < 10; k++) {
    r1 = _mm_loadu_pd(&thetab[0]);
    LMBC2IBCdot_tmp = k << 2;
    r2 = _mm_set1_pd(dv1[k] * 3.141592653589793 / 180.0);
    r3 = _mm_set1_pd(KR * constants->DynTwistMode[k] * 3.141592653589793 /
                     180.0);
    _mm_storeu_pd(&theta[LMBC2IBCdot_tmp],
                  _mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3));
    r1 = _mm_loadu_pd(&thetab[2]);
    _mm_storeu_pd(&theta[LMBC2IBCdot_tmp + 2],
                  _mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3));
    alphay[LMBC2IBCdot_tmp] = spsiE;
    Machtab[LMBC2IBCdot_tmp] = b_a;
    alphay[LMBC2IBCdot_tmp + 1] = cpsiE;
    Machtab[LMBC2IBCdot_tmp + 1] = sphi;
    alphay[LMBC2IBCdot_tmp + 2] = Tbody2NED_tmp;
    Machtab[LMBC2IBCdot_tmp + 2] = cphi;
    alphay[LMBC2IBCdot_tmp + 3] = a;
    Machtab[LMBC2IBCdot_tmp + 3] = cthe;
  }
  r = _mm_loadu_pd(&beta_dot[0]);
  r2 = _mm_loadu_pd(&cpsizeta[0]);
  r1 = _mm_loadu_pd(&spsizeta[0]);
  r14 = _mm_set1_pd(-1.0);
  _mm_storeu_pd(&Ftb[0],
                _mm_add_pd(_mm_add_pd(_mm_mul_pd(r, r14), _mm_mul_pd(r7, r2)),
                           _mm_mul_pd(r8, r1)));
  r = _mm_loadu_pd(&Fpb[0]);
  r1 = _mm_loadu_pd(&cpsi[0]);
  _mm_storeu_pd(&Mf_aero[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&cbeta[0]);
  _mm_storeu_pd(&Frb[0], _mm_mul_pd(r, r2));
  r = _mm_loadu_pd(&beta_dot[2]);
  r2 = _mm_loadu_pd(&cpsizeta[2]);
  r1 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&Ftb[2],
                _mm_add_pd(_mm_add_pd(_mm_mul_pd(r, r14), _mm_mul_pd(r7, r2)),
                           _mm_mul_pd(r8, r1)));
  r = _mm_loadu_pd(&Fpb[2]);
  r1 = _mm_loadu_pd(&cpsi[2]);
  _mm_storeu_pd(&Mf_aero[2], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&cbeta[2]);
  _mm_storeu_pd(&Frb[2], _mm_mul_pd(r, r2));
  for (k = 0; k < 10; k++) {
    r = _mm_loadu_pd(&Mf_aero[0]);
    LMBC2IBCdot_tmp = k << 2;
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp], r);
    r = _mm_loadu_pd(&Frb[0]);
    r1 = _mm_set1_pd(constants->RSEG[k]);
    _mm_storeu_pd(&b_cbeta[LMBC2IBCdot_tmp], _mm_mul_pd(r, r1));
    r = _mm_loadu_pd(&Mf_aero[2]);
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp + 2], r);
    r = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&b_cbeta[LMBC2IBCdot_tmp + 2], _mm_mul_pd(r, r1));
  }
  r = _mm_loadu_pd(&Fpb[0]);
  r1 = _mm_loadu_pd(&spsi[0]);
  _mm_storeu_pd(&Fpb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&cbeta[0]);
  r1 = _mm_loadu_pd(&spsizeta[0]);
  _mm_storeu_pd(&Frb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&Fpb[2]);
  r1 = _mm_loadu_pd(&spsi[2]);
  _mm_storeu_pd(&Fpb[2], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&cbeta[2]);
  r1 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&Frb[2], _mm_mul_pd(r, r1));
  spsiE = u[21];
  cpsiE = x[16];
  Tbody2NED_tmp = x[18];
  a = x[17];
  r15 = _mm_set1_pd(0.0);
  r16 = _mm_set1_pd(spsiE);
  r17 = _mm_set1_pd(-cpsiE);
  r18 = _mm_set1_pd(Tbody2NED_tmp);
  r4 = _mm_set1_pd(a);
  for (k = 0; k < 10; k++) {
    r5 = _mm_loadu_pd(&Frb[0]);
    r = _mm_loadu_pd(&Ftb[0]);
    LMBC2IBCdot_tmp = k << 2;
    r1 = _mm_loadu_pd(&alphay[LMBC2IBCdot_tmp]);
    r2 = _mm_loadu_pd(&Machtab[LMBC2IBCdot_tmp]);
    r6 = _mm_set1_pd(constants->RSEG[k]);
    _mm_storeu_pd(
        &Up[LMBC2IBCdot_tmp],
        _mm_add_pd(_mm_add_pd(r1, r2),
                   _mm_div_pd(_mm_add_pd(r15, _mm_mul_pd(r, r6)), r16)));
    r = _mm_loadu_pd(&cbeta[0]);
    r1 = _mm_loadu_pd(&b_Fpb[LMBC2IBCdot_tmp]);
    r2 = _mm_loadu_pd(&b_cbeta[LMBC2IBCdot_tmp]);
    r3 = _mm_loadu_pd(&Fpb[0]);
    _mm_storeu_pd(
        &Mach[LMBC2IBCdot_tmp],
        _mm_sub_pd(_mm_sub_pd(_mm_add_pd(r15, _mm_mul_pd(r17, r)),
                              _mm_mul_pd(r18, _mm_add_pd(r1, r2))),
                   _mm_mul_pd(r4, _mm_add_pd(r3, _mm_mul_pd(r5, r6)))));
    r5 = _mm_loadu_pd(&Frb[2]);
    r = _mm_loadu_pd(&Ftb[2]);
    r1 = _mm_loadu_pd(&alphay[LMBC2IBCdot_tmp + 2]);
    r2 = _mm_loadu_pd(&Machtab[LMBC2IBCdot_tmp + 2]);
    _mm_storeu_pd(
        &Up[LMBC2IBCdot_tmp + 2],
        _mm_add_pd(_mm_add_pd(r1, r2),
                   _mm_div_pd(_mm_add_pd(r15, _mm_mul_pd(r, r6)), r16)));
    r = _mm_loadu_pd(&cbeta[2]);
    r1 = _mm_loadu_pd(&b_Fpb[LMBC2IBCdot_tmp + 2]);
    r2 = _mm_loadu_pd(&b_cbeta[LMBC2IBCdot_tmp + 2]);
    r3 = _mm_loadu_pd(&Fpb[2]);
    _mm_storeu_pd(
        &Mach[LMBC2IBCdot_tmp + 2],
        _mm_sub_pd(_mm_sub_pd(_mm_add_pd(r15, _mm_mul_pd(r17, r)),
                              _mm_mul_pd(r18, _mm_add_pd(r1, r2))),
                   _mm_mul_pd(r4, _mm_add_pd(r3, _mm_mul_pd(r5, r6)))));
  }
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&Up[k]);
    r1 = _mm_loadu_pd(&Mach[k]);
    _mm_storeu_pd(&Up[k], _mm_add_pd(r, r1));
  }
  /*  + Upg;  */
  /* 'GHrotor:272'
   * Ut=(muxs*spsizeta+muys*cpsizeta-(e/OMEGA)*czeta*rminusO)*ones(1,NSEG) + ...
   */
  /* 'GHrotor:273'    +( (zeta_dot-rminusO).*cbeta
   * +(ps*cpsizeta-qs*spsizeta).*sbeta )*rseg/OMEGA; */
  r3 = _mm_loadu_pd(&spsizeta[0]);
  r18 = _mm_loadu_pd(&cpsizeta[0]);
  r = _mm_loadu_pd(&czeta[0]);
  r4 = _mm_set1_pd(muxs);
  _mm_storeu_pd(&Frb[0],
                _mm_sub_pd(_mm_add_pd(_mm_mul_pd(r4, r3), _mm_mul_pd(r10, r18)),
                           _mm_mul_pd(_mm_mul_pd(r12, r), r13)));
  r = _mm_loadu_pd(&zeta_dot[0]);
  r1 = _mm_loadu_pd(&cbeta[0]);
  r2 = _mm_loadu_pd(&sbeta[0]);
  _mm_storeu_pd(
      &Mf_aero[0],
      _mm_add_pd(
          _mm_mul_pd(_mm_sub_pd(r, r13), r1),
          _mm_mul_pd(_mm_sub_pd(_mm_mul_pd(r8, r18), _mm_mul_pd(r7, r3)), r2)));
  r3 = _mm_loadu_pd(&spsizeta[2]);
  r18 = _mm_loadu_pd(&cpsizeta[2]);
  r = _mm_loadu_pd(&czeta[2]);
  _mm_storeu_pd(&Frb[2],
                _mm_sub_pd(_mm_add_pd(_mm_mul_pd(r4, r3), _mm_mul_pd(r10, r18)),
                           _mm_mul_pd(_mm_mul_pd(r12, r), r13)));
  r = _mm_loadu_pd(&zeta_dot[2]);
  r1 = _mm_loadu_pd(&cbeta[2]);
  r2 = _mm_loadu_pd(&sbeta[2]);
  _mm_storeu_pd(
      &Mf_aero[2],
      _mm_add_pd(
          _mm_mul_pd(_mm_sub_pd(r, r13), r1),
          _mm_mul_pd(_mm_sub_pd(_mm_mul_pd(r8, r18), _mm_mul_pd(r7, r3)), r2)));
  r1 = _mm_set1_pd(0.0);
  r2 = _mm_set1_pd(spsiE);
  for (k = 0; k < 10; k++) {
    r = _mm_loadu_pd(&Frb[0]);
    LMBC2IBCdot_tmp = k << 2;
    _mm_storeu_pd(&Ut[LMBC2IBCdot_tmp], r);
    r = _mm_loadu_pd(&Mf_aero[0]);
    r3 = _mm_set1_pd(constants->RSEG[k]);
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp],
                  _mm_div_pd(_mm_add_pd(r1, _mm_mul_pd(r, r3)), r2));
    r = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Ut[LMBC2IBCdot_tmp + 2], r);
    r = _mm_loadu_pd(&Mf_aero[2]);
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp + 2],
                  _mm_div_pd(_mm_add_pd(r1, _mm_mul_pd(r, r3)), r2));
  }
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&Ut[k]);
    r1 = _mm_loadu_pd(&b_Fpb[k]);
    _mm_storeu_pd(&Ut[k], _mm_add_pd(r, r1));
  }
  /*  + Utg; */
  /* 'GHrotor:275'
   * Ur=(muxs*cbeta.*cpsizeta-muys*cbeta.*spsizeta+muzs*sbeta)*ones(1,NSEG) +
   * ... */
  /* 'GHrotor:276'
   * (e/OMEGA)*(sbeta.*(qs*cpsi+ps*spsi)+cbeta.*szeta*rminusO)*ones(1,NSEG) +
   * ... */
  /* 'GHrotor:277'     + Urd_pp; */
  r2 = _mm_loadu_pd(&cbeta[0]);
  r = _mm_loadu_pd(&szeta[0]);
  r3 = _mm_mul_pd(r2, r);
  _mm_storeu_pd(&Ur_tmp[0], r3);
  r = _mm_loadu_pd(&cpsizeta[0]);
  r1 = _mm_loadu_pd(&spsizeta[0]);
  r18 = _mm_loadu_pd(&sbeta[0]);
  _mm_storeu_pd(&Frb[0],
                _mm_add_pd(_mm_sub_pd(_mm_mul_pd(_mm_mul_pd(r4, r2), r),
                                      _mm_mul_pd(_mm_mul_pd(r10, r2), r1)),
                           _mm_mul_pd(r11, r18)));
  r = _mm_loadu_pd(&Up_tmp[0]);
  _mm_storeu_pd(&Ftb[0], _mm_mul_pd(r12, _mm_add_pd(_mm_mul_pd(r18, r),
                                                    _mm_mul_pd(r3, r13))));
  r2 = _mm_loadu_pd(&cbeta[2]);
  r = _mm_loadu_pd(&szeta[2]);
  r3 = _mm_mul_pd(r2, r);
  _mm_storeu_pd(&Ur_tmp[2], r3);
  r = _mm_loadu_pd(&cpsizeta[2]);
  r1 = _mm_loadu_pd(&spsizeta[2]);
  r18 = _mm_loadu_pd(&sbeta[2]);
  _mm_storeu_pd(&Frb[2],
                _mm_add_pd(_mm_sub_pd(_mm_mul_pd(_mm_mul_pd(r4, r2), r),
                                      _mm_mul_pd(_mm_mul_pd(r10, r2), r1)),
                           _mm_mul_pd(r11, r18)));
  r = _mm_loadu_pd(&Up_tmp[2]);
  _mm_storeu_pd(&Ftb[2], _mm_mul_pd(r12, _mm_add_pd(_mm_mul_pd(r18, r),
                                                    _mm_mul_pd(r3, r13))));
  spsiE = Frb[0];
  cpsiE = Frb[1];
  Tbody2NED_tmp = Frb[2];
  a = Frb[3];
  b_a = Ftb[0];
  sphi = Ftb[1];
  cphi = Ftb[2];
  cthe = Ftb[3];
  for (k = 0; k < 10; k++) {
    LMBC2IBCdot_tmp = k << 2;
    alphay[LMBC2IBCdot_tmp] = spsiE;
    Machtab[LMBC2IBCdot_tmp] = b_a;
    alphay[LMBC2IBCdot_tmp + 1] = cpsiE;
    Machtab[LMBC2IBCdot_tmp + 1] = sphi;
    alphay[LMBC2IBCdot_tmp + 2] = Tbody2NED_tmp;
    Machtab[LMBC2IBCdot_tmp + 2] = cphi;
    alphay[LMBC2IBCdot_tmp + 3] = a;
    Machtab[LMBC2IBCdot_tmp + 3] = cthe;
  }
  r = _mm_loadu_pd(&LIBC2MBCdot_tmp[0]);
  r1 = _mm_loadu_pd(&cpsi[0]);
  _mm_storeu_pd(&Frb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&sbeta[0]);
  r1 = _mm_loadu_pd(&cpsizeta[0]);
  _mm_storeu_pd(&Ftb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&LIBC2MBCdot_tmp[2]);
  r1 = _mm_loadu_pd(&cpsi[2]);
  _mm_storeu_pd(&Frb[2], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&sbeta[2]);
  r1 = _mm_loadu_pd(&cpsizeta[2]);
  _mm_storeu_pd(&Ftb[2], _mm_mul_pd(r, r1));
  for (k = 0; k < 10; k++) {
    r = _mm_loadu_pd(&Frb[0]);
    LMBC2IBCdot_tmp = k << 2;
    _mm_storeu_pd(&Mach[LMBC2IBCdot_tmp], r);
    r = _mm_loadu_pd(&Ftb[0]);
    r1 = _mm_set1_pd(constants->RSEG[k]);
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp], _mm_mul_pd(r, r1));
    r = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Mach[LMBC2IBCdot_tmp + 2], r);
    r = _mm_loadu_pd(&Ftb[2]);
    _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp + 2], _mm_mul_pd(r, r1));
  }
  r = _mm_loadu_pd(&LIBC2MBCdot_tmp[0]);
  r1 = _mm_loadu_pd(&spsi[0]);
  _mm_storeu_pd(&Frb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&sbeta[0]);
  r1 = _mm_loadu_pd(&spsizeta[0]);
  _mm_storeu_pd(&Ftb[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&LIBC2MBCdot_tmp[2]);
  r1 = _mm_loadu_pd(&spsi[2]);
  _mm_storeu_pd(&Frb[2], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&sbeta[2]);
  r1 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&Ftb[2], _mm_mul_pd(r, r1));
  spsiE = x[16];
  cpsiE = x[18];
  Tbody2NED_tmp = x[17];
  r = _mm_set1_pd(0.0);
  r1 = _mm_set1_pd(-spsiE);
  r2 = _mm_set1_pd(cpsiE);
  r3 = _mm_set1_pd(Tbody2NED_tmp);
  for (k = 0; k < 10; k++) {
    r4 = _mm_loadu_pd(&Ftb[0]);
    r5 = _mm_loadu_pd(&sbeta[0]);
    LMBC2IBCdot_tmp = k << 2;
    r18 = _mm_loadu_pd(&alphay[LMBC2IBCdot_tmp]);
    r6 = _mm_loadu_pd(&Machtab[LMBC2IBCdot_tmp]);
    r9 = _mm_loadu_pd(&Mach[LMBC2IBCdot_tmp]);
    r15 = _mm_loadu_pd(&b_Fpb[LMBC2IBCdot_tmp]);
    r16 = _mm_loadu_pd(&Frb[0]);
    r17 = _mm_set1_pd(constants->RSEG[k]);
    _mm_storeu_pd(
        &Ur[LMBC2IBCdot_tmp],
        _mm_add_pd(
            _mm_add_pd(r18, r6),
            _mm_sub_pd(_mm_sub_pd(_mm_add_pd(r, _mm_mul_pd(r1, r5)),
                                  _mm_mul_pd(r2, _mm_add_pd(r9, r15))),
                       _mm_mul_pd(r3, _mm_add_pd(r16, _mm_mul_pd(r4, r17))))));
    r4 = _mm_loadu_pd(&Ftb[2]);
    r5 = _mm_loadu_pd(&sbeta[2]);
    r18 = _mm_loadu_pd(&alphay[LMBC2IBCdot_tmp + 2]);
    r6 = _mm_loadu_pd(&Machtab[LMBC2IBCdot_tmp + 2]);
    r9 = _mm_loadu_pd(&Mach[LMBC2IBCdot_tmp + 2]);
    r15 = _mm_loadu_pd(&b_Fpb[LMBC2IBCdot_tmp + 2]);
    r16 = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(
        &Ur[LMBC2IBCdot_tmp + 2],
        _mm_add_pd(
            _mm_add_pd(r18, r6),
            _mm_sub_pd(_mm_sub_pd(_mm_add_pd(r, _mm_mul_pd(r1, r5)),
                                  _mm_mul_pd(r2, _mm_add_pd(r9, r15))),
                       _mm_mul_pd(r3, _mm_add_pd(r16, _mm_mul_pd(r4, r17))))));
  }
  /*  + Urg; */
  /* 'GHrotor:279' Utot=sqrt(Up.^2+Ut.^2+Ur.^2); */
  /* Local angles of attack, Mach, skew */
  /* 'GHrotor:282' cosgam=abs(Ut)./sqrt(Ut.^2+Ur.^2); */
  /* 'GHrotor:283' acosgam=abs(cosgam); */
  /* 'GHrotor:284'
   * alphay=(180./pi)*atan2((Ut.*tan(theta)+Up).*acosgam,(Ut-Up.*tan(theta).*cosgam.*cosgam));
   */
  /* 'GHrotor:285' Mach=sqrt(Ut.^2+Up.^2)*OMEGA*R/VSOUND; */
  /* 'GHrotor:286' Machtab=max(min(Mach,1.0),0.); */
  /* GENHEL ROTOR MODEL */
  /* 'GHrotor:289' atrans0=cosgam.*alphay; */
  /* 'GHrotor:290' atranslow=(alphay+180.).*cosgam-180.; */
  /* 'GHrotor:291' atranshigh=180.+(alphay-180.).*cosgam; */
  /* 'GHrotor:292'
   * atrans1=((1.-ACL1/90.)*atrans0-ACL1*(1.-cosgam))./(-ACL1/90.+cosgam); */
  cphi = 1.0 - constants->ACL1 / 90.0;
  /* 'GHrotor:293'
   * atrans2=((1.-ACL2/90.)*atranshigh+ACL2*(1.-cosgam))./(2.-ACL2/90.-cosgam);
   */
  cthe = constants->ACL2 / 90.0;
  /* 'GHrotor:294'
   * atrans3=((1.+ACL3/90.)*atrans0-ACL3*(1.-cosgam))./(ACL3/90.+cosgam); */
  KR = constants->ACL3 / 90.0;
  /* 'GHrotor:295'
   * atrans4=((1.+ACL4/90.)*atranslow+ACL4*(1.-cosgam))./(2.+ACL4/90.-cosgam);
   */
  muxs = constants->ACL4 / 90.0;
  /* 'GHrotor:297'
   * atrans=atrans0.*(atrans0<=ACL1).*(atrans0>=ACL3).*(abs(alphay)<90.) + ...
   */
  /* 'GHrotor:298'        atrans1.*(atrans0>ACL1).*(alphay<90.) + ... */
  /* 'GHrotor:299'        (atrans2.*(atranshigh<ACL2) +
   * atranshigh.*(atranshigh>=ACL2)).*(alphay>=90.) + ... */
  /* 'GHrotor:300'        atrans3.*(atrans0<ACL3).*(alphay>=-90.) + ... */
  /* 'GHrotor:301'        (atrans4.*(atranslow>ACL4) +
   * atranslow.*(atranslow<=ACL4)).*(alphay<-90.); */
  e = -constants->ACL1 / 90.0;
  /* 'GHrotor:303' atransBtab=max(min(atrans,32.),-32.); */
  /* 'GHrotor:304' alphayBtab=max(min(alphay,32.),-32.); */
  /* 'GHrotor:306'
   * CL=interp1(constants.AOAUTAB,constants.CLR0UTAB,atrans).*(abs(atrans)>32.)
   * + ... */
  /* 'GHrotor:307'
   * interp2(constants.AOABTAB,constants.MACHTAB,constants.CLR0BTAB,atransBtab,Machtab).*(abs(atrans)<=32.);
   */
  mutot = u[21];
  for (k = 0; k < 40; k++) {
    cpsiE = Ut[k];
    c_a = rt_powd_snf(cpsiE, 2.0);
    spsiE = rt_powd_snf(Ur[k], 2.0);
    b_Fpb[k] = spsiE;
    Tbody2NED_tmp = Up[k];
    a = rt_powd_snf(Tbody2NED_tmp, 2.0) + c_a;
    b_cbeta[k] = a;
    c_a += spsiE;
    c_a = sqrt(c_a);
    b_a = fabs(cpsiE) / c_a;
    acosgam[k] = b_a;
    sphi = tan(theta[k]);
    c_a = (cpsiE * sphi + Tbody2NED_tmp) * b_a;
    sphi = cpsiE - Tbody2NED_tmp * sphi * b_a * b_a;
    Tbody2NED_tmp = 57.29577951308232 * b_atan2(c_a, sphi);
    alphay[k] = Tbody2NED_tmp;
    Machtab[k] =
        fmax(fmin(sqrt(a) * mutot * constants->R / atmos_spsnd, 1.0), 0.0);
    spsiE = b_a * Tbody2NED_tmp;
    c_a = (Tbody2NED_tmp + 180.0) * b_a - 180.0;
    sphi = (Tbody2NED_tmp - 180.0) * b_a + 180.0;
    cpsiE = fabs(Tbody2NED_tmp);
    atrans_tmp[k] = cpsiE;
    spsiE = (((spsiE * (double)(spsiE <= constants->ACL1) *
                   (double)(spsiE >= constants->ACL3) * (double)(cpsiE < 90.0) +
               (cphi * spsiE - constants->ACL1 * (1.0 - b_a)) / (e + b_a) *
                   (double)(spsiE > constants->ACL1) *
                   (double)(Tbody2NED_tmp < 90.0)) +
              (((1.0 - cthe) * sphi + constants->ACL2 * (1.0 - b_a)) /
                   ((2.0 - cthe) - b_a) * (double)(sphi < constants->ACL2) +
               sphi * (double)(sphi >= constants->ACL2)) *
                  (double)(Tbody2NED_tmp >= 90.0)) +
             ((KR + 1.0) * spsiE - constants->ACL3 * (1.0 - b_a)) / (KR + b_a) *
                 (double)(spsiE < constants->ACL3) *
                 (double)(Tbody2NED_tmp >= -90.0)) +
            (((muxs + 1.0) * c_a + constants->ACL4 * (1.0 - b_a)) /
                 ((muxs + 2.0) - b_a) * (double)(c_a > constants->ACL4) +
             c_a * (double)(c_a <= constants->ACL4)) *
                (double)(Tbody2NED_tmp < -90.0);
    atrans0[k] = spsiE;
    atransBtab[k] = fmax(fmin(spsiE, 32.0), -32.0);
    sphi = fmin(Tbody2NED_tmp, 32.0);
    theta[k] = sphi;
    cosgam[k] = fmax(sphi, -32.0);
    Mach[k] = fabs(spsiE);
  }
  b_interp1(constants->AOAUTAB, constants->CLR0UTAB, atrans0, CL);
  b_interp2(constants->AOABTAB, constants->MACHTAB, constants->CLR0BTAB,
            atransBtab, Machtab, theta);
  for (k = 0; k < 40; k++) {
    spsiE = Mach[k];
    CL[k] = CL[k] * (double)(spsiE > 32.0) + theta[k] * (double)(spsiE <= 32.0);
  }
  /* 'GHrotor:309'
   * CD=interp1(constants.AOAUTAB,constants.CDR0UTAB,alphay).*(abs(alphay)>32.)
   * + ... */
  /* 'GHrotor:310'
   * interp2(constants.AOABTAB,constants.MACHTAB,constants.CDR0BTAB,alphayBtab,Machtab).*(abs(alphay)<=32.)
   * + ... */
  /* 'GHrotor:311'    constants.DCDMR; */
  b_interp1(constants->AOAUTAB, constants->CDR0UTAB, alphay, atrans0);
  b_interp2(constants->AOABTAB, constants->MACHTAB, constants->CDR0BTAB, cosgam,
            Machtab, theta);
  for (k = 0; k < 40; k++) {
    spsiE = atrans_tmp[k];
    atrans0[k] = (atrans0[k] * (double)(spsiE > 32.0) +
                  theta[k] * (double)(spsiE <= 32.0)) +
                 constants->DCDMR;
  }
  /* lift array specific to Peters-He inflow form */
  /* BLSEGLIFT =
   * ((0.5*(ones(NB,1)*CHORD))./R).*CL.*sign(Ut).*Utot.*sqrt(Ut.^2+Ur.^2);
   * %without density, sectional */
  /* Blade segment forces */
  /* 'GHrotor:317'
   * Fp=(0.5*RHO*OMEGA^2*R^3)*(ones(NB,1)*CHORD).*Utot.*(CL.*Ut./acosgam+CD.*Up).*(ones(NB,1)*delseg);
   */
  for (k = 0; k < 10; k++) {
    LMBC2IBCdot_tmp = k << 2;
    spsiE = constants->DELSEG[k];
    cosgam[LMBC2IBCdot_tmp] = spsiE;
    cosgam[LMBC2IBCdot_tmp + 1] = spsiE;
    cosgam[LMBC2IBCdot_tmp + 2] = spsiE;
    cosgam[LMBC2IBCdot_tmp + 3] = spsiE;
  }
  Tbody2NED_tmp = u[21] * u[21];
  spsiE = 0.5 * atmos_rho * Tbody2NED_tmp * rt_powd_snf(constants->R, 3.0);
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&b_cbeta[k]);
    r1 = _mm_loadu_pd(&b_Fpb[k]);
    _mm_storeu_pd(&b_cbeta[k], _mm_sqrt_pd(_mm_add_pd(r, r1)));
  }
  for (k = 0; k < 10; k++) {
    LMBC2IBCdot_tmp = k << 2;
    cpsiE = constants->CHORD[k];
    Mach[LMBC2IBCdot_tmp] = cpsiE;
    Mach[LMBC2IBCdot_tmp + 1] = cpsiE;
    Mach[LMBC2IBCdot_tmp + 2] = cpsiE;
    Mach[LMBC2IBCdot_tmp + 3] = cpsiE;
  }
  /* 'GHrotor:318'
   * Ft=(0.5*RHO*OMEGA^2*R^3)*(ones(NB,1)*CHORD).*Utot.*(CD.*Ut-CL.*Up.*acosgam).*(ones(NB,1)*delseg);
   */
  /* 'GHrotor:319'
   * Fr=(0.5*RHO*OMEGA^2*R^3)*(ones(NB,1)*CHORD).*Utot.*(CD-CL.*Up.*acosgam./Ut).*Ur.*(ones(NB,1)*delseg);
   */
  /* Total shear force at each blade hinge */
  /* 'GHrotor:322' Fpb=sum(Fp,2); */
  /* 'GHrotor:323' Ftb=sum(Ft,2); */
  /* 'GHrotor:324' Frb=sum(Fr,2); */
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&Mach[k]);
    r1 = _mm_loadu_pd(&b_cbeta[k]);
    r3 = _mm_mul_pd(_mm_mul_pd(_mm_set1_pd(spsiE), r), r1);
    r = _mm_loadu_pd(&CL[k]);
    r18 = _mm_loadu_pd(&Ut[k]);
    r1 = _mm_loadu_pd(&acosgam[k]);
    r4 = _mm_loadu_pd(&atrans0[k]);
    r2 = _mm_loadu_pd(&Up[k]);
    r5 = _mm_loadu_pd(&cosgam[k]);
    _mm_storeu_pd(
        &atransBtab[k],
        _mm_mul_pd(_mm_mul_pd(r3, _mm_add_pd(_mm_div_pd(_mm_mul_pd(r, r18), r1),
                                             _mm_mul_pd(r4, r2))),
                   r5));
    r = _mm_mul_pd(_mm_mul_pd(r, r2), r1);
    _mm_storeu_pd(&CL[k], r);
    _mm_storeu_pd(
        &theta[k],
        _mm_mul_pd(_mm_mul_pd(r3, _mm_sub_pd(_mm_mul_pd(r4, r18), r)), r5));
    r1 = _mm_loadu_pd(&Ur[k]);
    _mm_storeu_pd(
        &Mach[k],
        _mm_mul_pd(
            _mm_mul_pd(_mm_mul_pd(r3, _mm_sub_pd(r4, _mm_div_pd(r, r18))), r1),
            r5));
  }
  sum(atransBtab, Fpb);
  sum(theta, Ftb);
  sum(Mach, Frb);
  /* Sum total blade forces for dynamic twist model */
  /* 'GHrotor:327' Fp_DT=sum(sqrt(Fpb.^2+Ftb.^2))/constants.NB; */
  b_y[0] = rt_powd_snf(Fpb[0], 2.0);
  c_y[0] = rt_powd_snf(Ftb[0], 2.0);
  b_y[1] = rt_powd_snf(Fpb[1], 2.0);
  c_y[1] = rt_powd_snf(Ftb[1], 2.0);
  b_y[2] = rt_powd_snf(Fpb[2], 2.0);
  c_y[2] = rt_powd_snf(Ftb[2], 2.0);
  b_y[3] = rt_powd_snf(Fpb[3], 2.0);
  c_y[3] = rt_powd_snf(Ftb[3], 2.0);
  /* Total aero moment about each hinge */
  /* 'GHrotor:330' Mf_aero=R*sum((ones(NB,1)*rseg).*Fp,2); */
  for (k = 0; k < 10; k++) {
    LMBC2IBCdot_tmp = k << 2;
    spsiE = constants->RSEG[k];
    Mach[LMBC2IBCdot_tmp] = spsiE;
    Mach[LMBC2IBCdot_tmp + 1] = spsiE;
    Mach[LMBC2IBCdot_tmp + 2] = spsiE;
    Mach[LMBC2IBCdot_tmp + 3] = spsiE;
  }
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&Mach[k]);
    r1 = _mm_loadu_pd(&atransBtab[k]);
    _mm_storeu_pd(&atransBtab[k], _mm_mul_pd(r, r1));
  }
  sum(atransBtab, Mf_aero);
  /* 'GHrotor:331' Ml_aero=R*sum((ones(NB,1)*rseg).*Ft,2); */
  /* Aero moments */
  /* 'GHrotor:334' Lha=-sum(Mf_aero.*spsizeta); */
  /* 'GHrotor:335' Mha=-sum(Mf_aero.*cpsizeta); */
  /* Aero shear forces at each hinge */
  /* 'GHrotor:338' Fxa=Frb.*cbeta.*szeta-Ftb.*czeta-Fpb.*sbeta.*szeta; */
  /* 'GHrotor:339' Fya=Frb.*cbeta.*czeta+Ftb.*szeta-Fpb.*sbeta.*czeta; */
  /* 'GHrotor:340' Fza=-Frb.*sbeta-Fpb.*cbeta; */
  r = _mm_loadu_pd(&Mf_aero[0]);
  r4 = _mm_set1_pd(constants->R);
  _mm_storeu_pd(&Mf_aero[0], _mm_mul_pd(r4, r));
  r = _mm_loadu_pd(&Frb[0]);
  r1 = _mm_loadu_pd(&cbeta[0]);
  _mm_storeu_pd(&Fxa_tmp[0], _mm_mul_pd(r, r1));
  r2 = _mm_loadu_pd(&Fpb[0]);
  r3 = _mm_loadu_pd(&sbeta[0]);
  _mm_storeu_pd(&b_Fxa_tmp[0], _mm_mul_pd(r2, r3));
  _mm_storeu_pd(&Frb[0], _mm_sub_pd(_mm_mul_pd(_mm_mul_pd(r, r14), r3),
                                    _mm_mul_pd(r2, r1)));
  r = _mm_loadu_pd(&Mf_aero[2]);
  _mm_storeu_pd(&Mf_aero[2], _mm_mul_pd(r4, r));
  r = _mm_loadu_pd(&Frb[2]);
  r1 = _mm_loadu_pd(&cbeta[2]);
  _mm_storeu_pd(&Fxa_tmp[2], _mm_mul_pd(r, r1));
  r2 = _mm_loadu_pd(&Fpb[2]);
  r3 = _mm_loadu_pd(&sbeta[2]);
  _mm_storeu_pd(&b_Fxa_tmp[2], _mm_mul_pd(r2, r3));
  _mm_storeu_pd(&Frb[2], _mm_sub_pd(_mm_mul_pd(_mm_mul_pd(r, r14), r3),
                                    _mm_mul_pd(r2, r1)));
  /* Total aero thrust */
  /* 'GHrotor:343' Tha=-sum(Fza); */
  /* Aero force and momemnt coefficients (used by Pitt Peters model) */
  /* 'GHrotor:345' CTa=Tha/(pi*RHO*OMEGA^2*R^4); */
  CTa_tmp = 3.141592653589793 * atmos_rho * Tbody2NED_tmp;
  CTa = -(((Frb[0] + Frb[1]) + Frb[2]) + Frb[3]) /
        (CTa_tmp * rt_powd_snf(constants->R, 4.0));
  /* 'GHrotor:346' CLa=Lha/(pi*RHO*OMEGA^2*R^5); */
  /* 'GHrotor:347' CMa=Mha/(pi*RHO*OMEGA^2*R^5); */
  /* Lag damper kinematics - complex model used for UH-60A GENHEL */
  /* 'GHrotor:350' thetald=thetab-THETALDGEO; */
  /* 'GHrotor:351'
   * xld=ALD*sbeta+CLD+(BLD*cos(zeta+ZETA0)+DLD*sin(zeta+ZETA0)).*cbeta; */
  /* 'GHrotor:352'
   * yld=-RLD*cos(thetald)-BLD*sin(zeta+ZETA0)+DLD*cos(zeta+ZETA0); */
  /* 'GHrotor:353'
   * zld=ALD*cbeta-RLD*sin(thetald)-(BLD*cos(zeta+ZETA0)+DLD*sin(zeta+ZETA0)).*sbeta;
   */
  /* 'GHrotor:354' daxld=sqrt(xld.^2+yld.^2+zld.^2); */
  /* Lag damper rate */
  /* 'GHrotor:357' xld_dot =
   * ALD*beta_dot.*cbeta-beta_dot.*sbeta.*(BLD*cos(zeta+ZETA0)+DLD*sin(zeta+ZETA0))
   * + ... */
  /* 'GHrotor:358' (-BLD*sin(zeta+ZETA0)+DLD*cos(zeta+ZETA0)).*zeta_dot.*cbeta;
   */
  /* 'GHrotor:359' yld_dot = RLD*sin(thetald).*thetab_dot
   * -(BLD*cos(zeta+ZETA0)+DLD*cos(zeta+ZETA0)).*zeta_dot; */
  /* 'GHrotor:360' zld_dot = -ALD*sbeta.*beta_dot-RLD*cos(thetald).*thetab_dot
   * -cbeta.*beta_dot.*(BLD*cos(zeta+ZETA0)+DLD*sin(zeta+ZETA0)) + ... */
  /* 'GHrotor:361' -(-BLD*sin(zeta+ZETA0)+DLD*cos(zeta+ZETA0)).*zeta_dot.*sbeta;
   */
  /* 'GHrotor:362' raxld = (xld.*xld_dot+yld.*yld_dot+zld.*zld_dot)./daxld; */
  /* Lag damper force (LINEAR LAG DAMPER, CAN UPDATE TO LOOK UP TABLE) */
  /* 'GHrotor:364' Fld=CLAG*raxld; */
  /* Flap and lag moments due to lag damper force  */
  /* 'GHrotor:366' Mf_ld=-Fld.*((zld*CLD)+(xld.*sin(thetald)*RLD))./(12*daxld);
   */
  /* 'GHrotor:367'
   * Ml_ld=-Fld.*(RLD*cos(thetald).*(xld.*cbeta-zld.*sbeta)+yld.*(CLD*cbeta+RLD*sin(thetald).*sbeta))./(12.*daxld)
   * + ... */
  /* 'GHrotor:368'           -KLAG*(zeta+ZETA0); */
  /* Notional flap sping /damper */
  /* 'GHrotor:370' Mf_fd=-constants.KFLAP*beta-constants.CFLAP*beta_dot; */
  /* Flap and lag acclerations       */
  /* 'GHrotor:372'
   * beta_ddot=(MBETA/IBETA)*(cbeta.*(Vzsdot+HOFFSET*(2*OMEGA*(ps*cpsi-qs*spsi)+psdot*spsi+qsdot*cpsi))
   * + ... */
  /* 'GHrotor:373' sbeta.*czeta.*(Vysdot*spsi-Vxsdot*cpsi-HOFFSET*rminusO^2) +
   * sbeta.*szeta.*(Vysdot*spsi-Vxsdot*cpsi-HOFFSET*rsdotmomd)) +... */
  /* 'GHrotor:374'
   * (cbeta.^2).*(czeta.*(psdot*spsi+qsdot*cpsi-2*(zeta_dot+OMEGA).*(qs*spsi-ps*cpsi))
   * - szeta.*(2*(OMEGA+zeta_dot).*(ps*spsi+qs*cpsi)+(qsdot*spsi-psdot*cpsi)) )
   * + ...  */
  /* 'GHrotor:375' cbeta.*sbeta.*(2*zeta_dot*rminusO-rminusO^2-zeta_dot.^2) +
   * ... */
  /* 'GHrotor:376'            (Mf_aero+Mf_ld+Mf_fd)/IBETA; */
  cpsiE = 2.0 * u[21];
  c = rminusO * rminusO;
  Tbody2NED_tmp = constants->MBETA / constants->IBETA;
  a = constants->HOFFSET * rsdotmomd;
  /* 'GHrotor:377'
   * zeta_ddot=(MBETA./(IBETA*cbeta)).*(szeta.*(Vysdot*spsi-Vxsdot*cpsi -
   * HOFFSET*rminusO^2) + ... */
  /* 'GHrotor:378'               -czeta.*(Vxsdot*spsi+Vysdot*cpsi)) + rsdotmomd
   * + ... */
  /* 'GHrotor:379'
   * (sbeta./cbeta).*(2*beta_dot.*(OMEGA+zeta_dot-rs)+qsdot*spsizeta-psdot*cpsizeta)
   * + ... */
  /* 'GHrotor:380'
   * 2*beta_dot.*(czeta.*(qs*spsi-ps*cpsi)+szeta.*(ps*spsi+qs*cpsi)) + ... */
  /* 'GHrotor:381' (Ml_ld)./(IBETA*cbeta.^2)-Ml_aero./(IBETA*cbeta); */
  b_a = thetab[0] - constants->THETALDGEO;
  d2 = zeta[0] + constants->ZETA0;
  d3 = sin(d2);
  d4 = cos(d2);
  d5 = constants->BLD * d4;
  d6 = d5 + constants->DLD * d3;
  spsiE = (constants->ALD * sbeta[0] + constants->CLD) + d6 * cbeta[0];
  d4 *= constants->DLD;
  yld_tmp_idx_3 = cos(b_a);
  d7 = (-constants->RLD * yld_tmp_idx_3 - constants->BLD * d3) + d4;
  b_a = sin(b_a);
  zld_tmp_idx_3 = constants->RLD * b_a;
  d8 = (constants->ALD * cbeta[0] - zld_tmp_idx_3) - d6 * sbeta[0];
  d9 = sqrt((rt_powd_snf(spsiE, 2.0) + rt_powd_snf(d7, 2.0)) +
            rt_powd_snf(d8, 2.0));
  d3 = -constants->BLD * d3 + d4;
  yld_tmp_idx_3 *= constants->RLD;
  d6 = constants->CLAG *
       (((spsiE * ((constants->ALD * beta_dot[0] * cbeta[0] -
                    beta_dot[0] * sbeta[0] * d6) +
                   d3 * zeta_dot[0] * cbeta[0]) +
          d7 * (zld_tmp_idx_3 * thetab_dot_idx_0 - (d5 + d4) * zeta_dot[0])) +
         d8 * (((-constants->ALD * sbeta[0] * beta_dot[0] -
                 yld_tmp_idx_3 * thetab_dot_idx_0) -
                cbeta[0] * beta_dot[0] * d6) +
               -d3 * zeta_dot[0] * sbeta[0])) /
        d9);
  d9 *= 12.0;
  b_a = -d6 * (d8 * constants->CLD + spsiE * b_a * constants->RLD) / d9;
  thetab[0] = b_a;
  d6 = -d6 *
           (yld_tmp_idx_3 * (spsiE * cbeta[0] - d8 * sbeta[0]) +
            d7 * (constants->CLD * cbeta[0] + zld_tmp_idx_3 * sbeta[0])) /
           d9 +
       -constants->KLAG * d2;
  Fld[0] = d6;
  yld_tmp_idx_3 = Vxsdot * cpsi[0];
  yld_tmp_idx_0 = yld_tmp_idx_3;
  d7 = Vysdot * spsi[0];
  yld_idx_0 = d7;
  d_y = d7 - yld_tmp_idx_3;
  zld_tmp_idx_3 = psdot * spsi[0];
  zld_tmp_idx_0 = zld_tmp_idx_3;
  d8 = qsdot * cpsi[0];
  zld_idx_0 = d8;
  Lhub = spsi[0] * temp[1];
  Mhub = temp[0] * cpsi[0];
  d2 = zeta_dot[0] + u[21];
  LIBC2MBCdot_tmp[0] = d2;
  d9 = 2.0 * d2;
  daxld_idx_0 = d9;
  d3 = Lhub - Mhub;
  psi[0] = d3;
  d4 = rt_powd_snf(cbeta[0], 2.0);
  Fpb[0] = d4;
  e_y = rt_powd_snf(zeta_dot[0], 2.0);
  Fyt[0] = e_y;
  Mhub -= Lhub;
  y_idx_0 = Mhub;
  Lhub = sbeta[0] * czeta[0];
  b_y_idx_0 = Lhub;
  d10 = d9 * Up_tmp[0];
  thetab_dot_idx_0 = d10;
  beta_ddot_tmp_idx_3 = qsdot * spsi[0];
  beta_ddot_tmp_idx_0 = beta_ddot_tmp_idx_3;
  b_beta_ddot_tmp_idx_3 = psdot * cpsi[0];
  b_beta_ddot_tmp_idx_0 = b_beta_ddot_tmp_idx_3;
  c_beta_ddot_tmp_idx_3 = (cpsiE * Mhub + zld_tmp_idx_3) + d8;
  c_beta_ddot_tmp_idx_0 = c_beta_ddot_tmp_idx_3;
  sphi = constants->HOFFSET * c;
  d5 = d_y - sphi;
  xld_tmp_tmp[0] = d5;
  d_y =
      ((Tbody2NED_tmp *
            ((cbeta[0] * (Vzsdot + constants->HOFFSET * c_beta_ddot_tmp_idx_3) +
              Lhub * d5) +
             Fxt[0] * (d_y - a)) +
        d4 * (czeta[0] * ((zld_tmp_idx_3 + d8) - d9 * d3) -
              szeta[0] *
                  (d10 + (beta_ddot_tmp_idx_3 - b_beta_ddot_tmp_idx_3)))) +
       cbeta[0] * sbeta[0] * ((2.0 * zeta_dot[0] * rminusO - c) - e_y)) +
      ((Mf_aero[0] + b_a) +
       (-constants->KFLAP * beta[0] - constants->CFLAP * beta_dot[0])) /
          constants->IBETA;
  beta_ddot[0] = d_y;
  Hforce = 2.0 * beta_dot[0];
  zeta_ddot[0] = constants->IBETA * cbeta[0];
  zeta_ddot_tmp_idx_0 = Vxsdot * spsi[0] + Vysdot * cpsi[0];
  b_a = thetab[1] - constants->THETALDGEO;
  d2 = zeta[1] + constants->ZETA0;
  d3 = sin(d2);
  d4 = cos(d2);
  d5 = constants->BLD * d4;
  d6 = d5 + constants->DLD * d3;
  spsiE = (constants->ALD * sbeta[1] + constants->CLD) + d6 * cbeta[1];
  d4 *= constants->DLD;
  yld_tmp_idx_3 = cos(b_a);
  d7 = (-constants->RLD * yld_tmp_idx_3 - constants->BLD * d3) + d4;
  b_a = sin(b_a);
  zld_tmp_idx_3 = constants->RLD * b_a;
  d8 = (constants->ALD * cbeta[1] - zld_tmp_idx_3) - d6 * sbeta[1];
  d9 = sqrt((rt_powd_snf(spsiE, 2.0) + rt_powd_snf(d7, 2.0)) +
            rt_powd_snf(d8, 2.0));
  d3 = -constants->BLD * d3 + d4;
  yld_tmp_idx_3 *= constants->RLD;
  d6 = constants->CLAG *
       (((spsiE * ((constants->ALD * beta_dot[1] * cbeta[1] -
                    beta_dot[1] * sbeta[1] * d6) +
                   d3 * zeta_dot[1] * cbeta[1]) +
          d7 * (zld_tmp_idx_3 * thetab_dot_idx_1 - (d5 + d4) * zeta_dot[1])) +
         d8 * (((-constants->ALD * sbeta[1] * beta_dot[1] -
                 yld_tmp_idx_3 * thetab_dot_idx_1) -
                cbeta[1] * beta_dot[1] * d6) +
               -d3 * zeta_dot[1] * sbeta[1])) /
        d9);
  d9 *= 12.0;
  b_a = -d6 * (d8 * constants->CLD + spsiE * b_a * constants->RLD) / d9;
  thetab[1] = b_a;
  d6 = -d6 *
           (yld_tmp_idx_3 * (spsiE * cbeta[1] - d8 * sbeta[1]) +
            d7 * (constants->CLD * cbeta[1] + zld_tmp_idx_3 * sbeta[1])) /
           d9 +
       -constants->KLAG * d2;
  Fld[1] = d6;
  yld_tmp_idx_3 = Vxsdot * cpsi[1];
  yld_tmp_idx_1 = yld_tmp_idx_3;
  d7 = Vysdot * spsi[1];
  yld_idx_1 = d7;
  d_y = d7 - yld_tmp_idx_3;
  zld_tmp_idx_3 = psdot * spsi[1];
  zld_tmp_idx_1 = zld_tmp_idx_3;
  d8 = qsdot * cpsi[1];
  zld_idx_1 = d8;
  Lhub = temp[1] * spsi[1];
  Mhub = temp[0] * cpsi[1];
  d2 = zeta_dot[1] + u[21];
  LIBC2MBCdot_tmp[1] = d2;
  d9 = 2.0 * d2;
  daxld_idx_1 = d9;
  d3 = Lhub - Mhub;
  psi[1] = d3;
  d4 = rt_powd_snf(cbeta[1], 2.0);
  Fpb[1] = d4;
  e_y = rt_powd_snf(zeta_dot[1], 2.0);
  Fyt[1] = e_y;
  Mhub -= Lhub;
  y_idx_1 = Mhub;
  Lhub = sbeta[1] * czeta[1];
  b_y_idx_1 = Lhub;
  d10 = d9 * Up_tmp[1];
  thetab_dot_idx_1 = d10;
  beta_ddot_tmp_idx_3 = qsdot * spsi[1];
  beta_ddot_tmp_idx_1 = beta_ddot_tmp_idx_3;
  b_beta_ddot_tmp_idx_3 = psdot * cpsi[1];
  b_beta_ddot_tmp_idx_1 = b_beta_ddot_tmp_idx_3;
  c_beta_ddot_tmp_idx_3 = (cpsiE * Mhub + zld_tmp_idx_3) + d8;
  c_beta_ddot_tmp_idx_1 = c_beta_ddot_tmp_idx_3;
  d5 = d_y - sphi;
  xld_tmp_tmp[1] = d5;
  d_y =
      ((Tbody2NED_tmp *
            ((cbeta[1] * (Vzsdot + constants->HOFFSET * c_beta_ddot_tmp_idx_3) +
              Lhub * d5) +
             Fxt[1] * (d_y - a)) +
        d4 * (czeta[1] * ((zld_tmp_idx_3 + d8) - d9 * d3) -
              szeta[1] *
                  (d10 + (beta_ddot_tmp_idx_3 - b_beta_ddot_tmp_idx_3)))) +
       cbeta[1] * sbeta[1] * ((2.0 * zeta_dot[1] * rminusO - c) - e_y)) +
      ((Mf_aero[1] + b_a) +
       (-constants->KFLAP * beta[1] - constants->CFLAP * beta_dot[1])) /
          constants->IBETA;
  beta_ddot[1] = d_y;
  zeta_ddot_tmp_idx_1 = 2.0 * beta_dot[1];
  zeta_ddot[1] = constants->IBETA * cbeta[1];
  b_zeta_ddot_tmp_idx_1 = Vxsdot * spsi[1] + Vysdot * cpsi[1];
  b_a = thetab[2] - constants->THETALDGEO;
  d2 = zeta[2] + constants->ZETA0;
  d3 = sin(d2);
  d4 = cos(d2);
  d5 = constants->BLD * d4;
  d6 = d5 + constants->DLD * d3;
  spsiE = (constants->ALD * sbeta[2] + constants->CLD) + d6 * cbeta[2];
  d4 *= constants->DLD;
  yld_tmp_idx_3 = cos(b_a);
  d7 = (-constants->RLD * yld_tmp_idx_3 - constants->BLD * d3) + d4;
  b_a = sin(b_a);
  zld_tmp_idx_3 = constants->RLD * b_a;
  d8 = (constants->ALD * cbeta[2] - zld_tmp_idx_3) - d6 * sbeta[2];
  d9 = sqrt((rt_powd_snf(spsiE, 2.0) + rt_powd_snf(d7, 2.0)) +
            rt_powd_snf(d8, 2.0));
  d3 = -constants->BLD * d3 + d4;
  yld_tmp_idx_3 *= constants->RLD;
  d6 = constants->CLAG *
       (((spsiE * ((constants->ALD * beta_dot[2] * cbeta[2] -
                    beta_dot[2] * sbeta[2] * d6) +
                   d3 * zeta_dot[2] * cbeta[2]) +
          d7 * (zld_tmp_idx_3 * thetab_dot_idx_2 - (d5 + d4) * zeta_dot[2])) +
         d8 * (((-constants->ALD * sbeta[2] * beta_dot[2] -
                 yld_tmp_idx_3 * thetab_dot_idx_2) -
                cbeta[2] * beta_dot[2] * d6) +
               -d3 * zeta_dot[2] * sbeta[2])) /
        d9);
  d9 *= 12.0;
  b_a = -d6 * (d8 * constants->CLD + spsiE * b_a * constants->RLD) / d9;
  thetab[2] = b_a;
  d6 = -d6 *
           (yld_tmp_idx_3 * (spsiE * cbeta[2] - d8 * sbeta[2]) +
            d7 * (constants->CLD * cbeta[2] + zld_tmp_idx_3 * sbeta[2])) /
           d9 +
       -constants->KLAG * d2;
  Fld[2] = d6;
  yld_tmp_idx_3 = Vxsdot * cpsi[2];
  yld_tmp_idx_2 = yld_tmp_idx_3;
  d7 = Vysdot * spsi[2];
  yld_idx_2 = d7;
  d_y = d7 - yld_tmp_idx_3;
  zld_tmp_idx_3 = psdot * spsi[2];
  zld_tmp_idx_2 = zld_tmp_idx_3;
  d8 = qsdot * cpsi[2];
  zld_idx_2 = d8;
  Lhub = temp[1] * spsi[2];
  Mhub = temp[0] * cpsi[2];
  d2 = zeta_dot[2] + u[21];
  LIBC2MBCdot_tmp[2] = d2;
  d9 = 2.0 * d2;
  daxld_idx_2 = d9;
  d3 = Lhub - Mhub;
  psi[2] = d3;
  d4 = rt_powd_snf(cbeta[2], 2.0);
  Fpb[2] = d4;
  e_y = rt_powd_snf(zeta_dot[2], 2.0);
  Fyt[2] = e_y;
  Mhub -= Lhub;
  y_idx_2 = Mhub;
  Lhub = sbeta[2] * czeta[2];
  b_y_idx_2 = Lhub;
  d10 = d9 * Up_tmp[2];
  thetab_dot_idx_2 = d10;
  beta_ddot_tmp_idx_3 = qsdot * spsi[2];
  beta_ddot_tmp_idx_2 = beta_ddot_tmp_idx_3;
  b_beta_ddot_tmp_idx_3 = psdot * cpsi[2];
  b_beta_ddot_tmp_idx_2 = b_beta_ddot_tmp_idx_3;
  c_beta_ddot_tmp_idx_3 = (cpsiE * Mhub + zld_tmp_idx_3) + d8;
  c_beta_ddot_tmp_idx_2 = c_beta_ddot_tmp_idx_3;
  d5 = d_y - sphi;
  xld_tmp_tmp[2] = d5;
  d_y =
      ((Tbody2NED_tmp *
            ((cbeta[2] * (Vzsdot + constants->HOFFSET * c_beta_ddot_tmp_idx_3) +
              Lhub * d5) +
             Fxt[2] * (d_y - a)) +
        d4 * (czeta[2] * ((zld_tmp_idx_3 + d8) - d9 * d3) -
              szeta[2] *
                  (d10 + (beta_ddot_tmp_idx_3 - b_beta_ddot_tmp_idx_3)))) +
       cbeta[2] * sbeta[2] * ((2.0 * zeta_dot[2] * rminusO - c) - e_y)) +
      ((Mf_aero[2] + b_a) +
       (-constants->KFLAP * beta[2] - constants->CFLAP * beta_dot[2])) /
          constants->IBETA;
  beta_ddot[2] = d_y;
  zeta_ddot_tmp_idx_2 = 2.0 * beta_dot[2];
  zeta_ddot[2] = constants->IBETA * cbeta[2];
  b_zeta_ddot_tmp_idx_2 = Vxsdot * spsi[2] + Vysdot * cpsi[2];
  b_a = thetab[3] - constants->THETALDGEO;
  d2 = zeta[3] + constants->ZETA0;
  d3 = sin(d2);
  d4 = cos(d2);
  d5 = constants->BLD * d4;
  d6 = d5 + constants->DLD * d3;
  spsiE = (constants->ALD * sbeta[3] + constants->CLD) + d6 * cbeta[3];
  d4 *= constants->DLD;
  yld_tmp_idx_3 = cos(b_a);
  d7 = (-constants->RLD * yld_tmp_idx_3 - constants->BLD * d3) + d4;
  b_a = sin(b_a);
  zld_tmp_idx_3 = constants->RLD * b_a;
  d8 = (constants->ALD * cbeta[3] - zld_tmp_idx_3) - d6 * sbeta[3];
  d9 = sqrt((rt_powd_snf(spsiE, 2.0) + rt_powd_snf(d7, 2.0)) +
            rt_powd_snf(d8, 2.0));
  d3 = -constants->BLD * d3 + d4;
  yld_tmp_idx_3 *= constants->RLD;
  d6 =
      constants->CLAG *
      (((spsiE * ((constants->ALD * beta_dot[3] * cbeta[3] -
                   beta_dot[3] * sbeta[3] * d6) +
                  d3 * zeta_dot[3] * cbeta[3]) +
         d7 * (zld_tmp_idx_3 * zeta_ddot_tmp_idx_3 - (d5 + d4) * zeta_dot[3])) +
        d8 * (((-constants->ALD * sbeta[3] * beta_dot[3] -
                yld_tmp_idx_3 * zeta_ddot_tmp_idx_3) -
               cbeta[3] * beta_dot[3] * d6) +
              -d3 * zeta_dot[3] * sbeta[3])) /
       d9);
  d9 *= 12.0;
  b_a = -d6 * (d8 * constants->CLD + spsiE * b_a * constants->RLD) / d9;
  thetab[3] = b_a;
  d6 = -d6 *
           (yld_tmp_idx_3 * (spsiE * cbeta[3] - d8 * sbeta[3]) +
            d7 * (constants->CLD * cbeta[3] + zld_tmp_idx_3 * sbeta[3])) /
           d9 +
       -constants->KLAG * d2;
  Fld[3] = d6;
  yld_tmp_idx_3 = Vxsdot * d;
  d7 = Vysdot * d1;
  d_y = d7 - yld_tmp_idx_3;
  zld_tmp_idx_3 = psdot * d1;
  d8 = qsdot * d;
  Lhub = temp[1] * d1;
  Mhub = temp[0] * d;
  d2 = zeta_dot[3] + u[21];
  d9 = 2.0 * d2;
  d3 = Lhub - Mhub;
  d4 = rt_powd_snf(cbeta[3], 2.0);
  e_y = rt_powd_snf(zeta_dot[3], 2.0);
  Mhub -= Lhub;
  Lhub = sbeta[3] * czeta[3];
  d10 = d9 * Up_tmp[3];
  beta_ddot_tmp_idx_3 = qsdot * d1;
  b_beta_ddot_tmp_idx_3 = psdot * d;
  c_beta_ddot_tmp_idx_3 = (cpsiE * Mhub + zld_tmp_idx_3) + d8;
  d5 = d_y - sphi;
  d_y =
      ((Tbody2NED_tmp *
            ((cbeta[3] * (Vzsdot + constants->HOFFSET * c_beta_ddot_tmp_idx_3) +
              Lhub * d5) +
             Fxt[3] * (d_y - a)) +
        d4 * (czeta[3] * ((zld_tmp_idx_3 + d8) - d9 * d3) -
              szeta[3] *
                  (d10 + (beta_ddot_tmp_idx_3 - b_beta_ddot_tmp_idx_3)))) +
       cbeta[3] * sbeta[3] * ((2.0 * zeta_dot[3] * rminusO - c) - e_y)) +
      ((Mf_aero[3] + b_a) +
       (-constants->KFLAP * beta[3] - constants->CFLAP * beta_dot[3])) /
          constants->IBETA;
  beta_ddot[3] = d_y;
  zeta_ddot_tmp_idx_3 = 2.0 * beta_dot[3];
  zeta_ddot[3] = constants->IBETA * cbeta[3];
  cthe = Vxsdot * d1 + Vysdot * d;
  for (k = 0; k <= 38; k += 2) {
    r = _mm_loadu_pd(&Mach[k]);
    r1 = _mm_loadu_pd(&theta[k]);
    _mm_storeu_pd(&Mach[k], _mm_mul_pd(r, r1));
  }
  double xld[4];
  sum(Mach, xld);
  /* Inertial shear at each hinge */
  /* 'GHrotor:384'
   * Fxi=MBETA*(cbeta.*czeta.*(rsdotmomd-zeta_ddot)+2*sbeta.*czeta.*(zeta_dot.*beta_dot-rminusO*beta_dot)
   * + ... */
  /* 'GHrotor:385'
   * cbeta.*szeta.*(zeta_dot.^2+beta_dot.^2-2*rminusO*zeta_dot+rminusO^2) + ...
   */
  /* 'GHrotor:386'
   * 2*beta_dot.*cbeta.*(ps*cpsi-qs*spsi)+sbeta.*szeta.*beta_ddot)+ ... */
  /* 'GHrotor:387'             -WBLADE/G*(Vxsdot*spsi+Vysdot*cpsi); */
  KR = 2.0 * rminusO;
  muxs = -constants->WBLADE / constants->G;
  /* 'GHrotor:388'
   * Fyi=MBETA*(cbeta.*czeta.*(zeta_dot.^2+beta_dot.^2-2*rminusO*zeta_dot+rminusO^2)
   * + ... */
  /* 'GHrotor:389'            sbeta.*czeta.*beta_ddot+cbeta.*szeta.*zeta_ddot
   * -2*beta_dot.*cbeta.*(ps*spsi+qs*cpsi) + ... */
  /* 'GHrotor:390'            WBLADE*HOFFSET/(G*MBETA)*rminusO^2) +
   * WBLADE/G*(Vxsdot*cpsi-Vysdot*spsi); */
  mutot = constants->WBLADE / constants->G;
  /* 'GHrotor:391' Fzi=MBETA*(beta_ddot.*cbeta-(beta_dot.^2).*sbeta +
   * 2*sbeta.*czeta.*beta_dot.*(ps*spsi+qs*cpsi) + ... */
  /* 'GHrotor:392'
   * cbeta.*szeta.*(2*(OMEGA+zeta_dot).*(ps*spsi+qs*cpsi)+qsdot*spsi-psdot*cpsi)
   * + ... */
  /* 'GHrotor:393'
   * -cbeta.*czeta.*(2*(OMEGA+zeta_dot).*(ps*cpsi-qs*spsi)+psdot*spsi+qsdot*cpsi)
   * + ... */
  /* 'GHrotor:394'
   * WBLADE*HOFFSET/(G*MBETA)*((2*OMEGA*(ps*cpsi-qs*spsi)+psdot*spsi+qsdot*cpsi)))
   * - WBLADE/G*Vzsdot; */
  c_a = constants->WBLADE * constants->HOFFSET /
        (constants->G * constants->MBETA);
  /* Total shear force */
  /* 'GHrotor:397' Fxt=Fxi+Fxa; */
  /* 'GHrotor:398' Fyt=Fyi+Fya; */
  e = c_a * c;
  /* 'GHrotor:399' Fzt=Fzi+Fza; */
  a = mutot * Vzsdot;
  b_a =
      ((((constants->MBETA / zeta_ddot[0] *
              (szeta[0] * xld_tmp_tmp[0] + -czeta[0] * zeta_ddot_tmp_idx_0) +
          rsdotmomd) +
         sbeta[0] / cbeta[0] *
             ((Hforce * (LIBC2MBCdot_tmp[0] - temp[2]) + qsdot * spsizeta[0]) -
              psdot * cpsizeta[0])) +
        Hforce * (czeta[0] * psi[0] + szeta[0] * Up_tmp[0])) +
       Fld[0] / (constants->IBETA * Fpb[0])) -
      constants->R * xld[0] / zeta_ddot[0];
  zeta_ddot[0] = b_a;
  sphi = cbeta[0] * czeta[0];
  xld_tmp_tmp[0] = sphi;
  cphi = rt_powd_snf(beta_dot[0], 2.0);
  spsiE = Hforce * cbeta[0];
  cpsiE = 2.0 * sbeta[0] * czeta[0];
  Tbody2NED_tmp = ((Fyt[0] + cphi) - KR * zeta_dot[0]) + c;
  Fxt[0] =
      (constants->MBETA *
           ((((sphi * (rsdotmomd - b_a) +
               cpsiE * (zeta_dot[0] * beta_dot[0] - rminusO * beta_dot[0])) +
              Ur_tmp[0] * Tbody2NED_tmp) +
             spsiE * y_idx_0) +
            Fxt[0] * beta_ddot[0]) +
       muxs * zeta_ddot_tmp_idx_0) +
      ((Fxa_tmp[0] * szeta[0] - Ftb[0] * czeta[0]) - b_Fxa_tmp[0] * szeta[0]);
  Tbody2NED_tmp =
      (constants->MBETA * ((((sphi * Tbody2NED_tmp + b_y_idx_0 * beta_ddot[0]) +
                             Ur_tmp[0] * b_a) -
                            spsiE * Up_tmp[0]) +
                           e) +
       mutot * (yld_tmp_idx_0 - yld_idx_0)) +
      ((Fxa_tmp[0] * czeta[0] + Ftb[0] * szeta[0]) - b_Fxa_tmp[0] * czeta[0]);
  Fyt[0] = Tbody2NED_tmp;
  cbeta[0] = (constants->MBETA *
                  (((((beta_ddot[0] * cbeta[0] - cphi * sbeta[0]) +
                      cpsiE * beta_dot[0] * Up_tmp[0]) +
                     Ur_tmp[0] * ((thetab_dot_idx_0 + beta_ddot_tmp_idx_0) -
                                  b_beta_ddot_tmp_idx_0)) +
                    -cbeta[0] * czeta[0] *
                        ((daxld_idx_0 * y_idx_0 + zld_tmp_idx_0) + zld_idx_0)) +
                   c_a * c_beta_ddot_tmp_idx_0) -
              a) +
             Frb[0];
  b_a =
      ((((constants->MBETA / zeta_ddot[1] *
              (szeta[1] * xld_tmp_tmp[1] + -czeta[1] * b_zeta_ddot_tmp_idx_1) +
          rsdotmomd) +
         sbeta[1] / cbeta[1] *
             ((zeta_ddot_tmp_idx_1 * (LIBC2MBCdot_tmp[1] - temp[2]) +
               qsdot * spsizeta[1]) -
              psdot * cpsizeta[1])) +
        zeta_ddot_tmp_idx_1 * (czeta[1] * psi[1] + szeta[1] * Up_tmp[1])) +
       Fld[1] / (constants->IBETA * Fpb[1])) -
      constants->R * xld[1] / zeta_ddot[1];
  zeta_ddot[1] = b_a;
  sphi = cbeta[1] * czeta[1];
  xld_tmp_tmp[1] = sphi;
  cphi = rt_powd_snf(beta_dot[1], 2.0);
  spsiE = zeta_ddot_tmp_idx_1 * cbeta[1];
  cpsiE = 2.0 * sbeta[1] * czeta[1];
  Tbody2NED_tmp = ((Fyt[1] + cphi) - KR * zeta_dot[1]) + c;
  Fxt[1] =
      (constants->MBETA *
           ((((sphi * (rsdotmomd - b_a) +
               cpsiE * (zeta_dot[1] * beta_dot[1] - rminusO * beta_dot[1])) +
              Ur_tmp[1] * Tbody2NED_tmp) +
             spsiE * y_idx_1) +
            Fxt[1] * beta_ddot[1]) +
       muxs * b_zeta_ddot_tmp_idx_1) +
      ((Fxa_tmp[1] * szeta[1] - Ftb[1] * czeta[1]) - b_Fxa_tmp[1] * szeta[1]);
  Tbody2NED_tmp =
      (constants->MBETA * ((((sphi * Tbody2NED_tmp + b_y_idx_1 * beta_ddot[1]) +
                             Ur_tmp[1] * b_a) -
                            spsiE * Up_tmp[1]) +
                           e) +
       mutot * (yld_tmp_idx_1 - yld_idx_1)) +
      ((Fxa_tmp[1] * czeta[1] + Ftb[1] * szeta[1]) - b_Fxa_tmp[1] * czeta[1]);
  Fyt[1] = Tbody2NED_tmp;
  cbeta[1] = (constants->MBETA *
                  (((((beta_ddot[1] * cbeta[1] - cphi * sbeta[1]) +
                      cpsiE * beta_dot[1] * Up_tmp[1]) +
                     Ur_tmp[1] * ((thetab_dot_idx_1 + beta_ddot_tmp_idx_1) -
                                  b_beta_ddot_tmp_idx_1)) +
                    -cbeta[1] * czeta[1] *
                        ((daxld_idx_1 * y_idx_1 + zld_tmp_idx_1) + zld_idx_1)) +
                   c_a * c_beta_ddot_tmp_idx_1) -
              a) +
             Frb[1];
  b_a =
      ((((constants->MBETA / zeta_ddot[2] *
              (szeta[2] * xld_tmp_tmp[2] + -czeta[2] * b_zeta_ddot_tmp_idx_2) +
          rsdotmomd) +
         sbeta[2] / cbeta[2] *
             ((zeta_ddot_tmp_idx_2 * (LIBC2MBCdot_tmp[2] - temp[2]) +
               qsdot * spsizeta[2]) -
              psdot * cpsizeta[2])) +
        zeta_ddot_tmp_idx_2 * (czeta[2] * psi[2] + szeta[2] * Up_tmp[2])) +
       Fld[2] / (constants->IBETA * Fpb[2])) -
      constants->R * xld[2] / zeta_ddot[2];
  zeta_ddot[2] = b_a;
  sphi = cbeta[2] * czeta[2];
  xld_tmp_tmp[2] = sphi;
  cphi = rt_powd_snf(beta_dot[2], 2.0);
  spsiE = zeta_ddot_tmp_idx_2 * cbeta[2];
  cpsiE = 2.0 * sbeta[2] * czeta[2];
  Tbody2NED_tmp = ((Fyt[2] + cphi) - KR * zeta_dot[2]) + c;
  Fxt[2] =
      (constants->MBETA *
           ((((sphi * (rsdotmomd - b_a) +
               cpsiE * (zeta_dot[2] * beta_dot[2] - rminusO * beta_dot[2])) +
              Ur_tmp[2] * Tbody2NED_tmp) +
             spsiE * y_idx_2) +
            Fxt[2] * beta_ddot[2]) +
       muxs * b_zeta_ddot_tmp_idx_2) +
      ((Fxa_tmp[2] * szeta[2] - Ftb[2] * czeta[2]) - b_Fxa_tmp[2] * szeta[2]);
  Tbody2NED_tmp =
      (constants->MBETA * ((((sphi * Tbody2NED_tmp + b_y_idx_2 * beta_ddot[2]) +
                             Ur_tmp[2] * b_a) -
                            spsiE * Up_tmp[2]) +
                           e) +
       mutot * (yld_tmp_idx_2 - yld_idx_2)) +
      ((Fxa_tmp[2] * czeta[2] + Ftb[2] * szeta[2]) - b_Fxa_tmp[2] * czeta[2]);
  Fyt[2] = Tbody2NED_tmp;
  cbeta[2] = (constants->MBETA *
                  (((((beta_ddot[2] * cbeta[2] - cphi * sbeta[2]) +
                      cpsiE * beta_dot[2] * Up_tmp[2]) +
                     Ur_tmp[2] * ((thetab_dot_idx_2 + beta_ddot_tmp_idx_2) -
                                  b_beta_ddot_tmp_idx_2)) +
                    -cbeta[2] * czeta[2] *
                        ((daxld_idx_2 * y_idx_2 + zld_tmp_idx_2) + zld_idx_2)) +
                   c_a * c_beta_ddot_tmp_idx_2) -
              a) +
             Frb[2];
  b_a =
      ((((constants->MBETA / zeta_ddot[3] * (szeta[3] * d5 + -czeta[3] * cthe) +
          rsdotmomd) +
         sbeta[3] / cbeta[3] *
             ((zeta_ddot_tmp_idx_3 * (d2 - temp[2]) + qsdot * spsizeta[3]) -
              psdot * cpsizeta[3])) +
        zeta_ddot_tmp_idx_3 * (czeta[3] * d3 + szeta[3] * Up_tmp[3])) +
       d6 / (constants->IBETA * d4)) -
      constants->R * xld[3] / zeta_ddot[3];
  zeta_ddot[3] = b_a;
  sphi = cbeta[3] * czeta[3];
  xld_tmp_tmp[3] = sphi;
  cphi = rt_powd_snf(beta_dot[3], 2.0);
  spsiE = zeta_ddot_tmp_idx_3 * cbeta[3];
  cpsiE = 2.0 * sbeta[3] * czeta[3];
  Tbody2NED_tmp = ((e_y + cphi) - KR * zeta_dot[3]) + c;
  Fxt[3] =
      (constants->MBETA *
           ((((sphi * (rsdotmomd - b_a) +
               cpsiE * (zeta_dot[3] * beta_dot[3] - rminusO * beta_dot[3])) +
              Ur_tmp[3] * Tbody2NED_tmp) +
             spsiE * Mhub) +
            Fxt[3] * d_y) +
       muxs * cthe) +
      ((Fxa_tmp[3] * szeta[3] - Ftb[3] * czeta[3]) - b_Fxa_tmp[3] * szeta[3]);
  Tbody2NED_tmp =
      (constants->MBETA *
           ((((sphi * Tbody2NED_tmp + Lhub * d_y) + Ur_tmp[3] * b_a) -
             spsiE * Up_tmp[3]) +
            e) +
       mutot * (yld_tmp_idx_3 - d7)) +
      ((Fxa_tmp[3] * czeta[3] + Ftb[3] * szeta[3]) - b_Fxa_tmp[3] * czeta[3]);
  Fyt[3] = Tbody2NED_tmp;
  cbeta[3] = (constants->MBETA *
                  (((((d_y * cbeta[3] - cphi * sbeta[3]) +
                      cpsiE * beta_dot[3] * Up_tmp[3]) +
                     Ur_tmp[3] * ((d10 + beta_ddot_tmp_idx_3) -
                                  b_beta_ddot_tmp_idx_3)) +
                    -cbeta[3] * czeta[3] * ((d9 * Mhub + zld_tmp_idx_3) + d8)) +
                   c_a * c_beta_ddot_tmp_idx_3) -
              a) +
             Frb[3];
  /* Total rotor forces and moments */
  /* 'GHrotor:402' Thrust=-sum(Fzt); */
  zeta_ddot_tmp_idx_3 = ((cbeta[0] + cbeta[1]) + cbeta[2]) + cbeta[3];
  /* 'GHrotor:403' Hforce=sum(Fyt.*cpsi-Fxt.*spsi); */
  r = _mm_loadu_pd(&Fyt[0]);
  r1 = _mm_loadu_pd(&cpsi[0]);
  r2 = _mm_loadu_pd(&Fxt[0]);
  r3 = _mm_loadu_pd(&spsi[0]);
  _mm_storeu_pd(&Fpb[0], _mm_sub_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  r = _mm_loadu_pd(&Fyt[2]);
  r1 = _mm_loadu_pd(&cpsi[2]);
  r2 = _mm_loadu_pd(&Fxt[2]);
  r3 = _mm_loadu_pd(&spsi[2]);
  _mm_storeu_pd(&Fpb[2], _mm_sub_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  Hforce = ((Fpb[0] + Fpb[1]) + Fpb[2]) + Fpb[3];
  /* 'GHrotor:404' Jforce=-sum(Fxt.*cpsi+Fyt.*spsi); */
  r = _mm_loadu_pd(&Fxt[0]);
  r1 = _mm_loadu_pd(&cpsi[0]);
  r2 = _mm_loadu_pd(&Fyt[0]);
  r3 = _mm_loadu_pd(&spsi[0]);
  _mm_storeu_pd(&Fyt[0], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  r = _mm_loadu_pd(&Fxt[2]);
  r1 = _mm_loadu_pd(&cpsi[2]);
  r2 = _mm_loadu_pd(&Fyt[2]);
  r3 = _mm_loadu_pd(&spsi[2]);
  _mm_storeu_pd(&Fyt[2], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  d_y = ((Fyt[0] + Fyt[1]) + Fyt[2]) + Fyt[3];
  /* 'GHrotor:405' Lhub=sum(HOFFSET*Fzt.*spsi+Mf_ld.*spsizeta); */
  r = _mm_loadu_pd(&cbeta[0]);
  r18 = _mm_set1_pd(constants->HOFFSET);
  r = _mm_mul_pd(r18, r);
  _mm_storeu_pd(&cbeta[0], r);
  r1 = _mm_loadu_pd(&spsi[0]);
  r2 = _mm_loadu_pd(&thetab[0]);
  r3 = _mm_loadu_pd(&spsizeta[0]);
  _mm_storeu_pd(&Fpb[0], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  r = _mm_loadu_pd(&cbeta[2]);
  r = _mm_mul_pd(r18, r);
  _mm_storeu_pd(&cbeta[2], r);
  r1 = _mm_loadu_pd(&spsi[2]);
  r2 = _mm_loadu_pd(&thetab[2]);
  r3 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&Fpb[2], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  Lhub = ((Fpb[0] + Fpb[1]) + Fpb[2]) + Fpb[3];
  /* 'GHrotor:406' Mhub=sum(HOFFSET*Fzt.*cpsi+Mf_ld.*cpsizeta); */
  r = _mm_loadu_pd(&cbeta[0]);
  r1 = _mm_loadu_pd(&cpsi[0]);
  r2 = _mm_loadu_pd(&thetab[0]);
  r3 = _mm_loadu_pd(&cpsizeta[0]);
  _mm_storeu_pd(&cbeta[0], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  r = _mm_loadu_pd(&cbeta[2]);
  r1 = _mm_loadu_pd(&cpsi[2]);
  r2 = _mm_loadu_pd(&thetab[2]);
  r3 = _mm_loadu_pd(&cpsizeta[2]);
  _mm_storeu_pd(&cbeta[2], _mm_add_pd(_mm_mul_pd(r, r1), _mm_mul_pd(r2, r3)));
  Mhub = ((cbeta[0] + cbeta[1]) + cbeta[2]) + cbeta[3];
  /* 'GHrotor:407' Qhub=-sum(HOFFSET*Fxt-Ml_ld); */
  r = _mm_loadu_pd(&Fxt[0]);
  r1 = _mm_loadu_pd(&Fld[0]);
  _mm_storeu_pd(&Fxt[0], _mm_sub_pd(_mm_mul_pd(r18, r), r1));
  r = _mm_loadu_pd(&Fxt[2]);
  r1 = _mm_loadu_pd(&Fld[2]);
  _mm_storeu_pd(&Fxt[2], _mm_sub_pd(_mm_mul_pd(r18, r), r1));
  e_y = Fxt[0];
  /* Update with Ground Effect Model (from GENHEL) */
  /* 'GHrotor:410' temp=Tbody2NED*(constants.Tshaft')*[Xh;Yh;Zh]; */
  for (k = 0; k < 3; k++) {
    e_y += Fxt[k + 1];
    y_tmp[3 * k] = constants->Tshaft[k];
    y_tmp[3 * k + 1] = constants->Tshaft[k + 3];
    y_tmp[3 * k + 2] = constants->Tshaft[k + 6];
  }
  /* Get local position in NED frame */
  /* HAGL = -(xcg - constants.terrain.Z); */
  /* 'GHrotor:412' HAGL = -(zcg - constants.GroundZ); */
  /* 'GHrotor:413' HGEpar=max((HAGL- temp(3))/constants.R,0.1); */
  /* Non-dimensional Heigh above ground */
  /* 'GHrotor:414' if (constants.IGNDEFF==1) */
  if (constants->IGNDEFF == 1.0) {
    /* 'GHrotor:415' Kge = (1. +
     * constants.KGE1*(1/HGEpar)^2*(abs(lambda0-muzs)/sqrt(mu^2+(lambda0-muzs)^2)))^constants.KGE2;
     */
    memset(&b_Tbody2NED[0], 0, 9U * sizeof(double));
    lambda_dot[0] = Xh;
    lambda_dot[1] = Yh;
    lambda_dot[2] = Zh;
    memset(&c_Tbody2NED[0], 0, 3U * sizeof(double));
    for (k = 0; k < 3; k++) {
      spsiE = y_tmp[3 * k];
      r = _mm_loadu_pd(&Tbody2NED[0]);
      r1 = _mm_loadu_pd(&b_Tbody2NED[3 * k]);
      _mm_storeu_pd(&b_Tbody2NED[3 * k],
                    _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
      LMBC2IBCdot_tmp = 3 * k + 2;
      b_Tbody2NED[LMBC2IBCdot_tmp] += -sthe * spsiE;
      spsiE = y_tmp[3 * k + 1];
      r = _mm_loadu_pd(&Tbody2NED[3]);
      r1 = _mm_loadu_pd(&b_Tbody2NED[3 * k]);
      _mm_storeu_pd(&b_Tbody2NED[3 * k],
                    _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
      b_Tbody2NED[LMBC2IBCdot_tmp] += Tbody2NED[5] * spsiE;
      spsiE = y_tmp[LMBC2IBCdot_tmp];
      r = _mm_loadu_pd(&Tbody2NED[6]);
      r1 = _mm_loadu_pd(&b_Tbody2NED[3 * k]);
      _mm_storeu_pd(&b_Tbody2NED[3 * k],
                    _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
      b_Tbody2NED[LMBC2IBCdot_tmp] += Tbody2NED[8] * spsiE;
      r = _mm_loadu_pd(&b_Tbody2NED[3 * k]);
      r1 = _mm_loadu_pd(&c_Tbody2NED[0]);
      spsiE = lambda_dot[k];
      _mm_storeu_pd(&c_Tbody2NED[0],
                    _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
      c_Tbody2NED[2] += b_Tbody2NED[LMBC2IBCdot_tmp] * spsiE;
    }
    spsiE = 1.0 / fmax((-(u[14] - constants->GroundZ) - c_Tbody2NED[2]) /
                           constants->R,
                       0.1);
    cpsiE = x[16] - muzs;
    sphi = rt_powd_snf(constants->KGE1 * (spsiE * spsiE) *
                               (fabs(cpsiE) / sqrt(mu * mu + cpsiE * cpsiE)) +
                           1.0,
                       constants->KGE2);
  } else {
    /* 'GHrotor:416' else */
    /* 'GHrotor:417' Kge = 1.; */
    sphi = 1.0;
  }
  /*  Mean qs inflow computed by function QSInflowComp */
  /* 'GHrotor:421' [lambda0_qs,NoConverge] = QSInflowComp(CTa,muzs,mu,Kge); */
  Tbody2NED_tmp = QSInflowComp(CTa, muzs, mu, sphi, &spsiE);
  /* 'GHrotor:422' if NoConverge */
  if (spsiE != 0.0) {
    /* 'GHrotor:423' fprintf("Warning Rotor Inflow Iteration Not
     * Converging!\n"); */
    printf("Warning Rotor Inflow Iteration Not Converging!\n");
    fflush(stdout);
  }
  /* Inflow Dynamics */
  /* Pitt-Peters Model */
  /* Based on model developed in: */
  /* Pitt, D.M. and Peters, D.A., Theoretical Predicition of Dynamic Inflow
   * Derivatives, Vertica, Vol. 5, No 1, 1981. */
  /* Pitt-Peters with quasi-steady wake curvature effects.  Based on Zhao 2004
   */
  /*  Solve equations in shaft axes instead of wind axes.  Then */
  /*  transform the L matrix. (Method of Peters and HaQuang) */
  /*  Angle of attack and mass flow parameters */
  /* 'GHrotor:436' mutot=sqrt(mu^2+(muzs-lambda0_qs)^2); */
  spsiE = muzs - Tbody2NED_tmp;
  cpsiE = mu * mu;
  mutot = sqrt(cpsiE + spsiE * spsiE);
  /* 'GHrotor:437' Vmpp=(mu^2+(lambda0_qs-muzs)*(2*lambda0_qs-muzs))/mutot; */
  c_a = Tbody2NED_tmp - muzs;
  e = (cpsiE + c_a * (2.0 * Tbody2NED_tmp - muzs)) / mutot;
  /* 'GHrotor:438' Vpp=diag([mutot Vmpp Vmpp]); */
  /* Wind to shaft transformation */
  /* 'GHrotor:441' Ts2w=[1 0 0;0 cbetawind sbetawind;0 -sbetawind cbetawind]; */
  Ts2w[0] = 1.0;
  Ts2w[3] = 0.0;
  Ts2w[6] = 0.0;
  Ts2w[1] = 0.0;
  Ts2w[4] = cbetawind;
  Ts2w[7] = sbetawind;
  Ts2w[2] = 0.0;
  Ts2w[5] = -sbetawind;
  Ts2w[8] = cbetawind;
  /* 'GHrotor:442' Tw2s=Ts2w'; */
  /* 'GHrotor:443' beta1c_dot=x(NB+3); */
  /* 'GHrotor:444' beta1s_dot=x(NB+4); */
  /* 'GHrotor:445' beta0_dot=x(NB+1); */
  /* 'GHrotor:446' betastar=[beta0_dot;beta1s_dot;beta1c_dot]/constants.OMEGAT;
   */
  /* 'GHrotor:447' omegastar= [rs;ps;qs]/constants.OMEGAT; */
  cphi = temp[0] / constants->OMEGAT;
  cthe = temp[1] / constants->OMEGAT;
  /* 'GHrotor:449' Xpp=x(4*NB+6); */
  /* 'GHrotor:450' kcpp=x(4*NB+7); */
  /* 'GHrotor:451' kspp=x(4*NB+8); */
  /*  This is the wind-axis L matrix in wind axis */
  /* 'GHrotor:454' Lpp_w=[0.5                   0.            -15*pi/64*Xpp; ...
   */
  /* 'GHrotor:455'          0.0               2*(1+Xpp^2)         0; ... */
  /* 'GHrotor:456'         15*pi/64*Xpp       0.            2*(1-Xpp^2)]; */
  /* Transform to shaft axes */
  /* 'GHrotor:458' Lpp=Tw2s*Lpp_w*Ts2w; */
  /* Use constant value of constants.KR>=0, otherwise use airspeed schedule */
  /* 'GHrotor:461' if (constants.KR>=0.) */
  if (constants->KR >= 0.0) {
    /* 'GHrotor:462' KR=constants.KR; */
    KR = constants->KR;
  } else {
    /* 'GHrotor:463' else */
    /* 'GHrotor:464'
     * KR=interp1(constants.KRVsched,constants.KRsched,min(Veq,constants.KRVsched(end)));
     */
    KR = c_interp1(constants->KRVsched, constants->KRsched,
                   fmin(Veq, constants->KRVsched[3]));
  }
  /* Curvature and skew effects on L matrix */
  /* 'GHrotor:468' delL1=zeros(3); */
  memset(&delL3[0], 0, 9U * sizeof(double));
  memset(&delL1[0], 0, 9U * sizeof(double));
  /* 'GHrotor:469' delL1(2,1)=0.5*KR*kspp; */
  spsiE = 0.5 * KR;
  cpsiE = spsiE * x[23];
  delL1[1] = cpsiE;
  /* 'GHrotor:470' delL1(3,1)=0.5*KR*kcpp; */
  spsiE *= x[22];
  delL1[2] = spsiE;
  /* 'GHrotor:471' delL1(1,2)=0.5*KR*kspp; */
  delL1[3] = cpsiE;
  /* 'GHrotor:472' delL1(1,3)=0.5*KR*kcpp; */
  delL1[6] = spsiE;
  /* 'GHrotor:474' delL2=zeros(3); */
  memset(&delL2[0], 0, 9U * sizeof(double));
  /* 'GHrotor:475' delL2(2,1)=0.75*KR*kspp*Xpp^2; */
  spsiE = x[21] * x[21];
  delL2[1] = 0.75 * KR * x[23] * spsiE;
  /* 'GHrotor:475' delL2(3,1)=-0.75*KR*kcpp*Xpp^2; */
  delL2[2] = -0.75 * KR * x[22] * spsiE;
  /* 'GHrotor:477' delL3=zeros(3); */
  /* 'GHrotor:478' delL3(2,1)=1.25*mu*kcpp*Xpp*KR; */
  cpsiE = 1.25 * mu;
  delL3[1] = cpsiE * x[22] * x[21] * KR;
  /* 'GHrotor:479' delL3(2,2)=(-2.5*kcpp*Xpp-1.5*mu*kspp*(1.+1.5*Xpp^2))*KR; */
  Tbody2NED_tmp = 1.5 * mu;
  a = 1.5 * spsiE;
  delL3[4] = (-2.5 * x[22] * x[21] - Tbody2NED_tmp * x[23] * (a + 1.0)) * KR;
  /* 'GHrotor:480' delL3(2,3)=-2.5*kspp*Xpp*KR; */
  b_a = -2.5 * x[23] * x[21];
  delL3[7] = b_a * KR;
  /* 'GHrotor:481' delL3(3,1)=1.25*mu*kspp*Xpp*KR; */
  delL3[2] = cpsiE * x[23] * x[21] * KR;
  /* 'GHrotor:482' delL3(3,2)=(-2.5*kspp*Xpp-1.5*mu*kcpp*(1.-1.5*Xpp^2))*KR; */
  delL3[5] = (b_a - Tbody2NED_tmp * x[22] * (1.0 - a)) * KR;
  /* 'GHrotor:483' delL3(3,3)=-0.3*kcpp*Xpp*KR; */
  delL3[8] = -0.3 * x[22] * x[21] * KR;
  /*  Inflow dynamics in shaft axes */
  /*  PP inflow coefficients */
  /* 'GHrotor:487' lambda_dot=OMEGA*diag([(75.*pi)/128. (45.*pi)/16.
   * (45.*pi)/16.])*([Kge*CTa;-CLa;-CMa]-Vpp/(Lpp+delL1+delL2+delL3)*[lambda0;lambda1s;lambda1c]);
   */
  temp[0] = mutot;
  temp[1] = e;
  temp[2] = e;
  b_Tbody2NED[0] = 0.5;
  b_Tbody2NED[3] = 0.0;
  b_Tbody2NED[6] = -0.7363107781851077 * x[21];
  b_Tbody2NED[1] = 0.0;
  b_Tbody2NED[4] = 2.0 * (spsiE + 1.0);
  b_Tbody2NED[7] = 0.0;
  b_Tbody2NED[2] = 0.7363107781851077 * x[21];
  b_Tbody2NED[5] = 0.0;
  b_Tbody2NED[8] = 2.0 * (1.0 - spsiE);
  for (k = 0; k < 3; k++) {
    spsiE = b_Tbody2NED[3 * k];
    cpsiE = b_Tbody2NED[3 * k + 1];
    Tbody2NED_tmp = b_Tbody2NED[3 * k + 2];
    for (i = 0; i < 3; i++) {
      b_Ts2w[i + 3 * k] = (Ts2w[3 * i] * spsiE + Ts2w[3 * i + 1] * cpsiE) +
                          Ts2w[3 * i + 2] * Tbody2NED_tmp;
    }
  }
  for (k = 0; k < 3; k++) {
    spsiE = b_Ts2w[k];
    cpsiE = b_Ts2w[k + 3];
    Tbody2NED_tmp = b_Ts2w[k + 6];
    for (i = 0; i < 3; i++) {
      LMBC2IBCdot_tmp = k + 3 * i;
      b_Tbody2NED[LMBC2IBCdot_tmp] =
          ((((spsiE * Ts2w[3 * i] + cpsiE * Ts2w[3 * i + 1]) +
             Tbody2NED_tmp * Ts2w[3 * i + 2]) +
            delL1[LMBC2IBCdot_tmp]) +
           delL2[LMBC2IBCdot_tmp]) +
          delL3[LMBC2IBCdot_tmp];
    }
  }
  diag(temp, delL3);
  mrdiv(delL3, b_Tbody2NED, Ts2w);
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Ts2w[0]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[16]))));
  temp[2] += Ts2w[2] * x[16];
  r = _mm_loadu_pd(&Ts2w[3]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[17]))));
  temp[2] += Ts2w[5] * x[17];
  r = _mm_loadu_pd(&Ts2w[6]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[18]))));
  temp[2] += Ts2w[8] * x[18];
  r = _mm_loadu_pd(&Mf_aero[0]);
  r1 = _mm_loadu_pd(&spsizeta[0]);
  _mm_storeu_pd(&spsizeta[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&Mf_aero[2]);
  r1 = _mm_loadu_pd(&spsizeta[2]);
  _mm_storeu_pd(&spsizeta[2], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&Mf_aero[0]);
  r1 = _mm_loadu_pd(&cpsizeta[0]);
  _mm_storeu_pd(&Mf_aero[0], _mm_mul_pd(r, r1));
  r = _mm_loadu_pd(&Mf_aero[2]);
  r1 = _mm_loadu_pd(&cpsizeta[2]);
  _mm_storeu_pd(&Mf_aero[2], _mm_mul_pd(r, r1));
  c_Tbody2NED[0] = sphi * CTa - temp[0];
  spsiE = CTa_tmp * rt_powd_snf(constants->R, 5.0);
  c_Tbody2NED[1] =
      -(-(((spsizeta[0] + spsizeta[1]) + spsizeta[2]) + spsizeta[3]) / spsiE) -
      temp[1];
  c_Tbody2NED[2] =
      -(-(((Mf_aero[0] + Mf_aero[1]) + Mf_aero[2]) + Mf_aero[3]) / spsiE) -
      temp[2];
  memset(&lambda_dot[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&lambda_dot[0]);
  r1 = _mm_set1_pd(u[21]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_mul_pd(r1, _mm_loadu_pd(&b[0])),
                                         _mm_set1_pd(c_Tbody2NED[0]))));
  spsiE = u[21] * 0.0;
  lambda_dot[2] += spsiE * c_Tbody2NED[0];
  r = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_mul_pd(r1, _mm_loadu_pd(&b[3])),
                                         _mm_set1_pd(c_Tbody2NED[1]))));
  lambda_dot[2] += spsiE * c_Tbody2NED[1];
  r = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r, _mm_mul_pd(_mm_mul_pd(r1, _mm_loadu_pd(&b[6])),
                                         _mm_set1_pd(c_Tbody2NED[2]))));
  lambda_dot[2] += u[21] * 8.835729338221293 * c_Tbody2NED[2];
  /* Will need to limit the denominator here to be positive */
  /* 'GHrotor:490' kcqs=(omegastar(3)-betastar(3))/max((lambda0_qs-muzs),0.001);
   */
  b_a = fmax(c_a, 0.001);
  /* 'GHrotor:491' ksqs=(omegastar(2)-betastar(2))/max((lambda0_qs-muzs),0.001);
   */
  /* 'GHrotor:492' chi=atan2(mu,(lambda0_qs-muzs)); */
  /* 'GHrotor:493' Xqs=tan(0.5*chi); */
  /* 'GHrotor:494' Xpp_dot=constants.OMEGAT*(15.*pi*Vmpp)/32.*(Xqs-Xpp); */
  /* 'GHrotor:495' kcpp_dot=constants.OMEGAT*(15.*pi*mutot)/32.*(kcqs-kcpp); */
  /* 'GHrotor:496' kspp_dot=constants.OMEGAT*(15.*pi*mutot)/32.*(ksqs-kspp); */
  /* Build xdot vector */
  /* 'GHrotor:499' xdot=zeros(SizeConstants.NRSTATES,1); */
  /* 'GHrotor:500' xdot(1:NB)=LIBC2MBC*beta_dot+LIBC2MBCdot*beta; */
  memset(&Frb[0], 0, sizeof(double) << 2);
  memset(&Ftb[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Frb[0]);
    r2 = _mm_set1_pd(beta_dot[k]);
    _mm_storeu_pd(&Frb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Ftb[0]);
    r3 = _mm_set1_pd(beta[k]);
    _mm_storeu_pd(&Ftb[0], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Frb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Ftb[2]);
    _mm_storeu_pd(&Ftb[2], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
  }
  r = _mm_loadu_pd(&Frb[0]);
  r1 = _mm_loadu_pd(&Ftb[0]);
  _mm_storeu_pd(&xdot[0], _mm_add_pd(r, r1));
  r = _mm_loadu_pd(&Frb[2]);
  r1 = _mm_loadu_pd(&Ftb[2]);
  _mm_storeu_pd(&xdot[2], _mm_add_pd(r, r1));
  /* 'GHrotor:501'
   * xdot(NB+1:2*NB)=LIBC2MBC*beta_ddot+2*LIBC2MBCdot*beta_dot+LIBC2MBCddot*beta;
   */
  for (k = 0; k <= 14; k += 2) {
    r = _mm_loadu_pd(&LMBC2IBCdot[k]);
    _mm_storeu_pd(&xdot_tmp[k], _mm_mul_pd(_mm_set1_pd(2.0), r));
  }
  memset(&Frb[0], 0, sizeof(double) << 2);
  memset(&Mf_aero[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Frb[0]);
    r2 = _mm_set1_pd(beta_ddot[k]);
    _mm_storeu_pd(&Frb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&xdot_tmp[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Mf_aero[0]);
    r3 = _mm_set1_pd(beta_dot[k]);
    _mm_storeu_pd(&Mf_aero[0], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Frb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&xdot_tmp[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Mf_aero[2]);
    _mm_storeu_pd(&Mf_aero[2], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
  }
  spsiE = beta[0];
  cpsiE = beta[1];
  Tbody2NED_tmp = beta[2];
  a = beta[3];
  for (k = 0; k <= 2; k += 2) {
    r = _mm_loadu_pd(&Frb[k]);
    r1 = _mm_loadu_pd(&Mf_aero[k]);
    r2 = _mm_add_pd(r, r1);
    r = _mm_loadu_pd(&LIBC2MBCddot[k]);
    r1 = _mm_mul_pd(r, _mm_set1_pd(spsiE));
    r = _mm_loadu_pd(&LIBC2MBCddot[k + 4]);
    r = _mm_mul_pd(r, _mm_set1_pd(cpsiE));
    r1 = _mm_add_pd(r1, r);
    r = _mm_loadu_pd(&LIBC2MBCddot[k + 8]);
    r = _mm_mul_pd(r, _mm_set1_pd(Tbody2NED_tmp));
    r1 = _mm_add_pd(r1, r);
    r = _mm_loadu_pd(&LIBC2MBCddot[k + 12]);
    r = _mm_mul_pd(r, _mm_set1_pd(a));
    r = _mm_add_pd(r1, r);
    r = _mm_add_pd(r2, r);
    _mm_storeu_pd(&xdot[k + 4], r);
  }
  /* 'GHrotor:502' xdot(2*NB+1:3*NB)=LIBC2MBC*zeta_dot+LIBC2MBCdot*zeta; */
  memset(&Frb[0], 0, sizeof(double) << 2);
  memset(&Ftb[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Frb[0]);
    r2 = _mm_set1_pd(zeta_dot[k]);
    _mm_storeu_pd(&Frb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Ftb[0]);
    r3 = _mm_set1_pd(zeta[k]);
    _mm_storeu_pd(&Ftb[0], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Frb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&LMBC2IBCdot[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Ftb[2]);
    _mm_storeu_pd(&Ftb[2], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
  }
  r = _mm_loadu_pd(&Frb[0]);
  r1 = _mm_loadu_pd(&Ftb[0]);
  _mm_storeu_pd(&xdot[8], _mm_add_pd(r, r1));
  r = _mm_loadu_pd(&Frb[2]);
  r1 = _mm_loadu_pd(&Ftb[2]);
  _mm_storeu_pd(&xdot[10], _mm_add_pd(r, r1));
  /* 'GHrotor:503'
   * xdot(3*NB+1:4*NB)=LIBC2MBC*zeta_ddot+2*LIBC2MBCdot*zeta_dot+LIBC2MBCddot*zeta;
   */
  memset(&Frb[0], 0, sizeof(double) << 2);
  memset(&Mf_aero[0], 0, sizeof(double) << 2);
  for (k = 0; k < 4; k++) {
    LMBC2IBCdot_tmp = k << 2;
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Frb[0]);
    r2 = _mm_set1_pd(zeta_ddot[k]);
    _mm_storeu_pd(&Frb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&xdot_tmp[LMBC2IBCdot_tmp]);
    r1 = _mm_loadu_pd(&Mf_aero[0]);
    r3 = _mm_set1_pd(zeta_dot[k]);
    _mm_storeu_pd(&Mf_aero[0], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
    r = _mm_loadu_pd(&LMBC2IBC[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Frb[2]);
    _mm_storeu_pd(&Frb[2], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
    r = _mm_loadu_pd(&xdot_tmp[LMBC2IBCdot_tmp + 2]);
    r1 = _mm_loadu_pd(&Mf_aero[2]);
    _mm_storeu_pd(&Mf_aero[2], _mm_add_pd(r1, _mm_mul_pd(r, r3)));
  }
  /* 'GHrotor:504' xdot(4*NB+1:4*NB+3)=lambda_dot; */
  xdot[16] = lambda_dot[0];
  xdot[17] = lambda_dot[1];
  xdot[18] = lambda_dot[2];
  /* 'GHrotor:505' xdot(4*NB+4)=OMEGA; */
  xdot[19] = u[21];
  /* Added state for filtered dynamic twist force */
  /* 'GHrotor:507' xdot(4*NB+5)=(1./constants.TauDT)*(Fp_DT-x(4*NB+5)); */
  r = _mm_loadu_pd(&b_y[0]);
  r1 = _mm_loadu_pd(&c_y[0]);
  _mm_storeu_pd(&b_y[0], _mm_sqrt_pd(_mm_add_pd(r, r1)));
  r = _mm_loadu_pd(&b_y[2]);
  r1 = _mm_loadu_pd(&c_y[2]);
  _mm_storeu_pd(&b_y[2], _mm_sqrt_pd(_mm_add_pd(r, r1)));
  xdot[20] = 1.0 / constants->TauDT *
             ((((b_y[0] + b_y[1]) + b_y[2]) + b_y[3]) / constants->NB - x[20]);
  /* 'GHrotor:509' xdot(4*NB+6)=Xpp_dot; */
  xdot[21] = constants->OMEGAT * (47.12388980384689 * e) / 32.0 *
             (tan(0.5 * b_atan2(mu, c_a)) - x[21]);
  /* 'GHrotor:510' xdot(4*NB+7)=kcpp_dot; */
  spsiE = constants->OMEGAT * (47.12388980384689 * mutot) / 32.0;
  xdot[22] = spsiE * ((cthe - x[6] / constants->OMEGAT) / b_a - x[22]);
  /* 'GHrotor:511' xdot(4*NB+8)=kspp_dot; */
  xdot[23] = spsiE * ((cphi - x[7] / constants->OMEGAT) / b_a - x[23]);
  /* Rotor forces and moments in body frame at aircraft CG */
  /* 'GHrotor:514' Fmrb=constants.Tshaft'*[-Hforce;-Jforce;-Thrust]; */
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&y_tmp[0]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(-Hforce))));
  temp[2] += -Hforce * y_tmp[2];
  r = _mm_loadu_pd(&y_tmp[3]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(d_y))));
  temp[2] += d_y * y_tmp[5];
  r = _mm_loadu_pd(&y_tmp[6]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(
      &temp[0],
      _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(zeta_ddot_tmp_idx_3))));
  temp[2] += zeta_ddot_tmp_idx_3 * y_tmp[8];
  /* 'GHrotor:515' Mmrb=constants.Tshaft'*[Lhub;Mhub;Qhub]+[0 -Zh Yh;Zh 0
   * -Xh;-Yh Xh 0]*Fmrb; */
  /* Blade Segment Locations in shaft coordinates */
  /* 'GHrotor:518'
   * xsegs=(cbeta.*szeta.*spsi-cbeta.*czeta.*cpsi)*rseg*R+HOFFSET*cpsi*ones(1,NSEG);
   */
  /* 'GHrotor:519'
   * ysegs=(cbeta.*szeta.*cpsi+cbeta.*czeta.*spsi)*rseg*R+HOFFSET*spsi*ones(1,NSEG);
   */
  /* 'GHrotor:520' zsegs=-sbeta*rseg*R; */
  /* Transform to body coordinates */
  /* 'GHrotor:522'
   * psegb=constants.Tshaft'*[reshape(xsegs',NSEG*NB,1)'+Xh;reshape(ysegs',NSEG*NB,1)'+Yh;reshape(zsegs',NSEG*NB,1)'+Zh];
   */
  /* Transform to NED */
  /* 'GHrotor:524' psegNED=Tbody2NED*psegb+[xcg;ycg;zcg]*ones(1,NSEG*NB); */
  /* Blade Segment Locations in shaft coordinates */
  /* segloadxs=(spsizeta*ones(1,NSEG)).*(-Ft) -
   * ((cbeta.*cpsizeta)*ones(1,NSEG)).*(Fr) -
   * ((sbeta.*cpsizeta)*ones(1,NSEG)).*(-Fp); */
  /* segloadys=(cpsizeta*ones(1,NSEG)).*(-Ft) +
   * ((spsizeta.*cbeta)*ones(1,NSEG)).*(Fr) +
   * ((spsizeta.*sbeta)*ones(1,NSEG)).*(-Fp); */
  /* segloadzs=(-sbeta*ones(1,NSEG)).*(Fr)+(cbeta*ones(1,NSEG)).*(-Fp); */
  /* Transform to body coordinates */
  /* segloadb=constants.Tshaft'*[reshape(segloadxs',NSEG*NB,1)';reshape(segloadys',NSEG*NB,1)';reshape(segloadzs',NSEG*NB,1)'];
   */
  /* Transform to NED */
  /* segloadNED=Tbody2NED*segloadb; */
  /*  Segment positions out */
  /* 'GHrotor:536' CFDdataOut=reshape(psegNED,3*NSEG*NB,1); */
  /* Main Rotor horsepower */
  /* HPROTOR = Qhub*OMEGA*FtLb_s2Hp; % [hp] %not coded for non-100%Nr */
  /* OUTPUTS */
  /* 'GHrotor:542'
   * y=[Fmrb;Mmrb;Thrust;Hforce;Jforce;Lhub;Mhub;Qhub;rsdot;CFDdataOut]; */
  delL3[0] = 0.0;
  delL3[3] = -Zh;
  delL3[6] = Yh;
  delL3[1] = Zh;
  delL3[4] = 0.0;
  delL3[7] = -Xh;
  delL3[2] = -Yh;
  delL3[5] = Xh;
  delL3[8] = 0.0;
  memset(&c_Tbody2NED[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&y_tmp[0]);
  r1 = _mm_loadu_pd(&c_Tbody2NED[0]);
  _mm_storeu_pd(&c_Tbody2NED[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Lhub))));
  c_Tbody2NED[2] += Lhub * y_tmp[2];
  r = _mm_loadu_pd(&y_tmp[3]);
  r1 = _mm_loadu_pd(&c_Tbody2NED[0]);
  _mm_storeu_pd(&c_Tbody2NED[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Mhub))));
  c_Tbody2NED[2] += Mhub * y_tmp[5];
  r = _mm_loadu_pd(&y_tmp[6]);
  r1 = _mm_loadu_pd(&c_Tbody2NED[0]);
  _mm_storeu_pd(&c_Tbody2NED[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(-e_y))));
  c_Tbody2NED[2] += -e_y * y_tmp[8];
  memset(&lambda_dot[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&delL3[0]);
  r1 = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(temp[0]))));
  lambda_dot[2] += temp[0] * -Yh;
  r = _mm_loadu_pd(&delL3[3]);
  r1 = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(temp[1]))));
  lambda_dot[2] += temp[1] * Xh;
  r = _mm_loadu_pd(&delL3[6]);
  r1 = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&lambda_dot[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(temp[2]))));
  lambda_dot[2] += 0.0 * temp[2];
  for (k = 0; k < 4; k++) {
    xdot[k + 12] =
        (Frb[k] + Mf_aero[k]) +
        (((LIBC2MBCddot[k] * zeta[0] + LIBC2MBCddot[k + 4] * zeta[1]) +
          LIBC2MBCddot[k + 8] * zeta[2]) +
         LIBC2MBCddot[k + 12] * zeta[3]);
    spsiE = Ur_tmp[k];
    a = spsi[k];
    cpsiE = xld_tmp_tmp[k];
    b_a = cpsi[k];
    KR = spsiE * a - cpsiE * b_a;
    spsiE = spsiE * b_a + cpsiE * a;
    Ur_tmp[k] = spsiE;
    cpsiE = sbeta[k];
    Tbody2NED_tmp = -cpsiE;
    cpsiE = -cpsiE;
    sbeta[k] = cpsiE;
    for (i = 0; i <= 8; i += 2) {
      r = _mm_loadu_pd(&constants->RSEG[i]);
      LMBC2IBCdot_tmp = i + 10 * k;
      _mm_storeu_pd(&Mach[LMBC2IBCdot_tmp],
                    _mm_add_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(KR), r), r4),
                               _mm_set1_pd(constants->HOFFSET * b_a)));
      _mm_storeu_pd(
          &theta[LMBC2IBCdot_tmp],
          _mm_add_pd(_mm_mul_pd(_mm_mul_pd(_mm_set1_pd(spsiE), r), r4),
                     _mm_set1_pd(constants->HOFFSET * a)));
      _mm_storeu_pd(&b_Fpb[LMBC2IBCdot_tmp],
                    _mm_mul_pd(_mm_set1_pd(Tbody2NED_tmp),
                               _mm_loadu_pd(&constants->RSEG[i])));
    }
  }
  memset(&b_y_tmp[0], 0, 120U * sizeof(double));
  muxs = u[12];
  sphi = u[13];
  a = u[14];
  memset(&d_Tbody2NED[0], 0, 120U * sizeof(double));
  for (k = 0; k < 40; k++) {
    int i1;
    spsiE = b_Fpb[k] * constants->R;
    b_Fpb[k] = spsiE;
    cpsiE = Mach[k] + Xh;
    Tbody2NED_tmp = theta[k] + Yh;
    LMBC2IBCdot_tmp = 3 * k + 2;
    spsiE += Zh;
    r = _mm_loadu_pd(&y_tmp[0]);
    r1 = _mm_loadu_pd(&b_y_tmp[3 * k]);
    _mm_storeu_pd(&b_y_tmp[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(cpsiE))));
    b_y_tmp[LMBC2IBCdot_tmp] += y_tmp[2] * cpsiE;
    i1 = 3 * k + 1;
    r = _mm_loadu_pd(&y_tmp[3]);
    r1 = _mm_loadu_pd(&b_y_tmp[3 * k]);
    _mm_storeu_pd(&b_y_tmp[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(Tbody2NED_tmp))));
    b_y_tmp[LMBC2IBCdot_tmp] += y_tmp[5] * Tbody2NED_tmp;
    r = _mm_loadu_pd(&y_tmp[6]);
    r1 = _mm_loadu_pd(&b_y_tmp[3 * k]);
    _mm_storeu_pd(&b_y_tmp[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
    b_y_tmp[LMBC2IBCdot_tmp] += y_tmp[8] * spsiE;
    spsiE = b_y_tmp[3 * k];
    r = _mm_loadu_pd(&Tbody2NED[0]);
    r1 = _mm_loadu_pd(&d_Tbody2NED[3 * k]);
    _mm_storeu_pd(&d_Tbody2NED[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
    d_Tbody2NED[LMBC2IBCdot_tmp] += -sthe * spsiE;
    b_Ur_tmp[3 * k] = muxs;
    spsiE = b_y_tmp[i1];
    r = _mm_loadu_pd(&Tbody2NED[3]);
    r1 = _mm_loadu_pd(&d_Tbody2NED[3 * k]);
    _mm_storeu_pd(&d_Tbody2NED[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
    d_Tbody2NED[LMBC2IBCdot_tmp] += Tbody2NED[5] * spsiE;
    b_Ur_tmp[i1] = sphi;
    spsiE = b_y_tmp[LMBC2IBCdot_tmp];
    r = _mm_loadu_pd(&Tbody2NED[6]);
    r1 = _mm_loadu_pd(&d_Tbody2NED[3 * k]);
    _mm_storeu_pd(&d_Tbody2NED[3 * k],
                  _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsiE))));
    d_Tbody2NED[LMBC2IBCdot_tmp] += Tbody2NED[8] * spsiE;
    b_Ur_tmp[LMBC2IBCdot_tmp] = a;
  }
  for (k = 0; k <= 118; k += 2) {
    r = _mm_loadu_pd(&d_Tbody2NED[k]);
    r1 = _mm_loadu_pd(&b_Ur_tmp[k]);
    _mm_storeu_pd(&d_Tbody2NED[k], _mm_add_pd(r, r1));
  }
  r = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&y[0], r);
  r = _mm_loadu_pd(&c_Tbody2NED[0]);
  r1 = _mm_loadu_pd(&lambda_dot[0]);
  _mm_storeu_pd(&y[3], _mm_add_pd(r, r1));
  y[2] = temp[2];
  y[5] = c_Tbody2NED[2] + lambda_dot[2];
  y[6] = -zeta_ddot_tmp_idx_3;
  y[7] = Hforce;
  y[8] = -d_y;
  y[9] = Lhub;
  y[10] = Mhub;
  y[11] = -e_y;
  y[12] = rsdot;
  memcpy(&y[13], &d_Tbody2NED[0], 120U * sizeof(double));
}

/* End of code generation (GHrotor.c) */
