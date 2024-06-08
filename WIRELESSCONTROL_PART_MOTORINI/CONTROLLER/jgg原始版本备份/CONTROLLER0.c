/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLLER0.c
 *
 * Code generated for Simulink model 'CONTROLLER0'.
 *
 * Model version                  : 1.29
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Sat May 11 20:42:14 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "CONTROLLER0.h"
#include <math.h>

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void uTm_x1(float rtu_u, double rtu_Tm, float rtu_S, float *rty_x);
static void uTm_y2(float rtu_u, double rtu_Tm, double rtu_H, float *rty_y);
static void MATLABFunction1(float rtu_x1, double rtu_z1, float *rty_theta_OUT,
  float *rty_theta_IN);

/*
 * Output and update for atomic system:
 *    '<S2>/0-Tm_x1'
 *    '<S3>/0-Tm_x1'
 *    '<S4>/0-Tm_x1'
 *    '<S5>/0-Tm_x1'
 */
static void uTm_x1(float rtu_u, double rtu_Tm, float rtu_S, float *rty_x)
{
  if (rtu_u > 0.0F) {
    *rty_x = (rtu_u / (float)rtu_Tm - sinf(6.28318548F * rtu_u / (float)rtu_Tm) *
              0.159154937F) * rtu_S;
  } else {
    *rty_x = (-rtu_u / (float)rtu_Tm - sinf(6.28318548F * -rtu_u / (float)rtu_Tm)
              * 0.159154937F) * rtu_S;
  }
}

/*
 * Output and update for atomic system:
 *    '<S2>/0-Tm_y2'
 *    '<S3>/0-Tm_y2'
 *    '<S4>/0-Tm_y2'
 */
static void uTm_y2(float rtu_u, double rtu_Tm, double rtu_H, float *rty_y)
{
  if (rtu_u > 0.0F) {
    float tmp;
    float tmp_0;
    tmp = sinf(12.566371F * rtu_u / (float)rtu_Tm) * 0.0795774683F;
    tmp_0 = rtu_u / (float)rtu_Tm;
    *rty_y = ((1.0F - tmp_0) + tmp) * (float)(2.0 * rtu_H) * (float)((rtu_u >=
      rtu_Tm / 2.0) && (rtu_u < rtu_Tm)) + (tmp_0 - tmp) * (float)(2.0 * rtu_H) *
      (float)(rtu_u < rtu_Tm / 2.0);
  } else {
    *rty_y = 0.0F;
  }
}

/*
 * Output and update for atomic system:
 *    '<S2>/MATLAB Function1'
 *    '<S3>/MATLAB Function1'
 *    '<S4>/MATLAB Function1'
 *    '<S5>/MATLAB Function1'
 */
static void MATLABFunction1(float rtu_x1, double rtu_z1, float *rty_theta_OUT,
  float *rty_theta_IN)
{
  float L;
  float theta_left;
  L = sqrtf(rtu_x1 * rtu_x1 + (float)(rtu_z1 * rtu_z1));
  theta_left = asinf(rtu_x1 / L) * 57.2957802F;
  L = acosf(((L * L + 10000.0F) - 32400.0F) / (200.0F * L)) * 57.2957802F;
  *rty_theta_OUT = L - theta_left;
  *rty_theta_IN = L + theta_left;
}

/* Model step function */
void CONTROLLER0_step(void)
{
  double rtb_Sum_i;
  float rtb_theta_IN;
  float rtb_theta_OUT;
  float rtb_y;

  /* MATLAB Function: '<S5>/0-Tm_x1' incorporates:
   *  Constant: '<S5>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/RF_X'
   *  Inport: '<Root>/R_LENGTH'
   */
  uTm_x1(rtU.RF_X, 2.0, rtU.R_LENGTH, &rtb_theta_OUT);

  /* MATLAB Function: '<S5>/0-Tm_y2' incorporates:
   *  Constant: '<S5>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S5>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/RF_Y'
   */
  if (rtU.RF_Y > 0.0F) {
    rtb_y = sinf(12.566371F * rtU.RF_Y / 2.0F) * 0.0795774683F;
    rtb_y = ((1.0F - rtU.RF_Y / 2.0F) + rtb_y) * 80.0F * (float)((rtU.RF_Y >=
      1.0F) && (rtU.RF_Y < 2.0F)) + (rtU.RF_Y / 2.0F - rtb_y) * 80.0F * (float)
      ((rtU.RF_Y >= 0.0F) && (rtU.RF_Y < 1.0F));
  } else {
    rtb_y = 0.0F;
  }

  /* End of MATLAB Function: '<S5>/0-Tm_y2' */

  /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Gain: '<S5>/Gain4'
   *  Inport: '<Root>/R_LENGTH'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  MATLABFunction1(rtb_theta_OUT - 0.5F * rtU.R_LENGTH, rtb_y - 200.0,
                  &rtb_theta_IN, &rtb_theta_OUT);

  /* Outport: '<Root>/RF_theta_out' incorporates:
   *  Gain: '<S24>/Gain1'
   */
  rtY.RF_theta_out = 0.0174532924F * rtb_theta_IN;

  /* Outport: '<Root>/RF_theta_in' incorporates:
   *  Gain: '<S23>/Gain1'
   */
  rtY.RF_theta_in = 0.0174532924F * rtb_theta_OUT;

  /* MATLAB Function: '<S4>/0-Tm_y2' incorporates:
   *  Constant: '<S4>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S4>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/RB_Y'
   */
  uTm_y2(rtU.RB_Y, 2.0, 40.0, &rtb_theta_OUT);

  /* Sum: '<S4>/Sum' incorporates:
   *  Constant: '<S4>/Constant3'
   */
  rtb_Sum_i = rtb_theta_OUT - 200.0;

  /* MATLAB Function: '<S4>/0-Tm_x1' incorporates:
   *  Constant: '<S4>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/RB_X'
   *  Inport: '<Root>/R_LENGTH'
   */
  uTm_x1(rtU.RB_X, 2.0, rtU.R_LENGTH, &rtb_theta_OUT);

  /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
   *  Gain: '<S4>/Gain4'
   *  Inport: '<Root>/R_LENGTH'
   *  Sum: '<S4>/Sum1'
   */
  MATLABFunction1(rtb_theta_OUT - 0.5F * rtU.R_LENGTH, rtb_Sum_i, &rtb_theta_OUT,
                  &rtb_theta_IN);

  /* Outport: '<Root>/RB_theta_out' incorporates:
   *  Gain: '<S19>/Gain1'
   *  Gain: '<S4>/Gain1'
   */
  rtY.RB_theta_out = 0.0174532924F * -rtb_theta_OUT;

  /* Outport: '<Root>/RB_theta_in' incorporates:
   *  Gain: '<S18>/Gain1'
   *  Gain: '<S4>/Gain'
   */
  rtY.RB_theta_in = 0.0174532924F * -rtb_theta_IN;

  /* MATLAB Function: '<S2>/0-Tm_y2' incorporates:
   *  Constant: '<S2>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S2>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/LB_Y'
   */
  uTm_y2(rtU.LB_Y, 2.0, 40.0, &rtb_theta_OUT);

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/Constant3'
   */
  rtb_Sum_i = rtb_theta_OUT - 200.0;

  /* MATLAB Function: '<S2>/0-Tm_x1' incorporates:
   *  Constant: '<S2>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/LB_X'
   *  Inport: '<Root>/L_LENGTH'
   */
  uTm_x1(rtU.LB_X, 2.0, rtU.L_LENGTH, &rtb_theta_OUT);

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  Gain: '<S2>/Gain4'
   *  Inport: '<Root>/L_LENGTH'
   *  Sum: '<S2>/Sum1'
   */
  MATLABFunction1(rtb_theta_OUT - 0.5F * rtU.L_LENGTH, rtb_Sum_i, &rtb_theta_OUT,
                  &rtb_theta_IN);

  /* Outport: '<Root>/LB_theta_out' incorporates:
   *  Gain: '<S9>/Gain1'
   */
  rtY.LB_theta_out = 0.0174532924F * rtb_theta_OUT;

  /* Outport: '<Root>/LB_theta_in' incorporates:
   *  Gain: '<S8>/Gain1'
   */
  rtY.LB_theta_in = 0.0174532924F * rtb_theta_IN;

  /* MATLAB Function: '<S3>/0-Tm_y2' incorporates:
   *  Constant: '<S3>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S3>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/LF_Y'
   */
  uTm_y2(rtU.LF_Y, 2.0, 40.0, &rtb_theta_OUT);

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<S3>/Constant3'
   */
  rtb_Sum_i = rtb_theta_OUT - 200.0;

  /* MATLAB Function: '<S3>/0-Tm_x1' incorporates:
   *  Constant: '<S3>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Inport: '<Root>/LF_X'
   *  Inport: '<Root>/L_LENGTH'
   */
  uTm_x1(rtU.LF_X, 2.0, rtU.L_LENGTH, &rtb_theta_OUT);

  /* MATLAB Function: '<S3>/MATLAB Function1' incorporates:
   *  Gain: '<S3>/Gain4'
   *  Inport: '<Root>/L_LENGTH'
   *  Sum: '<S3>/Sum1'
   */
  MATLABFunction1(rtb_theta_OUT - 0.5F * rtU.L_LENGTH, rtb_Sum_i, &rtb_theta_OUT,
                  &rtb_theta_IN);

  /* Outport: '<Root>/LF_theta_out' incorporates:
   *  Gain: '<S14>/Gain1'
   *  Gain: '<S3>/Gain'
   */
  rtY.LF_theta_out = 0.0174532924F * -rtb_theta_IN;

  /* Outport: '<Root>/LF_theta_in' incorporates:
   *  Gain: '<S13>/Gain1'
   *  Gain: '<S3>/Gain1'
   */
  rtY.LF_theta_in = 0.0174532924F * -rtb_theta_OUT;
}

/* Model initialize function */
void CONTROLLER0_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
