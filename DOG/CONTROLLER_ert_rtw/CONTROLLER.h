/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLLER.h
 *
 * Code generated for Simulink model 'CONTROLLER'.
 *
 * Model version                  : 1.30
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sat Jun  8 22:45:01 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_CONTROLLER_h_
#define RTW_HEADER_CONTROLLER_h_
#ifndef CONTROLLER_COMMON_INCLUDES_
#define CONTROLLER_COMMON_INCLUDES_
#include <stdbool.h>
#include <stdint.h>
#endif                                 /* CONTROLLER_COMMON_INCLUDES_ */

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
  float RF_X;                          /* '<Root>/RF_X' */
  float RF_Y;                          /* '<Root>/RF_Y' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  float RF_theta_out;                  /* '<Root>/RF_theta_out' */
  float RF_theta_in;                   /* '<Root>/RF_theta_in' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void CONTROLLER_initialize(void);
extern void CONTROLLER_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S8>/Gain1' : Unused code path elimination
 * Block '<S9>/Gain1' : Unused code path elimination
 * Block '<S2>/步长2' : Unused code path elimination
 * Block '<S13>/Gain1' : Unused code path elimination
 * Block '<S14>/Gain1' : Unused code path elimination
 * Block '<S3>/Gain' : Unused code path elimination
 * Block '<S3>/Gain1' : Unused code path elimination
 * Block '<S3>/步长2' : Unused code path elimination
 * Block '<S18>/Gain1' : Unused code path elimination
 * Block '<S19>/Gain1' : Unused code path elimination
 * Block '<S4>/Gain' : Unused code path elimination
 * Block '<S4>/Gain1' : Unused code path elimination
 */

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
 * '<Root>' : 'CONTROLLER'
 * '<S1>'   : 'CONTROLLER/CONTROLLER'
 * '<S2>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LB'
 * '<S3>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LF'
 * '<S4>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_RB'
 * '<S5>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_RF'
 * '<S6>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LB/0-Tm_x1'
 * '<S7>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LB/0-Tm_y2'
 * '<S8>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LB/Degrees to Radians1'
 * '<S9>'   : 'CONTROLLER/CONTROLLER/CONTROLLER_LB/Degrees to Radians2'
 * '<S10>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LB/MATLAB Function1'
 * '<S11>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LF/0-Tm_x1'
 * '<S12>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LF/0-Tm_y2'
 * '<S13>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LF/Degrees to Radians1'
 * '<S14>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LF/Degrees to Radians2'
 * '<S15>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_LF/MATLAB Function1'
 * '<S16>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RB/0-Tm_x1'
 * '<S17>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RB/0-Tm_y2'
 * '<S18>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RB/Degrees to Radians1'
 * '<S19>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RB/Degrees to Radians2'
 * '<S20>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RB/MATLAB Function1'
 * '<S21>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RF/0-Tm_x1'
 * '<S22>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RF/0-Tm_y2'
 * '<S23>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RF/Degrees to Radians1'
 * '<S24>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RF/Degrees to Radians2'
 * '<S25>'  : 'CONTROLLER/CONTROLLER/CONTROLLER_RF/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_CONTROLLER_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
