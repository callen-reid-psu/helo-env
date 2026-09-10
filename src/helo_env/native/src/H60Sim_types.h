/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * H60Sim_types.h
 *
 * Code generation for function 'InitFcnH60'
 *
 */

#ifndef H60SIM_TYPES_H
#define H60SIM_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_FlightConditions_Struct
#define typedef_FlightConditions_Struct
typedef struct {
  double VXTRIM;
  double VYTRIM;
  double VZTRIM;
  double PSIDTRIM;
  double PSITRIM;
  double ALTTRIM;
  double XNTRIM;
  double YETRIM;
} FlightConditions_Struct;
#endif /* typedef_FlightConditions_Struct */

#ifndef typedef_constants_Struct
#define typedef_constants_Struct
typedef struct {
  double d2r;
  double r2d;
  double D2R;
  double R2D;
  double g;
  double FtLb_s2Hp;
  double fps2kts;
  double kts2fps;
  double rhoSLSTD;
  double R;
  double NB;
  double OMEGA;
  double OMEGAT;
  double HOFFSET;
  double SPAR;
  double RSEG[10];
  double DELSEG[10];
  double DynTwistMode[10];
  double TauDT;
  double TWISTTABR[21];
  double TWISTTABTHET[21];
  double BTL;
  double MBETA;
  double IBETA;
  double WBLADE;
  double G;
  double ALD;
  double BLD;
  double CLD;
  double DLD;
  double RLD;
  double THETALDGEO;
  double ITHSH;
  double IPHSH;
  double Tshaft[9];
  double DELSP;
  double DELTA3;
  double CLAG;
  double KLAG;
  double ZETA0;
  double CFLAP;
  double KFLAP;
  double CHORDT;
  double CHORDR;
  double CHORD[10];
  double istart;
  double inflow;
  double CLR0UTAB[181];
  double AOAUTAB[181];
  double CLR0BTAB[363];
  double AOABTAB[33];
  double MACHTAB[11];
  double CDR0UTAB[181];
  double CDR0BTAB[363];
  double ACL1;
  double ACL2;
  double ACL3;
  double ACL4;
  double DCDMR;
  double KR;
  double KRsched[4];
  double KRVsched[4];
  double FSCG;
  double WLCG;
  double BLCG;
  double FSMR;
  double WLMR;
  double BLMR;
  double WEIGHT;
  double WEIGHTNR;
  double MASS;
  double IX;
  double IY;
  double IZ;
  double IXZ;
  double FSCGB;
  double WLCGB;
  double BLCGB;
  double IGNDEFF;
  double KGE1;
  double KGE2;
  double FUSEAOA[25];
  double FUSEBETA[25];
  double FUSEABETA[13];
  double FUSEDA[25];
  double FUSEDB[13];
  double FUSEYB[25];
  double FUSELA[25];
  double FUSELB[25];
  double FUSERB[25];
  double FUSEMA[25];
  double FUSEMB[13];
  double FUSENB[25];
  double FSfus;
  double BLfus;
  double WLfus;
  double FSTR;
  double BLTR;
  double WLTR;
  double CantTR;
  double OmegaTR;
  double CHRDTR;
  double RTR;
  double BTLTR;
  double a0TR;
  double IbTR;
  double twistTR;
  double BIASTR;
  double D0TR;
  double D1TR;
  double D2TR;
  double CDTR;
  double TD3TR;
  double DELTTR;
  double BVTTR;
  double BVTTR1;
  double VBVTTR;
  double STAIL[2];
  double PHITAIL[2];
  double ITAIL[2];
  double FSTAIL[2];
  double BLTAIL[2];
  double WLTAIL[2];
  double ALTAIL[50];
  double CLTAIL[50];
  double CDTAIL[50];
  double CLELEV[2];
  double STABSET;
  double LNKGAIN[16];
  double MIXGAIN[16];
  double TRGAIN;
  double TRBIAS;
  double SWASHGAIN[9];
  double SWASHBIAS[3];
  double a1f_tab[3];
  double chi_tab[11];
  double ekxf_tab[33];
  double ekzf_tab[33];
  double ekxt_tab[33];
  double ekzt_tab[33];
  double alpha_tab[8];
  double qlossht_tab[8];
  double psivt_tab[13];
  double qlossvt_tab[13];
  double alphaeps_tab[25];
  double eps_tab[25];
  double psisig_tab[25];
  double sig_tab[25];
  double HPMAX;
  double TauEng;
  double QEMax;
  double IDEALENG;
  double HPACC;
  double GEARENG;
  double GEARACC;
  double GEARTR;
  double JTR;
  double JAC;
  double JENG;
  double JMROT;
  double JGBX;
  double RPM2RPS;
  double GBXDAMP;
  double XSCALE[39];
  double DELCLIN[4];
  double DELXLIN[39];
  double xp;
  double yp;
  double zp;
  double GroundZ;
  double dt;
  double IFREEZE;
  double FP_ITMAX;
  double FPTOL;
  double NREVSTEP;
  double NREVCONV;
  double NREVAVERAGE;
  double TRIMSTATE[8];
  double TRIMCTRL[4];
  double TRIMTARG[12];
  double TRIMRELAX;
  double TRIMTOL;
  double TRIMITMAX;
  double TRIMJACTOL;
} constants_Struct;
#endif /* typedef_constants_Struct */

#endif
/* End of code generation (H60Sim_types.h) */
