/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tailrotor.c
 *
 * Code generation for function 'tailrotor'
 *
 */

/* Include files */
#include "tailrotor.h"
#include "H60Sim_rtwutil.h"
#include "H60Sim_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * function [xtr_dot,Ftr,Mtr,Qtr,ptrNED] =
 * tailrotor(xtr,xf,controls,Vext,rotor_if,omega,atmos,constants)
 */
double tailrotor(double xtr, const double xf[12], const double controls[4],
                 const double rotor_if[8], double omega, double atmos_rho,
                 const constants_Struct *constants, double Ftr[3],
                 double Mtr[3], double *Qtr, double ptrNED[3])
{
  __m128d r;
  __m128d r1;
  __m128d r2;
  double Ftr_tmp[9];
  double TNED2body[9];
  double Tcant[9];
  double Vextb[3];
  double B10;
  double B2;
  double B3;
  double B4;
  double B5;
  double B6;
  double B7;
  double B8;
  double B9;
  double BT31;
  double BT32;
  double BT33;
  double GTR;
  double OMGRAT;
  double S1;
  double S2;
  double S3;
  double S5;
  double S6;
  double S7;
  double THT1TR;
  double VKT;
  double XMU2;
  double XTR;
  double YTR;
  double ZTR;
  double a_tmp;
  double cgam;
  double cphi;
  double cpsi;
  double cthe;
  double sphi;
  double sthe;
  double xtr_dot;
  double ytail;
  int i;
  int iter;
  /* Tail rotor model */
  /* implemented w/o time delay */
  /* map to local variables */
  /* R2D = constants.R2D; */
  /* 'tailrotor:8' D2R = constants.D2R; */
  /* FtLb_s2Hp = constants.FtLb_s2Hp; */
  /* 'tailrotor:10' fps2kts = constants.fps2kts; */
  /* 'tailrotor:12' u=xf(1); */
  /* v=xf(2); */
  /* 'tailrotor:14' w=xf(3); */
  /* 'tailrotor:15' VKT = sqrt(u^2 + w^2)*fps2kts; */
  VKT = sqrt(xf[0] * xf[0] + xf[2] * xf[2]) * constants->fps2kts;
  /* 'tailrotor:17' FSCGB = constants.FSCGB; */
  /* 'tailrotor:18' WLCGB = constants.WLCGB; */
  /* 'tailrotor:19' BLCGB = constants.BLCGB; */
  /* 'tailrotor:20' OMEGTR = constants.OmegaTR; */
  /* 'tailrotor:21' OMGRAT = omega/constants.OMEGAT; */
  OMGRAT = omega / constants->OMEGAT;
  /* 'tailrotor:23' RHO = atmos.rho; */
  /* 'tailrotor:25' FSTR = constants.FSTR; */
  /* 'tailrotor:26' WLTR = constants.WLTR; */
  /* 'tailrotor:27' BLTR = constants.BLTR; */
  /* 'tailrotor:29' ATR = constants.a0TR; */
  /* 'tailrotor:30' BLDSTR = constants.NB; */
  /* 'tailrotor:31' CHRDTR = constants.CHRDTR; */
  /* 'tailrotor:32' CDTR = constants.CDTR; */
  /* 'tailrotor:34' RTR = constants.RTR; */
  /* 'tailrotor:35' BTLTR = constants.BTLTR; */
  /* 'tailrotor:36' TWSTTR = constants.twistTR/D2R; */
  /* 'tailrotor:38' THETTRC = controls(4); */
  /* 'tailrotor:40' C12TR = 0.5; */
  /* 'tailrotor:41' C13TR = 0.333333333; */
  /* 'tailrotor:42' C14TR = 0.25; */
  /* 'tailrotor:43' C15TR = 0.2; */
  /* 'tailrotor:44' C16TR = 0.166666666; */
  /* 'tailrotor:45' C23TR = 0.666666666; */
  /* 'tailrotor:46' C25TR = 0.4; */
  /* 'tailrotor:47' C43TR = 1.333333333; */
  /* 'tailrotor:48' C54TR = 1.25; */
  /* 'tailrotor:49' C58TR = 0.625; */
  /* 'tailrotor:50' C83TR = 2.666666666; */
  /* 'tailrotor:51' C89TR = 0.888888888; */
  /* Dynamic inflow constant */
  /* 'tailrotor:54' XKINF = 4.0/(3.0*pi); */
  /* Angular rate inputs */
  /* 'tailrotor:57' PB=xf(4); */
  /* 'tailrotor:58' QB=xf(5); */
  /* 'tailrotor:59' RB=xf(6); */
  /* Euler angles */
  /* 'tailrotor:62' sphi=sin(xf(7)); */
  sphi = sin(xf[6]);
  /* 'tailrotor:63' cphi=cos(xf(7)); */
  cphi = cos(xf[6]);
  /* 'tailrotor:64' sthe=sin(xf(8)); */
  sthe = sin(xf[7]);
  /* 'tailrotor:65' cthe=cos(xf(8)); */
  cthe = cos(xf[7]);
  /* 'tailrotor:66' spsi=sin(xf(9)); */
  xtr_dot = sin(xf[8]);
  /* 'tailrotor:67' cpsi=cos(xf(9)); */
  cpsi = cos(xf[8]);
  /* 'tailrotor:68' TNED2body=[            cthe*cpsi               cthe*spsi
   * -sthe; ... */
  /* 'tailrotor:69'     (sphi*sthe*cpsi-cphi*spsi)  (sphi*sthe*spsi+cphi*cpsi)
   * sphi*cthe; ... */
  /* 'tailrotor:70'     (cphi*sthe*cpsi+sphi*spsi)  (cphi*sthe*spsi-sphi*cpsi)
   * cphi*cthe]; */
  TNED2body[0] = cthe * cpsi;
  TNED2body[3] = cthe * xtr_dot;
  TNED2body[6] = -sthe;
  ytail = sphi * sthe;
  TNED2body[1] = ytail * cpsi - cphi * xtr_dot;
  TNED2body[4] = ytail * xtr_dot + cphi * cpsi;
  TNED2body[7] = sphi * cthe;
  sthe *= cphi;
  TNED2body[2] = sthe * cpsi + sphi * xtr_dot;
  TNED2body[5] = sthe * xtr_dot - sphi * cpsi;
  TNED2body[8] = cphi * cthe;
  /* 'tailrotor:71' Vextb=TNED2body*Vext; */
  memset(&Vextb[0], 0, 3U * sizeof(double));
  /* Tail rotor geometry */
  /* 'tailrotor:74' XTR = -(FSTR-FSCGB)/12.0; */
  XTR = -(constants->FSTR - constants->FSCGB) / 12.0;
  /*  [ft] */
  /* 'tailrotor:75' ZTR = -(WLTR-WLCGB)/12.0; */
  ZTR = -(constants->WLTR - constants->WLCGB) / 12.0;
  /*  [ft] */
  /* 'tailrotor:76' YTR = (BLTR-BLCGB)/12.0; */
  YTR = (constants->BLTR - constants->BLCGB) / 12.0;
  /*  [ft] */
  /* Body to TR transform */
  /* 'tailrotor:80' cgam=cos((90-constants.CantTR)*D2R); */
  sthe = (90.0 - constants->CantTR) * constants->D2R;
  cgam = cos(sthe);
  /* 'tailrotor:81' sgam=sin((90-constants.CantTR)*D2R); */
  xtr_dot = sin(sthe);
  /* 'tailrotor:82' Tcant=[1. 0. 0.; 0. cgam sgam; 0. -sgam cgam]; */
  r = _mm_loadu_pd(&TNED2body[0]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  r2 = _mm_set1_pd(0.0);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Vextb[2] += TNED2body[2] * 0.0;
  Tcant[0] = 1.0;
  r = _mm_loadu_pd(&TNED2body[3]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Vextb[2] += TNED2body[5] * 0.0;
  Tcant[3] = 0.0;
  r = _mm_loadu_pd(&TNED2body[6]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Vextb[2] += TNED2body[8] * 0.0;
  Tcant[6] = 0.0;
  Tcant[1] = 0.0;
  Tcant[4] = cgam;
  Tcant[7] = xtr_dot;
  Tcant[2] = 0.0;
  Tcant[5] = -xtr_dot;
  Tcant[8] = cgam;
  /* 'tailrotor:84' GTR = ATR*BLDSTR*CHRDTR/(2.0*pi*RTR); */
  GTR = constants->a0TR * constants->NB * constants->CHRDTR /
        (6.283185307179586 * constants->RTR);
  /* 'tailrotor:86' S0 = ATR*CHRDTR*RTR^4/constants.IbTR; */
  /* 'tailrotor:87' S1 = BTLTR/2.0; */
  S1 = constants->BTLTR / 2.0;
  /* 'tailrotor:88' S2 = S1*BTLTR; */
  S2 = S1 * constants->BTLTR;
  /* 'tailrotor:89' S3 = S2^2; */
  S3 = S2 * S2;
  /* 'tailrotor:90' S4 = S2/2; */
  /* 'tailrotor:91' S5 = (BTLTR^3)/3.0; */
  S5 = rt_powd_snf(constants->BTLTR, 3.0) / 3.0;
  /* 'tailrotor:92' S6 = constants.DELTTR*constants.TD3TR; */
  S6 = constants->DELTTR * constants->TD3TR;
  /* 'tailrotor:93' CBLK = 1.0/(constants.VBVTTR^2); */
  /* 'tailrotor:95' B2 = BTLTR^2; */
  B2 = constants->BTLTR * constants->BTLTR;
  /* 'tailrotor:96' B3 = BTLTR*B2; */
  B3 = constants->BTLTR * B2;
  /* 'tailrotor:97' B4 = B2^2; */
  B4 = B2 * B2;
  /* 'tailrotor:98' B5 = B2*B3; */
  B5 = B2 * B3;
  /* 'tailrotor:99' B6 = B3^2; */
  B6 = B3 * B3;
  /* 'tailrotor:100' B7 = B3*B4; */
  B7 = B3 * B4;
  /* 'tailrotor:101' B8 = B4^2; */
  B8 = B4 * B4;
  /* 'tailrotor:102' B9 = B4*B5; */
  B9 = B4 * B5;
  /* 'tailrotor:103' B10 = B5^2; */
  B10 = B5 * B5;
  /* 'tailrotor:104' B11 = B5*B6; */
  /* 'tailrotor:105' B12 = B6^2; */
  /* 'tailrotor:107' S10 = B2/1296.0; */
  /* 'tailrotor:108' S11 = C83TR*BTLTR; */
  /* 'tailrotor:109' S12 = B9/864.0; */
  /* 'tailrotor:110' S13 = 2.0*B2; */
  /* 'tailrotor:111' S14 = B10/1080.0; */
  /* 'tailrotor:112' S15 = C89TR*B2; */
  /* 'tailrotor:113' S16 = B10/2304.0; */
  /* 'tailrotor:114' S17 = C43TR*B3; */
  /* 'tailrotor:115' S18 = B11/1440.0; */
  /* 'tailrotor:116' S19 = B4/2.0; */
  /* 'tailrotor:117' S20 = B12/3600.0; */
  /* S21 = -B5/108.0; */
  /* S22 = -B6/144.0; */
  /* S23 = -B7/180.0; */
  /* S24 = B2/36.0; */
  /* 'tailrotor:122' S25 = -C14TR+(1.0/B2)+(C12TR/B4); */
  /* 'tailrotor:123' S26 = (B4/162.0)-(B5/81.0)+(B6/144.0); */
  /* 'tailrotor:124' S27 = C43TR/BTLTR*(1.0+(1.0/B2)); */
  /* 'tailrotor:125' S28 = (B5/108.0)-(B6/54.0)+(B7/96.0); */
  /* 'tailrotor:126' S29 = 1.0+(1.0/B2); */
  /* 'tailrotor:127' S30 = (B6/135.0)*(1.0-(2.0*BTLTR))+(B8/120.0); */
  /* 'tailrotor:128' S31 = C14TR+(C89TR/B2); */
  /* 'tailrotor:129' S32 = (B6/288.0)-(B7/144.0)+(B8/256.0); */
  /* 'tailrotor:130' S33 = C13TR+(C43TR/BTLTR); */
  /* 'tailrotor:131' S34 = (B7/180.0)-(B8/90.0)+(B9/160.0); */
  /* 'tailrotor:132' S35 = (B8/450.0)-(B9/225.0)+(B10/400.0); */
  /* 'tailrotor:134' SIGTR = BLDSTR*CHRDTR/(pi*RTR); */
  /* 'tailrotor:135' THT1TR = TWSTTR*D2R; */
  THT1TR = constants->twistTR / constants->D2R * constants->D2R;
  /* 'tailrotor:137' S7 = pi*((OMEGTR*OMGRAT*RTR^2)^2); */
  a_tmp = constants->OmegaTR * OMGRAT;
  sthe = a_tmp * (constants->RTR * constants->RTR);
  S7 = 3.141592653589793 * (sthe * sthe);
  /* 'tailrotor:138' S8 = 1.0/(OMEGTR*RTR*OMGRAT); */
  cpsi = 1.0 / (constants->OmegaTR * constants->RTR * OMGRAT);
  /* 'tailrotor:139' S9 = S7*RTR; */
  /* Dynamic pressure ratio */
  /* Same as for vertical tail */
  /* 'tailrotor:143' idxtail = 1; */
  /* 'tailrotor:144' xtail=-(constants.FSTR(idxtail)-constants.FSCG)/12.; */
  sthe = -(constants->FSTR - constants->FSCG) / 12.0;
  /* 'tailrotor:145' ytail=(constants.BLTR(idxtail)-constants.BLCG)/12.; */
  ytail = (constants->BLTR - constants->BLCG) / 12.0;
  /* 'tailrotor:146' ztail=-(constants.WLTR(idxtail)-constants.WLCG)/12.; */
  sphi = -(constants->WLTR - constants->WLCG) / 12.0;
  /* 'tailrotor:148' qlossfac=sqrt(rotor_if(6)); */
  cphi = sqrt(rotor_if[5]);
  /* 'tailrotor:149'
   * ublocal=xf(1)*qlossfac+Vextb(1)+rotor_if(2)+(QB)*ztail-(RB)*ytail; */
  /* 'tailrotor:150'
   * vblocal=(xf(2)-D2R*xf(1)*rotor_if(8))*qlossfac+Vextb(2)-(PB)*ztail+(RB)*xtail;
   */
  /* 'tailrotor:151'
   * wblocal=(xf(3)-D2R*xf(1)*rotor_if(7))*qlossfac+Vextb(3)+rotor_if(1)+(PB)*ytail-(QB)*xtail;
   */
  /* Transform velocities to orientation of tail */
  /* 'tailrotor:154' temp=Tcant*[ublocal;vblocal;wblocal]; */
  ptrNED[0] = (((xf[0] * cphi + Vextb[0]) + rotor_if[1]) + xf[4] * sphi) -
              xf[5] * ytail;
  cthe = constants->D2R * xf[0];
  ptrNED[1] =
      (((xf[1] - cthe * rotor_if[7]) * cphi + Vextb[1]) - xf[3] * sphi) +
      xf[5] * sthe;
  ptrNED[2] =
      ((((xf[2] - cthe * rotor_if[6]) * cphi + Vextb[2]) + rotor_if[0]) +
       xf[3] * ytail) -
      xf[4] * sthe;
  memset(&Vextb[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Tcant[0]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(ptrNED[0]))));
  Vextb[2] += 0.0 * ptrNED[0];
  r = _mm_loadu_pd(&Tcant[3]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(ptrNED[1]))));
  Vextb[2] += ptrNED[1] * -xtr_dot;
  r = _mm_loadu_pd(&Tcant[6]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0],
                _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(ptrNED[2]))));
  Vextb[2] += ptrNED[2] * cgam;
  /* 'tailrotor:155' ut=temp(1); */
  /* 'tailrotor:156' vt=temp(2); */
  /* 'tailrotor:157' wt=temp(3); */
  /* Advance ratios */
  /* 'tailrotor:160' XMUXTR = ut*S8; */
  sthe = Vextb[0] * cpsi;
  /* 'tailrotor:161' XMUYTR = vt*S8; */
  ytail = Vextb[1] * cpsi;
  /* 'tailrotor:162' XMUZTR = wt*S8; */
  xtr_dot = Vextb[2] * cpsi;
  /* 'tailrotor:163' XMU2 = ((XMUXTR^2) + (XMUYTR^2)); */
  XMU2 = sthe * sthe + ytail * ytail;
  /* Bailey coefficents */
  /* 'tailrotor:166' BT31 = S2+(0.25*XMU2); */
  BT31 = S2 + 0.25 * XMU2;
  /* 'tailrotor:167' BT32 = S5+(S1*XMU2); */
  BT32 = S5 + S1 * XMU2;
  /* 'tailrotor:168' BT33 = S3+(S4*XMU2); */
  BT33 = S3 + S2 / 2.0 * XMU2;
  /* Additional Bailey coefficients for torque */
  /* 'tailrotor:171' XGAM = RHO*S0; */
  sthe = atmos_rho * (constants->a0TR * constants->CHRDTR *
                      rt_powd_snf(constants->RTR, 4.0) / constants->IbTR);
  /* 'tailrotor:172' XGAM2 = XGAM^2; */
  cpsi = sthe * sthe;
  /* 'tailrotor:173' BT41  = S2+(C54TR+(S10*XGAM2))*XMU2; */
  /* 'tailrotor:174' BT42  = S5+(S11+(S12*XGAM2))*XMU2; */
  /* 'tailrotor:175' BT43  = S3+(S13+(S14*XGAM2))*XMU2; */
  /* 'tailrotor:176' BT44  = (S15+(S16*XGAM2))*XMU2; */
  /* 'tailrotor:177' BT45  = (S17+(S18*XGAM2))*XMU2; */
  /* 'tailrotor:178' BT46  = (S19+(S20*XGAM2))*XMU2; */
  /* BT47  = S21*XMU2; */
  /* BT48  = S22*XMU2; */
  /* BT49  = S23*XMU2; */
  /* BT410 = S24*XMU2; */
  /* 'tailrotor:183' BT51  = C14TR*(1.0+XMU2); */
  ytail = 0.25 * (XMU2 + 1.0);
  /* 'tailrotor:184' BT52  = C13TR; */
  /* 'tailrotor:185' BT53  = BT51; */
  /* 'tailrotor:186' BT54  = C15TR+(C16TR*XMU2); */
  /* 'tailrotor:187' BT55  = C12TR+((S25+(S26*XGAM2))*XMU2); */
  /* 'tailrotor:188' BT56  = C23TR+((S27+(S28*XGAM2))*XMU2); */
  /* 'tailrotor:189' BT57  = C12TR+((S29+(S30*XGAM2))*XMU2); */
  /* 'tailrotor:190' BT58  = C14TR+((S31+(S32*XGAM2))*XMU2); */
  /* 'tailrotor:191' BT59  = C25TR+((S33+(S34*XGAM2))*XMU2); */
  /* 'tailrotor:192' BT510 = C16TR+((C58TR+(S35*XGAM2))*XMU2); */
  /* Vertical tail blockage factor */
  /* 'tailrotor:195' BLKTR = constants.BVTTR1; */
  S1 = constants->BVTTR1;
  /* 'tailrotor:197' if (VKT < constants.VBVTTR) */
  if (VKT < constants->VBVTTR) {
    /* 'tailrotor:198' BLKTR =
     * ((1.0-constants.BVTTR)*CBLK*(VKT^2))+constants.BVTTR; */
    S1 = (1.0 - constants->BVTTR) *
             (1.0 / (constants->VBVTTR * constants->VBVTTR)) * (VKT * VKT) +
         constants->BVTTR;
  }
  /* 'tailrotor:201' TTR = 200; */
  cthe = 200.0;
  /* 'tailrotor:202' DWTRSS = xtr(1); */
  sthe = xtr;
  /* 'tailrotor:203' XLAMTR=XMUZTR-xtr(1); */
  cgam = xtr_dot - xtr;
  sphi = cgam;
  /* Dummy statements to allow compilation */
  /* 'tailrotor:204' THETTR = D2R*(THETTRC); */
  OMGRAT = constants->D2R * controls[3];
  /* 'tailrotor:205' iter=0; */
  iter = 0;
  /* 'tailrotor:206' err=10; */
  cphi = 10.0;
  /* Iterate for steady-state induced velocity and thrust */
  /* 'tailrotor:208' while abs(err)>1e-6 && iter<200 */
  while ((fabs(cphi) > 1.0E-6) && (iter < 200)) {
    /* Tail rotor blade pitch */
    /* 'tailrotor:211' THETTR = D2R*(THETTRC-(TTR*S6)+constants.BIASTR); */
    OMGRAT = constants->D2R * ((controls[3] - cthe * S6) + constants->BIASTR);
    /*  [rad] */
    /* Tail rotor downwash, thrust */
    /* 'tailrotor:214' DWTRSS =
     * GTR*((XMUZTR*BT31)+(THETTR*BT32)+(D2R*TWSTTR*BT33))/... */
    /* 'tailrotor:215'         (2.0*sqrt(XMU2+((XMUZTR-DWTRSS)^2))+(GTR*BT31));
     */
    sthe = xtr_dot - sthe;
    sthe = GTR * ((xtr_dot * BT31 + OMGRAT * BT32) + THT1TR * BT33) /
           (2.0 * sqrt(XMU2 + sthe * sthe) + GTR * BT31);
    /* 'tailrotor:217' XLAMTR = XMUZTR-DWTRSS; */
    sphi = xtr_dot - sthe;
    /* 'tailrotor:219' TTR_new = 2.0*DWTRSS*sqrt(XMU2+(XLAMTR^2))*RHO*S7*BLKTR;
     */
    /* 'tailrotor:221' err = TTR_new-TTR; */
    cphi = 2.0 * sthe * sqrt(XMU2 + sphi * sphi) * atmos_rho * S7 * S1 - cthe;
    /* 'tailrotor:222' TTR = TTR+0.5*err; */
    cthe += 0.5 * cphi;
    /* This thrust is steady-state version, will get overwritten for current
     * inflow. */
    /* 'tailrotor:223' iter=iter+1; */
    iter++;
  }
  /* Inflow dynamics (no time delay) */
  /* 'tailrotor:227' VT = sqrt(XMU2+(XLAMTR^2)); */
  /* 'tailrotor:228' CDWTR = XKINF/(OMEGTR*OMGRAT*VT); */
  /* Inflow time constant */
  /* Inflow ratio */
  /* 'tailrotor:231' XLAMTR = XMUZTR-xtr(1); */
  /* Inflow dynamics */
  /* 'tailrotor:233' xtr_dot=(DWTRSS-xtr(1))/(CDWTR); */
  xtr_dot =
      (sthe - xtr) / (0.4244131815783876 / (a_tmp * sqrt(XMU2 + sphi * sphi)));
  /* Thrust */
  /* 'tailrotor:236' CTHTR =
   * GTR*((XLAMTR*BT31)+(THETTR*BT32)+(D2R*TWSTTR*BT33)); */
  /* 'tailrotor:237' TTR = CTHTR*RHO*S7*BLKTR; */
  /* Torque */
  /* 'tailrotor:240' CQTR = (((constants.D2TR*BT55)   -
   * (ATR*BT41))*(XLAMTR^2)... */
  /* 'tailrotor:241'     +((constants.D2TR*BT56)  - (ATR*BT42))*THETTR*XLAMTR...
   */
  /* 'tailrotor:242'     +((constants.D2TR*BT57)  - (ATR*BT43))*THT1TR*XLAMTR...
   */
  /* 'tailrotor:243'     +((constants.D2TR*BT58)  - (ATR*BT44))*(THETTR^2)... */
  /* 'tailrotor:244'     +((constants.D2TR*BT59)  - (ATR*BT45))*THT1TR*THETTR...
   */
  /* 'tailrotor:245'     +((constants.D2TR*BT510) - (ATR*BT46))*(THT1TR^2)... */
  /* 'tailrotor:246'     + (constants.D0TR*BT51 ) +
   * constants.D1TR*((BT52*XLAMTR)... */
  /* 'tailrotor:247'     + (BT53*THETTR)+ (BT54*THT1TR)))*0.5*SIGTR; */
  /* 'tailrotor:249' Qtr = CQTR*RHO*S9; */
  sthe = 1.0 / B2;
  sphi = 1.333333333 / constants->BTLTR;
  *Qtr =
      ((((((((constants->D2TR *
                  ((((sthe - 0.25) + 0.5 / B4) +
                    ((B4 / 162.0 - B5 / 81.0) + B6 / 144.0) * cpsi) *
                       XMU2 +
                   0.5) -
              constants->a0TR * (S2 + (B2 / 1296.0 * cpsi + 1.25) * XMU2)) *
                 (cgam * cgam) +
             (constants->D2TR *
                  ((sphi * (sthe + 1.0) +
                    ((B5 / 108.0 - B6 / 54.0) + B7 / 96.0) * cpsi) *
                       XMU2 +
                   0.666666666) -
              constants->a0TR *
                  (S5 + (2.666666666 * constants->BTLTR + B9 / 864.0 * cpsi) *
                            XMU2)) *
                 OMGRAT * cgam) +
            (constants->D2TR *
                 (((sthe + 1.0) +
                   (B6 / 135.0 * (1.0 - 2.0 * constants->BTLTR) + B8 / 120.0) *
                       cpsi) *
                      XMU2 +
                  0.5) -
             constants->a0TR * (S3 + (2.0 * B2 + B10 / 1080.0 * cpsi) * XMU2)) *
                THT1TR * cgam) +
           (constants->D2TR *
                (((0.888888888 / B2 + 0.25) +
                  ((B6 / 288.0 - B7 / 144.0) + B8 / 256.0) * cpsi) *
                     XMU2 +
                 0.25) -
            constants->a0TR *
                ((0.888888888 * B2 + B10 / 2304.0 * cpsi) * XMU2)) *
               (OMGRAT * OMGRAT)) +
          (constants->D2TR * (((sphi + 0.333333333) +
                               ((B7 / 180.0 - B8 / 90.0) + B9 / 160.0) * cpsi) *
                                  XMU2 +
                              0.4) -
           constants->a0TR *
               ((1.333333333 * B3 + B5 * B6 / 1440.0 * cpsi) * XMU2)) *
              THT1TR * OMGRAT) +
         (constants->D2TR *
              ((((B8 / 450.0 - B9 / 225.0) + B10 / 400.0) * cpsi + 0.625) *
                   XMU2 +
               0.166666666) -
          constants->a0TR * ((B4 / 2.0 + B6 * B6 / 3600.0 * cpsi) * XMU2)) *
             (THT1TR * THT1TR)) +
        constants->D0TR * ytail) +
       constants->D1TR * ((0.333333333 * cgam + ytail * OMGRAT) +
                          (0.166666666 * XMU2 + 0.2) * THT1TR)) *
      0.5 *
      (constants->NB * constants->CHRDTR /
       (3.141592653589793 * constants->RTR)) *
      atmos_rho * (S7 * constants->RTR);
  /* Tail Rotor Drag */
  /* 'tailrotor:252' DTR=0.5*CDTR*RHO*(ut^2); */
  /* Tail rotor horsepower */
  /* HPTR = Qtr*OMEGTR*OMGRAT*FtLb_s2Hp; % [hp] */
  /* Transform thrust, drag, torque from TR to body frame */
  /* 'tailrotor:258' Ftr=Tcant'*[-DTR;0.;-TTR]; */
  ptrNED[0] = -(0.5 * constants->CDTR * atmos_rho * (Vextb[0] * Vextb[0]));
  ptrNED[1] = 0.0;
  ptrNED[2] = -(GTR * ((cgam * BT31 + OMGRAT * BT32) + THT1TR * BT33) *
                atmos_rho * S7 * S1);
  memset(&Ftr[0], 0, 3U * sizeof(double));
  sthe = Ftr[0];
  ytail = Ftr[1];
  sphi = Ftr[2];
  for (i = 0; i < 3; i++) {
    cphi = Tcant[i];
    Ftr_tmp[3 * i] = cphi;
    cthe = ptrNED[i];
    sthe += cphi * cthe;
    cphi = Tcant[i + 3];
    Ftr_tmp[3 * i + 1] = cphi;
    ytail += cphi * cthe;
    cphi = Tcant[i + 6];
    Ftr_tmp[3 * i + 2] = cphi;
    sphi += cphi * cthe;
  }
  Ftr[2] = sphi;
  Ftr[1] = ytail;
  Ftr[0] = sthe;
  /* 'tailrotor:259' Mtr_local=Tcant'*[0.;0.;-Qtr]; */
  /* 'tailrotor:260' Mtr=[0. -ZTR YTR; ZTR 0. -XTR; -YTR XTR 0.]*Ftr+Mtr_local;
   */
  Tcant[0] = 0.0;
  Tcant[3] = -ZTR;
  Tcant[6] = YTR;
  Tcant[1] = ZTR;
  Tcant[4] = 0.0;
  Tcant[7] = -XTR;
  Tcant[2] = -YTR;
  Tcant[5] = XTR;
  Tcant[8] = 0.0;
  memset(&Mtr[0], 0, 3U * sizeof(double));
  memset(&Vextb[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Tcant[0]);
  r1 = _mm_loadu_pd(&Mtr[0]);
  _mm_storeu_pd(&Mtr[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(sthe))));
  r = _mm_loadu_pd(&Ftr_tmp[0]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Mtr[2] += sthe * -YTR;
  Vextb[2] += Ftr_tmp[2] * 0.0;
  r = _mm_loadu_pd(&Tcant[3]);
  r1 = _mm_loadu_pd(&Mtr[0]);
  _mm_storeu_pd(&Mtr[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(ytail))));
  r = _mm_loadu_pd(&Ftr_tmp[3]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Mtr[2] += ytail * XTR;
  Vextb[2] += Ftr_tmp[5] * 0.0;
  r = _mm_loadu_pd(&Tcant[6]);
  r1 = _mm_loadu_pd(&Mtr[0]);
  _mm_storeu_pd(&Mtr[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(sphi))));
  r = _mm_loadu_pd(&Ftr_tmp[6]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Vextb[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(-*Qtr))));
  Mtr[2] += 0.0 * sphi;
  Vextb[2] += -*Qtr * Ftr_tmp[8];
  r = _mm_loadu_pd(&Mtr[0]);
  r1 = _mm_loadu_pd(&Vextb[0]);
  _mm_storeu_pd(&Mtr[0], _mm_add_pd(r, r1));
  Mtr[2] += Vextb[2];
  /* 'tailrotor:261' ptrNED = xf(10:12)+TNED2body'*[XTR;YTR;ZTR]; */
  for (i = 0; i < 3; i++) {
    ptrNED[i] =
        xf[i + 9] + ((TNED2body[3 * i] * XTR + TNED2body[3 * i + 1] * YTR) +
                     TNED2body[3 * i + 2] * ZTR);
  }
  return xtr_dot;
}

/* End of code generation (tailrotor.c) */
