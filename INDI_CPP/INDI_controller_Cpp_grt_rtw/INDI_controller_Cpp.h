/*
 * INDI_controller_Cpp.h
 *
 * Code generation for model "INDI_controller_Cpp".
 *
 * Model version              : 1.397
 * Simulink Coder version : 8.13 (R2017b) 24-Jul-2017
 * C++ source code generated on : Tue Jan 29 09:20:18 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Custom Processor->Custom
 * Code generation objective: Execution efficiency
 * Validation result: Passed (11), Warning (1), Error (0)
 */

#ifndef RTW_HEADER_INDI_controller_Cpp_h_
#define RTW_HEADER_INDI_controller_Cpp_h_
#include <cmath>
#include <string.h>
#ifndef INDI_controller_Cpp_COMMON_INCLUDES_
# define INDI_controller_Cpp_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* INDI_controller_Cpp_COMMON_INCLUDES_ */

#include "INDI_controller_Cpp_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
# define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
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

/* Block signals (auto storage) */
typedef struct {
  real_T IdentityMatrix[9];            /* '<S1>/Identity Matrix' */
  real_T e_pqr[3];                     /* '<Root>/Sum1' */
  real_T FilterCoefficient[3];         /* '<S6>/Filter Coefficient' */
  real_T w_ddot_int[3];                /* '<S8>/w_ddot_int' */
  real_T w_dot_est[3];                 /* '<S8>/Sum10' */
  real_T w_dot_int[3];                 /* '<S8>/w_dot_int' */
  real_T xiwn[3];                      /* '<S8>/xiwn' */
  real_T Sum2[3];                      /* '<S8>/Sum2' */
} B_INDI_controller_Cpp_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T w_ddot_int_DSTATE[3];         /* '<S8>/w_ddot_int' */
  real_T w_dot_int_DSTATE[3];          /* '<S8>/w_dot_int' */
  uint32_T alpha_DWORK1;               /* '<S2>/alpha' */
  uint32_T nonbeta_DWORK1;             /* '<S2>/non beta' */
  uint32_T d_o_a_DWORK1;               /* '<S2>/d_o_a' */
  uint32_T d_c_e1_DWORK1;              /* '<S2>/d_c_e1' */
  uint32_T beta_DWORK1;                /* '<S2>/beta' */
  uint32_T d_c_e_DWORK1;               /* '<S2>/d_c_e' */
  uint32_T alpha_DWORK1_k;             /* '<S3>/alpha' */
  uint32_T nonbeta_DWORK1_d;           /* '<S3>/non beta' */
  uint32_T d_o_a_DWORK1_b;             /* '<S3>/d_o_a' */
  uint32_T d_c_e1_DWORK1_g;            /* '<S3>/d_c_e1' */
  uint32_T beta_DWORK1_c;              /* '<S3>/beta' */
  uint32_T d_c_e_DWORK1_i;             /* '<S3>/d_c_e' */
  uint32_T alpha_DWORK1_kx;            /* '<S13>/alpha' */
  uint32_T nonbeta_DWORK1_n;           /* '<S13>/non beta' */
  uint32_T d_o_a_DWORK1_e;             /* '<S13>/d_o_a' */
  uint32_T alpha_DWORK1_b;             /* '<S15>/alpha' */
  uint32_T nonbeta_DWORK1_e;           /* '<S15>/non beta' */
  uint32_T d_o_a_DWORK1_d;             /* '<S15>/d_o_a' */
  uint32_T alpha_DWORK1_n;             /* '<S14>/alpha' */
  uint32_T beta_DWORK1_g;              /* '<S14>/beta' */
  uint32_T d_o_e_DWORK1;               /* '<S14>/d_o_e' */
  uint32_T d_i_e_DWORK1;               /* '<S14>/d_i_e' */
  uint32_T d_c_e_DWORK1_j;             /* '<S14>/d_c_e' */
  uint32_T nonbeta_DWORK1_eg;          /* '<S14>/non beta' */
  uint32_T d_o_a_DWORK1_f;             /* '<S14>/d_o_a' */
  uint32_T d_i_e1_DWORK1;              /* '<S14>/d_i_e1' */
  uint32_T d_c_e1_DWORK1_o;            /* '<S14>/d_c_e1' */
  uint32_T alpha_DWORK1_p;             /* '<S16>/alpha' */
  uint32_T beta_DWORK1_p;              /* '<S16>/beta' */
  uint32_T d_o_e_DWORK1_h;             /* '<S16>/d_o_e' */
  uint32_T d_i_e_DWORK1_n;             /* '<S16>/d_i_e' */
  uint32_T d_c_e_DWORK1_d;             /* '<S16>/d_c_e' */
  uint32_T nonbeta_DWORK1_b;           /* '<S16>/non beta' */
  uint32_T d_o_a_DWORK1_o;             /* '<S16>/d_o_a' */
  uint32_T d_i_e1_DWORK1_c;            /* '<S16>/d_i_e1' */
  uint32_T d_c_e1_DWORK1_k;            /* '<S16>/d_c_e1' */
  uint32_T beta_DWORK1_h;              /* '<S13>/beta' */
  uint32_T d_o_e_DWORK1_n;             /* '<S13>/d_o_e' */
  uint32_T d_i_e_DWORK1_o;             /* '<S13>/d_i_e' */
  uint32_T d_c_e_DWORK1_m;             /* '<S13>/d_c_e' */
  uint32_T d_i_e1_DWORK1_i;            /* '<S13>/d_i_e1' */
  uint32_T d_c_e1_DWORK1_c;            /* '<S13>/d_c_e1' */
} DW_INDI_controller_Cpp_T;

/* Continuous states (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S6>/Integrator' */
  real_T Filter_CSTATE[3];             /* '<S6>/Filter' */
} X_INDI_controller_Cpp_T;

/* State derivatives (auto storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S6>/Integrator' */
  real_T Filter_CSTATE[3];             /* '<S6>/Filter' */
} XDot_INDI_controller_Cpp_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S6>/Integrator' */
  boolean_T Filter_CSTATE[3];          /* '<S6>/Filter' */
} XDis_INDI_controller_Cpp_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (auto storage) */
typedef struct {
  /* Expression: diag([bref cbar bref])
   * Referenced by: '<Root>/bcb'
   */
  real_T bcb_Value[9];

  /* Pooled Parameter (Expression: alpha_breakpoint)
   * Referenced by:
   *   '<S2>/alpha'
   *   '<S3>/alpha'
   *   '<S13>/alpha'
   *   '<S14>/alpha'
   *   '<S15>/alpha'
   *   '<S16>/alpha'
   */
  real_T pooled1[15];

  /* Pooled Parameter (Expression: beta_nsym_breakpoint)
   * Referenced by:
   *   '<S2>/non beta'
   *   '<S3>/non beta'
   *   '<S13>/non beta'
   *   '<S14>/non beta'
   *   '<S15>/non beta'
   *   '<S16>/non beta'
   */
  real_T pooled2[9];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S2>/d_o_a'
   *   '<S3>/d_o_a'
   *   '<S13>/d_i_e1'
   *   '<S13>/d_o_a'
   *   '<S14>/d_i_e1'
   *   '<S14>/d_o_a'
   *   '<S15>/d_o_a'
   *   '<S16>/d_i_e1'
   *   '<S16>/d_o_a'
   */
  real_T pooled4[7];

  /* Pooled Parameter (Expression: d_o_a_Cr)
   * Referenced by:
   *   '<S2>/d_o_a_Cr Using Prelookup4'
   *   '<S3>/d_o_a_Cr Using Prelookup4'
   *   '<S13>/d_o_e_Cr Using Prelookup4'
   *   '<S14>/d_o_e_Cr Using Prelookup4'
   *   '<S15>/d_o_e_Cr Using Prelookup4'
   *   '<S16>/d_o_e_Cr Using Prelookup4'
   */
  real_T pooled5[945];

  /* Pooled Parameter (Mixed Expressions)
   * Referenced by:
   *   '<S2>/d_c_e'
   *   '<S2>/d_c_e1'
   *   '<S3>/d_c_e'
   *   '<S3>/d_c_e1'
   *   '<S13>/d_c_e'
   *   '<S13>/d_c_e1'
   *   '<S13>/d_i_e'
   *   '<S13>/d_o_e'
   *   '<S14>/d_c_e'
   *   '<S14>/d_c_e1'
   *   '<S14>/d_i_e'
   *   '<S14>/d_o_e'
   *   '<S16>/d_c_e'
   *   '<S16>/d_c_e1'
   *   '<S16>/d_i_e'
   *   '<S16>/d_o_e'
   */
  real_T pooled6[13];

  /* Pooled Parameter (Expression: d_r_Cr)
   * Referenced by:
   *   '<S2>/d_o_r_Cr Using Prelookup6'
   *   '<S3>/d_o_r_Cr Using Prelookup6'
   *   '<S14>/d_o_e_Cr Using Prelookup6'
   *   '<S16>/d_o_e_Cr Using Prelookup6'
   */
  real_T pooled7[1755];

  /* Pooled Parameter (Expression: beta_sym_breakpoint)
   * Referenced by:
   *   '<S2>/beta'
   *   '<S3>/beta'
   *   '<S13>/beta'
   *   '<S14>/beta'
   *   '<S16>/beta'
   */
  real_T pooled8[5];

  /* Pooled Parameter (Expression: d_c_e_CM)
   * Referenced by:
   *   '<S2>/d_o_e_CM Using Prelookup2'
   *   '<S3>/d_o_e_CM Using Prelookup2'
   *   '<S13>/d_o_e_CM Using Prelookup2'
   *   '<S14>/d_o_e_CM Using Prelookup2'
   */
  real_T pooled9[975];

  /* Pooled Parameter (Expression: d_o_a_Cn)
   * Referenced by:
   *   '<S2>/d_o_e_Cn Using Prelookup5'
   *   '<S3>/d_o_e_Cn Using Prelookup5'
   *   '<S13>/d_o_e_Cn Using Prelookup5'
   *   '<S14>/d_o_e_Cn Using Prelookup5'
   *   '<S15>/d_o_e_Cn Using Prelookup5'
   *   '<S16>/d_o_e_Cn Using Prelookup5'
   */
  real_T pooled10[945];

  /* Pooled Parameter (Expression: d_r_Cn)
   * Referenced by:
   *   '<S2>/d_o_e_Cn Using Prelookup6'
   *   '<S3>/d_o_e_Cn Using Prelookup6'
   *   '<S14>/d_o_e_Cn Using Prelookup6'
   *   '<S16>/d_o_e_Cn Using Prelookup6'
   */
  real_T pooled11[1755];

  /* Pooled Parameter (Expression: inertia)
   * Referenced by:
   *   '<Root>/Constant4'
   *   '<S8>/Constant'
   */
  real_T pooled14[9];

  /* Expression: Sref*diag([bref cbar bref])
   * Referenced by: '<Root>/Gain1'
   */
  real_T Gain1_Gain[9];

  /* Pooled Parameter (Expression: d_o_e_Cr)
   * Referenced by:
   *   '<S14>/d_o_e_Cr Using Prelookup1'
   *   '<S16>/d_o_e_Cr Using Prelookup1'
   */
  real_T pooled15[975];

  /* Pooled Parameter (Expression: d_i_e_Cr)
   * Referenced by:
   *   '<S14>/d_o_e_Cr Using Prelookup2'
   *   '<S16>/d_o_e_Cr Using Prelookup2'
   */
  real_T pooled16[975];

  /* Pooled Parameter (Expression: d_c_e_Cr)
   * Referenced by:
   *   '<S14>/d_o_e_Cr Using Prelookup3'
   *   '<S16>/d_o_e_Cr Using Prelookup3'
   */
  real_T pooled17[975];

  /* Pooled Parameter (Expression: d_i_a_Cr)
   * Referenced by:
   *   '<S14>/d_o_e_Cr Using Prelookup5'
   *   '<S16>/d_o_e_Cr Using Prelookup5'
   */
  real_T pooled18[945];

  /* Pooled Parameter (Expression: d_o_e_CM)
   * Referenced by:
   *   '<S13>/d_o_e_CM Using Prelookup3'
   *   '<S14>/d_o_e_CM Using Prelookup3'
   */
  real_T pooled19[975];

  /* Pooled Parameter (Expression: d_i_e_CM)
   * Referenced by:
   *   '<S13>/d_o_e_CM Using Prelookup1'
   *   '<S14>/d_o_e_CM Using Prelookup1'
   */
  real_T pooled20[975];

  /* Pooled Parameter (Expression: d_o_a_CM)
   * Referenced by:
   *   '<S13>/d_o_e_CM Using Prelookup6'
   *   '<S14>/d_o_e_CM Using Prelookup6'
   */
  real_T pooled21[945];

  /* Pooled Parameter (Expression: d_i_a_CM)
   * Referenced by:
   *   '<S13>/d_o_e_CM Using Prelookup4'
   *   '<S14>/d_o_e_CM Using Prelookup4'
   */
  real_T pooled22[945];

  /* Pooled Parameter (Expression: d_r_CM)
   * Referenced by:
   *   '<S13>/d_o_e_CM Using Prelookup5'
   *   '<S14>/d_o_e_CM Using Prelookup5'
   */
  real_T pooled23[1755];

  /* Pooled Parameter (Expression: d_o_e_Cn)
   * Referenced by:
   *   '<S14>/d_o_e_Cn Using Prelookup2'
   *   '<S16>/d_o_e_Cn Using Prelookup2'
   */
  real_T pooled24[975];

  /* Pooled Parameter (Expression: d_i_e_Cn)
   * Referenced by:
   *   '<S14>/d_o_e_Cn Using Prelookup1'
   *   '<S16>/d_o_e_Cn Using Prelookup1'
   */
  real_T pooled25[975];

  /* Pooled Parameter (Expression: d_c_e_Cn)
   * Referenced by:
   *   '<S14>/d_o_e_Cn Using Prelookup3'
   *   '<S16>/d_o_e_Cn Using Prelookup3'
   */
  real_T pooled26[975];

  /* Pooled Parameter (Expression: d_i_a_Cn)
   * Referenced by:
   *   '<S14>/d_o_e_Cn Using Prelookup4'
   *   '<S16>/d_o_e_Cn Using Prelookup4'
   */
  real_T pooled27[945];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S2>/d_o_a_Cr Using Prelookup4'
   *   '<S2>/d_o_e_Cn Using Prelookup5'
   *   '<S2>/d_o_e_Cn Using Prelookup6'
   *   '<S2>/d_o_r_Cr Using Prelookup6'
   *   '<S3>/d_o_a_Cr Using Prelookup4'
   *   '<S3>/d_o_e_Cn Using Prelookup5'
   *   '<S3>/d_o_e_Cn Using Prelookup6'
   *   '<S3>/d_o_r_Cr Using Prelookup6'
   *   '<S13>/d_o_e_CM Using Prelookup4'
   *   '<S13>/d_o_e_CM Using Prelookup5'
   *   '<S13>/d_o_e_CM Using Prelookup6'
   *   '<S13>/d_o_e_Cn Using Prelookup5'
   *   '<S13>/d_o_e_Cr Using Prelookup4'
   *   '<S14>/d_o_e_CM Using Prelookup4'
   *   '<S14>/d_o_e_CM Using Prelookup5'
   *   '<S14>/d_o_e_CM Using Prelookup6'
   *   '<S14>/d_o_e_Cn Using Prelookup4'
   *   '<S14>/d_o_e_Cn Using Prelookup5'
   *   '<S14>/d_o_e_Cn Using Prelookup6'
   *   '<S14>/d_o_e_Cr Using Prelookup4'
   *   '<S14>/d_o_e_Cr Using Prelookup5'
   *   '<S14>/d_o_e_Cr Using Prelookup6'
   *   '<S15>/d_o_e_Cn Using Prelookup5'
   *   '<S15>/d_o_e_Cr Using Prelookup4'
   *   '<S16>/d_o_e_Cn Using Prelookup4'
   *   '<S16>/d_o_e_Cn Using Prelookup5'
   *   '<S16>/d_o_e_Cn Using Prelookup6'
   *   '<S16>/d_o_e_Cr Using Prelookup4'
   *   '<S16>/d_o_e_Cr Using Prelookup5'
   *   '<S16>/d_o_e_Cr Using Prelookup6'
   */
  uint32_T pooled29[3];

  /* Pooled Parameter (Expression: )
   * Referenced by:
   *   '<S2>/d_o_e_CM Using Prelookup2'
   *   '<S3>/d_o_e_CM Using Prelookup2'
   *   '<S13>/d_o_e_CM Using Prelookup1'
   *   '<S13>/d_o_e_CM Using Prelookup2'
   *   '<S13>/d_o_e_CM Using Prelookup3'
   *   '<S14>/d_o_e_CM Using Prelookup1'
   *   '<S14>/d_o_e_CM Using Prelookup2'
   *   '<S14>/d_o_e_CM Using Prelookup3'
   *   '<S14>/d_o_e_Cn Using Prelookup1'
   *   '<S14>/d_o_e_Cn Using Prelookup2'
   *   '<S14>/d_o_e_Cn Using Prelookup3'
   *   '<S14>/d_o_e_Cr Using Prelookup1'
   *   '<S14>/d_o_e_Cr Using Prelookup2'
   *   '<S14>/d_o_e_Cr Using Prelookup3'
   *   '<S16>/d_o_e_Cn Using Prelookup1'
   *   '<S16>/d_o_e_Cn Using Prelookup2'
   *   '<S16>/d_o_e_Cn Using Prelookup3'
   *   '<S16>/d_o_e_Cr Using Prelookup1'
   *   '<S16>/d_o_e_Cr Using Prelookup2'
   *   '<S16>/d_o_e_Cr Using Prelookup3'
   */
  uint32_T pooled30[3];
} ConstP_INDI_controller_Cpp_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  are ctrlsfc;                         /* '<Root>/ctrlsfc' */
  real_T DCMbe[9];                     /* '<Root>/DCMbe' */
  real_T abar;                         /* '<Root>/qbar' */
  real_T pqr_des[3];                   /* '<Root>/pqr_des' */
  real_T pqr[3];                       /* '<Root>/pqr' */
  real_T v_ned[3];                     /* '<Root>/v_ned' */
} ExtU_INDI_controller_Cpp_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  actCmd actCMD;                       /* '<Root>/actCMD' */
} ExtY_INDI_controller_Cpp_T;

/* Real-time Model Data Structure */
struct tag_RTM_INDI_controller_Cpp_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_INDI_controller_Cpp_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
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
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* External data declarations for dependent source files */
extern const actCmd INDI_controller_Cpp_rtZactCmd;/* actCmd ground */

/* Constant parameters (auto storage) */
extern const ConstP_INDI_controller_Cpp_T INDI_controller_Cpp_ConstP;

/* Class declaration for model INDI_controller_Cpp */
class INDI_controller_CppModelClass {
  /* public data and function members */
 public:
  /* External inputs */
  ExtU_INDI_controller_Cpp_T INDI_controller_Cpp_U;

  /* External outputs */
  ExtY_INDI_controller_Cpp_T INDI_controller_Cpp_Y;

  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  INDI_controller_CppModelClass();

  /* Destructor */
  ~INDI_controller_CppModelClass();

  /* Real-Time Model get method */
  RT_MODEL_INDI_controller_Cpp_T * getRTM();

  /* private data and function members */
 private:
  /* Block signals */
  B_INDI_controller_Cpp_T INDI_controller_Cpp_B;

  /* Block states */
  DW_INDI_controller_Cpp_T INDI_controller_Cpp_DW;
  X_INDI_controller_Cpp_T INDI_controller_Cpp_X;/* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_INDI_controller_Cpp_T INDI_controller_Cpp_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void INDI_controller_Cpp_derivatives();
};

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
 * '<Root>' : 'INDI_controller_Cpp'
 * '<S1>'   : 'INDI_controller_Cpp/ LU Inverse1'
 * '<S2>'   : 'INDI_controller_Cpp/(PSS) control surface'
 * '<S3>'   : 'INDI_controller_Cpp/(PSS) control surface1'
 * '<S4>'   : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)'
 * '<S5>'   : 'INDI_controller_Cpp/MATLAB Function'
 * '<S6>'   : 'INDI_controller_Cpp/PID_pqr'
 * '<S7>'   : 'INDI_controller_Cpp/moment coeff Matrix'
 * '<S8>'   : 'INDI_controller_Cpp/pqr_est_blk'
 * '<S9>'   : 'INDI_controller_Cpp/ LU Inverse1/LU Solver'
 * '<S10>'  : 'INDI_controller_Cpp/ LU Inverse1/LU Solver/Check Signal Attributes'
 * '<S11>'  : 'INDI_controller_Cpp/ LU Inverse1/LU Solver/Check Signal Attributes1'
 * '<S12>'  : 'INDI_controller_Cpp/ LU Inverse1/LU Solver/Check Signal Attributes2'
 * '<S13>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/ParameterSearchSystem(PSS)'
 * '<S14>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/ParameterSearchSystem(PSS)1'
 * '<S15>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/ParameterSearchSystem(PSS)2'
 * '<S16>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/ParameterSearchSystem(PSS)4'
 * '<S17>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/formulation 1 for (CL CD CM)CM'
 * '<S18>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/formulation 2 for (CY Cn Cr)Cn'
 * '<S19>'  : 'INDI_controller_Cpp/CoefficientSearch & CalculationSystem(CSCS)/formulation 2 for (CY Cn Cr)Cr'
 * '<S20>'  : 'INDI_controller_Cpp/pqr_est_blk/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_INDI_controller_Cpp_h_ */
