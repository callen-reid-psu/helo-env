/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * eqnmot.c
 *
 * Code generation for function 'eqnmot'
 *
 */

/* Include files */
#include "eqnmot.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * function [xf_dot]  = eqnmot(xf,Ftot,Mtot,constants)
 */
void eqnmot(const double xf[12], const double Ftot[3], const double Mtot[3],
            double constants_g, double constants_MASS, double constants_IX,
            double constants_IY, double constants_IZ, double constants_IXZ,
            double xf_dot[12])
{
  double b_xf_dot_tmp;
  double cphi;
  double cpsi;
  double cthe;
  double gam;
  double sphi;
  double spsi;
  double sthe;
  double xf_dot_tmp;
  /* 'eqnmot:3' IX=constants.IX; */
  /* 'eqnmot:4' IY=constants.IY; */
  /* 'eqnmot:5' IZ=constants.IZ; */
  /* 'eqnmot:6' IXZ=constants.IXZ; */
  /* 'eqnmot:7' G=constants.g; */
  /* 'eqnmot:8' MASS=constants.MASS; */
  /* 'eqnmot:10' X=Ftot(1); */
  /* 'eqnmot:11' Y=Ftot(2); */
  /* 'eqnmot:12' Z=Ftot(3); */
  /* 'eqnmot:13' L=Mtot(1); */
  /* 'eqnmot:14' M=Mtot(2); */
  /* 'eqnmot:15' N=Mtot(3); */
  /* 'eqnmot:17' u=xf(1); */
  /* 'eqnmot:18' v=xf(2); */
  /* 'eqnmot:19' w=xf(3); */
  /* 'eqnmot:20' p=xf(4); */
  /* 'eqnmot:21' q=xf(5); */
  /* 'eqnmot:22' r=xf(6); */
  /* 'eqnmot:23' phi=xf(7); */
  /* 'eqnmot:24' theta=xf(8); */
  /* 'eqnmot:25' psi=xf(9); */
  /* 'eqnmot:28' cphi=cos(phi); */
  cphi = cos(xf[6]);
  /* 'eqnmot:29' sphi=sin(phi); */
  sphi = sin(xf[6]);
  /* 'eqnmot:30' cthe=cos(theta); */
  cthe = cos(xf[7]);
  /* 'eqnmot:31' sthe=sin(theta); */
  sthe = sin(xf[7]);
  /* 'eqnmot:32' cpsi=cos(psi); */
  cpsi = cos(xf[8]);
  /* 'eqnmot:33' spsi=sin(psi); */
  spsi = sin(xf[8]);
  /* 'eqnmot:35' xf_dot=zeros(SizeConstants.NFSTATES,1); */
  /* The following equations are given in Padfield pages 92 and 173-178 */
  /*  Calculate state derivatives */
  /* Velocities */
  /* udot eqn. */
  /* 'eqnmot:42' xf_dot(1)=X/MASS-G*sthe-q*w+r*v; */
  xf_dot[0] =
      ((Ftot[0] / constants_MASS - constants_g * sthe) - xf[2] * xf[4]) +
      xf[1] * xf[5];
  /* vdot eqn. */
  /* 'eqnmot:44' xf_dot(2)=Y/MASS+G*cthe*sphi-r*u+p*w; */
  xf_dot_tmp = constants_g * cthe;
  xf_dot[1] = ((Ftot[1] / constants_MASS + xf_dot_tmp * sphi) - xf[0] * xf[5]) +
              xf[2] * xf[3];
  /* wdot eqn. */
  /* 'eqnmot:46' xf_dot(3)=Z/MASS+G*cthe*cphi-p*v+q*u; */
  xf_dot[2] = ((Ftot[2] / constants_MASS + xf_dot_tmp * cphi) - xf[1] * xf[3]) +
              xf[0] * xf[4];
  /* Angular rates */
  /* 'eqnmot:49' gam=IX*IZ-IXZ^2; */
  xf_dot_tmp = constants_IXZ * constants_IXZ;
  gam = constants_IX * constants_IZ - xf_dot_tmp;
  /* pdot eqn. */
  /* 'eqnmot:51'
   * xf_dot(4)=(IZ*L+IXZ*N+IXZ*(IX-IY+IZ)*p*q-(IZ^2-IY*IZ+IXZ^2)*q*r)/gam; */
  b_xf_dot_tmp = constants_IXZ * ((constants_IX - constants_IY) + constants_IZ);
  xf_dot[3] = (((constants_IZ * Mtot[0] + constants_IXZ * Mtot[2]) +
                b_xf_dot_tmp * xf[3] * xf[4]) -
               ((constants_IZ * constants_IZ - constants_IY * constants_IZ) +
                xf_dot_tmp) *
                   xf[4] * xf[5]) /
              gam;
  /* qdot eqn. */
  /* 'eqnmot:53' xf_dot(5)=(M+(IZ-IX)*p*r-IXZ*(p^2-r^2))/IY; */
  xf_dot[4] = ((Mtot[1] + (constants_IZ - constants_IX) * xf[3] * xf[5]) -
               constants_IXZ * (xf[3] * xf[3] - xf[5] * xf[5])) /
              constants_IY;
  /* rdot eqn. */
  /* 'eqnmot:55'
   * xf_dot(6)=(IX*N+IXZ*L-IXZ*(IX-IY+IZ)*q*r+(IX^2-IX*IY+IXZ^2)*p*q)/gam; */
  xf_dot[5] = (((constants_IX * Mtot[2] + constants_IXZ * Mtot[0]) -
                b_xf_dot_tmp * xf[4] * xf[5]) +
               ((constants_IX * constants_IX - constants_IX * constants_IY) +
                xf_dot_tmp) *
                   xf[3] * xf[4]) /
              gam;
  /* Attitudes */
  /* phi dot eqn. */
  /* 'eqnmot:59' xf_dot(7)=p+q*sphi*sthe/cthe+r*cphi*sthe/cthe; */
  xf_dot_tmp = xf[4] * sphi;
  gam = xf[5] * cphi;
  xf_dot[6] = (xf[3] + xf_dot_tmp * sthe / cthe) + gam * sthe / cthe;
  /* theta dot eqn. */
  /* 'eqnmot:61' xf_dot(8)=q*cphi-r*sphi; */
  xf_dot[7] = xf[4] * cphi - xf[5] * sphi;
  /* psi dot eqn. */
  /* 'eqnmot:63' xf_dot(9)=q*sphi/cthe+r*cphi/cthe; */
  xf_dot[8] = xf_dot_tmp / cthe + gam / cthe;
  /* Position */
  /* 'eqnmot:66'
   * xf_dot(10)=u*cthe*cpsi+v*(sphi*sthe*cpsi-cphi*spsi)+w*(cphi*sthe*cpsi+sphi*spsi);
   */
  xf_dot_tmp = xf[0] * cthe;
  gam = sphi * sthe;
  b_xf_dot_tmp = cphi * sthe;
  xf_dot[9] = (xf_dot_tmp * cpsi + xf[1] * (gam * cpsi - cphi * spsi)) +
              xf[2] * (b_xf_dot_tmp * cpsi + sphi * spsi);
  /* 'eqnmot:67'
   * xf_dot(11)=u*cthe*spsi+v*(sphi*sthe*spsi+cphi*cpsi)+w*(cphi*sthe*spsi-sphi*cpsi);
   */
  xf_dot[10] = (xf_dot_tmp * spsi + xf[1] * (gam * spsi + cphi * cpsi)) +
               xf[2] * (b_xf_dot_tmp * spsi - sphi * cpsi);
  /* 'eqnmot:68' xf_dot(12)=-u*sthe    +v*sphi*cthe +w*cphi*cthe; */
  xf_dot[11] = (-xf[0] * sthe + xf[1] * sphi * cthe) + xf[2] * cphi * cthe;
}

/* End of code generation (eqnmot.c) */
