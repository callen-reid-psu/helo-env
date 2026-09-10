/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * rotor_int_H60.c
 *
 * Code generation for function 'rotor_int_H60'
 *
 */

/* Include files */
#include "rotor_int_H60.h"
#include "H60Sim_types.h"
#include "atan2.h"
#include "interp2.h"
#include "rt_nonfinite.h"
#include "table_lookup.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * function [rotor_if]=rotor_int_H60(x,cg,constants)
 */
void rotor_int_H60(const double x[39], const constants_Struct *constants,
                   double rotor_if[8])
{
  __m128d r;
  __m128d r1;
  double Tshaft_tmp[9];
  double temp[3];
  double A1F;
  double A1Ftab;
  double alpha;
  double beta;
  double chitab;
  int done;
  int k;
  /* This module is used to calculate rotor intereference effects - the effect
   * of the rotor */
  /*  downwash on the fuselage and tail.  Based on the model used in the UH-60
   * GenHel simulation. */
  /*  Also calculates dynamic pressure drop on ht and vt due to blockage of
   * fuselage. */
  /* Inputs:  u,v,w velocities */
  /*          Rotor Downwash, lambda0 */
  /*          Rotor long. flapping angle, beta1c */
  /*          Rotor speed, omega */
  /* Outputs: Rotor downwash on fuselage, rotor_if(1) */
  /*          Rotor in-plane wash on fuselage, rotor_if(2) */
  /*          Rotor downwash on tail, rotor_if(3) */
  /*          Rotor inplane wash on tail, rotor_if(4) */
  /*          Q loss at horz tail., rotor_if(5) */
  /*          Q loss at vert tail., rotor_if(6) */
  /*          Fuselage Downwash at tail, rotor_if(7)  */
  /*          Fuselage Sidewash at tail, rotor_if(8) */
  /* 'rotor_int_H60:21' RADIUS=constants.R; */
  /* 'rotor_int_H60:22' ITHSH=constants.ITHSH; */
  /* 'rotor_int_H60:23' IPHSH=constants.IPHSH; */
  /* 'rotor_int_H60:24' D2R=constants.D2R; */
  /* 'rotor_int_H60:25' R2D=constants.R2D; */
  /* 'rotor_int_H60:26' omega=constants.OMEGA; */
  /* Body to shaft coordinate transform */
  /* 'rotor_int_H60:28' Tshaft=[cos(ITHSH*D2R) 0. -sin(ITHSH*D2R); ... */
  /* 'rotor_int_H60:29'         sin(ITHSH*D2R)*sin(IPHSH*D2R) cos(IPHSH*D2R)
   * cos(ITHSH*D2R)*sin(IPHSH*D2R); ... */
  /* 'rotor_int_H60:30'         sin(ITHSH*D2R)*cos(IPHSH*D2R) -sin(IPHSH*D2R)
   * cos(ITHSH*D2R)*cos(IPHSH*D2R)]; */
  A1Ftab = constants->ITHSH * constants->D2R;
  beta = sin(A1Ftab);
  chitab = cos(A1Ftab);
  A1Ftab = constants->IPHSH * constants->D2R;
  alpha = sin(A1Ftab);
  A1Ftab = cos(A1Ftab);
  /* 'rotor_int_H60:32' u=x(1); */
  /* 'rotor_int_H60:33' v=x(2); */
  /* 'rotor_int_H60:34' w=x(3); */
  /* 'rotor_int_H60:35' beta1c=x(15); */
  /* 'rotor_int_H60:36' A1F=-beta1c*R2D; */
  A1F = -x[14] * constants->R2D;
  /* 'rotor_int_H60:37' lambda0=x(29); */
  /* 'rotor_int_H60:38' Gif=1-cg; */
  /* 'rotor_int_H60:41' temp=Tshaft*[u;v;w]; */
  Tshaft_tmp[0] = chitab;
  Tshaft_tmp[3] = 0.0;
  Tshaft_tmp[6] = -beta;
  Tshaft_tmp[1] = beta * alpha;
  Tshaft_tmp[4] = A1Ftab;
  Tshaft_tmp[7] = chitab * alpha;
  Tshaft_tmp[2] = beta * A1Ftab;
  Tshaft_tmp[5] = -alpha;
  Tshaft_tmp[8] = chitab * A1Ftab;
  memset(&temp[0], 0, 3U * sizeof(double));
  r = _mm_loadu_pd(&Tshaft_tmp[0]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[0]))));
  temp[2] += x[0] * Tshaft_tmp[2];
  r = _mm_loadu_pd(&Tshaft_tmp[3]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[1]))));
  temp[2] += -alpha * x[1];
  r = _mm_loadu_pd(&Tshaft_tmp[6]);
  r1 = _mm_loadu_pd(&temp[0]);
  _mm_storeu_pd(&temp[0], _mm_add_pd(r1, _mm_mul_pd(r, _mm_set1_pd(x[2]))));
  temp[2] += x[2] * Tshaft_tmp[8];
  /* 'rotor_int_H60:42' us=temp(1); */
  /* 'rotor_int_H60:43' vs=temp(2); */
  /* 'rotor_int_H60:44' ws=temp(3); */
  /* 'rotor_int_H60:45' muxs=us/(omega*RADIUS); */
  /* 'rotor_int_H60:46' muzs=ws/(omega*RADIUS); */
  /* 'rotor_int_H60:47' chi=R2D*atan2(muxs,abs(lambda0-muzs))+A1F; */
  /* 'rotor_int_H60:48' alpha=atan2(w,abs(u))*R2D; */
  alpha = b_atan2(x[2], fabs(x[0])) * constants->R2D;
  /* 'rotor_int_H60:49' beta=atan2(v,sqrt(u^2+w^2))*R2D; */
  beta = b_atan2(x[1], sqrt(x[0] * x[0] + x[2] * x[2])) * constants->R2D;
  /* 'rotor_int_H60:50' psif=-beta; */
  /* 'rotor_int_H60:52' chitab=min(max(chi,0.),100.); */
  A1Ftab = constants->OMEGA * constants->R;
  chitab = fmin(fmax(constants->R2D * b_atan2(temp[0] / A1Ftab,
                                              fabs(x[28] - temp[2] / A1Ftab)) +
                         A1F,
                     0.0),
                100.0);
  /* 'rotor_int_H60:53' A1Ftab=min(max(A1F,-6.),6.); */
  A1Ftab = fmin(fmax(A1F, -6.0), 6.0);
  /* 'rotor_int_H60:55'
   * ekxf=interp2(constants.chi_tab,constants.a1f_tab,constants.ekxf_tab,chitab,A1Ftab);
   */
  /* 'rotor_int_H60:56'
   * ekzf=interp2(constants.chi_tab,constants.a1f_tab,constants.ekzf_tab,chitab,A1Ftab);
   */
  /* 'rotor_int_H60:57'
   * ekxt=interp2(constants.chi_tab,constants.a1f_tab,constants.ekxt_tab,chitab,A1Ftab);
   */
  /* 'rotor_int_H60:58'
   * ekzt=interp2(constants.chi_tab,constants.a1f_tab,constants.ekzt_tab,chitab,A1Ftab);
   */
  /* 'rotor_int_H60:60' rotor_if=zeros(8,1); */
  /* 'rotor_int_H60:61' rotor_if(1)=-Gif*ekzf*lambda0*omega*RADIUS; */
  rotor_if[0] = -interp2(constants->chi_tab, constants->a1f_tab,
                         constants->ekzf_tab, chitab, A1Ftab) *
                x[28] * constants->OMEGA * constants->R;
  /* 'rotor_int_H60:62' rotor_if(2)=Gif*ekxf*lambda0*omega*RADIUS; */
  rotor_if[1] = interp2(constants->chi_tab, constants->a1f_tab,
                        constants->ekxf_tab, chitab, A1Ftab) *
                x[28] * constants->OMEGA * constants->R;
  /* 'rotor_int_H60:63' rotor_if(3)=-Gif*ekzt*lambda0*omega*RADIUS; */
  rotor_if[2] = -interp2(constants->chi_tab, constants->a1f_tab,
                         constants->ekzt_tab, chitab, A1Ftab) *
                x[28] * constants->OMEGA * constants->R;
  /* 'rotor_int_H60:64' rotor_if(4)=Gif*ekxt*lambda0*omega*RADIUS; */
  rotor_if[3] = interp2(constants->chi_tab, constants->a1f_tab,
                        constants->ekxt_tab, chitab, A1Ftab) *
                x[28] * constants->OMEGA * constants->R;
  /* 'rotor_int_H60:65'
   * rotor_if(5)=table_lookup(constants.alpha_tab,constants.qlossht_tab,alpha);
   */
  /* This sub-module is used to do a simple 1-dimensional table look up */
  /* 'table_lookup:5' out=datout(1); */
  rotor_if[4] = constants->qlossht_tab[0];
  /* 'table_lookup:6' if (in<=datin(1)) */
  if (alpha <= constants->alpha_tab[0]) {
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
    /* 'table_lookup:13' ; */
    /* 'table_lookup:14' k=k+1; */
    k++;
    /* 'table_lookup:15' if (in<=datin(k)) */
    A1Ftab = constants->alpha_tab[k + 1];
    if (alpha <= A1Ftab) {
      /* 'table_lookup:15' ; */
      /* 'table_lookup:16'
       * out=datout(k-1)+(datout(k)-datout(k-1))/(datin(k)-datin(k-1))*(in-datin(k-1));
       */
      rotor_if[4] =
          constants->qlossht_tab[k] +
          (constants->qlossht_tab[k + 1] - constants->qlossht_tab[k]) /
              (A1Ftab - constants->alpha_tab[k]) *
              (alpha - constants->alpha_tab[k]);
      /* 'table_lookup:17' done=1; */
      done = 1;
    } else if (k + 2 >= 8) {
      /* 'table_lookup:18' elseif (k>=length(datin)) */
      /* 'table_lookup:18' ; */
      /* 'table_lookup:19' out=datout(k); */
      rotor_if[4] = constants->qlossht_tab[7];
      /* 'table_lookup:20' done=1; */
      done = 1;
    }
  }
  /* 'rotor_int_H60:66'
   * rotor_if(6)=table_lookup(constants.psivt_tab,constants.qlossvt_tab,psif);
   */
  rotor_if[5] =
      table_lookup(constants->psivt_tab, constants->qlossvt_tab, -beta);
  /* 'rotor_int_H60:67'
   * rotor_if(7)=table_lookup(constants.alphaeps_tab,constants.eps_tab,alpha);
   */
  rotor_if[6] =
      b_table_lookup(constants->alphaeps_tab, constants->eps_tab, alpha);
  /* 'rotor_int_H60:68'
   * rotor_if(8)=table_lookup(constants.psisig_tab,constants.sig_tab,psif); */
  rotor_if[7] =
      b_table_lookup(constants->psisig_tab, constants->sig_tab, -beta);
}

/* End of code generation (rotor_int_H60.c) */
