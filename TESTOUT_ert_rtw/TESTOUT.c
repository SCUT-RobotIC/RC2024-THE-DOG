/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TESTOUT.c
 *
 * Code generated for Simulink model 'TESTOUT'.
 *
 * Model version                  : 1.53
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Apr 18 11:16:35 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "TESTOUT.h"
#include "rtwtypes.h"
#include <math.h>

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Continuous states */
X rtX;

/* Block signals and states (default storage) */
DW rtDW;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;
static void MATLABFunction(real_T rtu_u, real_T *rty_y);

/* private model entry point functions */
extern void TESTOUT_derivatives(void);
static void rate_scheduler(void);

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 * (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 * (t2 - t1)                  (t2 - t1)
 */
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                 /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
{
  int_T i;
  real_T yout, t1, t2, u1, u2;
  real_T* tBuf = uBuf + bufSz;

  /*
   * If there is only one data point in the buffer, this data point must be
   * the t= 0 and tMinusDelay > t0, it ask for something unknown. The best
   * guess if initial output as well
   */
  if ((newIdx == 0) && (oldestIdx ==0 ) && (tMinusDelay > tStart))
    return initOutput;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 *         This function updates active task flag for each subrate.
 *         The function is called at model base rate, hence the
 *         generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (rtM->Timing.TaskCounters.TID[2])++;
  if ((rtM->Timing.TaskCounters.TID[2]) > 9999) {/* Sample time: [1.0s, 0.0s] */
    rtM->Timing.TaskCounters.TID[2] = 0;
  }

  (rtM->Timing.TaskCounters.TID[3])++;
  if ((rtM->Timing.TaskCounters.TID[3]) > 19999) {/* Sample time: [2.0s, 0.0s] */
    rtM->Timing.TaskCounters.TID[3] = 0;
  }

  (rtM->Timing.TaskCounters.TID[4])++;
  if ((rtM->Timing.TaskCounters.TID[4]) > 39999) {/* Sample time: [4.0s, 0.0s] */
    rtM->Timing.TaskCounters.TID[4] = 0;
  }
}

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
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  TESTOUT_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  TESTOUT_step();
  TESTOUT_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  TESTOUT_step();
  TESTOUT_derivatives();

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
 *    '<S6>/MATLAB Function'
 *    '<S6>/MATLAB Function1'
 *    '<S7>/MATLAB Function'
 *    '<S7>/MATLAB Function1'
 */
static void MATLABFunction(real_T rtu_u, real_T *rty_y)
{
  if (rtu_u == 0.0) {
    *rty_y = -1.0;
  } else {
    *rty_y = 1.0;
  }
}

/* Model step function */
void TESTOUT_step(void)
{
  /* local block i/o variables */
  real_T rtb_TransportDelay1;
  real_T rtb_Sum_p;
  real_T rtb_Sum;
  real_T rtb_Sum_pd;
  real_T rtb_Sum_c;
  real_T rtb_Product;
  real_T rtb_Product_d;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* TransportDelay: '<S1>/Transport Delay' */
  {
    real_T **uBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[0];
    real_T simTime = rtM->Timing.t[0];
    real_T tMinusDelay = simTime - 1.0;
    rtb_TransportDelay1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *uBuffer,
      rtDW.TransportDelay_IWORK.CircularBufSize,
      &rtDW.TransportDelay_IWORK.Last,
      rtDW.TransportDelay_IWORK.Tail,
      rtDW.TransportDelay_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Outport: '<Root>/Out1' */
  rtY.Out1 = rtb_TransportDelay1;

  /* TransportDelay: '<S1>/Transport Delay1' incorporates:
   *  Integrator: '<S6>/Integrator1'
   */
  rtb_TransportDelay1 = rtX.Integrator1_CSTATE;
  if (rtmIsMajorTimeStep(rtM) &&
      rtM->Timing.TaskCounters.TID[3] == 0) {
    /* Sum: '<S8>/Sum' incorporates:
     *  Constant: '<S8>/Constant'
     *  UnitDelay: '<S8>/Unit Delay'
     */
    rtb_Sum = 1.0 - rtDW.UnitDelay_DSTATE;

    /* MATLAB Function: '<S6>/MATLAB Function' */
    MATLABFunction(rtb_Sum, &rtDW.y_o);
  }

  /* Product: '<S6>/Product' */
  rtb_Product = rtb_TransportDelay1 * rtDW.y_o;

  /* MATLAB Function: '<S2>/0-Tm_y2' incorporates:
   *  Constant: '<S2>/&#x62AC;&#x817F;&#x9AD8;&#x5EA6;2'
   *  Constant: '<S2>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   */
  if (rtb_Product > 0.0) {
    rtb_Product_d = sin(12.566370614359172 * rtb_Product / 2.0) *
      0.079577471545947673;
    rtb_Product = ((1.0 - rtb_Product / 2.0) + rtb_Product_d) * 40.0 * (real_T)
      ((rtb_Product >= 1.0) && (rtb_Product < 2.0)) + (rtb_Product / 2.0 -
      rtb_Product_d) * 40.0 * (real_T)(rtb_Product < 1.0);
  } else {
    rtb_Product = 0.0;
  }

  /* End of MATLAB Function: '<S2>/0-Tm_y2' */

  /* Sum: '<S2>/Sum' incorporates:
   *  Constant: '<S2>/Constant'
   */
  rtb_Product -= 200.0;

  /* TransportDelay: '<S1>/Transport Delay1' incorporates:
   *  Integrator: '<S7>/Integrator1'
   */
  rtb_TransportDelay1 = rtX.Integrator1_CSTATE_k;
  if (rtmIsMajorTimeStep(rtM) &&
      rtM->Timing.TaskCounters.TID[4] == 0) {
    /* Sum: '<S12>/Sum' incorporates:
     *  Constant: '<S12>/Constant'
     *  UnitDelay: '<S12>/Unit Delay'
     */
    rtb_Sum_c = 1.0 - rtDW.UnitDelay_DSTATE_c;

    /* MATLAB Function: '<S7>/MATLAB Function' */
    MATLABFunction(rtb_Sum_c, &rtDW.y_f);
  }

  /* Product: '<S7>/Product' */
  rtb_Product_d = rtb_TransportDelay1 * rtDW.y_f;

  /* MATLAB Function: '<S2>/0-Tm_x1' incorporates:
   *  Constant: '<S2>/&#x6446;&#x52A8;&#x76F8;&#x5468;&#x671F;2'
   *  Constant: '<S2>/&#x6B65;&#x957F;2'
   */
  if (rtb_Product_d > 0.0) {
    rtb_Product_d = (rtb_Product_d / 2.0 - sin(6.2831853071795862 *
      rtb_Product_d / 2.0) * 0.15915494309189535) * 100.0;
  } else {
    rtb_Product_d = (-rtb_Product_d / 2.0 - sin(6.2831853071795862 *
      -rtb_Product_d / 2.0) * 0.15915494309189535) * 100.0;
  }

  /* End of MATLAB Function: '<S2>/0-Tm_x1' */

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Sum: '<S2>/Sum1'
   */
  rtb_Product = sqrt((rtb_Product_d - 50.0) * (rtb_Product_d - 50.0) +
                     rtb_Product * rtb_Product);
  rtb_Product_d = asin((rtb_Product_d - 50.0) / rtb_Product) *
    57.295779513082323;
  rtb_Product = acos(((rtb_Product * rtb_Product + 10000.0) - 32400.0) / (200.0 *
    rtb_Product)) * 57.295779513082323;
  rtDW.y = rtb_Product - rtb_Product_d;
  rtDW.w = rtb_Product + rtb_Product_d;

  /* TransportDelay: '<S1>/Transport Delay1' */
  {
    real_T **uBuffer = (real_T**)&rtDW.TransportDelay1_PWORK.TUbufferPtrs[0];
    real_T simTime = rtM->Timing.t[0];
    real_T tMinusDelay = simTime - 1.0;
    rtb_TransportDelay1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *uBuffer,
      rtDW.TransportDelay1_IWORK.CircularBufSize,
      &rtDW.TransportDelay1_IWORK.Last,
      rtDW.TransportDelay1_IWORK.Tail,
      rtDW.TransportDelay1_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Outport: '<Root>/Out2' */
  rtY.Out2 = rtb_TransportDelay1;
  if (rtmIsMajorTimeStep(rtM) &&
      rtM->Timing.TaskCounters.TID[2] == 0) {
    /* Sum: '<S9>/Sum' incorporates:
     *  Constant: '<S9>/Constant'
     *  UnitDelay: '<S9>/Unit Delay'
     */
    rtb_Sum_p = 1.0 - rtDW.UnitDelay_DSTATE_e;

    /* MATLAB Function: '<S6>/MATLAB Function1' */
    MATLABFunction(rtb_Sum_p, &rtDW.y_fq);
  }

  if (rtmIsMajorTimeStep(rtM) &&
      rtM->Timing.TaskCounters.TID[3] == 0) {
    /* Sum: '<S13>/Sum' incorporates:
     *  Constant: '<S13>/Constant'
     *  UnitDelay: '<S13>/Unit Delay'
     */
    rtb_Sum_pd = 1.0 - rtDW.UnitDelay_DSTATE_b;

    /* MATLAB Function: '<S7>/MATLAB Function1' */
    MATLABFunction(rtb_Sum_pd, &rtDW.y_l);
  }

  if (rtmIsMajorTimeStep(rtM)) {
    /* Update for TransportDelay: '<S1>/Transport Delay' */
    {
      real_T **uBuffer = (real_T**)&rtDW.TransportDelay_PWORK.TUbufferPtrs[0];
      real_T simTime = rtM->Timing.t[0];
      rtDW.TransportDelay_IWORK.Head = ((rtDW.TransportDelay_IWORK.Head <
        (rtDW.TransportDelay_IWORK.CircularBufSize-1)) ?
        (rtDW.TransportDelay_IWORK.Head+1) : 0);
      if (rtDW.TransportDelay_IWORK.Head == rtDW.TransportDelay_IWORK.Tail) {
        rtDW.TransportDelay_IWORK.Tail = ((rtDW.TransportDelay_IWORK.Tail <
          (rtDW.TransportDelay_IWORK.CircularBufSize-1)) ?
          (rtDW.TransportDelay_IWORK.Tail+1) : 0);
      }

      (*uBuffer + rtDW.TransportDelay_IWORK.CircularBufSize)
        [rtDW.TransportDelay_IWORK.Head] = simTime;
      (*uBuffer)[rtDW.TransportDelay_IWORK.Head] = rtDW.w;
    }

    if (rtmIsMajorTimeStep(rtM) &&
        rtM->Timing.TaskCounters.TID[3] == 0) {
      /* Update for UnitDelay: '<S8>/Unit Delay' */
      rtDW.UnitDelay_DSTATE = rtb_Sum;
    }

    if (rtmIsMajorTimeStep(rtM) &&
        rtM->Timing.TaskCounters.TID[4] == 0) {
      /* Update for UnitDelay: '<S12>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_c = rtb_Sum_c;
    }

    /* Update for TransportDelay: '<S1>/Transport Delay1' */
    {
      real_T **uBuffer = (real_T**)&rtDW.TransportDelay1_PWORK.TUbufferPtrs[0];
      real_T simTime = rtM->Timing.t[0];
      rtDW.TransportDelay1_IWORK.Head = ((rtDW.TransportDelay1_IWORK.Head <
        (rtDW.TransportDelay1_IWORK.CircularBufSize-1)) ?
        (rtDW.TransportDelay1_IWORK.Head+1) : 0);
      if (rtDW.TransportDelay1_IWORK.Head == rtDW.TransportDelay1_IWORK.Tail) {
        rtDW.TransportDelay1_IWORK.Tail = ((rtDW.TransportDelay1_IWORK.Tail <
          (rtDW.TransportDelay1_IWORK.CircularBufSize-1)) ?
          (rtDW.TransportDelay1_IWORK.Tail+1) : 0);
      }

      (*uBuffer + rtDW.TransportDelay1_IWORK.CircularBufSize)
        [rtDW.TransportDelay1_IWORK.Head] = simTime;
      (*uBuffer)[rtDW.TransportDelay1_IWORK.Head] = rtDW.y;
    }

    if (rtmIsMajorTimeStep(rtM) &&
        rtM->Timing.TaskCounters.TID[2] == 0) {
      /* Update for UnitDelay: '<S9>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_e = rtb_Sum_p;
    }

    if (rtmIsMajorTimeStep(rtM) &&
        rtM->Timing.TaskCounters.TID[3] == 0) {
      /* Update for UnitDelay: '<S13>/Unit Delay' */
      rtDW.UnitDelay_DSTATE_b = rtb_Sum_pd;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }

    rate_scheduler();
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void TESTOUT_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S6>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = rtDW.y_fq;

  /* Derivatives for Integrator: '<S7>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_k = rtDW.y_l;
}

/* Model initialize function */
void TESTOUT_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&rtM->solverInfo, false);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.0001;

  /* Start for TransportDelay: '<S1>/Transport Delay' */
  {
    real_T *pBuffer = &rtDW.TransportDelay_RWORK.TUbufferArea[0];
    rtDW.TransportDelay_IWORK.Tail = 0;
    rtDW.TransportDelay_IWORK.Head = 0;
    rtDW.TransportDelay_IWORK.Last = 0;
    rtDW.TransportDelay_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = rtM->Timing.t[0];
    rtDW.TransportDelay_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
  }

  /* Start for TransportDelay: '<S1>/Transport Delay1' */
  {
    real_T *pBuffer = &rtDW.TransportDelay1_RWORK.TUbufferArea[0];
    rtDW.TransportDelay1_IWORK.Tail = 0;
    rtDW.TransportDelay1_IWORK.Head = 0;
    rtDW.TransportDelay1_IWORK.Last = 0;
    rtDW.TransportDelay1_IWORK.CircularBufSize = 1024;
    pBuffer[0] = 0.0;
    pBuffer[1024] = rtM->Timing.t[0];
    rtDW.TransportDelay1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
  }

  /* InitializeConditions for Integrator: '<S6>/Integrator1' */
  rtX.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S7>/Integrator1' */
  rtX.Integrator1_CSTATE_k = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
