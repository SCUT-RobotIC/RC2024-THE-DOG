/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.c
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.8
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Wed May  1 23:33:13 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Subsystem.h"
#include <math.h>
#include "rtwtypes.h"

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* Model step function */
void Subsystem_step(void)
{
  real_T rtb_x;
  real_T rtb_y;

  /* MATLAB Function: '<S1>/0-Tm_x1' incorporates:
   *  Constant: '<S1>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Constant: '<S1>/&#x6B65;&#x957F;2'
   *  Inport: '<Root>/RF_X'
   */
  if (rtU.RF_X > 0.0) {
    rtb_x = (rtU.RF_X / 2.0 - sin(6.2831853071795862 * rtU.RF_X / 2.0) *
             0.15915494309189535) * 120.0;
  } else {
    rtb_x = (-rtU.RF_X / 2.0 - sin(6.2831853071795862 * -rtU.RF_X / 2.0) *
             0.15915494309189535) * 120.0;
  }

  /* End of MATLAB Function: '<S1>/0-Tm_x1' */

  /* Sum: '<S1>/Sum1' */
  rtb_x -= 60.0;

  /* MATLAB Function: '<S1>/0-Tm_y2' incorporates:
   *  Constant: '<S1>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S1>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/RF_Y'
   */
  if (rtU.RF_Y > 0.0) {
    rtb_y = sin(12.566370614359172 * rtU.RF_Y / 2.0) * 0.079577471545947673;
    rtb_y = ((1.0 - rtU.RF_Y / 2.0) + rtb_y) * 80.0 * (real_T)((rtU.RF_Y >= 1.0)
      && (rtU.RF_Y < 2.0)) + (rtU.RF_Y / 2.0 - rtb_y) * 80.0 * (real_T)
      ((rtU.RF_Y >= 0.0) && (rtU.RF_Y < 1.0));
  } else {
    rtb_y = 0.0;
  }

  /* End of MATLAB Function: '<S1>/0-Tm_y2' */

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Constant: '<S1>/Constant3'
   *  Sum: '<S1>/Sum'
   */
  rtb_y = sqrt((rtb_y - 200.0) * (rtb_y - 200.0) + rtb_x * rtb_x);
  rtb_x = asin(rtb_x / rtb_y) * 57.295779513082323;
  rtb_y = acos(((rtb_y * rtb_y + 10000.0) - 32400.0) / (200.0 * rtb_y)) *
    57.295779513082323;

  /* Outport: '<Root>/RF_theta_out' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  rtY.RF_theta_out = rtb_y - rtb_x;

  /* Outport: '<Root>/RF_theta_in' incorporates:
   *  Gain: '<S1>/Gain'
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  rtY.RF_theta_in = -(rtb_y + rtb_x);
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
