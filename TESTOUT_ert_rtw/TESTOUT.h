/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TESTOUT.h
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

#ifndef RTW_HEADER_TESTOUT_h_
#define RTW_HEADER_TESTOUT_h_
#ifndef TESTOUT_COMMON_INCLUDES_
#define TESTOUT_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* TESTOUT_COMMON_INCLUDES_ */

#include <float.h>
#include <math.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay_RWORK;              /* '<S1>/Transport Delay' */

  struct {
    real_T modelTStart;
    real_T TUbufferArea[2048];
  } TransportDelay1_RWORK;             /* '<S1>/Transport Delay1' */

  real_T y;                            /* '<S1>/MATLAB Function' */
  real_T w;                            /* '<S1>/MATLAB Function' */
  real_T y_l;                          /* '<S7>/MATLAB Function1' */
  real_T y_f;                          /* '<S7>/MATLAB Function' */
  real_T y_fq;                         /* '<S6>/MATLAB Function1' */
  real_T y_o;                          /* '<S6>/MATLAB Function' */
  real_T UnitDelay_DSTATE;             /* '<S8>/Unit Delay' */
  real_T UnitDelay_DSTATE_c;           /* '<S12>/Unit Delay' */
  real_T UnitDelay_DSTATE_e;           /* '<S9>/Unit Delay' */
  real_T UnitDelay_DSTATE_b;           /* '<S13>/Unit Delay' */
  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay_IWORK;              /* '<S1>/Transport Delay' */

  struct {
    int_T Tail;
    int_T Head;
    int_T Last;
    int_T CircularBufSize;
  } TransportDelay1_IWORK;             /* '<S1>/Transport Delay1' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay_PWORK;              /* '<S1>/Transport Delay' */

  struct {
    void *TUbufferPtrs[2];
  } TransportDelay1_PWORK;             /* '<S1>/Transport Delay1' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_k;         /* '<S7>/Integrator1' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator1_CSTATE;           /* '<S6>/Integrator1' */
  real_T Integrator1_CSTATE_k;         /* '<S7>/Integrator1' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE;        /* '<S6>/Integrator1' */
  boolean_T Integrator1_CSTATE_k;      /* '<S7>/Integrator1' */
} XDis;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Out1;                         /* '<Root>/Out1' */
  real_T Out2;                         /* '<Root>/Out2' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

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
    time_T stepSize0;
    uint32_T clockTick1;
    struct {
      uint16_T TID[5];
    } TaskCounters;

    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[5];
  } Timing;
};

/* Continuous states (default storage) */
extern X rtX;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void TESTOUT_initialize(void);
extern void TESTOUT_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope2' : Unused code path elimination
 * Block '<S1>/Scope3' : Unused code path elimination
 */

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
 * hilite_system('OUTTO_STMCODEER/TESTOUT')    - opens subsystem OUTTO_STMCODEER/TESTOUT
 * hilite_system('OUTTO_STMCODEER/TESTOUT/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OUTTO_STMCODEER'
 * '<S1>'   : 'OUTTO_STMCODEER/TESTOUT'
 * '<S2>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER'
 * '<S3>'   : 'OUTTO_STMCODEER/TESTOUT/MATLAB Function'
 * '<S4>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/0-Tm_x1'
 * '<S5>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/0-Tm_y2'
 * '<S6>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem'
 * '<S7>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem1'
 * '<S8>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem/Clock'
 * '<S9>'   : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem/Clock1'
 * '<S10>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem/MATLAB Function'
 * '<S11>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem/MATLAB Function1'
 * '<S12>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem1/Clock'
 * '<S13>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem1/Clock1'
 * '<S14>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem1/MATLAB Function'
 * '<S15>'  : 'OUTTO_STMCODEER/TESTOUT/BEZIER/Subsystem1/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_TESTOUT_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
