/*
 * Movement.h
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

#ifndef RTW_HEADER_Movement_h_
#define RTW_HEADER_Movement_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef Movement_COMMON_INCLUDES_
# define Movement_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* Movement_COMMON_INCLUDES_ */

#include "Movement_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->ModelData.blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->ModelData.blkStateChange = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->ModelData.contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->ModelData.contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->ModelData.contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->ModelData.contStates = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->ModelData.derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->ModelData.derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->ModelData.intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->ModelData.intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->ModelData.odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->ModelData.odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->ModelData.odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->ModelData.odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->ModelData.periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->ModelData.periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->ModelData.periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->ModelData.periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->ModelData.zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->ModelData.zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->ModelData.derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->ModelData.derivs = (val))
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

/* Block signals for system '<Root>/q_mtr 1' */
typedef struct {
  real_T q_mtr[4];                     /* '<Root>/q_mtr 1' */
} B_q_mtr1_Movement_T;

/* Block signals (auto storage) */
typedef struct {
  real_T Q0[4];                        /* '<S4>/Q0' */
  real_T XYZ0[3];                      /* '<S4>/XYZ 0' */
  real_T LinearInertialPosition[3];    /* '<Root>/Linear Inertial Position' */
  real_T dE0[3];                       /* '<S4>/dE0' */
  real_T AngularVelocity[3];           /* '<Root>/Angular Velocity' */
  real_T dV0[3];                       /* '<S4>/dV0' */
  real_T LinearVelocity[3];            /* '<Root>/Linear Velocity' */
  real_T dQ[4];                        /* '<Root>/Velocities' */
  real_T dN[3];                        /* '<Root>/Velocities' */
  real_T dE[3];                        /* '<Root>/Accelerations' */
  real_T dV[3];                        /* '<Root>/Accelerations' */
  B_q_mtr1_Movement_T sf_q_mtr4;       /* '<Root>/q_mtr 4' */
  B_q_mtr1_Movement_T sf_q_mtr3;       /* '<Root>/q_mtr 3' */
  B_q_mtr1_Movement_T sf_q_mtr2;       /* '<Root>/q_mtr 2' */
  B_q_mtr1_Movement_T sf_q_mtr1;       /* '<Root>/q_mtr 1' */
} B_Movement_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<Root>/Scope1' */

  struct {
    int_T IcNeedsLoading;
  } QuaternionAttitude_IWORK;          /* '<Root>/Quaternion Attitude' */

  struct {
    int_T IcNeedsLoading;
  } LinearInertialPosition_IWORK;      /* '<Root>/Linear Inertial Position' */

  struct {
    int_T IcNeedsLoading;
  } AngularVelocity_IWORK;             /* '<Root>/Angular Velocity' */

  struct {
    int_T IcNeedsLoading;
  } LinearVelocity_IWORK;              /* '<Root>/Linear Velocity' */
} DW_Movement_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Quaternion[4];                /* '<Root>/Quaternion Attitude' */
  real_T LinearInertialPosition_CSTATE[3];/* '<Root>/Linear Inertial Position' */
  real_T AngularVelocity_CSTATE[3];    /* '<Root>/Angular Velocity' */
  real_T LinearVelocity_CSTATE[3];     /* '<Root>/Linear Velocity' */
  real_T AngularPosition_CSTATE[3];    /* '<Root>/Angular Position' */
  real_T LinearPosition_CSTATE[3];     /* '<Root>/Linear Position' */
} X_Movement_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Quaternion[4];                /* '<Root>/Quaternion Attitude' */
  real_T LinearInertialPosition_CSTATE[3];/* '<Root>/Linear Inertial Position' */
  real_T AngularVelocity_CSTATE[3];    /* '<Root>/Angular Velocity' */
  real_T LinearVelocity_CSTATE[3];     /* '<Root>/Linear Velocity' */
  real_T AngularPosition_CSTATE[3];    /* '<Root>/Angular Position' */
  real_T LinearPosition_CSTATE[3];     /* '<Root>/Linear Position' */
} XDot_Movement_T;

/* State disabled  */
typedef struct {
  boolean_T Quaternion[4];             /* '<Root>/Quaternion Attitude' */
  boolean_T LinearInertialPosition_CSTATE[3];/* '<Root>/Linear Inertial Position' */
  boolean_T AngularVelocity_CSTATE[3]; /* '<Root>/Angular Velocity' */
  boolean_T LinearVelocity_CSTATE[3];  /* '<Root>/Linear Velocity' */
  boolean_T AngularPosition_CSTATE[3]; /* '<Root>/Angular Position' */
  boolean_T LinearPosition_CSTATE[3];  /* '<Root>/Linear Position' */
} XDis_Movement_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Parameters (auto storage) */
struct P_Movement_T_ {
  real_T Q0_Value[4];                  /* Expression: [1 0 0 0]
                                        * Referenced by: '<S4>/Q0'
                                        */
  real_T XYZ0_Value[3];                /* Expression: [0 0 2]
                                        * Referenced by: '<S4>/XYZ 0'
                                        */
  real_T DimL_Value;                   /* Expression: 0.23
                                        * Referenced by: '<S4>/Dim L'
                                        */
  real_T Prop_Value;                   /* Expression: 0.1
                                        * Referenced by: '<S4>/Prop'
                                        */
  real_T Motor1_Value[2];              /* Expression: [pi/2 0]
                                        * Referenced by: '<Root>/Motor 1'
                                        */
  real_T Motor2_Value[2];              /* Expression: [0 pi]
                                        * Referenced by: '<Root>/Motor 2'
                                        */
  real_T Motor3_Value[2];              /* Expression: [0 0]
                                        * Referenced by: '<Root>/Motor 3'
                                        */
  real_T Motor4_Value[2];              /* Expression: [0 0]
                                        * Referenced by: '<Root>/Motor 4'
                                        */
  real_T dE0_Value[3];                 /* Expression: [0 0 0]
                                        * Referenced by: '<S4>/dE0'
                                        */
  real_T dV0_Value[3];                 /* Expression: [0 0 0]
                                        * Referenced by: '<S4>/dV0'
                                        */
  real_T m_Value;                      /* Expression: 0.87
                                        * Referenced by: '<S4>/m'
                                        */
  real_T Inertia_Value[3];             /* Expression: [0.0052 0.0052 0.0082]
                                        * Referenced by: '<S4>/Inertia'
                                        */
  real_T AngularPosition_IC;           /* Expression: 0
                                        * Referenced by: '<Root>/Angular Position'
                                        */
  real_T LinearPosition_IC;            /* Expression: 0
                                        * Referenced by: '<Root>/Linear Position'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Movement_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    X_Movement_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T blkStateChange;
    real_T odeY[19];
    real_T odeF[3][19];
    ODE3_IntgData intgData;
  } ModelData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    boolean_T firstInitCondFlag;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_Movement_T Movement_P;

/* Block signals (auto storage) */
extern B_Movement_T Movement_B;

/* Continuous states (auto storage) */
extern X_Movement_T Movement_X;

/* Block states (auto storage) */
extern DW_Movement_T Movement_DW;

/* Model entry point functions */
extern void Movement_initialize(void);
extern void Movement_step(void);
extern void Movement_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Movement_T *const Movement_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Movement'
 * '<S1>'   : 'Movement/Accelerations'
 * '<S2>'   : 'Movement/Calc Force'
 * '<S3>'   : 'Movement/Calc Torque'
 * '<S4>'   : 'Movement/Constants'
 * '<S5>'   : 'Movement/Plot Function'
 * '<S6>'   : 'Movement/Velocities'
 * '<S7>'   : 'Movement/q_mtr 1'
 * '<S8>'   : 'Movement/q_mtr 2'
 * '<S9>'   : 'Movement/q_mtr 3'
 * '<S10>'  : 'Movement/q_mtr 4'
 */
#endif                                 /* RTW_HEADER_Movement_h_ */
