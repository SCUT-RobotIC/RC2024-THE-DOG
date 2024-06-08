/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLLER_RF.h
 *
 * Code generated for Simulink model 'CONTROLLER_RF'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu May  2 01:24:55 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CONTROLLER_RF_h_
#define RTW_HEADER_CONTROLLER_RF_h_
#ifndef CONTROLLER_RF_COMMON_INCLUDES_
#define CONTROLLER_RF_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* CONTROLLER_RF_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T RF_X;                         /* '<Root>/RF_X' */
  real_T RF_Y;                         /* '<Root>/RF_Y' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T RF_theta_out;                 /* '<Root>/RF_theta_out' */
  real_T RF_theta_in;                  /* '<Root>/RF_theta_in' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void CONTROLLER_RF_initialize(void);
extern void CONTROLLER_RF_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('CONTROLLER/CONTROLLER_RF')    - opens subsystem CONTROLLER/CONTROLLER_RF
 * hilite_system('CONTROLLER/CONTROLLER_RF/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'CONTROLLER'
 * '<S1>'   : 'CONTROLLER/CONTROLLER_RF'
 * '<S2>'   : 'CONTROLLER/CONTROLLER_RF/0-Tm_x1'
 * '<S3>'   : 'CONTROLLER/CONTROLLER_RF/0-Tm_y2'
 * '<S4>'   : 'CONTROLLER/CONTROLLER_RF/Degrees to Radians1'
 * '<S5>'   : 'CONTROLLER/CONTROLLER_RF/Degrees to Radians2'
 * '<S6>'   : 'CONTROLLER/CONTROLLER_RF/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_CONTROLLER_RF_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
