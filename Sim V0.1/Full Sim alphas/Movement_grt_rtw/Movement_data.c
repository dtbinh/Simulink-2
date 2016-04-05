/*
 * Movement_data.c
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

/* Block parameters (auto storage) */
P_Movement_T Movement_P = {
  /*  Expression: [1 0 0 0]
   * Referenced by: '<S4>/Q0'
   */
  { 1.0, 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 2]
   * Referenced by: '<S4>/XYZ 0'
   */
  { 0.0, 0.0, 2.0 },
  0.23,                                /* Expression: 0.23
                                        * Referenced by: '<S4>/Dim L'
                                        */
  0.1,                                 /* Expression: 0.1
                                        * Referenced by: '<S4>/Prop'
                                        */

  /*  Expression: [pi/2 0]
   * Referenced by: '<Root>/Motor 1'
   */
  { 1.5707963267948966, 0.0 },

  /*  Expression: [0 pi]
   * Referenced by: '<Root>/Motor 2'
   */
  { 0.0, 3.1415926535897931 },

  /*  Expression: [0 0]
   * Referenced by: '<Root>/Motor 3'
   */
  { 0.0, 0.0 },

  /*  Expression: [0 0]
   * Referenced by: '<Root>/Motor 4'
   */
  { 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S4>/dE0'
   */
  { 0.0, 0.0, 0.0 },

  /*  Expression: [0 0 0]
   * Referenced by: '<S4>/dV0'
   */
  { 0.0, 0.0, 0.0 },
  0.87,                                /* Expression: 0.87
                                        * Referenced by: '<S4>/m'
                                        */

  /*  Expression: [0.0052 0.0052 0.0082]
   * Referenced by: '<S4>/Inertia'
   */
  { 0.0052, 0.0052, 0.0082 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Angular Position'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<Root>/Linear Position'
                                        */
};
