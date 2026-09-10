/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * InitFcnH60.c
 *
 * Code generation for function 'InitFcnH60'
 *
 */

/* Include files */
#include "InitFcnH60.h"
#include "H60Sim_types.h"
#include "RunRevs.h"
#include "StepH60.h"
#include "atan2.h"
#include "norm.h"
#include "pinv.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Definitions */
/*
 * function [x0,u0,xdot0,y0,itrim,constants] = InitFcnH60(FlightConditions)
 */
void InitFcnH60(FlightConditions_Struct *FlightConditions, double x0[39],
                double u0[4], double xdot0[39], double b_y0[7], double *itrim,
                constants_Struct *constants)
{
  static const double dv11[363] = {
      0.7014, 0.7014, 0.7014, 0.7014, 0.6904, 0.6859, 0.684,  0.673,  0.6678,
      0.6633, 0.6589, 0.63,   0.63,   0.63,   0.63,   0.63,   0.63,   0.63,
      0.63,   0.63,   0.63,   0.63,   0.5584, 0.5584, 0.5584, 0.5584, 0.5696,
      0.5741, 0.576,  0.587,  0.5922, 0.5967, 0.6011, 0.4869, 0.4869, 0.4869,
      0.4869, 0.5093, 0.5182, 0.522,  0.544,  0.5544, 0.5633, 0.5722, 0.4153,
      0.4153, 0.4153, 0.4153, 0.4489, 0.4624, 0.468,  0.501,  0.5167, 0.53,
      0.5433, 0.3438, 0.3438, 0.3438, 0.3438, 0.3885, 0.4065, 0.414,  0.458,
      0.4789, 0.4967, 0.5144, 0.2722, 0.2722, 0.2722, 0.2722, 0.3281, 0.3506,
      0.36,   0.415,  0.4411, 0.4633, 0.4856, 0.2007, 0.2007, 0.2007, 0.2007,
      0.2678, 0.2947, 0.3267, 0.372,  0.4033, 0.43,   0.4567, 0.1291, 0.1291,
      0.1291, 0.1291, 0.2074, 0.2388, 0.2887, 0.329,  0.3656, 0.3967, 0.4278,
      0.0576, 0.0576, 0.0576, 0.0576, 0.147,  0.1829, 0.246,  0.286,  0.3278,
      0.3633, 0.3989, 0.0174, 0.0174, 0.0174, 0.0174, 0.0225, 0.12,   0.191,
      0.243,  0.29,   0.33,   0.37,   0.0115, 0.0115, 0.0115, 0.0115, 0.0132,
      0.068,  0.127,  0.177,  0.225,  0.262,  0.297,  0.0082, 0.0082, 0.0082,
      0.0082, 0.0095, 0.0206, 0.07,   0.113,  0.16,   0.203,  0.248,  0.0078,
      0.0078, 0.0078, 0.0078, 0.0085, 0.0097, 0.026,  0.06,   0.1,    0.149,
      0.202,  0.0075, 0.0075, 0.0075, 0.0075, 0.008,  0.008,  0.0125, 0.03,
      0.065,  0.115,  0.152,  0.0075, 0.0075, 0.0075, 0.0075, 0.008,  0.0075,
      0.0085, 0.012,  0.028,  0.066,  0.117,  0.0075, 0.0075, 0.0075, 0.0075,
      0.008,  0.0075, 0.008,  0.008,  0.017,  0.05,   0.09,   0.008,  0.008,
      0.008,  0.008,  0.0082, 0.0075, 0.0075, 0.0105, 0.04,   0.08,   0.1175,
      0.0085, 0.0085, 0.0085, 0.0085, 0.0085, 0.008,  0.011,  0.036,  0.09,
      0.12,   0.1525, 0.009,  0.009,  0.009,  0.009,  0.0105, 0.011,  0.029,
      0.081,  0.128,  0.167,  0.203,  0.011,  0.011,  0.011,  0.011,  0.014,
      0.026,  0.0743, 0.126,  0.17,   0.21,   0.249,  0.017,  0.017,  0.017,
      0.017,  0.021,  0.08,   0.1247, 0.162,  0.225,  0.262,  0.298,  0.026,
      0.026,  0.026,  0.026,  0.0935, 0.153,  0.18,   0.238,  0.285,  0.3225,
      0.363,  0.145,  0.145,  0.145,  0.145,  0.1635, 0.2121, 0.232,  0.2816,
      0.3233, 0.3567, 0.3927, 0.2147, 0.2147, 0.2147, 0.2147, 0.2259, 0.2644,
      0.284,  0.3251, 0.3617, 0.3908, 0.4223, 0.274,  0.274,  0.274,  0.274,
      0.2836, 0.3166, 0.3267, 0.3687, 0.4,    0.425,  0.452,  0.3333, 0.3333,
      0.3333, 0.3333, 0.3413, 0.3688, 0.36,   0.4122, 0.4383, 0.4592, 0.4817,
      0.3927, 0.3927, 0.3927, 0.3927, 0.3991, 0.4211, 0.414,  0.4558, 0.4767,
      0.4933, 0.5113, 0.452,  0.452,  0.452,  0.452,  0.4568, 0.4733, 0.468,
      0.4993, 0.515,  0.5275, 0.541,  0.5113, 0.5113, 0.5113, 0.5113, 0.5145,
      0.5255, 0.522,  0.5429, 0.5533, 0.5617, 0.5707, 0.5707, 0.5707, 0.5707,
      0.5707, 0.5723, 0.5778, 0.576,  0.5864, 0.5917, 0.5958, 0.6003, 0.63,
      0.63,   0.63,   0.63,   0.63,   0.63,   0.63,   0.63,   0.63,   0.63,
      0.63,   0.7014, 0.7014, 0.7014, 0.7014, 0.6877, 0.6822, 0.684,  0.6736,
      0.6683, 0.6642, 0.6597};
  static const double dv8[363] = {
      -0.9675, -0.9675, -0.9675, -0.9675, -0.946,  -0.962,  -0.954,  -0.956,
      -0.9687, -0.978,  -0.982,  -1.0,    -1.0,    -1.0,    -1.0,    -0.95,
      -0.95,   -0.95,   -0.95,   -0.95,   -0.95,   -0.95,   -0.995,  -0.995,
      -0.995,  -0.995,  -0.954,  -0.938,  -0.946,  -0.944,  -0.9312, -0.922,
      -0.918,  -0.99,   -0.99,   -0.99,   -0.99,   -0.958,  -0.926,  -0.942,
      -0.938,  -0.9125, -0.894,  -0.886,  -0.985,  -0.985,  -0.985,  -0.985,
      -0.961,  -0.922,  -0.938,  -0.932,  -0.8937, -0.866,  -0.854,  -0.98,
      -0.98,   -0.98,   -0.98,   -0.963,  -0.926,  -0.934,  -0.926,  -0.875,
      -0.838,  -0.822,  -0.975,  -0.975,  -0.975,  -0.975,  -0.965,  -0.93,
      -0.93,   -0.92,   -0.8562, -0.81,   -0.79,   -0.969,  -0.969,  -0.969,
      -0.969,  -0.967,  -0.934,  -0.926,  -0.914,  -0.8375, -0.782,  -0.758,
      -0.963,  -0.963,  -0.963,  -0.963,  -0.969,  -0.938,  -0.922,  -0.908,
      -0.8187, -0.754,  -0.726,  -1.07,   -1.07,   -1.07,   -1.07,   -0.824,
      -0.8025, -0.805,  -0.88,   -0.8,    -0.726,  -0.694,  -0.718,  -0.718,
      -0.718,  -0.718,  -0.532,  -0.5275, -0.66,   -0.83,   -0.79,   -0.698,
      -0.662,  -0.366,  -0.366,  -0.366,  -0.366,  -0.24,   -0.4,    -0.61,
      -0.78,   -0.81,   -0.67,   -0.63,   -0.245,  -0.245,  -0.245,  -0.245,
      -0.3,    -0.33,   -0.55,   -0.74,   -0.75,   -0.6665, -0.6225, -0.39,
      -0.39,   -0.39,   -0.39,   -0.44,   -0.32,   -0.52,   -0.68,   -0.69,
      -0.663,  -0.615,  -0.4,    -0.4,    -0.4,    -0.4,    -0.42,   -0.44,
      -0.47,   -0.58,   -0.47,   -0.4865, -0.4275, -0.1853, -0.1853, -0.1853,
      -0.1853, -0.1862, -0.196,  -0.1989, -0.255,  -0.25,   -0.31,   -0.24,
      0.0293,  0.0293,  0.0293,  0.0293,  0.0477,  0.048,   0.0722,  0.07,
      0.07,    -0.15,   -0.05,   0.244,   0.244,   0.244,   0.244,   0.2815,
      0.292,   0.3433,  0.395,   0.35,    0.138,   0.2,     0.4587,  0.4587,
      0.4587,  0.4587,  0.5154,  0.536,   0.6144,  0.72,    0.56,    0.39,
      0.449,   0.6733,  0.6733,  0.6733,  0.6733,  0.7492,  0.78,    0.84,
      0.83,    0.705,   0.64,    0.7,     0.888,   0.888,   0.888,   0.888,
      0.9831,  0.96,    0.91,    0.8767,  0.805,   0.765,   0.806,   1.1027,
      1.1027,  1.1027,  1.1027,  1.17,    1.01,    0.9467,  0.92,    0.8417,
      0.81,    0.85,    1.25,    1.25,    1.25,    1.25,    1.13,    0.96,
      1.0,     0.924,   0.845,   0.829,   0.865,   1.1,     1.1,     1.1,
      1.1,     1.03,    1.07,    1.0533,  0.928,   0.8483,  0.848,   0.88,
      0.98,    0.98,    0.98,    0.98,    0.96,    1.06,    1.0476,  0.92,
      0.86,    0.867,   0.895,   0.9829,  0.9829,  0.9829,  0.9829,  0.9657,
      1.07,    1.0418,  0.9,     0.88,    0.886,   0.91,    0.9857,  0.9857,
      0.9857,  0.9857,  0.9714,  1.0583,  1.0361,  0.9,     0.9,     0.905,
      0.925,   0.9886,  0.9886,  0.9886,  0.9886,  0.9771,  1.0467,  1.0303,
      0.92,    0.92,    0.924,   0.94,    0.9914,  0.9914,  0.9914,  0.9914,
      0.9829,  1.035,   1.0246,  0.9433,  0.94,    0.943,   0.955,   0.9943,
      0.9943,  0.9943,  0.9943,  0.9886,  1.0233,  1.0188,  0.97,    0.96,
      0.962,   0.97,    0.9971,  0.9971,  0.9971,  0.9971,  0.9943,  1.0117,
      1.0131,  0.985,   0.98,    0.981,   0.985,   1.0,     1.0,     1.0,
      1.0,     1.0,     1.0,     1.0073,  1.0,     1.0,     1.0,     1.0,
      0.9675,  0.9675,  0.9675,  0.9675,  1.0057,  0.9883,  1.0016,  1.015,
      1.02,    1.019,   1.015};
  static const double dv10[181] = {
      0.02,   0.035,  0.055,  0.08,   0.11,   0.1584, 0.2067, 0.2551, 0.3035,
      0.3518, 0.4002, 0.4485, 0.4969, 0.5453, 0.5936, 0.642,  0.7127, 0.7835,
      0.8542, 0.925,  0.9957, 1.0665, 1.1372, 1.2079, 1.2787, 1.3494, 1.4202,
      1.4909, 1.5617, 1.6324, 1.7031, 1.7739, 1.8446, 1.888,  1.904,  1.92,
      1.936,  1.952,  1.968,  1.984,  2.0,    2.016,  2.032,  2.048,  2.064,
      2.08,   2.064,  2.048,  2.032,  2.016,  2.0,    1.984,  1.968,  1.952,
      1.936,  1.92,   1.904,  1.888,  1.8443, 1.7729, 1.7014, 1.63,   1.5586,
      1.4871, 1.4157, 1.3443, 1.2729, 1.2014, 1.13,   1.0586, 0.9871, 0.9157,
      0.8443, 0.7729, 0.7014, 0.63,   0.5584, 0.4869, 0.4153, 0.3438, 0.2722,
      0.2007, 0.1291, 0.0576, 0.0174, 0.0115, 0.0082, 0.0078, 0.0075, 0.0075,
      0.0075, 0.008,  0.0085, 0.009,  0.011,  0.017,  0.026,  0.145,  0.2147,
      0.274,  0.3333, 0.3927, 0.452,  0.5113, 0.5707, 0.63,   0.7014, 0.7729,
      0.8443, 0.9157, 0.9871, 1.0586, 1.13,   1.2014, 1.2729, 1.3443, 1.4157,
      1.4871, 1.5586, 1.63,   1.7014, 1.7729, 1.8443, 1.888,  1.904,  1.92,
      1.936,  1.952,  1.968,  1.984,  2.0,    2.016,  2.032,  2.048,  2.064,
      2.08,   2.032,  1.984,  1.936,  1.888,  1.84,   1.792,  1.744,  1.696,
      1.648,  1.6,    1.552,  1.504,  1.456,  1.408,  1.36,   1.312,  1.264,
      1.216,  1.168,  1.12,   1.072,  1.024,  0.976,  0.928,  0.88,   0.832,
      0.784,  0.736,  0.688,  0.64,   0.5918, 0.5436, 0.4955, 0.4473, 0.3991,
      0.3509, 0.3027, 0.2545, 0.2064, 0.1582, 0.11,   0.08,   0.055,  0.035,
      0.02};
  static const double dv6[181] = {
      0.0,     0.195,   0.39,    0.585,   0.78,    0.7567, 0.7333,  0.71,
      0.6867,  0.6633,  0.64,    0.66,    0.7325,  0.805,  0.8775,  0.95,
      0.9175,  0.885,   0.8525,  0.82,    0.7875,  0.755,  0.7225,  0.69,
      0.6575,  0.625,   0.5925,  0.56,    0.5275,  0.495,  0.4625,  0.43,
      0.3975,  0.365,   0.3325,  0.3,     0.2675,  0.235,  0.2025,  0.17,
      0.1375,  0.105,   0.0725,  0.04,    0.0075,  -0.025, -0.0575, -0.09,
      -0.1225, -0.155,  -0.1875, -0.22,   -0.2525, -0.285, -0.3175, -0.35,
      -0.3825, -0.415,  -0.4475, -0.48,   -0.5125, -0.545, -0.5775, -0.61,
      -0.6425, -0.675,  -0.7075, -0.74,   -0.7725, -0.805, -0.8375, -0.87,
      -0.9025, -0.935,  -0.9675, -1.0,    -0.995,  -0.99,  -0.985,  -0.98,
      -0.975,  -0.969,  -0.963,  -1.07,   -0.718,  -0.366, -0.245,  -0.39,
      -0.4,    -0.1853, 0.0293,  0.244,   0.4587,  0.6733, 0.888,   1.1027,
      1.25,    1.1,     0.98,    0.9829,  0.9857,  0.9886, 0.9914,  0.9943,
      0.9971,  1.0,     0.9675,  0.935,   0.9025,  0.87,   0.8375,  0.805,
      0.7725,  0.74,    0.7075,  0.675,   0.6425,  0.61,   0.5775,  0.545,
      0.5125,  0.48,    0.4475,  0.415,   0.3825,  0.35,   0.3175,  0.285,
      0.2525,  0.22,    0.1875,  0.155,   0.1225,  0.09,   0.0575,  0.025,
      -0.0075, -0.04,   -0.0725, -0.105,  -0.1375, -0.17,  -0.2025, -0.235,
      -0.2675, -0.3,    -0.3325, -0.365,  -0.3975, -0.43,  -0.4625, -0.495,
      -0.5275, -0.56,   -0.5925, -0.625,  -0.6575, -0.69,  -0.7225, -0.755,
      -0.7875, -0.82,   -0.8525, -0.885,  -0.9175, -0.95,  -0.8667, -0.7833,
      -0.7,    -0.66,   -0.64,   -0.6633, -0.6867, -0.71,  -0.7333, -0.7567,
      -0.78,   -0.585,  -0.39,   -0.195,  0.0};
  static const double dv14[50] = {
      0.0,    0.0,   -0.294, -0.12, -0.558, -0.28, -0.745, -0.46, -0.847, -0.66,
      -0.847, -0.88, -0.97,  -1.0,  -1.03,  -1.0,  -1.03,  -0.93, -0.93,  -0.73,
      -0.71,  -0.5,  -0.356, -0.28, 0.0,    -0.06, 0.356,  0.16,  0.71,   0.38,
      0.93,   0.61,  1.03,   0.82,  1.03,   0.89,  0.97,   0.89,  0.847,  0.8,
      0.847,  0.63,  0.745,  0.48,  0.558,  0.32,  0.294,  0.17,  0.0,    0.0};
  static const double dv15[50] = {
      1.2,   1.1,   1.161, 1.025, 1.05, 0.965, 0.888, 0.875, 0.702, 0.745,
      0.531, 0.575, 0.43,  0.36,  0.37, 0.265, 0.36,  0.174, 0.19,  0.118,
      0.04,  0.066, 0.022, 0.033, 0.01, 0.018, 0.022, 0.021, 0.04,  0.044,
      0.19,  0.092, 0.36,  0.162, 0.37, 0.248, 0.43,  0.355, 0.531, 0.58,
      0.702, 0.75,  0.888, 0.875, 1.05, 0.965, 1.161, 1.02,  1.2,   1.08};
  static const double dv28[39] = {1.0,
                                  1.0,
                                  1.0,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  1.0,
                                  1.0,
                                  1.0,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.017453292519943295,
                                  0.0002760867464557364,
                                  0.0002760867464557364,
                                  0.0002760867464557364,
                                  0.017453292519943295,
                                  1.0,
                                  0.01,
                                  0.01,
                                  0.01,
                                  0.00029179334145102413,
                                  0.017453292519943295,
                                  1.0};
  static const double dv29[39] = {0.01,
                                  0.01,
                                  0.01,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.01,
                                  0.01,
                                  0.01,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  0.00017453292519943296,
                                  2.760867464557364E-6,
                                  2.760867464557364E-6,
                                  2.760867464557364E-6,
                                  0.00017453292519943296,
                                  0.01,
                                  0.0001,
                                  0.0001,
                                  0.0001,
                                  2.9179334145102416E-6,
                                  0.00017453292519943296,
                                  0.01};
  static const double dv20[33] = {
      0.08, 0.0,  -0.12, 0.18, 0.1,  0.02, 0.3, 0.21, 0.08, 0.43, 0.32,
      0.18, 0.55, 0.42,  0.28, 0.66, 0.54, 0.4, 0.79, 0.66, 0.53, 0.9,
      0.8,  0.67, 1.03,  0.94, 0.82, 0.55, 0.5, 0.4,  0.0,  0.0,  0.0};
  static const double dv21[33] = {
      1.11, 1.12, 1.15, 1.09, 1.12, 1.15, 1.08, 1.12, 1.15, 1.065, 1.12,
      1.15, 1.05, 1.12, 1.16, 1.04, 1.12, 1.17, 1.02, 1.12, 1.18,  1.01,
      1.12, 1.22, 1.0,  1.11, 1.16, 0.88, 0.96, 0.98, 0.6,  0.6,   0.6};
  static const double dv22[33] = {
      0.0,   -0.4, -0.56, -0.2, -0.6, -0.8, 0.05, -0.2, -0.74, 0.3, 0.12,
      -0.32, 0.54, 0.36,  0.04, 0.8,  0.6,  0.32, 1.04, 0.83,  0.6, 1.3,
      1.06,  0.86, 1.55,  1.3,  1.12, 0.8,  0.66, 0.54, 0.0,   0.0, 0.0};
  static const double dv23[33] = {
      -0.13, 0.4,  0.78, 0.8,  0.94, 1.36, 1.8,  1.84, 1.91, 1.82, 1.91,
      1.98,  1.86, 1.98, 2.06, 1.88, 2.04, 2.14, 1.91, 2.08, 2.21, 1.94,
      2.14,  2.28, 1.69, 1.89, 2.16, 1.42, 1.62, 1.96, 1.14, 1.35, 1.56};
  static const double dv12[25] = {
      150.0, 145.0, 133.0, 114.0, 88.0,  61.0,  45.08, 37.58, 31.68,
      27.48, 25.06, 23.58, 23.58, 25.08, 27.58, 31.28, 36.58, 43.08,
      51.08, 66.0,  84.0,  110.0, 132.0, 145.0, 150.0};
  static const double dv26[25] = {0.0,   0.25,  0.7,   1.2,   1.6,  1.9,  1.8,
                                  1.4,   1.1,   0.8,   0.55,  0.5,  0.45, 0.4,
                                  0.38,  0.33,  0.19,  -0.12, -0.4, -0.7, -0.75,
                                  -0.65, -0.45, -0.15, 0.0};
  static const double dv27[25] = {
      0.0,   0.0,  0.0,  0.0,  0.0,  1.0,  2.0,  2.0, 1.9, 1.8, 1.5, 0.88, 0.0,
      -0.88, -1.5, -1.8, -1.9, -2.0, -2.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  static const double dv3[21] = {0.0,
                                 0.05,
                                 0.1,
                                 0.15000000000000002,
                                 0.2,
                                 0.25,
                                 0.30000000000000004,
                                 0.35000000000000003,
                                 0.4,
                                 0.45,
                                 0.5,
                                 0.55,
                                 0.6,
                                 0.6499999999999999,
                                 0.7,
                                 0.75,
                                 0.8,
                                 0.85,
                                 0.9,
                                 0.95,
                                 1.0};
  static const double dv4[21] = {
      0.0,   0.0,  0.0,  0.0,  -0.15, -0.95, -1.8,   -2.75, -3.55, -4.4, -5.3,
      -6.15, -7.1, -7.9, -8.8, -9.65, -10.3, -10.75, -12.3, -13.1, -10.9};
  static const double dv16[16] = {0.2062, 0.0, 0.0, 0.0,  0.0,    0.2172,
                                  0.0,    0.0, 0.0, 0.0,  0.2025, 0.0,
                                  0.0,    0.0, 0.0, 0.378};
  static const double dv17[16] = {0.68,  0.0,        0.0,       0.0,
                                  0.0,   1.202,      -1.202,    0.0,
                                  0.993, 0.905,      1.299,     -0.8553819456,
                                  0.0,   -0.4287534, 0.4287534, 1.604276856};
  static const double dv13[13] = {0.0,  1.0,   4.0,   9.0,   16.3,  28.0, 38.5,
                                  76.5, 113.5, 141.5, 164.5, 169.5, 170.5};
  static const double dv25[13] = {1.0,  0.88, 0.79, 0.72, 0.66, 0.64, 0.62,
                                  0.64, 0.66, 0.72, 0.79, 0.88, 1.0};
  static const double dv9[11] = {
      0.0, 0.1, 0.2, 0.30000000000000004, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0};
  static const double dv[10] = {0.21063902864405154, 0.3589530117749918,
                                0.46601459010183915, 0.5542941682110577,
                                0.6311710885665992,  0.7001752891308831,
                                0.7633215363363854,  0.8218885506963806,
                                0.8767481215285446,  0.9285261869684501};
  static const double dv1[10] = {0.2091306875602619,  0.12260223635207923,
                                 0.09630711081686538, 0.08198573445957091,
                                 0.0726212238232129,  0.06588018591161571,
                                 0.0607272805762048,  0.05662233438335362,
                                 0.05325199180007367, 0.0504202266164262};
  static const double dv2[10] = {0.513904182438075,  0.6647949890753484,
                                 0.7612257285951431, 0.8306339190864953,
                                 0.8825074458202575, 0.9216146755035635,
                                 0.9508128372160943, 0.9720043077523407,
                                 0.9865484480458087, 0.9954670604248002};
  static const double dv18[9] = {11.34127598363601,
                                 0.0,
                                 0.0,
                                 -5.670637991818,
                                 -5.670637991818,
                                 3.50342147029408,
                                 -5.670637991818,
                                 5.670637991818,
                                 3.50342147029408};
  static const double dv5[9] = {
      0.9986295347545738,   -0.0, -0.052335956242943835, 0.0, 1.0, -0.0,
      0.052335956242943835, 0.0,  0.9986295347545738};
  static const double dv24[8] = {1.0, 0.875, 0.76, 0.76, 0.82, 0.91, 1.0, 1.0};
  static const double dv19[3] = {-7.97382781203715, 9.72804497738283,
                                 10.11112699620666};
  static const short iv6[25] = {
      440, 392, 332, 259, 160, 40,  -140, -190, -240, -220, -180, -100, 0,
      100, 180, 220, 240, 190, 140, 59,   -30,  -125, -220, -320, -420};
  static const short iv7[25] = {-200, -470, -645, -730, -760, -760, -740,
                                -700, -630, -520, -380, -230, -90,  10,
                                100,  290,  450,  600,  750,  810,  825,
                                780,  650,  470,  200};
  static const signed char iv8[50] = {
      -90, -90, -80, -80, -70, -70, -60, -60, -50, -50, -40, -40, -30,
      -30, -25, -25, -20, -20, -15, -15, -10, -10, -5,  -5,  0,   0,
      5,   5,   10,  10,  15,  15,  20,  20,  25,  25,  30,  30,  40,
      40,  50,  50,  60,  60,  70,  70,  80,  80,  90,  90};
  static const signed char iv[25] = {
      -90, -80, -70, -60, -50, -40, -30, -25, -20, -15, -10, -5, 0,
      5,   10,  15,  20,  25,  30,  40,  50,  60,  70,  80,  90};
  static const signed char iv2[25] = {
      -37, -64, -84, -100, -103, -92, -72, -65, -50, -35, -23, -11, 0,
      11,  23,  35,  50,   65,   72,  92,  103, 100, 84,  64,  37};
  static const signed char iv3[25] = {
      -24, -54, -72, -81, -85, -83, -70, -52, -35, -25, -13, -5, 1,
      10,  20,  25,  30,  34,  37,  43,  48,  50,  48,  39,  22};
  static const signed char iv4[25] = {30, 30, 30, 30, 30, 30, 30, 20, 12,
                                      7,  3,  2,  0,  2,  5,  10, 15, 22,
                                      30, 30, 30, 30, 30, 30, 30};
  static const signed char iv5[25] = {
      100, 100, 100, 101, 103,  106,  110,  120,  75,   30,   0,    0,   0,
      0,   0,   -30, -75, -120, -110, -106, -103, -101, -100, -100, -100};
  static const signed char iv1[13] = {0,  5,  10, 15, 20, 25, 30,
                                      40, 50, 60, 70, 80, 90};
  static const unsigned char uv[13] = {0U,   10U,  20U,  50U,  90U,  130U, 180U,
                                       180U, 180U, 180U, 180U, 180U, 180U};
  static const signed char iv9[8] = {-30, -25, -20, 10, 15, 20, 25, 30};
  __m128d r;
  __m128d r1;
  __m128d r2;
  constants_Struct b_constants;
  double Jac[144];
  double b_x0[39];
  double b_xdot0[39];
  double xr[24];
  double NormErr_tmp[12];
  double b_err[12];
  double err[12];
  double trimvec[12];
  double xdotav_n[12];
  double xf[12];
  double a__1[7];
  double dv7[2];
  double NormErr;
  double xf_tmp;
  int i;
  int it;
  int ix;
  int x0_tmp;
  /* Set constants */
  /* 'InitFcnH60:4' constants = H60_constants; */
  constants->d2r = 0.017453292519943295;
  constants->r2d = 57.29577951308232;
  constants->D2R = 0.017453292519943295;
  constants->R2D = 57.29577951308232;
  constants->g = 32.17;
  constants->FtLb_s2Hp = 0.0018181818181818182;
  constants->fps2kts = 0.5924170616113744;
  constants->kts2fps = 1.688;
  constants->rhoSLSTD = 0.002378;
  constants->R = 26.83;
  constants->NB = 4.0;
  constants->OMEGA = 27.0;
  constants->OMEGAT = 27.0;
  constants->HOFFSET = 1.25;
  constants->SPAR = 2.25;
  memcpy(&constants->RSEG[0], &dv[0], 10U * sizeof(double));
  memcpy(&constants->DELSEG[0], &dv1[0], 10U * sizeof(double));
  memcpy(&constants->DynTwistMode[0], &dv2[0], 10U * sizeof(double));
  constants->TauDT = 0.05;
  memcpy(&constants->TWISTTABR[0], &dv3[0], 21U * sizeof(double));
  memcpy(&constants->TWISTTABTHET[0], &dv4[0], 21U * sizeof(double));
  constants->BTL = 0.97;
  constants->MBETA = 86.7;
  constants->IBETA = 1512.6;
  constants->WBLADE = 256.9;
  constants->G = 32.17;
  constants->ALD = 0.227;
  constants->BLD = 3.242;
  constants->CLD = 12.04;
  constants->DLD = 10.0102;
  constants->RLD = 6.898;
  constants->THETALDGEO = 0.0;
  constants->ITHSH = -3.0;
  constants->IPHSH = 0.0;
  memcpy(&constants->Tshaft[0], &dv5[0], 9U * sizeof(double));
  constants->DELSP = -0.16929693744344995;
  constants->DELTA3 = 0.0;
  constants->CLAG = 1500.0;
  constants->KLAG = 15060.0;
  constants->ZETA0 = 0.12217304763960307;
  constants->CFLAP = 0.0;
  constants->KFLAP = 0.0;
  constants->CHORDT = 1.73;
  constants->CHORDR = 1.73;
  for (i = 0; i < 10; i++) {
    constants->CHORD[i] = 1.73;
  }
  constants->istart = 1.0;
  constants->inflow = 1.0;
  for (i = 0; i <= 178; i += 2) {
    _mm_storeu_pd(&constants->CLR0UTAB[i], _mm_loadu_pd(&dv6[i]));
    dv7[0] = i;
    dv7[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(
        &constants->AOAUTAB[i],
        _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(2.0), r), _mm_set1_pd(180.0)));
  }
  constants->CLR0UTAB[180] = dv6[180];
  constants->AOAUTAB[180] = 180.0;
  memcpy(&constants->CLR0BTAB[0], &dv8[0], 363U * sizeof(double));
  for (i = 0; i <= 30; i += 2) {
    dv7[0] = i;
    dv7[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(
        &constants->AOABTAB[i],
        _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(2.0), r), _mm_set1_pd(32.0)));
  }
  constants->AOABTAB[32] = 32.0;
  memcpy(&constants->MACHTAB[0], &dv9[0], 11U * sizeof(double));
  memcpy(&constants->CDR0UTAB[0], &dv10[0], 181U * sizeof(double));
  memcpy(&constants->CDR0BTAB[0], &dv11[0], 363U * sizeof(double));
  constants->ACL1 = 11.0;
  constants->ACL2 = 172.0;
  constants->ACL3 = -5.0;
  constants->ACL4 = -172.0;
  constants->DCDMR = 0.002;
  constants->KR = -1.0;
  constants->KRsched[0] = 1.5;
  constants->KRVsched[0] = 0.0;
  constants->KRsched[1] = 1.5;
  constants->KRVsched[1] = 20.0;
  constants->KRsched[2] = 0.0;
  constants->KRVsched[2] = 40.0;
  constants->KRsched[3] = 0.0;
  constants->KRVsched[3] = 160.0;
  constants->FSCG = 358.0;
  constants->WLCG = 248.2;
  constants->BLCG = 0.0;
  constants->FSMR = 341.25;
  constants->WLMR = 315.0;
  constants->BLMR = 0.0;
  constants->WEIGHT = 17000.0;
  constants->WEIGHTNR = 15972.4;
  constants->MASS = 496.4998445756916;
  constants->IX = 4659.0;
  constants->IY = 38512.0;
  constants->IZ = 36796.0;
  constants->IXZ = 1882.0;
  constants->FSCGB = 359.07762765770957;
  constants->WLCGB = 243.90235656507477;
  constants->BLCGB = 0.0;
  constants->IGNDEFF = 0.0;
  constants->KGE1 = 0.5;
  constants->KGE2 = -0.6667;
  for (i = 0; i < 25; i++) {
    x0_tmp = iv[i];
    constants->FUSEAOA[i] = x0_tmp;
    constants->FUSEBETA[i] = x0_tmp;
  }
  for (i = 0; i < 13; i++) {
    constants->FUSEABETA[i] = iv1[i];
  }
  memcpy(&constants->FUSEDA[0], &dv12[0], 25U * sizeof(double));
  memcpy(&constants->FUSEDB[0], &dv13[0], 13U * sizeof(double));
  for (i = 0; i < 25; i++) {
    constants->FUSEYB[i] = iv2[i];
    constants->FUSELA[i] = iv3[i];
    constants->FUSELB[i] = iv4[i];
    constants->FUSERB[i] = iv5[i];
    constants->FUSEMA[i] = iv7[i];
  }
  for (i = 0; i < 13; i++) {
    constants->FUSEMB[i] = uv[i];
  }
  for (i = 0; i < 25; i++) {
    constants->FUSENB[i] = iv6[i];
  }
  constants->FSfus = 345.5;
  constants->BLfus = 0.0;
  constants->WLfus = 234.0;
  constants->FSTR = 732.0;
  constants->BLTR = -14.0;
  constants->WLTR = 324.7;
  constants->CantTR = 20.0;
  constants->OmegaTR = 124.62;
  constants->CHRDTR = 0.81;
  constants->RTR = 5.5;
  constants->BTLTR = 0.92;
  constants->a0TR = 5.73;
  constants->IbTR = 3.1;
  constants->twistTR = -0.30019663134302466;
  constants->BIASTR = 5.0;
  constants->D0TR = 0.0087;
  constants->D1TR = -0.0216;
  constants->D2TR = 0.4;
  constants->CDTR = 0.0;
  constants->TD3TR = 0.7002075;
  constants->DELTTR = 0.001455;
  constants->BVTTR = 0.9;
  constants->BVTTR1 = 1.0;
  constants->VBVTTR = 30.0;
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->STAIL[0],
                _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-12.700000000000003), r),
                           _mm_set1_pd(45.0)));
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->PHITAIL[0], _mm_mul_pd(_mm_set1_pd(-90.0), r));
  r1 = _mm_set1_pd(0.0);
  _mm_storeu_pd(&constants->ITAIL[0], r1);
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(
      &constants->FSTAIL[0],
      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(-5.0), r), _mm_set1_pd(700.0)));
  _mm_storeu_pd(&constants->BLTAIL[0], r1);
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(
      &constants->WLTAIL[0],
      _mm_add_pd(_mm_mul_pd(_mm_set1_pd(29.0), r), _mm_set1_pd(244.0)));
  for (i = 0; i < 50; i++) {
    constants->ALTAIL[i] = iv8[i];
    constants->CLTAIL[i] = dv14[i];
    constants->CDTAIL[i] = dv15[i];
  }
  constants->CLELEV[0] = 0.0;
  constants->CLELEV[1] = 0.0;
  constants->STABSET = 0.0;
  memcpy(&constants->LNKGAIN[0], &dv16[0], 16U * sizeof(double));
  memcpy(&constants->MIXGAIN[0], &dv17[0], 16U * sizeof(double));
  constants->TRGAIN = -9.142;
  constants->TRBIAS = 21.98;
  memcpy(&constants->SWASHGAIN[0], &dv18[0], 9U * sizeof(double));
  _mm_storeu_pd(&constants->SWASHBIAS[0], _mm_loadu_pd(&dv19[0]));
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  r2 = _mm_set1_pd(6.0);
  _mm_storeu_pd(&constants->a1f_tab[0], _mm_sub_pd(_mm_mul_pd(r2, r), r2));
  constants->SWASHBIAS[2] = 10.11112699620666;
  constants->a1f_tab[2] = 6.0;
  for (i = 0; i <= 8; i += 2) {
    dv7[0] = i;
    dv7[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(&constants->chi_tab[i], _mm_mul_pd(_mm_set1_pd(10.0), r));
  }
  constants->chi_tab[10] = 100.0;
  memcpy(&constants->ekxf_tab[0], &dv20[0], 33U * sizeof(double));
  memcpy(&constants->ekzf_tab[0], &dv21[0], 33U * sizeof(double));
  memcpy(&constants->ekxt_tab[0], &dv22[0], 33U * sizeof(double));
  memcpy(&constants->ekzt_tab[0], &dv23[0], 33U * sizeof(double));
  for (i = 0; i < 8; i++) {
    constants->alpha_tab[i] = iv9[i];
    constants->qlossht_tab[i] = dv24[i];
  }
  for (i = 0; i <= 10; i += 2) {
    dv7[0] = i;
    dv7[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(
        &constants->psivt_tab[i],
        _mm_sub_pd(_mm_mul_pd(_mm_set1_pd(5.0), r), _mm_set1_pd(30.0)));
    _mm_storeu_pd(&constants->qlossvt_tab[i], _mm_loadu_pd(&dv25[i]));
  }
  constants->psivt_tab[12] = 30.0;
  constants->qlossvt_tab[12] = dv25[12];
  for (i = 0; i < 25; i++) {
    x0_tmp = iv[i];
    constants->alphaeps_tab[i] = x0_tmp;
    constants->eps_tab[i] = dv26[i];
    constants->psisig_tab[i] = x0_tmp;
    constants->sig_tab[i] = dv27[i];
  }
  constants->HPMAX = 2825.0;
  constants->TauEng = 0.1;
  constants->QEMax = 34527.77777777778;
  constants->HPACC = 60.0;
  constants->GEARENG = 81.042;
  constants->GEARACC = 51.4;
  constants->GEARTR = 4.6156;
  constants->JTR = 419.4711005584;
  constants->JAC = 10.56784;
  constants->JENG = 407.20395736800003;
  constants->JMROT = 41.85;
  constants->JGBX = 208.4;
  constants->RPM2RPS = 0.10471975511965977;
  constants->GBXDAMP = 50.0;
  constants->DELCLIN[0] = 1.0;
  constants->DELCLIN[1] = 1.0;
  constants->DELCLIN[2] = 1.0;
  constants->DELCLIN[3] = 1.0;
  memcpy(&constants->XSCALE[0], &dv28[0], 39U * sizeof(double));
  memcpy(&constants->DELXLIN[0], &dv29[0], 39U * sizeof(double));
  constants->xp = 10.62553;
  constants->yp = 2.0;
  constants->zp = 0.939163;
  constants->GroundZ = 0.0;
  constants->dt = 0.01;
  constants->IFREEZE = 0.0;
  constants->FP_ITMAX = 100.0;
  constants->FPTOL = 1.0E-6;
  constants->NREVSTEP = 36.0;
  constants->NREVCONV = 2.0;
  constants->NREVAVERAGE = 1.0;
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  r2 = _mm_set1_pd(1.0);
  _mm_storeu_pd(&constants->TRIMSTATE[0], _mm_add_pd(r, r2));
  dv7[0] = 2.0;
  dv7[1] = 3.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->TRIMSTATE[2], _mm_add_pd(r, r2));
  dv7[0] = 4.0;
  dv7[1] = 5.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->TRIMSTATE[4], _mm_add_pd(r, r2));
  dv7[0] = 6.0;
  dv7[1] = 7.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->TRIMSTATE[6], _mm_add_pd(r, r2));
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->TRIMCTRL[0], _mm_add_pd(r, r2));
  dv7[0] = 2.0;
  dv7[1] = 3.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&constants->TRIMCTRL[2], _mm_add_pd(r, r2));
  constants->TRIMRELAX = 0.5;
  constants->TRIMTOL = 1.0E-5;
  constants->TRIMITMAX = 100.0;
  constants->TRIMJACTOL = 2.0;
  /* Initialization Function for UH-60 PSUHeloSim model */
  /* Must be run to set trim of the aircraft */
  /* Must set aircraft constants and trim defaultss before running this! */
  /* Initialize sim with trim condition */
  /* Initialize state vectors and initial guess */
  /* 'InitFcnH60:12' xf=zeros(SizeConstants.NFSTATES,1); */
  for (i = 0; i <= 10; i += 2) {
    dv7[0] = i;
    dv7[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(&constants->TRIMTARG[i], _mm_add_pd(r, r2));
    _mm_storeu_pd(&xf[i], r1);
  }
  /*  xf = [u v w p q r phi theta psi x y z] */
  /* 'InitFcnH60:13' xr=zeros(SizeConstants.NRSTATES,1); */
  memset(&xr[0], 0, 24U * sizeof(double));
  /*  xr =[ beta0 beta0d beta1c beta1s, equiv derivatives of flapping MBC (4),
   * equivalent lag MBC and deriv (8), main inflow states (3), azimuth, blade
   * load state for dyn twist, additional inflow for Peters-He] */
  /* 'InitFcnH60:14' xtr=zeros(SizeConstants.NTRSTATES,1); */
  /* xtr =[tail rotor inflow] */
  /* Initial engine state guess */
  /* 'InitFcnH60:17' xe0 = [27.;35000.]; */
  /* 'InitFcnH60:18' xp=xe0; */
  /* Initial Guess is Centered controls */
  /* 'InitFcnH60:21' u0=[50.;50.;50.;50.]; */
  /* Set non-zero inflow state */
  /* 'InitFcnH60:23' xr(17)=0.05; */
  xr[16] = 0.05;
  /* Azimuth of rotor (can get different trim with different azimuth due to */
  /* periodic nature of helicopter dynamics */
  /* 'InitFcnH60:26' xr(20)=0.; */
  xr[19] = 0.0;
  /* Init Dynamic Twist Blade Load Value */
  /* 'InitFcnH60:28' xr(21)=constants.WEIGHT/constants.NB; */
  xr[20] = 4250.0;
  /* Tail rotor inflow guess */
  /* 'InitFcnH60:31' xtr(1)=0.05; */
  /* Check total airspeed for flight condition.  Cannot be exactly 0. */
  /* 'InitFcnH60:34' Vtot =
   * sqrt(FlightConditions.VXTRIM^2+FlightConditions.VYTRIM^2+FlightConditions.VZTRIM^2);
   */
  /* 'InitFcnH60:35' if Vtot < 0.001 */
  if (sqrt((FlightConditions->VXTRIM * FlightConditions->VXTRIM +
            FlightConditions->VYTRIM * FlightConditions->VYTRIM) +
           FlightConditions->VZTRIM * FlightConditions->VZTRIM) < 0.001) {
    /* 'InitFcnH60:36' FlightConditions.VXTRIM = 0.001; */
    FlightConditions->VXTRIM = 0.001;
  }
  /* Initial guess for trim solution (based on trim defaults) */
  /* 'InitFcnH60:40' xf(1)=FlightConditions.VXTRIM; */
  xf[0] = FlightConditions->VXTRIM;
  /* 'InitFcnH60:41' xf(2)=FlightConditions.VYTRIM; */
  xf[1] = FlightConditions->VYTRIM;
  /* 'InitFcnH60:42' xf(3)=FlightConditions.VZTRIM; */
  xf[2] = FlightConditions->VZTRIM;
  /* 'InitFcnH60:43' xf(9)=FlightConditions.PSITRIM; */
  xf[8] = FlightConditions->PSITRIM;
  /* 'InitFcnH60:44' xf(10)=FlightConditions.XNTRIM; */
  xf[9] = FlightConditions->XNTRIM;
  /* 'InitFcnH60:45' xf(11)=FlightConditions.YETRIM; */
  xf[10] = FlightConditions->YETRIM;
  /* 'InitFcnH60:46' xf(12)=-FlightConditions.ALTTRIM; */
  xf[11] = -FlightConditions->ALTTRIM;
  /* 'InitFcnH60:48' x0=[xf;xr;xtr;xp]; */
  memcpy(&x0[0], &xf[0], 12U * sizeof(double));
  memcpy(&x0[12], &xr[0], 24U * sizeof(double));
  x0[36] = 0.05;
  dv7[0] = 0.0;
  dv7[1] = 1.0;
  r = _mm_loadu_pd(&dv7[0]);
  _mm_storeu_pd(&x0[37], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(34973.0), r),
                                    _mm_set1_pd(27.0)));
  /* Run trim */
  /* Set trim target */
  /* 'InitFcnH60:52' target=zeros(SizeConstants.NFSTATES,1); */
  memset(&xf[0], 0, 12U * sizeof(double));
  /* 'InitFcnH60:53'
   * target(9:12)=[FlightConditions.PSIDTRIM;FlightConditions.VXTRIM*cos(FlightConditions.PSITRIM)-FlightConditions.VYTRIM*cos(FlightConditions.PSITRIM);
   * ... */
  /* 'InitFcnH60:54'
   * FlightConditions.VXTRIM*sin(FlightConditions.PSITRIM)+FlightConditions.VYTRIM*cos(FlightConditions.PSITRIM);
   * ... */
  /* 'InitFcnH60:55'     FlightConditions.VZTRIM]; */
  NormErr = cos(FlightConditions->PSITRIM);
  xf[8] = FlightConditions->PSIDTRIM;
  xf_tmp = FlightConditions->VYTRIM * NormErr;
  xf[9] = FlightConditions->VXTRIM * NormErr - xf_tmp;
  xf[10] = FlightConditions->VXTRIM * sin(FlightConditions->PSITRIM) + xf_tmp;
  xf[11] = FlightConditions->VZTRIM;
  /* 'InitFcnH60:57' xdot0 = zeros(SizeConstants.NSTATES,1); */
  memset(&xdot0[0], 0, 39U * sizeof(double));
  /* 'InitFcnH60:58' xdot0(constants.TRIMTARG) = target; */
  memcpy(&xdot0[0], &xf[0], 12U * sizeof(double));
  /* 'InitFcnH60:59' xdot0(SizeConstants.IDXAZ) = constants.OMEGAT; */
  xdot0[31] = 27.0;
  /* Option to trim in zero sideselip or zero bank angle */
  /* 'InitFcnH60:62' if (FlightConditions.VXTRIM>=60*1.688) */
  if (FlightConditions->VXTRIM >= 101.28) {
    /* Trim heading for zero bank angle above 60 kts */
    /* 'InitFcnH60:64' x0(7)=0.; */
    x0[6] = 0.0;
    /* 'InitFcnH60:65' constants.TRIMSTATE(7:8)=[8 9]; */
    dv7[0] = 0.0;
    dv7[1] = 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(&constants->TRIMSTATE[6], _mm_add_pd(r, _mm_set1_pd(8.0)));
  } else {
    /* 'InitFcnH60:66' else */
    /* Otherwise set heading to flight path */
    /* 'InitFcnH60:68'
     * x0(9)=atan2(FlightConditions.VYTRIM,FlightConditions.VXTRIM); */
    x0[8] = b_atan2(FlightConditions->VYTRIM, FlightConditions->VXTRIM);
    /* 'InitFcnH60:69' constants.TRIMSTATE(7:8)=[7 8]; */
    dv7[0] = 0.0;
    dv7[1] = 1.0;
    r = _mm_loadu_pd(&dv7[0]);
    _mm_storeu_pd(&constants->TRIMSTATE[6], _mm_add_pd(r, _mm_set1_pd(7.0)));
  }
  /* Set engine to idea */
  /* 'InitFcnH60:73' IDEAL_save = constants.IDEALENG; */
  /* 'InitFcnH60:74' constants.IDEALENG = 1; */
  constants->IDEALENG = 1.0;
  /*  */
  /* Trim and set initial conditions */
  /* 'InitFcnH60:78'
   * [x0,u0,xdot0,y0,itrim]=trimmer2(x0,u0,xdot0,target,constants); */
  b_constants = *constants;
  u0[0] = 50.0;
  u0[1] = 50.0;
  u0[2] = 50.0;
  u0[3] = 50.0;
  /* New H60 Trimmer (hard coded for H60) */
  /*  Lets rotor run and trims body states and controls only */
  /* 'trimmer2:6' it=0; */
  it = 0;
  /* 'trimmer2:7' itrim = 0; */
  *itrim = 0.0;
  /*  Set dt so revolution is integral number of steps */
  /* 'trimmer2:10' dt = 2*pi/constants.OMEGAT/constants.NREVSTEP; */
  /* Vector sizes */
  /* 'trimmer2:13' nTarg = length(constants.TRIMTARG); */
  /* 'trimmer2:14' nTrimState = length(constants.TRIMSTATE); */
  /* 'trimmer2:15' nTrimCtrl = length(constants.TRIMCTRL); */
  /* 'trimmer2:16' nTrimVars = nTrimState + nTrimCtrl; */
  /* 'trimmer2:18' if (nTrimVars ~= nTarg) */
  /* Init trim variables */
  /* 'trimmer2:22' trimvec = [x0(constants.TRIMSTATE);u0(constants.TRIMCTRL)];
   */
  for (i = 0; i < 8; i++) {
    trimvec[i] = x0[(int)b_constants.TRIMSTATE[i] - 1];
  }
  trimvec[8] = 50.0;
  trimvec[9] = 50.0;
  trimvec[10] = 50.0;
  trimvec[11] = 50.0;
  /* Need to freeze fuselage states */
  /* 'trimmer2:25' constants.IFREEZE = 1; */
  /* Step through desired revolutions, take average accel */
  /* 'trimmer2:28' [xdotav, x0, xdot0,y0] = RunRevs(x0,u0,xdot0,dt,constants);
   */
  /* 'RunRevs:3' x = x0; */
  /* 'RunRevs:4' u = u0; */
  /* 'RunRevs:5' xdot = xdot0; */
  /* Run revolutions to convergence */
  /* 'RunRevs:8' for istep = 1:constants.NREVSTEP*constants.NREVCONV */
  for (i = 0; i < 72; i++) {
    /* 'RunRevs:9' [x,~,xdot] = StepH60(x,u,xdot,dt,constants); */
    memcpy(&b_x0[0], &x0[0], 39U * sizeof(double));
    memcpy(&b_xdot0[0], &xdot0[0], 39U * sizeof(double));
    b_StepH60(b_x0, b_xdot0, &b_constants, x0, a__1, xdot0);
  }
  /* Run revolutions to average */
  /* 'RunRevs:13' Navg = constants.NREVSTEP*constants.NREVAVERAGE; */
  /* 'RunRevs:14' xdotav = zeros(SizeConstants.NFSTATES,1); */
  memset(&err[0], 0, 12U * sizeof(double));
  /* 'RunRevs:15' yav = zeros(SizeConstants.NOUT,1); */
  for (i = 0; i < 7; i++) {
    b_y0[i] = 0.0;
  }
  /* 'RunRevs:16' for istep = 1:Navg */
  r1 = _mm_set1_pd(36.0);
  for (i = 0; i < 36; i++) {
    /* 'RunRevs:17' [x,y,xdot] = StepH60(x,u,xdot,dt,constants); */
    memcpy(&b_x0[0], &x0[0], 39U * sizeof(double));
    memcpy(&b_xdot0[0], &xdot0[0], 39U * sizeof(double));
    b_StepH60(b_x0, b_xdot0, &b_constants, x0, a__1, xdot0);
    /* 'RunRevs:18' xdotav = xdotav + xdot(SizeConstants.IDXF)/Navg; */
    for (ix = 0; ix <= 10; ix += 2) {
      r = _mm_loadu_pd(&xdot0[ix]);
      r2 = _mm_loadu_pd(&err[ix]);
      _mm_storeu_pd(&err[ix], _mm_add_pd(r2, _mm_div_pd(r, _mm_set1_pd(36.0))));
    }
    /* 'RunRevs:19' yav = yav + y/Navg; */
    r = _mm_loadu_pd(&a__1[0]);
    r2 = _mm_loadu_pd(&b_y0[0]);
    _mm_storeu_pd(&b_y0[0], _mm_add_pd(r2, _mm_div_pd(r, r1)));
    r = _mm_loadu_pd(&a__1[2]);
    r2 = _mm_loadu_pd(&b_y0[2]);
    _mm_storeu_pd(&b_y0[2], _mm_add_pd(r2, _mm_div_pd(r, r1)));
    r = _mm_loadu_pd(&a__1[4]);
    r2 = _mm_loadu_pd(&b_y0[4]);
    _mm_storeu_pd(&b_y0[4], _mm_add_pd(r2, _mm_div_pd(r, r1)));
    b_y0[6] += a__1[6] / 36.0;
  }
  /*  Calculate the error between the target and the averaged state derivative
   */
  /* 'trimmer2:30' err = xdotav - target; */
  /* 'trimmer2:31' NormErr = norm(err./constants.XSCALE(constants.TRIMTARG)); */
  for (i = 0; i < 12; i++) {
    xf_tmp = err[i] - xf[i];
    err[i] = xf_tmp;
    NormErr = b_constants.XSCALE[(int)b_constants.TRIMTARG[i] - 1];
    NormErr_tmp[i] = NormErr;
    b_err[i] = xf_tmp / NormErr;
  }
  NormErr = b_norm(b_err);
  /* 'trimmer2:32' fprintf("Trim Iteration: %d  Normalized Error: %8.5f
   * \n",int16(it),NormErr); */
  printf("Trim Iteration: %d  Normalized Error: %8.5f \n", 0, NormErr);
  fflush(stdout);
  /* Initialize Jacobian */
  /* 'trimmer2:35' nJac = length(constants.TRIMTARG); */
  /* 'trimmer2:36' Jac = zeros(nJac,nJac); */
  memset(&Jac[0], 0, 144U * sizeof(double));
  /* 'trimmer2:37' done = 0; */
  /* 'trimmer2:38' while (~done) */
  int exitg1;
  do {
    double dv30[144];
    exitg1 = 0;
    /* Next iteration */
    /* 'trimmer2:40' it=it+1; */
    it++;
    /* 'trimmer2:42' if ( (it ==1) || (NormErr > constants.TRIMJACTOL)) */
    if ((it == 1) || (NormErr > 2.0)) {
      /* Form Jacobian */
      /* Perturbations to each trim variable */
      /* 'trimmer2:45' icol = 0; */
      /* 'trimmer2:46' for ix = constants.TRIMSTATE */
      for (ix = 0; ix < 8; ix++) {
        /* 'trimmer2:47' x0(ix) = x0(ix) + constants.DELXLIN(ix); */
        x0_tmp = (int)b_constants.TRIMSTATE[ix] - 1;
        xf_tmp = b_constants.DELXLIN[x0_tmp];
        x0[x0_tmp] += xf_tmp;
        /* 'trimmer2:48' [xdotav_p, x0, xdot0,~] =
         * RunRevs(x0,u0,xdot0,dt,constants); */
        RunRevs(x0, u0, xdot0, &b_constants, b_err, a__1);
        /* 'trimmer2:49' x0(ix) = x0(ix) - 2*constants.DELXLIN(ix); */
        NormErr = 2.0 * xf_tmp;
        x0[x0_tmp] -= NormErr;
        /* 'trimmer2:50' [xdotav_n, x0, xdot0,~] =
         * RunRevs(x0,u0,xdot0,dt,constants); */
        RunRevs(x0, u0, xdot0, &b_constants, xdotav_n, a__1);
        /* 'trimmer2:51' x0(ix) = x0(ix) + constants.DELXLIN(ix); */
        x0[x0_tmp] += xf_tmp;
        /* 'trimmer2:52' icol = icol + 1; */
        /* 'trimmer2:53' Jac(:,icol) =
         * (xdotav_p-xdotav_n)/(2.*constants.DELXLIN(ix)); */
        for (i = 0; i <= 10; i += 2) {
          r = _mm_loadu_pd(&b_err[i]);
          r2 = _mm_loadu_pd(&xdotav_n[i]);
          _mm_storeu_pd(&Jac[i + 12 * ix],
                        _mm_div_pd(_mm_sub_pd(r, r2), _mm_set1_pd(NormErr)));
        }
      }
      /* Perturbations to each control */
      /* 'trimmer2:56' for iu = 1:SizeConstants.NCTRLS */
      for (i = 0; i < 4; i++) {
        /* 'trimmer2:57' u0(iu) = u0(iu) + constants.DELCLIN(iu); */
        u0[i]++;
        /* 'trimmer2:58' [xdotav_p, x0, xdot0,~] =
         * RunRevs(x0,u0,xdot0,dt,constants); */
        RunRevs(x0, u0, xdot0, &b_constants, b_err, a__1);
        /* 'trimmer2:59' u0(iu) = u0(iu) - 2*constants.DELCLIN(iu); */
        u0[i] -= 2.0;
        /* 'trimmer2:60' [xdotav_n, x0, xdot0,~] =
         * RunRevs(x0,u0,xdot0,dt,constants); */
        RunRevs(x0, u0, xdot0, &b_constants, xdotav_n, a__1);
        /* 'trimmer2:61' u0(iu) = u0(iu) + constants.DELCLIN(iu); */
        u0[i]++;
        /* 'trimmer2:62' icol = icol + 1; */
        /* 'trimmer2:63' Jac(:,icol) =
         * (xdotav_p-xdotav_n)/(2.*constants.DELCLIN(iu)); */
        for (ix = 0; ix <= 10; ix += 2) {
          r = _mm_loadu_pd(&b_err[ix]);
          r2 = _mm_loadu_pd(&xdotav_n[ix]);
          _mm_storeu_pd(&Jac[ix + 12 * (i + 8)],
                        _mm_div_pd(_mm_sub_pd(r, r2), _mm_set1_pd(2.0)));
        }
      }
    }
    /*  Newton Raphson Step */
    /* 'trimmer2:68' trimvec = trimvec - constants.TRIMRELAX*pinv(Jac)*err; */
    pinv(Jac, dv30);
    for (i = 0; i < 12; i++) {
      xf_tmp = 0.0;
      for (ix = 0; ix < 12; ix++) {
        xf_tmp += 0.5 * dv30[i + 12 * ix] * err[ix];
      }
      trimvec[i] -= xf_tmp;
    }
    /* 'trimmer2:69' x0(constants.TRIMSTATE) = trimvec(1:nTrimState); */
    for (i = 0; i < 8; i++) {
      x0[(int)b_constants.TRIMSTATE[i] - 1] = trimvec[i];
    }
    /* 'trimmer2:70' u0(constants.TRIMCTRL) = trimvec(nTrimState+(1:nTrimCtrl));
     */
    u0[(int)b_constants.TRIMCTRL[0] - 1] = trimvec[8];
    u0[(int)b_constants.TRIMCTRL[1] - 1] = trimvec[9];
    u0[(int)b_constants.TRIMCTRL[2] - 1] = trimvec[10];
    u0[(int)b_constants.TRIMCTRL[3] - 1] = trimvec[11];
    /* Step through desired revolutions, take average accel */
    /* 'trimmer2:73' [xdotav, x0, xdot0,y0] = RunRevs(x0,u0,xdot0,dt,constants);
     */
    RunRevs(x0, u0, xdot0, &b_constants, err, b_y0);
    /*  Calculate the error between the target and the averaged state derivative
     */
    /* 'trimmer2:75' err = xdotav - target; */
    /* 'trimmer2:77' NormErr = norm(err./constants.XSCALE(constants.TRIMTARG));
     */
    for (i = 0; i <= 10; i += 2) {
      r = _mm_loadu_pd(&err[i]);
      r2 = _mm_loadu_pd(&xf[i]);
      r = _mm_sub_pd(r, r2);
      _mm_storeu_pd(&err[i], r);
      r2 = _mm_loadu_pd(&NormErr_tmp[i]);
      _mm_storeu_pd(&b_err[i], _mm_div_pd(r, r2));
    }
    NormErr = b_norm(b_err);
    /* 'trimmer2:78' fprintf("Trim Iteration: %i  Normalized Error: %8.5f
     * \n",int16(it),NormErr); */
    printf("Trim Iteration: %i  Normalized Error: %8.5f \n", (short)it,
           NormErr);
    fflush(stdout);
    /* Check convergence */
    /* 'trimmer2:81' if (NormErr < constants.TRIMTOL) */
    if (NormErr < 1.0E-5) {
      /* 'trimmer2:82' done = 1; */
      /* 'trimmer2:83' itrim = 1; */
      *itrim = 1.0;
      /* 'trimmer2:84' fprintf("Trim Converged!\n"); */
      printf("Trim Converged!\n");
      fflush(stdout);
      exitg1 = 1;
    } else if (it > 100) {
      /* 'trimmer2:85' elseif (it>constants.TRIMITMAX) */
      /* 'trimmer2:86' done = 1; */
      /* 'trimmer2:87' warning("Trimmer did not converge"); */
      exitg1 = 1;
    }
  } while (exitg1 == 0);
  /* 'InitFcnH60:80' constants.IDEALENG = IDEAL_save; */
  constants->IDEALENG = 0.0;
}

/* End of code generation (InitFcnH60.c) */
