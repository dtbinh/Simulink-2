/*
 * Movement.c
 *
 * Code generation for model "Movement".
 *
 * Model version              : 1.328
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Mon Jun 01 09:13:37 2015
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Movement.h"
#include "Movement_private.h"

/* Block signals (auto storage) */
B_Movement_T Movement_B;

/* Continuous states */
X_Movement_T Movement_X;

/* Block states (auto storage) */
DW_Movement_T Movement_DW;

/* Real-time model */
RT_MODEL_Movement_T Movement_M_;
RT_MODEL_Movement_T *const Movement_M = &Movement_M_;

/* Forward declaration for local functions */
static void Movement_quatmultiply(const real_T q[4], const real_T r[4], real_T
  qout[4]);
static void Movement_eml_xscal(real_T a, real_T *x);
static void Movement_eml_xscal_c(real_T a, real_T x[9], int32_T ix0);
static void Movement_eml_xswap(real_T x[9], int32_T ix0, int32_T iy0);
static void Movement_eml_xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
static void Movement_eml_xrot(real_T x[9], int32_T iy0, real_T c, real_T s);
static real_T Movement_eml_xdotc(int32_T n, const real_T x[9], int32_T ix0,
  const real_T y[9], int32_T iy0);
static void Movement_eml_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[9],
  int32_T iy0);
static void Movement_svd(const real_T A[3], real_T *U, real_T S[3], real_T V[9]);
static void Movement_quatmultiply_g(const real_T q[4], const real_T r[4], real_T
  qout[4]);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 19;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Movement_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Movement_step();
  Movement_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Movement_step();
  Movement_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for atomic system:
 *    '<Root>/q_mtr 1'
 *    '<Root>/q_mtr 2'
 *    '<Root>/q_mtr 3'
 *    '<Root>/q_mtr 4'
 */
void Movement_q_mtr1(const real_T rtu_motor[2], B_q_mtr1_Movement_T *localB)
{
  real_T q_gamma_idx_0;
  real_T q_gamma_idx_2;
  real_T q_delta_idx_0;
  real_T q_delta_idx_1;

  /* MATLAB Function 'q_mtr 1': '<S7>:1' */
  /* '<S7>:1:3' */
  /* '<S7>:1:4' */
  /* '<S7>:1:5' */
  q_gamma_idx_0 = cos(rtu_motor[0] / 2.0);
  q_gamma_idx_2 = sin(rtu_motor[0] / 2.0);

  /* '<S7>:1:6' */
  q_delta_idx_0 = cos(rtu_motor[1] / 2.0);
  q_delta_idx_1 = sin(rtu_motor[1] / 2.0);

  /* '<S7>:1:7' */
  localB->q_mtr[0] = (q_gamma_idx_0 * q_delta_idx_0 - 0.0 * q_delta_idx_1) -
    q_gamma_idx_2 * 0.0;
  localB->q_mtr[1] = (q_gamma_idx_0 * q_delta_idx_1 + q_delta_idx_0 * 0.0) +
    q_gamma_idx_2 * 0.0;
  localB->q_mtr[2] = (q_gamma_idx_0 * 0.0 + q_delta_idx_0 * q_gamma_idx_2) + 0.0
    * q_delta_idx_1;
  localB->q_mtr[3] = (q_gamma_idx_0 * 0.0 + q_delta_idx_0 * 0.0) + (0.0 -
    q_gamma_idx_2 * q_delta_idx_1);

  /* '<S7>:1:8' */
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_quatmultiply(const real_T q[4], const real_T r[4], real_T
  qout[4])
{
  qout[0] = ((q[0] * r[0] - q[1] * r[1]) - q[2] * r[2]) - q[3] * r[3];
  qout[1] = (q[0] * r[1] + r[0] * q[1]) + (q[2] * r[3] - q[3] * r[2]);
  qout[2] = (q[0] * r[2] + r[0] * q[2]) + (q[3] * r[1] - q[1] * r[3]);
  qout[3] = (q[0] * r[3] + r[0] * q[3]) + (q[1] * r[2] - q[2] * r[1]);
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xscal(real_T a, real_T *x)
{
  *x *= a;
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xscal_c(real_T a, real_T x[9], int32_T ix0)
{
  int32_T k;
  for (k = ix0; k <= ix0 + 2; k++) {
    x[k - 1] *= a;
  }
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xswap(real_T x[9], int32_T ix0, int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  real_T temp;
  ix = ix0 - 1;
  iy = iy0 - 1;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
  ix++;
  iy++;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
  ix++;
  iy++;
  temp = x[ix];
  x[ix] = x[iy];
  x[iy] = temp;
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xrotg(real_T *a, real_T *b, real_T *c, real_T *s)
{
  real_T roe;
  real_T absa;
  real_T absb;
  real_T scale;
  real_T ads;
  real_T bds;
  roe = *b;
  absa = fabs(*a);
  absb = fabs(*b);
  if (absa > absb) {
    roe = *a;
  }

  scale = absa + absb;
  if (scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    ads = 0.0;
    scale = 0.0;
  } else {
    ads = absa / scale;
    bds = absb / scale;
    ads = sqrt(ads * ads + bds * bds) * scale;
    if (roe < 0.0) {
      ads = -ads;
    }

    *c = *a / ads;
    *s = *b / ads;
    if (absa > absb) {
      scale = *s;
    } else if (*c != 0.0) {
      scale = 1.0 / *c;
    } else {
      scale = 1.0;
    }
  }

  *a = ads;
  *b = scale;
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xrot(real_T x[9], int32_T iy0, real_T c, real_T s)
{
  int32_T iy;
  real_T temp;
  iy = iy0 - 1;
  temp = c * x[0] + s * x[iy];
  x[iy] = c * x[iy] - s * x[0];
  x[0] = temp;
  iy++;
  temp = c * x[1] + s * x[iy];
  x[iy] = c * x[iy] - s * x[1];
  x[1] = temp;
  iy++;
  temp = c * x[2] + s * x[iy];
  x[iy] = c * x[iy] - s * x[2];
  x[2] = temp;
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static real_T Movement_eml_xdotc(int32_T n, const real_T x[9], int32_T ix0,
  const real_T y[9], int32_T iy0)
{
  real_T d;
  int32_T ix;
  int32_T iy;
  int32_T k;
  d = 0.0;
  if (!(n < 1)) {
    ix = ix0;
    iy = iy0;
    for (k = 1; k <= n; k++) {
      d += x[ix - 1] * y[iy - 1];
      ix++;
      iy++;
    }
  }

  return d;
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_eml_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y[9],
  int32_T iy0)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  if (!((n < 1) || (a == 0.0))) {
    ix = ix0 - 1;
    iy = iy0 - 1;
    for (k = 0; k < n; k++) {
      y[iy] += a * y[ix];
      ix++;
      iy++;
    }
  }
}

/* Function for MATLAB Function: '<Root>/Plot Function' */
static void Movement_svd(const real_T A[3], real_T *U, real_T S[3], real_T V[9])
{
  real_T s[2];
  real_T e[3];
  int32_T q;
  int32_T m;
  int32_T iter;
  real_T snorm;
  int32_T kase;
  int32_T qs;
  real_T f;
  real_T sm;
  real_T sqds;
  real_T nrm;
  int32_T b_q;
  real_T scale;
  real_T varargin_1[5];
  real_T mtmp;
  int32_T ixstart;
  boolean_T exitg2;
  memset(&V[0], 0, 9U * sizeof(real_T));
  e[1] = A[1];
  e[2] = A[2];
  scale = 2.2250738585072014E-308;
  sm = fabs(A[1]);
  if (sm > 2.2250738585072014E-308) {
    nrm = 1.0;
    scale = sm;
  } else {
    f = sm / 2.2250738585072014E-308;
    nrm = f * f;
  }

  sm = fabs(A[2]);
  if (sm > scale) {
    f = scale / sm;
    nrm = nrm * f * f + 1.0;
    scale = sm;
  } else {
    f = sm / scale;
    nrm += f * f;
  }

  nrm = scale * sqrt(nrm);
  if (nrm == 0.0) {
    e[0] = 0.0;
  } else {
    if (A[1] < 0.0) {
      nrm = -nrm;
    }

    e[0] = nrm;
    if (fabs(nrm) >= 1.0020841800044864E-292) {
      nrm = 1.0 / nrm;
      e[1] = nrm * A[1];
      e[2] = nrm * A[2];
    } else {
      e[1] = A[1] / nrm;
      e[2] = A[2] / nrm;
    }

    e[1]++;
    e[0] = -e[0];
  }

  V[1] = e[1];
  V[2] = e[2];
  m = 2;
  s[0] = A[0];
  s[1] = 0.0;
  e[1] = 0.0;
  *U = 1.0;
  for (b_q = 2; b_q >= 0; b_q += -1) {
    if ((b_q + 1 <= 1) && (e[0] != 0.0)) {
      Movement_eml_xaxpy(2, -(Movement_eml_xdotc(2, V, 2, V, 5) / V[1]), 2, V, 5);
      Movement_eml_xaxpy(2, -(Movement_eml_xdotc(2, V, 2, V, 8) / V[1]), 2, V, 8);
    }

    V[3 * b_q] = 0.0;
    V[1 + 3 * b_q] = 0.0;
    V[2 + 3 * b_q] = 0.0;
    V[b_q + 3 * b_q] = 1.0;
  }

  sm = e[0];
  if (A[0] != 0.0) {
    scale = fabs(A[0]);
    nrm = A[0] / scale;
    s[0] = scale;
    sm = e[0] / nrm;
    Movement_eml_xscal(nrm, U);
  }

  if (sm != 0.0) {
    scale = fabs(sm);
    nrm = scale / sm;
    sm = scale;
    s[1] = 0.0 * nrm;
    Movement_eml_xscal_c(nrm, V, 4);
  }

  e[0] = sm;
  iter = 0;
  snorm = 0.0;
  if ((s[0] >= sm) || rtIsNaN(sm)) {
    sm = s[0];
  }

  if (!((0.0 >= sm) || rtIsNaN(sm))) {
    snorm = sm;
  }

  if (s[1] >= 0.0) {
    sm = s[1];
  } else {
    sm = 0.0;
  }

  if (!((snorm >= sm) || rtIsNaN(sm))) {
    snorm = sm;
  }

  while ((m > 0) && (!(iter >= 75))) {
    ixstart = m - 1;
    do {
      kase = 0;
      q = ixstart;
      if (ixstart == 0) {
        kase = 1;
      } else {
        nrm = fabs(e[0]);
        if ((nrm <= (fabs(s[0]) + fabs(s[1])) * 2.2204460492503131E-16) || (nrm <=
             1.0020841800044864E-292) || ((iter > 20) && (nrm <=
              2.2204460492503131E-16 * snorm))) {
          e[0] = 0.0;
          kase = 1;
        } else {
          ixstart = 0;
        }
      }
    } while (kase == 0);

    if (m - 1 == ixstart) {
      kase = 4;
    } else {
      qs = m;
      b_q = m;
      exitg2 = false;
      while ((!exitg2) && (b_q >= ixstart)) {
        qs = b_q;
        if (b_q == ixstart) {
          exitg2 = true;
        } else {
          nrm = 0.0;
          if (b_q < m) {
            nrm = fabs(e[0]);
          }

          if (b_q > ixstart + 1) {
            nrm += fabs(e[0]);
          }

          scale = fabs(s[b_q - 1]);
          if ((scale <= 2.2204460492503131E-16 * nrm) || (scale <=
               1.0020841800044864E-292)) {
            s[b_q - 1] = 0.0;
            exitg2 = true;
          } else {
            b_q--;
          }
        }
      }

      if (qs == ixstart) {
        kase = 3;
      } else {
        if (qs != m) {
          kase = 2;
          q = qs;
        }
      }
    }

    switch (kase) {
     case 1:
      f = e[0];
      e[0] = 0.0;
      kase = m - 1;
      while (kase >= q + 1) {
        nrm = s[0];
        Movement_eml_xrotg(&nrm, &f, &scale, &sm);
        s[0] = nrm;
        Movement_eml_xrot(V, 1 + 3 * (m - 1), scale, sm);
        kase = 0;
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0;
      while (q + 1 <= m) {
        nrm = s[q];
        Movement_eml_xrotg(&nrm, &f, &scale, &sm);
        s[q] = nrm;
        f = -sm * e[q];
        e[q] *= scale;
        *U = scale * *U + sm * *U;
        q++;
      }
      break;

     case 3:
      varargin_1[0] = fabs(s[m - 1]);
      varargin_1[1] = fabs(s[0]);
      varargin_1[2] = fabs(e[0]);
      varargin_1[3] = fabs(s[q]);
      varargin_1[4] = fabs(e[q]);
      ixstart = 1;
      mtmp = varargin_1[0];
      if (rtIsNaN(varargin_1[0])) {
        b_q = 2;
        exitg2 = false;
        while ((!exitg2) && (b_q < 6)) {
          ixstart = b_q;
          if (!rtIsNaN(varargin_1[b_q - 1])) {
            mtmp = varargin_1[b_q - 1];
            exitg2 = true;
          } else {
            b_q++;
          }
        }
      }

      if (ixstart < 5) {
        while (ixstart + 1 < 6) {
          if (varargin_1[ixstart] > mtmp) {
            mtmp = varargin_1[ixstart];
          }

          ixstart++;
        }
      }

      sm = s[m - 1] / mtmp;
      nrm = s[0] / mtmp;
      scale = e[0] / mtmp;
      sqds = s[q] / mtmp;
      f = ((nrm + sm) * (nrm - sm) + scale * scale) / 2.0;
      nrm = sm * scale;
      nrm *= nrm;
      if ((f != 0.0) || (nrm != 0.0)) {
        scale = sqrt(f * f + nrm);
        if (f < 0.0) {
          scale = -scale;
        }

        scale = nrm / (f + scale);
      } else {
        scale = 0.0;
      }

      f = (sqds + sm) * (sqds - sm) + scale;
      sm = e[q] / mtmp * sqds;
      kase = q;
      while (kase + 1 <= 1) {
        Movement_eml_xrotg(&f, &sm, &nrm, &scale);
        f = nrm * s[0] + scale * e[0];
        e[0] = nrm * e[0] - scale * s[0];
        sm = scale * s[1];
        s[1] *= nrm;
        Movement_eml_xrot(V, 4, nrm, scale);
        Movement_eml_xrotg(&f, &sm, &nrm, &scale);
        s[0] = f;
        f = nrm * e[0] + scale * s[1];
        s[1] = -scale * e[0] + nrm * s[1];
        sm = scale * e[1];
        e[1] *= nrm;
        kase = 1;
      }

      e[0] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0) {
        s[q] = -s[q];
        Movement_eml_xscal_c(-1.0, V, 1 + 3 * q);
      }

      while ((q + 1 < 2) && (s[0] < s[1])) {
        scale = s[0];
        s[0] = s[1];
        s[1] = scale;
        Movement_eml_xswap(V, 1, 4);
        q = 1;
      }

      iter = 0;
      m--;
      break;
    }
  }

  S[1] = 0.0;
  S[2] = 0.0;
  S[0] = s[0];
}

/* Function for MATLAB Function: '<Root>/Velocities' */
static void Movement_quatmultiply_g(const real_T q[4], const real_T r[4], real_T
  qout[4])
{
  qout[0] = ((q[0] * r[0] - q[1] * r[1]) - q[2] * r[2]) - q[3] * r[3];
  qout[1] = (q[0] * r[1] + r[0] * q[1]) + (q[2] * r[3] - q[3] * r[2]);
  qout[2] = (q[0] * r[2] + r[0] * q[2]) + (q[3] * r[1] - q[1] * r[3]);
  qout[3] = (q[0] * r[3] + r[0] * q[3]) + (q[1] * r[2] - q[2] * r[1]);
}

/* Model step function */
void Movement_step(void)
{
  /* local block i/o variables */
  real_T rtb_QuaternionAttitude[4];
  real_T rtb_Clock;
  real_T Q[4];
  real_T Q_conj[4];
  real_T L2[4];
  real_T N_w[3];
  real_T Q_mtr1[4];
  real_T qm;
  real_T scale;
  real_T V[9];
  static const real_T b[4] = { 0.0, 0.0, 0.0, 1.0 };

  real_T E[3];
  real_T absxk;
  real_T t;
  real_T tmp[4];
  real_T tmp_0[4];
  real_T L2_0[3];
  real_T tmp_1[4];
  real_T tmp_2[4];
  real_T tmp_3[4];
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* set solver stop time */
    if (!(Movement_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Movement_M->solverInfo,
                            ((Movement_M->Timing.clockTickH0 + 1) *
        Movement_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Movement_M->solverInfo,
                            ((Movement_M->Timing.clockTick0 + 1) *
        Movement_M->Timing.stepSize0 + Movement_M->Timing.clockTickH0 *
        Movement_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Movement_M)) {
    Movement_M->Timing.t[0] = rtsiGetT(&Movement_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Constant: '<S4>/Q0' */
    Movement_B.Q0[0] = Movement_P.Q0_Value[0];
    Movement_B.Q0[1] = Movement_P.Q0_Value[1];
    Movement_B.Q0[2] = Movement_P.Q0_Value[2];
    Movement_B.Q0[3] = Movement_P.Q0_Value[3];
  }

  /* Integrator: '<Root>/Quaternion Attitude' */
  if (Movement_DW.QuaternionAttitude_IWORK.IcNeedsLoading) {
    Movement_X.Quaternion[0] = Movement_B.Q0[0];
    Movement_X.Quaternion[1] = Movement_B.Q0[1];
    Movement_X.Quaternion[2] = Movement_B.Q0[2];
    Movement_X.Quaternion[3] = Movement_B.Q0[3];
  }

  rtb_QuaternionAttitude[0] = Movement_X.Quaternion[0];
  rtb_QuaternionAttitude[1] = Movement_X.Quaternion[1];
  rtb_QuaternionAttitude[2] = Movement_X.Quaternion[2];
  rtb_QuaternionAttitude[3] = Movement_X.Quaternion[3];
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Constant: '<S4>/XYZ 0' */
    Movement_B.XYZ0[0] = Movement_P.XYZ0_Value[0];
    Movement_B.XYZ0[1] = Movement_P.XYZ0_Value[1];
    Movement_B.XYZ0[2] = Movement_P.XYZ0_Value[2];
  }

  /* Integrator: '<Root>/Linear Inertial Position' */
  if (Movement_DW.LinearInertialPosition_IWORK.IcNeedsLoading) {
    Movement_X.LinearInertialPosition_CSTATE[0] = Movement_B.XYZ0[0];
    Movement_X.LinearInertialPosition_CSTATE[1] = Movement_B.XYZ0[1];
    Movement_X.LinearInertialPosition_CSTATE[2] = Movement_B.XYZ0[2];
  }

  Movement_B.LinearInertialPosition[0] =
    Movement_X.LinearInertialPosition_CSTATE[0];
  Movement_B.LinearInertialPosition[1] =
    Movement_X.LinearInertialPosition_CSTATE[1];
  Movement_B.LinearInertialPosition[2] =
    Movement_X.LinearInertialPosition_CSTATE[2];

  /* Clock: '<Root>/Clock' */
  rtb_Clock = Movement_M->Timing.t[0];
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* MATLAB Function: '<Root>/q_mtr 1' incorporates:
     *  Constant: '<Root>/Motor 1'
     */
    Movement_q_mtr1(Movement_P.Motor1_Value, &Movement_B.sf_q_mtr1);

    /* MATLAB Function: '<Root>/q_mtr 2' incorporates:
     *  Constant: '<Root>/Motor 2'
     */
    Movement_q_mtr1(Movement_P.Motor2_Value, &Movement_B.sf_q_mtr2);

    /* MATLAB Function: '<Root>/q_mtr 3' incorporates:
     *  Constant: '<Root>/Motor 3'
     */
    Movement_q_mtr1(Movement_P.Motor3_Value, &Movement_B.sf_q_mtr3);

    /* MATLAB Function: '<Root>/q_mtr 4' incorporates:
     *  Constant: '<Root>/Motor 4'
     */
    Movement_q_mtr1(Movement_P.Motor4_Value, &Movement_B.sf_q_mtr4);
  }

  /* MATLAB Function: '<Root>/Plot Function' */
  /* MATLAB Function 'Plot Function': '<S5>:1' */
  /* Input t */
  /* CG Cartesian Co-ordinates */
  /* '<S5>:1:4' */
  /* X Position */
  /* '<S5>:1:5' */
  /* Y Position */
  /* '<S5>:1:6' */
  /* Z Position */
  /* Calculate Motor Positions relative to 0;0;0 */
  /* l may be variable */
  /* '<S5>:1:9' */
  /* '<S5>:1:10' */
  /* '<S5>:1:11' */
  /* '<S5>:1:12' */
  /* %Calculate Body Attidue (Normal Vector) */
  /* '<S5>:1:14' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(rtb_QuaternionAttitude[0]);
  if (absxk > 2.2250738585072014E-308) {
    qm = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    qm = t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[1]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[2]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[3]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  qm = scale * sqrt(qm);
  Q[0] = rtb_QuaternionAttitude[0] / qm;
  Q[1] = rtb_QuaternionAttitude[1] / qm;
  Q[2] = rtb_QuaternionAttitude[2] / qm;
  Q[3] = rtb_QuaternionAttitude[3] / qm;

  /* Body Quaternion, read from d/dt(Q) */
  /* '<S5>:1:15' */
  Q_conj[0] = Q[0];
  Q_conj[1] = -Q[1];
  Q_conj[2] = -Q[2];
  Q_conj[3] = -(rtb_QuaternionAttitude[3] / qm);

  /* Quaternion conjugate */
  /* normal vector in Body frame */
  /* Build normal quaternion */
  /* '<S5>:1:18' */
  /* '<S5>:1:19' */
  Movement_quatmultiply(Q_conj, b, tmp_2);
  Movement_quatmultiply(tmp_2, Q, L2);

  /* Normal rotated by Body Quaternion */
  /* '<S5>:1:20' */
  N_w[0] = L2[1];
  N_w[1] = L2[2];
  N_w[2] = L2[3];

  /* Normal vector in inertial frame */
  /* %Calculate Motor 1 Attitudes */
  /* '<S5>:1:22' */
  /* XYZ position of motor 1 from CG */
  /* '<S5>:1:23' */
  /* '<S5>:1:24' */
  /* Rotate rotor arm by body quaternion */
  /* '<S5>:1:25' */
  /* Calculate new XYZ position using attitude quaternion */
  /* k considered to be normal for motor 1 (Force acting just in the Z-direction) */
  /* '<S5>:1:27' */
  Q_mtr1[0] = Movement_B.sf_q_mtr1.q_mtr[0];
  Q_mtr1[1] = Movement_B.sf_q_mtr1.q_mtr[1];
  Q_mtr1[2] = Movement_B.sf_q_mtr1.q_mtr[2];
  Q_mtr1[3] = Movement_B.sf_q_mtr1.q_mtr[3];

  /* Calculate motor 1 attitude from motor 1 quaternion */
  /* '<S5>:1:28' */
  L2[0] = Movement_B.sf_q_mtr1.q_mtr[0];
  L2[1] = -Movement_B.sf_q_mtr1.q_mtr[1];
  L2[2] = -Movement_B.sf_q_mtr1.q_mtr[2];
  L2[3] = -Movement_B.sf_q_mtr1.q_mtr[3];

  /* '<S5>:1:29' */
  /* '<S5>:1:30' */
  /* '<S5>:1:31' */
  /* '<S5>:1:32' */
  Movement_quatmultiply(L2, b, tmp_2);
  Movement_quatmultiply(tmp_2, Q_mtr1, tmp_3);
  Movement_quatmultiply(Q_conj, tmp_3, tmp_1);
  Movement_quatmultiply(tmp_1, Q, L2);

  /* '<S5>:1:33' */
  /* Motor 1 Normal Vector */
  /* %Calculate Motor 3 Attitudes */
  /* '<S5>:1:35' */
  /* '<S5>:1:36' */
  /* '<S5>:1:37' */
  /* '<S5>:1:38' */
  /* Calculate motor 3 attitude from motor 3 quaternion */
  /* Q_mtr3_conj = quatconj(Q_mtr3); */
  /* L1 = quatmultiply(Q_mtr3_conj,L_3); */
  /* L2 = quatmultiply(L1,Q_mtr3); */
  /* mtr3_N = [L2(2) L2(3) L2(4)]; %Motor 3 Normal Vector */
  /* %Calculate Motor 2 Attitudes */
  /* '<S5>:1:46' */
  /* '<S5>:1:47' */
  /* '<S5>:1:48' */
  /* '<S5>:1:49' */
  /* N_2 = [0 0 1]; */
  /* L_2 = [0 N_2(1) N_2(2) N_2(3)]; */
  /* Q_mtr2 = qmtr2.'; %Calculate motor 2 attitude from motor 2 quaternion */
  /* Q_mtr2_conj = quatconj(Q_mtr2); */
  /* L1 = quatmultiply(Q_mtr2_conj,L_2); */
  /* L2 = quatmultiply(L1,Q_mtr2); */
  /* mtr2_N = [L2(2) L2(3) L2(4)]; %Motor 2 Normal Vector */
  /* %Calculate Motor 4 Attitudes */
  /* '<S5>:1:58' */
  /* '<S5>:1:59' */
  /* '<S5>:1:60' */
  /* '<S5>:1:61' */
  /* N_4 = [0 0 1]; */
  /* L_4 = [0 N_4(1) N_4(2) N_4(3)]; */
  /* Q_mtr4 = qmtr4.'; %Calculate motor 4 attitude from motor 4 quaternion */
  /* Q_mtr4_conj = quatconj(Q_mtr4); */
  /* L1 = quatmultiply(Q_mtr4_conj,L_4); */
  /* L2 = quatmultiply(L1,Q_mtr4); */
  /* mtr4_N = [L2(2) L2(3) L2(4)]; %Motor 4 Normal Vector */
  /* %Open Figure if first time instance */
  /* %Clear and Construct Figure */
  /* %Display Time */
  /* disp(t); */
  /* %Plot Quad Function */
  /* Taken from: http://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d */
  /* Author: Christian Reinbacher */
  L2_0[0] = L2[1];
  L2_0[1] = L2[2];
  L2_0[2] = L2[3];
  Movement_svd(L2_0, &qm, E, V);

  /* Taken from: http://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d */
  /* Author: Christian Reinbacher */
  Movement_svd(N_w, &qm, E, V);

  /* Taken from: http://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d */
  /* Author: Christian Reinbacher */
  Movement_svd(N_w, &qm, E, V);

  /* Taken from: http://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d */
  /* Author: Christian Reinbacher */
  Movement_svd(N_w, &qm, E, V);

  /* Taken from: http://www.mathworks.com/matlabcentral/fileexchange/26588-plot-circle-in-3d */
  /* Author: Christian Reinbacher */
  Movement_svd(N_w, &qm, E, V);

  /* End of MATLAB Function: '<Root>/Plot Function' */
  /* % */
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Constant: '<S4>/dE0' */
    Movement_B.dE0[0] = Movement_P.dE0_Value[0];
    Movement_B.dE0[1] = Movement_P.dE0_Value[1];
    Movement_B.dE0[2] = Movement_P.dE0_Value[2];
  }

  /* Integrator: '<Root>/Angular Velocity' */
  if (Movement_DW.AngularVelocity_IWORK.IcNeedsLoading) {
    Movement_X.AngularVelocity_CSTATE[0] = Movement_B.dE0[0];
    Movement_X.AngularVelocity_CSTATE[1] = Movement_B.dE0[1];
    Movement_X.AngularVelocity_CSTATE[2] = Movement_B.dE0[2];
  }

  Movement_B.AngularVelocity[0] = Movement_X.AngularVelocity_CSTATE[0];
  Movement_B.AngularVelocity[1] = Movement_X.AngularVelocity_CSTATE[1];
  Movement_B.AngularVelocity[2] = Movement_X.AngularVelocity_CSTATE[2];
  if (rtmIsMajorTimeStep(Movement_M)) {
  }

  /* MATLAB Function 'Calc Force': '<S2>:1' */
  /* '<S2>:1:3' */
  /* '<S2>:1:4' */
  /* '<S2>:1:5' */
  /* '<S2>:1:6' */
  /* MATLAB Function 'Calc Torque': '<S3>:1' */
  /* '<S3>:1:3' */
  /* '<S3>:1:4' */
  /* '<S3>:1:5' */
  /* '<S3>:1:6' */
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Constant: '<S4>/dV0' */
    Movement_B.dV0[0] = Movement_P.dV0_Value[0];
    Movement_B.dV0[1] = Movement_P.dV0_Value[1];
    Movement_B.dV0[2] = Movement_P.dV0_Value[2];
  }

  /* Integrator: '<Root>/Linear Velocity' */
  if (Movement_DW.LinearVelocity_IWORK.IcNeedsLoading) {
    Movement_X.LinearVelocity_CSTATE[0] = Movement_B.dV0[0];
    Movement_X.LinearVelocity_CSTATE[1] = Movement_B.dV0[1];
    Movement_X.LinearVelocity_CSTATE[2] = Movement_B.dV0[2];
  }

  Movement_B.LinearVelocity[0] = Movement_X.LinearVelocity_CSTATE[0];
  Movement_B.LinearVelocity[1] = Movement_X.LinearVelocity_CSTATE[1];
  Movement_B.LinearVelocity[2] = Movement_X.LinearVelocity_CSTATE[2];

  /* MATLAB Function: '<Root>/Accelerations' incorporates:
   *  Constant: '<S4>/Inertia'
   *  Constant: '<S4>/m'
   *  MATLAB Function: '<Root>/Calc Torque'
   */
  /* MATLAB Function 'Accelerations': '<S1>:1' */
  /* variable mass */
  /* %Mass Moment of Inertia */
  /* '<S1>:1:4' */
  /* '<S1>:1:5' */
  /* '<S1>:1:6' */
  /* Kg.Nm */
  /* %control action */
  /* %All in F_b */
  /* %Force Inputs */
  /* '<S1>:1:10' */
  /* '<S1>:1:11' */
  /* '<S1>:1:12' */
  /* '<S1>:1:13' */
  /* N */
  /* %Torque Inputs */
  /* '<S1>:1:15' */
  /* '<S1>:1:16' */
  /* '<S1>:1:17' */
  /* Nm */
  /* %current state translational velocity */
  /* '<S1>:1:20' */
  /* '<S1>:1:21' */
  /* '<S1>:1:22' */
  /* '<S1>:1:23' */
  /* m.s^-1 */
  /* %current state angular velocity */
  /* '<S1>:1:25' */
  /* '<S1>:1:26' */
  /* '<S1>:1:27' */
  /* '<S1>:1:28' */
  /* rad.s^-1 */
  /* %Angular accelerations in Body Frame */
  /* '<S1>:1:30' */
  /* '<S1>:1:31' */
  /* '<S1>:1:32' */
  /* '<S1>:1:33' */
  Movement_B.dE[0] = 0.0;
  Movement_B.dE[1] = 0.0;
  Movement_B.dE[2] = 0.0;

  /* rad.s^-2 */
  /* '<S1>:1:34' */
  Movement_B.dE[0] = ((Movement_P.Inertia_Value[1] - Movement_P.Inertia_Value[2])
                      * Movement_B.AngularVelocity[1] *
                      Movement_B.AngularVelocity[2] + 0.01) * (1.0 /
    Movement_P.Inertia_Value[0]);

  /* '<S1>:1:35' */
  Movement_B.dE[1] = ((Movement_P.Inertia_Value[2] - Movement_P.Inertia_Value[0])
                      * Movement_B.AngularVelocity[0] *
                      Movement_B.AngularVelocity[2] + 0.01) * (1.0 /
    Movement_P.Inertia_Value[1]);

  /* '<S1>:1:36' */
  Movement_B.dE[2] = (Movement_P.Inertia_Value[0] - Movement_P.Inertia_Value[1])
    * Movement_B.AngularVelocity[0] * Movement_B.AngularVelocity[1] * (1.0 /
    Movement_P.Inertia_Value[2]);

  /* %Linear accelerations in Body Frame */
  /* '<S1>:1:38' */
  qm = 1.0 / Movement_P.m_Value;
  Movement_B.dV[0] = (Movement_B.AngularVelocity[1] * Movement_B.LinearVelocity
                      [2] - Movement_B.AngularVelocity[2] *
                      Movement_B.LinearVelocity[1]) + qm;
  Movement_B.dV[1] = (Movement_B.AngularVelocity[2] * Movement_B.LinearVelocity
                      [0] - Movement_B.AngularVelocity[0] *
                      Movement_B.LinearVelocity[2]) + qm;
  Movement_B.dV[2] = (Movement_B.AngularVelocity[0] * Movement_B.LinearVelocity
                      [1] - Movement_B.AngularVelocity[1] *
                      Movement_B.LinearVelocity[0]) + -qm;

  /* MATLAB Function: '<Root>/Velocities' */
  /* m.s^-2 */
  /* Integrals take place outside dynamics function */
  /* MATLAB Function 'Velocities': '<S6>:1' */
  /* '<S6>:1:3' */
  /* '<S6>:1:4' */
  /* '<S6>:1:5' */
  scale = 2.2250738585072014E-308;
  absxk = fabs(rtb_QuaternionAttitude[0]);
  if (absxk > 2.2250738585072014E-308) {
    qm = 1.0;
    scale = absxk;
  } else {
    t = absxk / 2.2250738585072014E-308;
    qm = t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[1]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[2]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  absxk = fabs(rtb_QuaternionAttitude[3]);
  if (absxk > scale) {
    t = scale / absxk;
    qm = qm * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    qm += t * t;
  }

  qm = scale * sqrt(qm);
  Q[0] = rtb_QuaternionAttitude[0] / qm;
  Q[1] = rtb_QuaternionAttitude[1] / qm;
  Q[2] = rtb_QuaternionAttitude[2] / qm;
  Q[3] = rtb_QuaternionAttitude[3] / qm;

  /* '<S6>:1:6' */
  Q_conj[0] = Q[0];
  Q_conj[1] = -Q[1];
  Q_conj[2] = -Q[2];
  Q_conj[3] = -(rtb_QuaternionAttitude[3] / qm);

  /* '<S6>:1:7' */
  tmp_0[0] = 0.0;
  tmp_0[1] = Movement_B.AngularVelocity[0];
  tmp_0[2] = Movement_B.AngularVelocity[1];
  tmp_0[3] = Movement_B.AngularVelocity[2];
  Movement_quatmultiply_g(Q, tmp_0, Movement_B.dQ);
  Movement_B.dQ[0] *= 0.5;
  Movement_B.dQ[1] *= 0.5;
  Movement_B.dQ[2] *= 0.5;
  Movement_B.dQ[3] *= 0.5;

  /* ndQ = quatnormalize(dQ); */
  /* '<S6>:1:9' */
  /* '<S6>:1:10' */
  /* '<S6>:1:11' */
  tmp[0] = 0.0;
  tmp[1] = Movement_B.LinearVelocity[0];
  tmp[2] = Movement_B.LinearVelocity[1];
  tmp[3] = Movement_B.LinearVelocity[2];
  Movement_quatmultiply_g(Q_conj, tmp, tmp_2);
  Movement_quatmultiply_g(tmp_2, Q, Q_conj);

  /* '<S6>:1:12' */
  Movement_B.dN[0] = Q_conj[1];
  Movement_B.dN[1] = Q_conj[2];
  Movement_B.dN[2] = Q_conj[3];

  /* End of MATLAB Function: '<Root>/Velocities' */
  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(Movement_M->rtwLogInfo, (Movement_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Movement_M)) {
    /* Update for Integrator: '<Root>/Quaternion Attitude' */
    Movement_DW.QuaternionAttitude_IWORK.IcNeedsLoading = 0;

    /* Update for Integrator: '<Root>/Linear Inertial Position' */
    Movement_DW.LinearInertialPosition_IWORK.IcNeedsLoading = 0;

    /* Update for Integrator: '<Root>/Angular Velocity' */
    Movement_DW.AngularVelocity_IWORK.IcNeedsLoading = 0;

    /* Update for Integrator: '<Root>/Linear Velocity' */
    Movement_DW.LinearVelocity_IWORK.IcNeedsLoading = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(Movement_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(Movement_M)!=-1) &&
          !((rtmGetTFinal(Movement_M)-(((Movement_M->Timing.clockTick1+
               Movement_M->Timing.clockTickH1* 4294967296.0)) * 0.01)) >
            (((Movement_M->Timing.clockTick1+Movement_M->Timing.clockTickH1*
               4294967296.0)) * 0.01) * (DBL_EPSILON))) {
        rtmSetErrorStatus(Movement_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&Movement_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++Movement_M->Timing.clockTick0)) {
      ++Movement_M->Timing.clockTickH0;
    }

    Movement_M->Timing.t[0] = rtsiGetSolverStopTime(&Movement_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      Movement_M->Timing.clockTick1++;
      if (!Movement_M->Timing.clockTick1) {
        Movement_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Movement_derivatives(void)
{
  XDot_Movement_T *_rtXdot;
  _rtXdot = ((XDot_Movement_T *) Movement_M->ModelData.derivs);

  /* Derivatives for Integrator: '<Root>/Quaternion Attitude' */
  {
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->Quaternion[0] =
      Movement_B.dQ[0];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->Quaternion[1] =
      Movement_B.dQ[1];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->Quaternion[2] =
      Movement_B.dQ[2];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->Quaternion[3] =
      Movement_B.dQ[3];
  }

  /* Derivatives for Integrator: '<Root>/Linear Inertial Position' */
  {
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)
      ->LinearInertialPosition_CSTATE[0] = Movement_B.dN[0];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)
      ->LinearInertialPosition_CSTATE[1] = Movement_B.dN[1];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)
      ->LinearInertialPosition_CSTATE[2] = Movement_B.dN[2];
  }

  /* Derivatives for Integrator: '<Root>/Angular Velocity' */
  {
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->AngularVelocity_CSTATE[0]
      = Movement_B.dE[0];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->AngularVelocity_CSTATE[1]
      = Movement_B.dE[1];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->AngularVelocity_CSTATE[2]
      = Movement_B.dE[2];
  }

  /* Derivatives for Integrator: '<Root>/Linear Velocity' */
  {
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->LinearVelocity_CSTATE[0]
      = Movement_B.dV[0];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->LinearVelocity_CSTATE[1]
      = Movement_B.dV[1];
    ((XDot_Movement_T *) Movement_M->ModelData.derivs)->LinearVelocity_CSTATE[2]
      = Movement_B.dV[2];
  }

  /* Derivatives for Integrator: '<Root>/Angular Position' */
  _rtXdot->AngularPosition_CSTATE[0] = Movement_B.AngularVelocity[0];
  _rtXdot->AngularPosition_CSTATE[1] = Movement_B.AngularVelocity[1];
  _rtXdot->AngularPosition_CSTATE[2] = Movement_B.AngularVelocity[2];

  /* Derivatives for Integrator: '<Root>/Linear Position' */
  _rtXdot->LinearPosition_CSTATE[0] = Movement_B.LinearVelocity[0];
  _rtXdot->LinearPosition_CSTATE[1] = Movement_B.LinearVelocity[1];
  _rtXdot->LinearPosition_CSTATE[2] = Movement_B.LinearVelocity[2];
}

/* Model initialize function */
void Movement_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Movement_M, 0,
                sizeof(RT_MODEL_Movement_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Movement_M->solverInfo,
                          &Movement_M->Timing.simTimeStep);
    rtsiSetTPtr(&Movement_M->solverInfo, &rtmGetTPtr(Movement_M));
    rtsiSetStepSizePtr(&Movement_M->solverInfo, &Movement_M->Timing.stepSize0);
    rtsiSetdXPtr(&Movement_M->solverInfo, &Movement_M->ModelData.derivs);
    rtsiSetContStatesPtr(&Movement_M->solverInfo, (real_T **)
                         &Movement_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&Movement_M->solverInfo,
      &Movement_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&Movement_M->solverInfo, (&rtmGetErrorStatus
      (Movement_M)));
    rtsiSetRTModelPtr(&Movement_M->solverInfo, Movement_M);
  }

  rtsiSetSimTimeStep(&Movement_M->solverInfo, MAJOR_TIME_STEP);
  Movement_M->ModelData.intgData.y = Movement_M->ModelData.odeY;
  Movement_M->ModelData.intgData.f[0] = Movement_M->ModelData.odeF[0];
  Movement_M->ModelData.intgData.f[1] = Movement_M->ModelData.odeF[1];
  Movement_M->ModelData.intgData.f[2] = Movement_M->ModelData.odeF[2];
  Movement_M->ModelData.contStates = ((X_Movement_T *) &Movement_X);
  rtsiSetSolverData(&Movement_M->solverInfo, (void *)
                    &Movement_M->ModelData.intgData);
  rtsiSetSolverName(&Movement_M->solverInfo,"ode3");
  rtmSetTPtr(Movement_M, &Movement_M->Timing.tArray[0]);
  rtmSetTFinal(Movement_M, 10.0);
  Movement_M->Timing.stepSize0 = 0.01;
  rtmSetFirstInitCond(Movement_M, 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    Movement_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(Movement_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(Movement_M->rtwLogInfo, (NULL));
    rtliSetLogT(Movement_M->rtwLogInfo, "tout");
    rtliSetLogX(Movement_M->rtwLogInfo, "");
    rtliSetLogXFinal(Movement_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(Movement_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(Movement_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(Movement_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(Movement_M->rtwLogInfo, 1);
    rtliSetLogY(Movement_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(Movement_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(Movement_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &Movement_B), 0,
                sizeof(B_Movement_T));

  /* states (continuous) */
  {
    (void) memset((void *)&Movement_X, 0,
                  sizeof(X_Movement_T));
  }

  /* states (dwork) */
  (void) memset((void *)&Movement_DW, 0,
                sizeof(DW_Movement_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(Movement_M->rtwLogInfo, 0.0, rtmGetTFinal
    (Movement_M), Movement_M->Timing.stepSize0, (&rtmGetErrorStatus(Movement_M)));

  /* Start for Constant: '<S4>/Q0' */
  Movement_B.Q0[0] = Movement_P.Q0_Value[0];
  Movement_B.Q0[1] = Movement_P.Q0_Value[1];
  Movement_B.Q0[2] = Movement_P.Q0_Value[2];
  Movement_B.Q0[3] = Movement_P.Q0_Value[3];

  /* Start for Constant: '<S4>/XYZ 0' */
  Movement_B.XYZ0[0] = Movement_P.XYZ0_Value[0];
  Movement_B.XYZ0[1] = Movement_P.XYZ0_Value[1];
  Movement_B.XYZ0[2] = Movement_P.XYZ0_Value[2];

  /* Start for Constant: '<S4>/dE0' */
  Movement_B.dE0[0] = Movement_P.dE0_Value[0];
  Movement_B.dE0[1] = Movement_P.dE0_Value[1];
  Movement_B.dE0[2] = Movement_P.dE0_Value[2];

  /* Start for Constant: '<S4>/dV0' */
  Movement_B.dV0[0] = Movement_P.dV0_Value[0];
  Movement_B.dV0[1] = Movement_P.dV0_Value[1];
  Movement_B.dV0[2] = Movement_P.dV0_Value[2];

  /* InitializeConditions for Integrator: '<Root>/Quaternion Attitude' */
  if (rtmIsFirstInitCond(Movement_M)) {
    Movement_X.Quaternion[0] = 1.0;
    Movement_X.Quaternion[1] = 0.0;
    Movement_X.Quaternion[2] = 0.0;
    Movement_X.Quaternion[3] = 0.0;
  }

  Movement_DW.QuaternionAttitude_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<Root>/Linear Inertial Position' */
  if (rtmIsFirstInitCond(Movement_M)) {
    Movement_X.LinearInertialPosition_CSTATE[0] = 0.0;
    Movement_X.LinearInertialPosition_CSTATE[1] = 0.0;
    Movement_X.LinearInertialPosition_CSTATE[2] = 2.0;
  }

  Movement_DW.LinearInertialPosition_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<Root>/Angular Velocity' */
  if (rtmIsFirstInitCond(Movement_M)) {
    Movement_X.AngularVelocity_CSTATE[0] = 0.0;
    Movement_X.AngularVelocity_CSTATE[1] = 0.0;
    Movement_X.AngularVelocity_CSTATE[2] = 0.0;
  }

  Movement_DW.AngularVelocity_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<Root>/Linear Velocity' */
  if (rtmIsFirstInitCond(Movement_M)) {
    Movement_X.LinearVelocity_CSTATE[0] = 0.0;
    Movement_X.LinearVelocity_CSTATE[1] = 0.0;
    Movement_X.LinearVelocity_CSTATE[2] = 0.0;
  }

  Movement_DW.LinearVelocity_IWORK.IcNeedsLoading = 1;

  /* InitializeConditions for Integrator: '<Root>/Angular Position' */
  Movement_X.AngularPosition_CSTATE[0] = Movement_P.AngularPosition_IC;
  Movement_X.AngularPosition_CSTATE[1] = Movement_P.AngularPosition_IC;
  Movement_X.AngularPosition_CSTATE[2] = Movement_P.AngularPosition_IC;

  /* InitializeConditions for Integrator: '<Root>/Linear Position' */
  Movement_X.LinearPosition_CSTATE[0] = Movement_P.LinearPosition_IC;
  Movement_X.LinearPosition_CSTATE[1] = Movement_P.LinearPosition_IC;
  Movement_X.LinearPosition_CSTATE[2] = Movement_P.LinearPosition_IC;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(Movement_M)) {
    rtmSetFirstInitCond(Movement_M, 0);
  }
}

/* Model terminate function */
void Movement_terminate(void)
{
  /* (no terminate code required) */
}
