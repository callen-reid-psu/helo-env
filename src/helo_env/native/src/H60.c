/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * H60.c
 *
 * Code generation for function 'H60'
 *
 */

/* Include files */
#include "H60.h"
#include "GHrotor.h"
#include "H60Sim_rtwutil.h"
#include "H60Sim_types.h"
#include "atan2.h"
#include "eqnmot.h"
#include "fuselage.h"
#include "rotor_int_H60.h"
#include "rt_nonfinite.h"
#include "tail.h"
#include "tailrotor.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * function [x_dot,y]=H60(x,u,xdot,constants)
 */
void H60(const double x[39], const double xdot[39],
         const constants_Struct *constants, double x_dot[39], double y[7])
{
  static const double uin[4] = {5.0, 5.0, 5.0, 2.69};
  __m128d r;
  __m128d r1;
  double yr[133];
  double xr_dot[24];
  double ur[23];
  double dv[12];
  double b_constants[4];
  double controls[4];
  double servos[4];
  double Fht[3];
  double Ftot[3];
  double Ftr[3];
  double Mf[3];
  double Mht[3];
  double Mtr[3];
  double Mvt[3];
  double c_constants[3];
  double T;
  double Tfac;
  double Veq;
  double atmos_rho;
  double xtr_dot;
  int b_i;
  int i;
  /* Simulation of H-60 based on NASA CR 166309 */
  /* (https://ntrs.nasa.gov/citations/19840020737) */
  /* This the main executive, calls each of the sub-modules for trim and */
  /* initialization or numerical integration outside of Simulink */
  /*  Input: time, t */
  /*         aircraft state vector, x */
  /*         pilot control input (or pilot + AFCS), u */
  /*  Output: state derivative, x_dot */
  /* Partition state vector */
  /*  Fuselage states */
  /* 'H60:14' xf=x(SizeConstants.IDXF); */
  /* Rotor states */
  /* 'H60:16' xr=x(SizeConstants.IDXR); */
  /* Tail Rotor states */
  /* 'H60:18' xtr=x(SizeConstants.IDXTR); */
  /* Landing Gear States */
  /* xlg=x(constants.NFSTATES+constants.NRSTATES+constants.NTRSTATES+1:constants.NFSTATES+constants.NRSTATES+constants.NTRSTATES+constants.NLGSTATES);
   */
  /* Engine states */
  /* 'H60:22' xe=x(SizeConstants.IDXP); */
  /* Atmosphere model */
  /* -1*xf(12) = altitude in ft, 0 indicates Imperial units */
  /* 'H60:26' atmos = std_atmos(-xf(12),constants,0); */
  /* Standard atmosphere model */
  /*  Returns density (sl/ft^2) and speed of sound (ft/sec) as function of
   * altitude (ft) */
  /*  good up to 65,617 ft */
  /*  AJ if in MKS mode, convert altitude from m to ft */
  /* 'std_atmos:7' if IMKS */
  /* 'std_atmos:11' rho0=constants.rhoSLSTD; */
  /* 'std_atmos:12' Tfac = 1.0 - 0.703E-5 * alt; */
  Tfac = 1.0 - 7.03E-6 * -x[11];
  /* 'std_atmos:13' T    = 519.0 * Tfac; */
  T = 519.0 * Tfac;
  /* 'std_atmos:14' if alt > 36089.0 */
  if (-x[11] > 36089.0) {
    /* 'std_atmos:15' T = 390.0; */
    T = 390.0;
  }
  /* 'std_atmos:17' atmos.rho  = rho0 * (Tfac^4.14); */
  atmos_rho = constants->rhoSLSTD * rt_powd_snf(Tfac, 4.14);
  /* 'std_atmos:18' atmos.spsnd= sqrt(1.4*1716.3*T); */
  /*  AJ convert density and speed of sound to MKS if necessary */
  /* 'std_atmos:21' if IMKS */
  /* Control System Mixing */
  /* 'H60:29' controls=H60_mixing(u(1:4),constants); */
  /* Control mixing module - converts pilot + AFCS controls to control surface
   * deflections */
  /*                 Models mechanical mixing unit of UH-60 */
  /* Convert to inches */
  /* 'H60_mixing:9' uin=diag([0.1 0.1 0.1 5.38/100.])*u(1:4); */
  /* Mixer input */
  /* 'H60_mixing:12' umix=constants.LNKGAIN*uin; */
  /* 'H60_mixing:14' servos=constants.MIXGAIN*umix; */
  memset(&b_constants[0], 0, sizeof(double) << 2);
  for (i = 0; i < 4; i++) {
    r = _mm_loadu_pd(&b_constants[0]);
    b_i = i << 2;
    r1 = _mm_set1_pd(uin[i]);
    _mm_storeu_pd(
        &b_constants[0],
        _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->LNKGAIN[b_i]), r1)));
    r = _mm_loadu_pd(&b_constants[2]);
    _mm_storeu_pd(
        &b_constants[2],
        _mm_add_pd(r,
                   _mm_mul_pd(_mm_loadu_pd(&constants->LNKGAIN[b_i + 2]), r1)));
  }
  memset(&servos[0], 0, sizeof(double) << 2);
  /* 'H60_mixing:16' control=zeros(4,1); */
  for (i = 0; i < 4; i++) {
    r = _mm_loadu_pd(&servos[0]);
    b_i = i << 2;
    r1 = _mm_set1_pd(b_constants[i]);
    _mm_storeu_pd(
        &servos[0],
        _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->MIXGAIN[b_i]), r1)));
    r = _mm_loadu_pd(&servos[2]);
    _mm_storeu_pd(
        &servos[2],
        _mm_add_pd(r,
                   _mm_mul_pd(_mm_loadu_pd(&constants->MIXGAIN[b_i + 2]), r1)));
    controls[i] = 0.0;
  }
  double rotor_if[8];
  double a__4[3];
  /* 'H60_mixing:17'
   * control(1:3)=constants.SWASHGAIN*servos(1:3)+constants.SWASHBIAS; */
  Tfac = servos[0];
  xtr_dot = servos[1];
  Veq = servos[2];
  r = _mm_loadu_pd(&constants->SWASHGAIN[0]);
  r1 = _mm_mul_pd(r, _mm_set1_pd(Tfac));
  r = _mm_loadu_pd(&constants->SWASHGAIN[3]);
  r = _mm_mul_pd(r, _mm_set1_pd(xtr_dot));
  r1 = _mm_add_pd(r1, r);
  r = _mm_loadu_pd(&constants->SWASHGAIN[6]);
  r = _mm_mul_pd(r, _mm_set1_pd(Veq));
  r = _mm_add_pd(r1, r);
  r1 = _mm_loadu_pd(&constants->SWASHBIAS[0]);
  r = _mm_add_pd(r, r1);
  _mm_storeu_pd(&controls[0], r);
  controls[2] =
      ((constants->SWASHGAIN[2] * Tfac + constants->SWASHGAIN[5] * xtr_dot) +
       constants->SWASHGAIN[8] * Veq) +
      constants->SWASHBIAS[2];
  /* Cyclic defined with opposite sign as used by rotor module */
  /* 'H60_mixing:19' control(1:2)=-control(1:2); */
  r = _mm_loadu_pd(&controls[0]);
  _mm_storeu_pd(&controls[0], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
  /* 'H60_mixing:20' control(4)=constants.TRGAIN*servos(4)+constants.TRBIAS; */
  controls[3] = -9.142 * servos[3] + 21.98;
  /* Wf=u(5); */
  /* Rotor interference module */
  /* 'H60:33' [rotor_if]=rotor_int_H60(x,0.,constants); */
  rotor_int_H60(x, constants, rotor_if);
  /* External velocities zeroed out for this application */
  /* 'H60:36' VextF=zeros(3,1); */
  /* 'H60:37' VextTR=zeros(3,1); */
  /* 'H60:38' VextHT=zeros(3,1); */
  /* 'H60:39' VextVT=zeros(3,1); */
  /* Fuselage Forces and Moments */
  /* 'H60:42' [Ff,Mf,~]=fuselage(xf,VextF,rotor_if,atmos,constants); */
  fuselage(&x[0], rotor_if, atmos_rho, constants, Ftot, Mf, c_constants);
  /* Tail Rotor Forces and Moments */
  /* 'H60:45'
   * [xtr_dot,Ftr,Mtr,Qtr,~]=tailrotor(xtr,xf,controls,VextTR,rotor_if,constants.OMEGAT,atmos,constants);
   */
  xtr_dot = tailrotor(x[36], &x[0], controls, rotor_if, 27.0, atmos_rho,
                      constants, Ftr, Mtr, &Tfac, c_constants);
  /* Equiv Airspeed used in Stabilator Schedule */
  /* 'H60:48' Veq=sqrt( (x(1))^2 + (x(2))^2 + (x(3))^2
   * )/1.688*sqrt(atmos.rho/constants.rhoSLSTD); */
  Veq = sqrt((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) / 1.688 *
        sqrt(atmos_rho / 0.002378);
  /* 'H60:49'
   * ayg=(xdot(2)-constants.g*sin(x(7))*cos(x(8))+x(6)*x(1)-x(4)*x(3))/constants.g;
   */
  /* 'H60:50' StabSet=constants.STABSET; */
  /* 'H60:51' StabInc=H60StabSched(u(3),Veq,ayg,x(5),StabSet); */
  /* Horizontal Tail */
  /* 'H60:54' [Fht,Mht,~]=tail(xf,VextHT,StabInc,rotor_if,1,atmos,constants); */
  /*  Stabilator Schedule and Controller   */
  /*  Scheduled is function of Airspeed and Collective. */
  /*  Dynamic feedback on ay and pitch rate (q) */
  /*  If StabSet != 0, then stabilator is fixed at value of StabSet (just use */
  /*  very small value of StabSet to effectively set it to 0.) */
  /* 'H60StabSched:11' if (StabSet==0) */
  /* 'H60StabSched:13' aylim=max(min(ayg,0.13),-0.13); */
  /* 'H60StabSched:15' stab_ay=-0.0433*min((Veq-30.),30.)*aylim; */
  /* 'H60StabSched:16' stab_q=0.16*180/pi*q; */
  /* 'H60StabSched:18' VSchedule=-0.1119*min(max(Veq-80.,0.),67.); */
  /* 'H60StabSched:19' PR50=min(max(Veq-30.,0.),50.); */
  /* 'H60StabSched:21' C1=min(max(70.-Coll,0.),20.); */
  /* 'H60StabSched:22' C2=min(max(50.-Coll,0.),50.); */
  /* 'H60StabSched:23' CollSchedule=-1.*PR50*(0.003286*(C1+C2)+0.67); */
  /* 'H60StabSched:25' IHT0=42.+CollSchedule+VSchedule+stab_q+stab_ay; */
  /* 'H60StabSched:27' StabInc=min(max(IHT0,-8.),39.); */
  /* Stabilator Incidence in degrees */
  tail(&x[0],
       fmin(fmax((((-fmin(fmax(Veq - 30.0, 0.0), 50.0) * 0.73572 + 42.0) +
                   -0.1119 * fmin(fmax(Veq - 80.0, 0.0), 67.0)) +
                  9.167324722093172 * x[4]) +
                     -0.0433 * fmin(Veq - 30.0, 30.0) *
                         fmax(fmin((((xdot[1] - 32.17 * sin(x[6]) * cos(x[7])) +
                                     x[0] * x[5]) -
                                    x[2] * x[3]) /
                                       32.17,
                                   0.13),
                              -0.13),
                 -8.0),
            39.0),
       rotor_if, 1.0, atmos_rho, constants, Fht, Mht, c_constants);
  /* Vertical Tail */
  /* 'H60:57' [Fvt,Mvt,~]=tail(xf,VextVT,0.,rotor_if,2,atmos,constants); */
  tail(&x[0], 0.0, rotor_if, 2.0, atmos_rho, constants, c_constants, Mvt, a__4);
  /* Landing Gear */
  /* nTerrain = constants.terrain.ng; */
  /* zTerrain = constants.terrain.Z - (constants.terrain.ng(1)*xf(10) +
   * constants.terrain.ng(2)*xf(11))/constants.terrain.ng(3); */
  /* [xlg_dot,Flg,Mlg,~] = LandingGear(xlg,xf,zTerrain,nTerrain,constants); */
  /* Main Rotor */
  /* Define inouts to module */
  /* 'H60:66' ur=zeros(SizeConstants.NUROTOR,1); */
  memset(&ur[0], 0, 23U * sizeof(double));
  /* 'H60:67' ur(1)=controls(1)*pi/180.; */
  ur[0] = controls[0] * 3.141592653589793 / 180.0;
  /* 'H60:68' ur(2)=controls(2)*pi/180.; */
  ur[1] = controls[1] * 3.141592653589793 / 180.0;
  /* 'H60:69' ur(3)=controls(3)*pi/180.; */
  ur[2] = controls[2] * 3.141592653589793 / 180.0;
  /* 'H60:70' ur(4:15)=xf(1:12); */
  memcpy(&ur[3], &x[0], 12U * sizeof(double));
  /* 'H60:71' ur(16:21)=xdot(1:6); */
  for (i = 0; i < 6; i++) {
    ur[i + 15] = xdot[i];
  }
  __m128d r2;
  __m128d r3;
  __m128d r4;
  /* Nominal rotorspeed */
  /* 'H60:73' ur(22)=constants.OMEGAT; */
  ur[21] = 27.0;
  /* 'H60:74' ur(23)=xdot(SizeConstants.IDXP(1)); */
  ur[22] = xdot[37];
  /*  Run rotr module */
  /* 'H60:77' [xr_dot,yr] = GHrotor(xr,ur,atmos,constants); */
  GHrotor(&x[12], ur, atmos_rho, sqrt(2402.8199999999997 * T), constants,
          xr_dot, yr);
  /* 'H60:79' Fr=yr(1:3); */
  /* 'H60:80' Mr=yr(4:6); */
  /* 'H60:81' Qr=yr(12); */
  /*  Sum forces and Moments */
  /* Ftot=Fr+Ff+Fht+Fvt+Ftr+sum(Flg,2); */
  /* Mtot=Mr+Mf+Mht+Mvt+Mtr+sum(Mlg,2); */
  /* 'H60:86' Ftot=Fr+Ff+Fht+Fvt+Ftr; */
  r = _mm_loadu_pd(&yr[0]);
  r1 = _mm_loadu_pd(&Ftot[0]);
  r2 = _mm_loadu_pd(&Fht[0]);
  r3 = _mm_loadu_pd(&c_constants[0]);
  r4 = _mm_loadu_pd(&Ftr[0]);
  _mm_storeu_pd(
      &Ftot[0],
      _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3), r4));
  Ftot[2] = (((yr[2] + Ftot[2]) + Fht[2]) + c_constants[2]) + Ftr[2];
  /* 'H60:87' Mtot=Mr+Mf+Mht+Mvt+Mtr; */
  /* 'H60:88' Qreq=Qr+Qtr*constants.GEARTR; */
  Tfac = yr[11] + Tfac * 4.6156;
  /* Equations of Motion */
  /* 'H60:91' xf_dot = eqnmot(xf,Ftot,Mtot,constants); */
  /* need to compute rsdot for engine module */
  /* 'H60:94' temp=constants.Tshaft*xdot(4:6); */
  /* 'H60:95' rsdot=temp(3); */
  /* Engine */
  /* [ xe_dot, ~, ~, ~, ~, ~, ~, ~ ] = t700eng(
   * xe,Wf,constants.Pstd,constants.Tstd,2,Qreq,rsdot,constants ); */
  /* 'H60:99' Neng = 2; */
  /* This can be set to 1 or zero to simulate engine failure */
  /* 'H60:100' xe_dot = SimpleEngine(xe,Qreq,rsdot,Neng,atmos,constants); */
  /* Total state derivative */
  /* x_dot=[xf_dot;xr_dot;xtr_dot;xlg_dot;xe_dot]; */
  /* 'H60:104' x_dot=[xf_dot;xr_dot;xtr_dot;xe_dot]; */
  /* coder.cstructname(constants, 'constants_Struct'); */
  /* Simple ideal engine model.  Engine torque = filtered required torque */
  /* Init state derivative */
  /* 'SimpleEngine:7' xedot = zeros(SizeConstants.NPSTATES,1); */
  /* 'SimpleEngine:9' Omega = xe(1); */
  /* 'SimpleEngine:10' QE = xe(2); */
  /* Accessory Torque Required */
  /* 'SimpleEngine:13'
   * Qacc=constants.HPACC*550./constants.OMEGAT*(0.9+0.1*xe(1)/constants.OMEGAT);
   */
  /* MAke engine torque = to required torque with a filter */
  /* 'SimpleEngine:16' QEreq = Qreq+Qacc+constants.GBXDAMP*Omega; */
  /* 'SimpleEngine:18' Qgbx = QEreq - QE; */
  /* Equivalent Inertial Load */
  /* 'SimpleEngine:21'
   * FacIbx=constants.JTR+constants.JAC+constants.JENG*Neng+constants.JMROT; */
  /* Max torque */
  /* 'SimpleEngine:24' QEMax = constants.QEMax*atmos.rho/constants.rhoSLSTD; */
  /* State equations for Omega dot and Q dot */
  /* 'SimpleEngine:27' if (Neng > 0) */
  /* 'SimpleEngine:28' if (constants.IDEALENG == 1) */
  /* 'SimpleEngine:29' xedot(1)=0.; */
  /* 'SimpleEngine:33' xedot(2) = 1./constants.TauEng*(QEreq -
   * min(QE,QEMax*Neng)); */
  r = _mm_loadu_pd(&yr[3]);
  r1 = _mm_loadu_pd(&Mf[0]);
  r2 = _mm_loadu_pd(&Mht[0]);
  r3 = _mm_loadu_pd(&Mvt[0]);
  r4 = _mm_loadu_pd(&Mtr[0]);
  _mm_storeu_pd(
      &Mf[0],
      _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3), r4));
  Mf[2] = (((Mf[2] + yr[5]) + Mht[2]) + Mvt[2]) + Mtr[2];
  eqnmot(&x[0], Ftot, Mf, constants->g, constants->MASS, constants->IX,
         constants->IY, constants->IZ, constants->IXZ, dv);
  memcpy(&x_dot[0], &dv[0], 12U * sizeof(double));
  memcpy(&x_dot[12], &xr_dot[0], 24U * sizeof(double));
  x_dot[36] = xtr_dot;
  x_dot[37] = 0.0;
  x_dot[38] =
      1.0 / constants->TauEng *
      (((Tfac + constants->HPACC * 550.0 / constants->OMEGAT *
                    (0.1 * x[37] / constants->OMEGAT + 0.9)) +
        constants->GBXDAMP * x[37]) -
       fmin(x[38], constants->QEMax * atmos_rho / constants->rhoSLSTD * 2.0));
  /* Output data */
  /* Horsepower required */
  /* 'H60:108' HPreq=Qreq*constants.OMEGA/550.; */
  /* 'H60:109' HPPCT=100.*HPreq/constants.HPMAX; */
  /* Airspeed and accelerometers */
  /* 'H60:112' ax=Ftot(1)/(constants.MASS*constants.g); */
  /* 'H60:113' ay=Ftot(2)/(constants.MASS*constants.g); */
  /* 'H60:114' az=Ftot(3)/(constants.MASS*constants.g); */
  /* 'H60:116' Vg=sqrt(x_dot(10)^2+x_dot(11)^2)/1.688; */
  /* 'H60:117' Vgc=atan2d(x_dot(11),x_dot(10)); */
  /* 'H60:119' y=[Veq;ax;ay;az;HPPCT;Vg;Vgc]; */
  y[0] = Veq;
  y[1] = Ftot[0] / 15972.4;
  y[2] = Ftot[1] / 15972.4;
  y[3] = Ftot[2] / 15972.4;
  y[4] = 100.0 * (Tfac * 27.0 / 550.0) / 2825.0;
  y[5] = sqrt(x_dot[9] * x_dot[9] + x_dot[10] * x_dot[10]) / 1.688;
  y[6] = 57.29577951308232 * b_atan2(x_dot[10], x_dot[9]);
}

/*
 * function [x_dot,y]=H60(x,u,xdot,constants)
 */
void b_H60(const double x[39], const double u[4], const double xdot[39],
           const constants_Struct *constants, double x_dot[39], double y[7])
{
  static const double a[16] = {0.1, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0,
                               0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0538};
  __m128d r;
  __m128d r1;
  __m128d r2;
  __m128d r3;
  __m128d r4;
  double yr[133];
  double xr_dot[24];
  double ur[23];
  double dv[12];
  double rotor_if[8];
  double b_constants[4];
  double controls[4];
  double servos[4];
  double Fht[3];
  double Ftot[3];
  double Ftr[3];
  double Mf[3];
  double Mht[3];
  double Mtr[3];
  double Mvt[3];
  double a__4[3];
  double c_constants[3];
  double Qreq;
  double T;
  double Tfac;
  double Veq;
  double atmos_rho;
  double xedot_idx_0;
  double xtr_dot;
  int b_i;
  int i;
  /* Simulation of H-60 based on NASA CR 166309 */
  /* (https://ntrs.nasa.gov/citations/19840020737) */
  /* This the main executive, calls each of the sub-modules for trim and */
  /* initialization or numerical integration outside of Simulink */
  /*  Input: time, t */
  /*         aircraft state vector, x */
  /*         pilot control input (or pilot + AFCS), u */
  /*  Output: state derivative, x_dot */
  /* Partition state vector */
  /*  Fuselage states */
  /* 'H60:14' xf=x(SizeConstants.IDXF); */
  /* Rotor states */
  /* 'H60:16' xr=x(SizeConstants.IDXR); */
  /* Tail Rotor states */
  /* 'H60:18' xtr=x(SizeConstants.IDXTR); */
  /* Landing Gear States */
  /* xlg=x(constants.NFSTATES+constants.NRSTATES+constants.NTRSTATES+1:constants.NFSTATES+constants.NRSTATES+constants.NTRSTATES+constants.NLGSTATES);
   */
  /* Engine states */
  /* 'H60:22' xe=x(SizeConstants.IDXP); */
  /* Atmosphere model */
  /* -1*xf(12) = altitude in ft, 0 indicates Imperial units */
  /* 'H60:26' atmos = std_atmos(-xf(12),constants,0); */
  /* Standard atmosphere model */
  /*  Returns density (sl/ft^2) and speed of sound (ft/sec) as function of
   * altitude (ft) */
  /*  good up to 65,617 ft */
  /*  AJ if in MKS mode, convert altitude from m to ft */
  /* 'std_atmos:7' if IMKS */
  /* 'std_atmos:11' rho0=constants.rhoSLSTD; */
  /* 'std_atmos:12' Tfac = 1.0 - 0.703E-5 * alt; */
  Tfac = 1.0 - 7.03E-6 * -x[11];
  /* 'std_atmos:13' T    = 519.0 * Tfac; */
  T = 519.0 * Tfac;
  /* 'std_atmos:14' if alt > 36089.0 */
  if (-x[11] > 36089.0) {
    /* 'std_atmos:15' T = 390.0; */
    T = 390.0;
  }
  /* 'std_atmos:17' atmos.rho  = rho0 * (Tfac^4.14); */
  atmos_rho = constants->rhoSLSTD * rt_powd_snf(Tfac, 4.14);
  /* 'std_atmos:18' atmos.spsnd= sqrt(1.4*1716.3*T); */
  /*  AJ convert density and speed of sound to MKS if necessary */
  /* 'std_atmos:21' if IMKS */
  /* Control System Mixing */
  /* 'H60:29' controls=H60_mixing(u(1:4),constants); */
  /* Control mixing module - converts pilot + AFCS controls to control surface
   * deflections */
  /*                 Models mechanical mixing unit of UH-60 */
  /* Convert to inches */
  /* 'H60_mixing:9' uin=diag([0.1 0.1 0.1 5.38/100.])*u(1:4); */
  /* Mixer input */
  /* 'H60_mixing:12' umix=constants.LNKGAIN*uin; */
  /* 'H60_mixing:14' servos=constants.MIXGAIN*umix; */
  memset(&servos[0], 0, sizeof(double) << 2);
  for (i = 0; i < 4; i++) {
    r = _mm_loadu_pd(&servos[0]);
    b_i = i << 2;
    r1 = _mm_set1_pd(u[i]);
    _mm_storeu_pd(&servos[0],
                  _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&a[b_i]), r1)));
    r = _mm_loadu_pd(&servos[2]);
    _mm_storeu_pd(&servos[2],
                  _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&a[b_i + 2]), r1)));
  }
  memset(&b_constants[0], 0, sizeof(double) << 2);
  for (i = 0; i < 4; i++) {
    r = _mm_loadu_pd(&b_constants[0]);
    b_i = i << 2;
    r1 = _mm_set1_pd(servos[i]);
    _mm_storeu_pd(
        &b_constants[0],
        _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->LNKGAIN[b_i]), r1)));
    r = _mm_loadu_pd(&b_constants[2]);
    _mm_storeu_pd(
        &b_constants[2],
        _mm_add_pd(r,
                   _mm_mul_pd(_mm_loadu_pd(&constants->LNKGAIN[b_i + 2]), r1)));
  }
  memset(&servos[0], 0, sizeof(double) << 2);
  /* 'H60_mixing:16' control=zeros(4,1); */
  for (i = 0; i < 4; i++) {
    r = _mm_loadu_pd(&servos[0]);
    b_i = i << 2;
    r1 = _mm_set1_pd(b_constants[i]);
    _mm_storeu_pd(
        &servos[0],
        _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->MIXGAIN[b_i]), r1)));
    r = _mm_loadu_pd(&servos[2]);
    _mm_storeu_pd(
        &servos[2],
        _mm_add_pd(r,
                   _mm_mul_pd(_mm_loadu_pd(&constants->MIXGAIN[b_i + 2]), r1)));
    controls[i] = 0.0;
  }
  /* 'H60_mixing:17'
   * control(1:3)=constants.SWASHGAIN*servos(1:3)+constants.SWASHBIAS; */
  Tfac = servos[0];
  Qreq = servos[1];
  xedot_idx_0 = servos[2];
  r = _mm_loadu_pd(&constants->SWASHGAIN[0]);
  r1 = _mm_mul_pd(r, _mm_set1_pd(Tfac));
  r = _mm_loadu_pd(&constants->SWASHGAIN[3]);
  r = _mm_mul_pd(r, _mm_set1_pd(Qreq));
  r1 = _mm_add_pd(r1, r);
  r = _mm_loadu_pd(&constants->SWASHGAIN[6]);
  r = _mm_mul_pd(r, _mm_set1_pd(xedot_idx_0));
  r = _mm_add_pd(r1, r);
  r1 = _mm_loadu_pd(&constants->SWASHBIAS[0]);
  r = _mm_add_pd(r, r1);
  _mm_storeu_pd(&controls[0], r);
  controls[2] =
      ((constants->SWASHGAIN[2] * Tfac + constants->SWASHGAIN[5] * Qreq) +
       constants->SWASHGAIN[8] * xedot_idx_0) +
      constants->SWASHBIAS[2];
  /* Cyclic defined with opposite sign as used by rotor module */
  /* 'H60_mixing:19' control(1:2)=-control(1:2); */
  r = _mm_loadu_pd(&controls[0]);
  _mm_storeu_pd(&controls[0], _mm_mul_pd(r, _mm_set1_pd(-1.0)));
  /* 'H60_mixing:20' control(4)=constants.TRGAIN*servos(4)+constants.TRBIAS; */
  controls[3] = constants->TRGAIN * servos[3] + constants->TRBIAS;
  /* Wf=u(5); */
  /* Rotor interference module */
  /* 'H60:33' [rotor_if]=rotor_int_H60(x,0.,constants); */
  rotor_int_H60(x, constants, rotor_if);
  /* External velocities zeroed out for this application */
  /* 'H60:36' VextF=zeros(3,1); */
  /* 'H60:37' VextTR=zeros(3,1); */
  /* 'H60:38' VextHT=zeros(3,1); */
  /* 'H60:39' VextVT=zeros(3,1); */
  /* Fuselage Forces and Moments */
  /* 'H60:42' [Ff,Mf,~]=fuselage(xf,VextF,rotor_if,atmos,constants); */
  fuselage(&x[0], rotor_if, atmos_rho, constants, Ftot, Mf, c_constants);
  /* Tail Rotor Forces and Moments */
  /* 'H60:45'
   * [xtr_dot,Ftr,Mtr,Qtr,~]=tailrotor(xtr,xf,controls,VextTR,rotor_if,constants.OMEGAT,atmos,constants);
   */
  xtr_dot = tailrotor(x[36], &x[0], controls, rotor_if, constants->OMEGAT,
                      atmos_rho, constants, Ftr, Mtr, &Tfac, c_constants);
  /* Equiv Airspeed used in Stabilator Schedule */
  /* 'H60:48' Veq=sqrt( (x(1))^2 + (x(2))^2 + (x(3))^2
   * )/1.688*sqrt(atmos.rho/constants.rhoSLSTD); */
  Veq = sqrt((x[0] * x[0] + x[1] * x[1]) + x[2] * x[2]) / 1.688 *
        sqrt(atmos_rho / constants->rhoSLSTD);
  /* 'H60:49'
   * ayg=(xdot(2)-constants.g*sin(x(7))*cos(x(8))+x(6)*x(1)-x(4)*x(3))/constants.g;
   */
  /* 'H60:50' StabSet=constants.STABSET; */
  /* 'H60:51' StabInc=H60StabSched(u(3),Veq,ayg,x(5),StabSet); */
  /* Horizontal Tail */
  /* 'H60:54' [Fht,Mht,~]=tail(xf,VextHT,StabInc,rotor_if,1,atmos,constants); */
  /*  Stabilator Schedule and Controller   */
  /*  Scheduled is function of Airspeed and Collective. */
  /*  Dynamic feedback on ay and pitch rate (q) */
  /*  If StabSet != 0, then stabilator is fixed at value of StabSet (just use */
  /*  very small value of StabSet to effectively set it to 0.) */
  /* 'H60StabSched:11' if (StabSet==0) */
  if (constants->STABSET == 0.0) {
    /* 'H60StabSched:13' aylim=max(min(ayg,0.13),-0.13); */
    /* 'H60StabSched:15' stab_ay=-0.0433*min((Veq-30.),30.)*aylim; */
    /* 'H60StabSched:16' stab_q=0.16*180/pi*q; */
    /* 'H60StabSched:18' VSchedule=-0.1119*min(max(Veq-80.,0.),67.); */
    /* 'H60StabSched:19' PR50=min(max(Veq-30.,0.),50.); */
    /* 'H60StabSched:21' C1=min(max(70.-Coll,0.),20.); */
    /* 'H60StabSched:22' C2=min(max(50.-Coll,0.),50.); */
    /* 'H60StabSched:23' CollSchedule=-1.*PR50*(0.003286*(C1+C2)+0.67); */
    /* 'H60StabSched:25' IHT0=42.+CollSchedule+VSchedule+stab_q+stab_ay; */
    /* 'H60StabSched:27' StabInc=min(max(IHT0,-8.),39.); */
    Qreq = fmin(fmax((((-fmin(fmax(Veq - 30.0, 0.0), 50.0) *
                            (0.003286 * (fmin(fmax(70.0 - u[2], 0.0), 20.0) +
                                         fmin(fmax(50.0 - u[2], 0.0), 50.0)) +
                             0.67) +
                        42.0) +
                       -0.1119 * fmin(fmax(Veq - 80.0, 0.0), 67.0)) +
                      9.167324722093172 * x[4]) +
                         -0.0433 * fmin(Veq - 30.0, 30.0) *
                             fmax(fmin((((xdot[1] - constants->g * sin(x[6]) *
                                                        cos(x[7])) +
                                         x[0] * x[5]) -
                                        x[2] * x[3]) /
                                           constants->g,
                                       0.13),
                                  -0.13),
                     -8.0),
                39.0);
    /* Stabilator Incidence in degrees */
  } else {
    /* 'H60StabSched:29' else */
    /* 'H60StabSched:30' StabInc=StabSet; */
    Qreq = constants->STABSET;
  }
  tail(&x[0], Qreq, rotor_if, 1.0, atmos_rho, constants, Fht, Mht, c_constants);
  /* Vertical Tail */
  /* 'H60:57' [Fvt,Mvt,~]=tail(xf,VextVT,0.,rotor_if,2,atmos,constants); */
  tail(&x[0], 0.0, rotor_if, 2.0, atmos_rho, constants, c_constants, Mvt, a__4);
  /* Landing Gear */
  /* nTerrain = constants.terrain.ng; */
  /* zTerrain = constants.terrain.Z - (constants.terrain.ng(1)*xf(10) +
   * constants.terrain.ng(2)*xf(11))/constants.terrain.ng(3); */
  /* [xlg_dot,Flg,Mlg,~] = LandingGear(xlg,xf,zTerrain,nTerrain,constants); */
  /* Main Rotor */
  /* Define inouts to module */
  /* 'H60:66' ur=zeros(SizeConstants.NUROTOR,1); */
  memset(&ur[0], 0, 23U * sizeof(double));
  /* 'H60:67' ur(1)=controls(1)*pi/180.; */
  ur[0] = controls[0] * 3.141592653589793 / 180.0;
  /* 'H60:68' ur(2)=controls(2)*pi/180.; */
  ur[1] = controls[1] * 3.141592653589793 / 180.0;
  /* 'H60:69' ur(3)=controls(3)*pi/180.; */
  ur[2] = controls[2] * 3.141592653589793 / 180.0;
  /* 'H60:70' ur(4:15)=xf(1:12); */
  memcpy(&ur[3], &x[0], 12U * sizeof(double));
  /* 'H60:71' ur(16:21)=xdot(1:6); */
  for (i = 0; i < 6; i++) {
    ur[i + 15] = xdot[i];
  }
  /* Nominal rotorspeed */
  /* 'H60:73' ur(22)=constants.OMEGAT; */
  ur[21] = constants->OMEGAT;
  /* 'H60:74' ur(23)=xdot(SizeConstants.IDXP(1)); */
  ur[22] = xdot[37];
  /*  Run rotr module */
  /* 'H60:77' [xr_dot,yr] = GHrotor(xr,ur,atmos,constants); */
  GHrotor(&x[12], ur, atmos_rho, sqrt(2402.8199999999997 * T), constants,
          xr_dot, yr);
  /* 'H60:79' Fr=yr(1:3); */
  /* 'H60:80' Mr=yr(4:6); */
  /* 'H60:81' Qr=yr(12); */
  /*  Sum forces and Moments */
  /* Ftot=Fr+Ff+Fht+Fvt+Ftr+sum(Flg,2); */
  /* Mtot=Mr+Mf+Mht+Mvt+Mtr+sum(Mlg,2); */
  /* 'H60:86' Ftot=Fr+Ff+Fht+Fvt+Ftr; */
  r = _mm_loadu_pd(&yr[0]);
  r1 = _mm_loadu_pd(&Ftot[0]);
  r2 = _mm_loadu_pd(&Fht[0]);
  r3 = _mm_loadu_pd(&c_constants[0]);
  r4 = _mm_loadu_pd(&Ftr[0]);
  _mm_storeu_pd(
      &Ftot[0],
      _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3), r4));
  Ftot[2] = (((yr[2] + Ftot[2]) + Fht[2]) + c_constants[2]) + Ftr[2];
  /* 'H60:87' Mtot=Mr+Mf+Mht+Mvt+Mtr; */
  /* 'H60:88' Qreq=Qr+Qtr*constants.GEARTR; */
  Qreq = yr[11] + Tfac * constants->GEARTR;
  /* Equations of Motion */
  /* 'H60:91' xf_dot = eqnmot(xf,Ftot,Mtot,constants); */
  /* need to compute rsdot for engine module */
  /* 'H60:94' temp=constants.Tshaft*xdot(4:6); */
  /* 'H60:95' rsdot=temp(3); */
  /* Engine */
  /* [ xe_dot, ~, ~, ~, ~, ~, ~, ~ ] = t700eng(
   * xe,Wf,constants.Pstd,constants.Tstd,2,Qreq,rsdot,constants ); */
  /* 'H60:99' Neng = 2; */
  /* This can be set to 1 or zero to simulate engine failure */
  /* 'H60:100' xe_dot = SimpleEngine(xe,Qreq,rsdot,Neng,atmos,constants); */
  /* Total state derivative */
  /* x_dot=[xf_dot;xr_dot;xtr_dot;xlg_dot;xe_dot]; */
  /* 'H60:104' x_dot=[xf_dot;xr_dot;xtr_dot;xe_dot]; */
  /* coder.cstructname(constants, 'constants_Struct'); */
  /* Simple ideal engine model.  Engine torque = filtered required torque */
  /* Init state derivative */
  /* 'SimpleEngine:7' xedot = zeros(SizeConstants.NPSTATES,1); */
  /* 'SimpleEngine:9' Omega = xe(1); */
  /* 'SimpleEngine:10' QE = xe(2); */
  /* Accessory Torque Required */
  /* 'SimpleEngine:13'
   * Qacc=constants.HPACC*550./constants.OMEGAT*(0.9+0.1*xe(1)/constants.OMEGAT);
   */
  /* MAke engine torque = to required torque with a filter */
  /* 'SimpleEngine:16' QEreq = Qreq+Qacc+constants.GBXDAMP*Omega; */
  Tfac = (Qreq + constants->HPACC * 550.0 / constants->OMEGAT *
                     (0.1 * x[37] / constants->OMEGAT + 0.9)) +
         constants->GBXDAMP * x[37];
  /* 'SimpleEngine:18' Qgbx = QEreq - QE; */
  /* Equivalent Inertial Load */
  /* 'SimpleEngine:21'
   * FacIbx=constants.JTR+constants.JAC+constants.JENG*Neng+constants.JMROT; */
  /* Max torque */
  /* 'SimpleEngine:24' QEMax = constants.QEMax*atmos.rho/constants.rhoSLSTD; */
  /* State equations for Omega dot and Q dot */
  /* 'SimpleEngine:27' if (Neng > 0) */
  /* 'SimpleEngine:28' if (constants.IDEALENG == 1) */
  if (constants->IDEALENG == 1.0) {
    /* 'SimpleEngine:29' xedot(1)=0.; */
    xedot_idx_0 = 0.0;
  } else {
    /* 'SimpleEngine:30' else */
    /* 'SimpleEngine:31'
     * xedot(1)=(rsdot-Qgbx/constants.JGBX)/(1.+FacIbx/constants.JGBX); */
    memset(&c_constants[0], 0, 3U * sizeof(double));
    r = _mm_loadu_pd(&c_constants[0]);
    _mm_storeu_pd(&c_constants[0],
                  _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[0]),
                                           _mm_set1_pd(xdot[3]))));
    c_constants[2] += constants->Tshaft[2] * xdot[3];
    r = _mm_loadu_pd(&c_constants[0]);
    _mm_storeu_pd(&c_constants[0],
                  _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[3]),
                                           _mm_set1_pd(xdot[4]))));
    c_constants[2] += xdot[4] * constants->Tshaft[5];
    r = _mm_loadu_pd(&c_constants[0]);
    _mm_storeu_pd(&c_constants[0],
                  _mm_add_pd(r, _mm_mul_pd(_mm_loadu_pd(&constants->Tshaft[6]),
                                           _mm_set1_pd(xdot[5]))));
    c_constants[2] += xdot[5] * constants->Tshaft[8];
    xedot_idx_0 =
        (c_constants[2] - (Tfac - x[38]) / constants->JGBX) /
        ((((constants->JTR + constants->JAC) + constants->JENG * 2.0) +
          constants->JMROT) /
             constants->JGBX +
         1.0);
  }
  /* 'SimpleEngine:33' xedot(2) = 1./constants.TauEng*(QEreq -
   * min(QE,QEMax*Neng)); */
  r = _mm_loadu_pd(&yr[3]);
  r1 = _mm_loadu_pd(&Mf[0]);
  r2 = _mm_loadu_pd(&Mht[0]);
  r3 = _mm_loadu_pd(&Mvt[0]);
  r4 = _mm_loadu_pd(&Mtr[0]);
  _mm_storeu_pd(
      &Mf[0],
      _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd(r, r1), r2), r3), r4));
  Mf[2] = (((Mf[2] + yr[5]) + Mht[2]) + Mvt[2]) + Mtr[2];
  eqnmot(&x[0], Ftot, Mf, constants->g, constants->MASS, constants->IX,
         constants->IY, constants->IZ, constants->IXZ, dv);
  memcpy(&x_dot[0], &dv[0], 12U * sizeof(double));
  memcpy(&x_dot[12], &xr_dot[0], 24U * sizeof(double));
  x_dot[36] = xtr_dot;
  x_dot[37] = xedot_idx_0;
  x_dot[38] = 1.0 / constants->TauEng *
              (Tfac - fmin(x[38], constants->QEMax * atmos_rho /
                                      constants->rhoSLSTD * 2.0));
  /* Output data */
  /* Horsepower required */
  /* 'H60:108' HPreq=Qreq*constants.OMEGA/550.; */
  /* 'H60:109' HPPCT=100.*HPreq/constants.HPMAX; */
  /* Airspeed and accelerometers */
  /* 'H60:112' ax=Ftot(1)/(constants.MASS*constants.g); */
  /* 'H60:113' ay=Ftot(2)/(constants.MASS*constants.g); */
  /* 'H60:114' az=Ftot(3)/(constants.MASS*constants.g); */
  /* 'H60:116' Vg=sqrt(x_dot(10)^2+x_dot(11)^2)/1.688; */
  /* 'H60:117' Vgc=atan2d(x_dot(11),x_dot(10)); */
  /* 'H60:119' y=[Veq;ax;ay;az;HPPCT;Vg;Vgc]; */
  y[0] = Veq;
  Tfac = constants->MASS * constants->g;
  y[1] = Ftot[0] / Tfac;
  y[2] = Ftot[1] / Tfac;
  y[3] = Ftot[2] / Tfac;
  y[4] = 100.0 * (Qreq * constants->OMEGA / 550.0) / constants->HPMAX;
  y[5] = sqrt(x_dot[9] * x_dot[9] + x_dot[10] * x_dot[10]) / 1.688;
  y[6] = 57.29577951308232 * b_atan2(x_dot[10], x_dot[9]);
}

/* End of code generation (H60.c) */
