/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * tail.c
 *
 * Code generation for function 'tail'
 *
 */

/* Include files */
#include "tail.h"
#include "H60Sim_types.h"
#include "atan2.h"
#include "rt_nonfinite.h"
#include "table_lookup.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * function [Ft,Mt,ptNED]=tail(xf,Vext,elev,rotor_if,idxtail,atmos,constants)
 */
void tail(const double xf[12], double elev, const double rotor_if[8],
          double idxtail, double atmos_rho, const constants_Struct *constants,
          double Ft[3], double Mt[3], double ptNED[3])
{
  __m128d r;
  __m128d r1;
  __m128d r2;
  double b_constants[25];
  double c_constants[25];
  double T[9];
  double TNED2body[9];
  double b_cb[9];
  double Vxz;
  double cb;
  double cphi;
  double cpsi;
  double cthe;
  double d;
  double epsilon;
  double qlossfac;
  double sigma;
  double sphi;
  double spsi;
  double sthe;
  double xtail;
  double ytail;
  double ztail;
  int constants_tmp;
  int i;
  int i1;
  /* Empennage Aerodynamics Model */
  /* Inputs: Fuselage state, xf */
  /*         External Velocities from rotor interference or external gusts, Vext
   */
  /*         Elevator control surface delfection, elev */
  /*         rotor_if: Rotor interference - rotor_if(1:3) = [Vz, Vx, qloss]'; */
  /*         idxtail (index indicationg which tail surface properties to use. */
  /*         Vext (in body frame now) */
  /*         Constants (parameter) */
  /* 'tail:14' RHO=atmos.rho; */
  /* 'tail:15' D2R=constants.d2r; */
  /* 'tail:16' R2D=constants.r2d; */
  /* 'tail:18' xtail=-(constants.FSTAIL(idxtail)-constants.FSCG)/12.; */
  xtail = -(constants->FSTAIL[(int)idxtail - 1] - constants->FSCG) / 12.0;
  /* 'tail:19' ytail=(constants.BLTAIL(idxtail)-constants.BLCG)/12.; */
  ytail = (constants->BLTAIL[(int)idxtail - 1] - constants->BLCG) / 12.0;
  /* 'tail:20' ztail=-(constants.WLTAIL(idxtail)-constants.WLCG)/12.; */
  ztail = -(constants->WLTAIL[(int)idxtail - 1] - constants->WLCG) / 12.0;
  /* 'tail:22' if(isempty(idxtail)) */
  /* Euler angles */
  /* 'tail:27' sphi=sin(xf(7)); */
  sphi = sin(xf[6]);
  /* 'tail:28' cphi=cos(xf(7)); */
  cphi = cos(xf[6]);
  /* 'tail:29' sthe=sin(xf(8)); */
  sthe = sin(xf[7]);
  /* 'tail:30' cthe=cos(xf(8)); */
  cthe = cos(xf[7]);
  /* 'tail:31' spsi=sin(xf(9)); */
  spsi = sin(xf[8]);
  /* 'tail:32' cpsi=cos(xf(9)); */
  cpsi = cos(xf[8]);
  /* 'tail:33' TNED2body=[            cthe*cpsi               cthe*spsi -sthe;
   * ... */
  /* 'tail:34'             (sphi*sthe*cpsi-cphi*spsi) (sphi*sthe*spsi+cphi*cpsi)
   * sphi*cthe; ... */
  /* 'tail:35'             (cphi*sthe*cpsi+sphi*spsi) (cphi*sthe*spsi-sphi*cpsi)
   * cphi*cthe]; */
  TNED2body[0] = cthe * cpsi;
  TNED2body[3] = cthe * spsi;
  TNED2body[6] = -sthe;
  cb = sphi * sthe;
  TNED2body[1] = cb * cpsi - cphi * spsi;
  TNED2body[4] = cb * spsi + cphi * cpsi;
  TNED2body[7] = sphi * cthe;
  Vxz = cphi * sthe;
  TNED2body[2] = Vxz * cpsi + sphi * spsi;
  TNED2body[5] = Vxz * spsi - sphi * cpsi;
  TNED2body[8] = cphi * cthe;
  /* 'tail:36' Vextb=TNED2body*Vext; */
  memset(&Mt[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&TNED2body[0]);
  r1 = _mm_loadu_pd(&Mt[0]);
  r2 = _mm_set1_pd(0.0);
  _mm_storeu_pd(&Mt[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Mt[2] += TNED2body[2] * 0.0;
  r = _mm_loadu_pd(&TNED2body[3]);
  r1 = _mm_loadu_pd(&Mt[0]);
  _mm_storeu_pd(&Mt[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Mt[2] += TNED2body[5] * 0.0;
  r = _mm_loadu_pd(&TNED2body[6]);
  r1 = _mm_loadu_pd(&Mt[0]);
  _mm_storeu_pd(&Mt[0], _mm_add_pd(r1, _mm_mul_pd(r, r2)));
  Mt[2] += TNED2body[8] * 0.0;
  /* 'tail:38' if (idxtail==1) */
  if (idxtail == 1.0) {
    /* 'tail:39' qlossfac=sqrt(rotor_if(5)); */
    qlossfac = sqrt(rotor_if[4]);
    /* 'tail:40' epsilon=rotor_if(7); */
    epsilon = rotor_if[6];
    /* 'tail:41' sigma=0.; */
    sigma = 0.0;
  } else {
    /* 'tail:42' elseif (idxtail==2) */
    /* 'tail:43' qlossfac=sqrt(rotor_if(6)); */
    qlossfac = sqrt(rotor_if[5]);
    /* 'tail:44' epsilon=0.; */
    epsilon = 0.0;
    /* 'tail:45' sigma=rotor_if(8); */
    sigma = rotor_if[7];
  }
  /* Local velcities */
  /* 'tail:53' u=(xf(1))*qlossfac+Vextb(1)+rotor_if(4); */
  /* 'tail:54' v=(xf(2)-D2R*xf(1)*sigma)+Vextb(2); */
  /* 'tail:55' w=(xf(3)-D2R*xf(1)*epsilon)*qlossfac+Vextb(3)+rotor_if(3); */
  /* 'tail:56' p=xf(4); */
  /* 'tail:57' q=xf(5); */
  /* 'tail:58' r=xf(6); */
  /* 'tail:60' ublocal=u+(q)*ztail-(r)*ytail; */
  /* 'tail:61' vblocal=v-(p)*ztail+(r)*xtail; */
  /* 'tail:62' wblocal=w+(p)*ytail-(q)*xtail; */
  /* ITAIL = Fixed Pitch Incidence */
  /* inc_con = Incidence set by controller for moving stabilizer. */
  /* PHITAIL = Roll Incidence (cant), = +/- 90 for vertical tail */
  /* IF constants.CLELEV = 0. then elev control incidence */
  /* 'tail:68' if (constants.CLELEV(idxtail) == 0.) */
  d = constants->CLELEV[(int)idxtail - 1];
  if (d == 0.0) {
    /* 'tail:69' cthe=cos((constants.ITAIL(idxtail)+elev)*D2R); */
    cpsi = (constants->ITAIL[(int)idxtail - 1] + elev) * constants->d2r;
    cthe = cos(cpsi);
    /* 'tail:70' sthe=sin((constants.ITAIL(idxtail)+elev)*D2R); */
    sthe = sin(cpsi);
  } else {
    /* 'tail:71' else */
    /* 'tail:72' cthe=cos(constants.ITAIL(idxtail)*D2R); */
    cb = constants->ITAIL[(int)idxtail - 1] * constants->d2r;
    cthe = cos(cb);
    /* 'tail:73' sthe=sin(constants.ITAIL(idxtail)*D2R); */
    sthe = sin(cb);
  }
  /* 'tail:75' cphi=cos(constants.PHITAIL(idxtail)*D2R); */
  Vxz = constants->PHITAIL[(int)idxtail - 1] * constants->d2r;
  cphi = cos(Vxz);
  /* 'tail:76' sphi=sin(constants.PHITAIL(idxtail)*D2R); */
  sphi = sin(Vxz);
  /* 'tail:77' T=[cthe sthe*sphi -sthe*cphi; 0 cphi sphi; sthe -sphi*cthe
   * cphi*cthe]; */
  T[0] = cthe;
  T[3] = sthe * sphi;
  T[6] = -sthe * cphi;
  T[1] = 0.0;
  T[4] = cphi;
  T[7] = sphi;
  T[2] = sthe;
  T[5] = -sphi * cthe;
  T[8] = cphi * cthe;
  /* Transfrom veclocities to orientation of tail */
  /* 'tail:81' temp=T*[ublocal;vblocal;wblocal]; */
  spsi = (((xf[0] * qlossfac + Mt[0]) + rotor_if[3]) + xf[4] * ztail) -
         xf[5] * ytail;
  Vxz = constants->d2r * xf[0];
  cb = (((xf[1] - Vxz * sigma) + Mt[1]) - xf[3] * ztail) + xf[5] * xtail;
  cpsi = ((((xf[2] - Vxz * epsilon) * qlossfac + Mt[2]) + rotor_if[2]) +
          xf[3] * ytail) -
         xf[4] * xtail;
  memset(&Ft[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&T[0]);
  r1 = _mm_loadu_pd(&Ft[0]);
  _mm_storeu_pd(&Ft[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(spsi))));
  Ft[2] += sthe * spsi;
  r = _mm_loadu_pd(&T[3]);
  r1 = _mm_loadu_pd(&Ft[0]);
  _mm_storeu_pd(&Ft[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(cb))));
  Ft[2] += T[5] * cb;
  r = _mm_loadu_pd(&T[6]);
  r1 = _mm_loadu_pd(&Ft[0]);
  _mm_storeu_pd(&Ft[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(cpsi))));
  Ft[2] += T[8] * cpsi;
  /* 'tail:82' ut=temp(1); */
  /* 'tail:83' vt=temp(2); */
  /* 'tail:84' wt=temp(3); */
  /* 'tail:85' Vtot2=ut^2+vt^2+wt^2; */
  cb = Ft[0] * Ft[0];
  spsi = Ft[2] * Ft[2];
  epsilon = (cb + Ft[1] * Ft[1]) + spsi;
  /* 'tail:86' Vtot=sqrt(Vtot2); */
  cpsi = sqrt(epsilon);
  /* 'tail:87' Vxz=sqrt(ut^2+wt^2); */
  Vxz = sqrt(cb + spsi);
  /* 'tail:88' qt=0.5*RHO*Vtot2; */
  /* Angle of attack and sideslip angle of tail */
  /* 'tail:91' alphat=atan2(wt,ut)*R2D; */
  qlossfac = b_atan2(Ft[2], Ft[0]) * constants->r2d;
  /* 'tail:92' sa=wt/Vxz; */
  sphi = Ft[2] / Vxz;
  /* 'tail:93' ca=ut/Vxz; */
  cphi = Ft[0] / Vxz;
  /* 'tail:94' sb=vt/Vtot; */
  sigma = Ft[1] / cpsi;
  /* 'tail:95' cb=Vxz/Vtot; */
  cb = Vxz / cpsi;
  /* Lift and drag coefficients */
  /* 'tail:98'
   * CLt=table_lookup(constants.ALTAIL(idxtail,:),constants.CLTAIL(idxtail,:),alphat)+constants.CLELEV(idxtail)*elev;
   */
  for (i = 0; i < 25; i++) {
    constants_tmp = ((int)idxtail + (i << 1)) - 1;
    b_constants[i] = constants->ALTAIL[constants_tmp];
    c_constants[i] = constants->CLTAIL[constants_tmp];
  }
  spsi = b_table_lookup(b_constants, c_constants, qlossfac) + d * elev;
  /* 'tail:99'
   * CDt=table_lookup(constants.ALTAIL(idxtail,:),constants.CDTAIL(idxtail,:),alphat);
   */
  for (i = 0; i < 25; i++) {
    constants_tmp = ((int)idxtail + (i << 1)) - 1;
    b_constants[i] = constants->ALTAIL[constants_tmp];
    c_constants[i] = constants->CDTAIL[constants_tmp];
  }
  /* 'tail:100' Lift=qt*constants.STAIL(idxtail)*CLt; */
  /* 'tail:101' Drag=qt*constants.STAIL(idxtail)*CDt; */
  /* 'tail:103' Tw2t=[cb*ca -sb -cb*sa; sb*ca cb -sb*sa; sa 0. ca]; */
  /* 'tail:105' temp=T'*Tw2t*[-Drag;0.;-Lift]; */
  b_cb[0] = cb * cphi;
  b_cb[3] = -sigma;
  b_cb[6] = -cb * sphi;
  b_cb[1] = sigma * cphi;
  b_cb[4] = cb;
  b_cb[7] = -sigma * sphi;
  b_cb[2] = sphi;
  b_cb[5] = 0.0;
  b_cb[8] = cphi;
  cpsi = 0.5 * atmos_rho * epsilon * constants->STAIL[(int)idxtail - 1];
  Mt[0] = -(cpsi * b_table_lookup(b_constants, c_constants, qlossfac));
  Mt[1] = 0.0;
  Mt[2] = -(cpsi * spsi);
  memset(&Ft[0], 0, 3U * sizeof(double));
  for (i = 0; i < 3; i++) {
    cpsi = b_cb[3 * i];
    cb = b_cb[3 * i + 1];
    spsi = b_cb[3 * i + 2];
    Vxz = Mt[i];
    for (i1 = 0; i1 < 3; i1++) {
      Ft[i1] +=
          ((T[3 * i1] * cpsi + T[3 * i1 + 1] * cb) + T[3 * i1 + 2] * spsi) *
          Vxz;
    }
  }
  /* Forces and moments at aircraft CG */
  /* 'tail:108' Ft=temp; */
  /* 'tail:109' Mt=[0. -ztail ytail; ztail 0. -xtail;-ytail xtail 0.]*Ft; */
  T[0] = 0.0;
  T[3] = -ztail;
  T[6] = ytail;
  T[1] = ztail;
  T[4] = 0.0;
  T[7] = -xtail;
  T[2] = -ytail;
  T[5] = xtail;
  T[8] = 0.0;
  memset(&Mt[0], 0, 3U * sizeof(double));
  /* 'tail:111' ptNED=xf(10:12)+TNED2body'*[xtail;ytail;ztail]; */
  cpsi = Mt[0];
  cb = Mt[1];
  spsi = Mt[2];
  for (i = 0; i < 3; i++) {
    int Mt_tmp;
    Vxz = Ft[i];
    cpsi += T[3 * i] * Vxz;
    constants_tmp = 3 * i + 1;
    cb += T[constants_tmp] * Vxz;
    Mt_tmp = 3 * i + 2;
    spsi += T[Mt_tmp] * Vxz;
    ptNED[i] = xf[i + 9] +
               ((TNED2body[3 * i] * xtail + TNED2body[constants_tmp] * ytail) +
                TNED2body[Mt_tmp] * ztail);
  }
  Mt[2] = spsi;
  Mt[1] = cb;
  Mt[0] = cpsi;
}

/* End of code generation (tail.c) */
