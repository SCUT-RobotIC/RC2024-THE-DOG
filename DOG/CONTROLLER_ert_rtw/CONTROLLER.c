/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: CONTROLLER.c
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

#include "CONTROLLER.h"
#include <math.h>

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void uTm_x1(float rtu_u, double rtu_Tm, float rtu_S, float *rty_x);
static void uTm_y2(float rtu_u, double rtu_Tm, float rtu_H, float *rty_y);
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
static void uTm_y2(float rtu_u, double rtu_Tm, float rtu_H, float *rty_y)
{
  if (rtu_u > 0.0F) {
    float tmp;
    float tmp_0;
    tmp = sinf(12.566371F * rtu_u / (float)rtu_Tm) * 0.0795774683F;
    tmp_0 = rtu_u / (float)rtu_Tm;
    *rty_y = ((1.0F - tmp_0) + tmp) * (2.0F * rtu_H) * (float)((rtu_u >= rtu_Tm /
      2.0) && (rtu_u < rtu_Tm)) + (tmp_0 - tmp) * (2.0F * rtu_H) * (float)(rtu_u
      < rtu_Tm / 2.0);
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
void CONTROLLER_step(void)
{
  float rtb_theta_IN;
  float rtb_theta_OUT;
  float rtb_y;
  float rtb_y_d;

  /* MATLAB Function: '<S5>/0-Tm_x1' incorporates:
   *  Constant: '<S5>/摆动相周期2'
   *  Inport: '<Root>/RF_X'
   */
  uTm_x1(rtU.RF_X, 2.0, 0.0F, &rtb_y_d);

  /* MATLAB Function: '<S5>/0-Tm_y2' incorporates:
   *  Constant: '<S5>/摆动相周期2'
   *  Inport: '<Root>/RF_Y'
   */
  if (rtU.RF_Y > 0.0F) {
    rtb_y = sinf(12.566371F * rtU.RF_Y / 2.0F) * 0.0795774683F;
    rtb_y = ((1.0F - rtU.RF_Y / 2.0F) + rtb_y) * 0.0F * (float)((rtU.RF_Y >=
      1.0F) && (rtU.RF_Y < 2.0F)) + (rtU.RF_Y / 2.0F - rtb_y) * 0.0F * (float)
      ((rtU.RF_Y >= 0.0F) && (rtU.RF_Y < 1.0F));
  } else {
    rtb_y = 0.0F;
  }

  /* End of MATLAB Function: '<S5>/0-Tm_y2' */

  /* MATLAB Function: '<S5>/MATLAB Function1' incorporates:
   *  Constant: '<S5>/Constant3'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  MATLABFunction1(rtb_y_d, rtb_y - 200.0, &rtb_theta_OUT, &rtb_theta_IN);

  /* Outport: '<Root>/RF_theta_out' incorporates:
   *  Gain: '<S24>/Gain1'
   */
  rtY.RF_theta_out = 0.0174532924F * rtb_theta_OUT;

  /* Outport: '<Root>/RF_theta_in' incorporates:
   *  Gain: '<S23>/Gain1'
   */
  rtY.RF_theta_in = 0.0174532924F * rtb_theta_IN;

  /* MATLAB Function: '<S4>/0-Tm_x1' incorporates:
   *  Constant: '<S4>/摆动相周期2'
   */
  uTm_x1(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* Sum: '<S4>/Sum1' */
  rtb_y = rtb_y_d;

  /* MATLAB Function: '<S4>/0-Tm_y2' incorporates:
   *  Constant: '<S4>/摆动相周期2'
   */
  uTm_y2(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* MATLAB Function: '<S4>/MATLAB Function1' incorporates:
   *  Constant: '<S4>/Constant3'
   *  Sum: '<S4>/Sum'
   */
  MATLABFunction1(rtb_y, rtb_y_d - 200.0, &rtb_theta_OUT, &rtb_theta_IN);

  /* MATLAB Function: '<S2>/0-Tm_x1' incorporates:
   *  Constant: '<S2>/摆动相周期2'
   */
  uTm_x1(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* Sum: '<S2>/Sum1' */
  rtb_y = rtb_y_d;

  /* MATLAB Function: '<S2>/0-Tm_y2' incorporates:
   *  Constant: '<S2>/摆动相周期2'
   */
  uTm_y2(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  Constant: '<S2>/Constant3'
   *  Sum: '<S2>/Sum'
   */
  MATLABFunction1(rtb_y, rtb_y_d - 200.0, &rtb_theta_OUT, &rtb_theta_IN);

  /* MATLAB Function: '<S3>/0-Tm_x1' incorporates:
   *  Constant: '<S3>/摆动相周期2'
   */
  uTm_x1(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* Sum: '<S3>/Sum1' */
  rtb_y = rtb_y_d;

  /* MATLAB Function: '<S3>/0-Tm_y2' incorporates:
   *  Constant: '<S3>/摆动相周期2'
   */
  uTm_y2(0.0F, 2.0, 0.0F, &rtb_y_d);

  /* MATLAB Function: '<S3>/MATLAB Function1' incorporates:
   *  Constant: '<S3>/Constant3'
   *  Sum: '<S3>/Sum'
   */
  MATLABFunction1(rtb_y, rtb_y_d - 200.0, &rtb_theta_OUT, &rtb_theta_IN);
}

/* Model initialize function */
void CONTROLLER_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
