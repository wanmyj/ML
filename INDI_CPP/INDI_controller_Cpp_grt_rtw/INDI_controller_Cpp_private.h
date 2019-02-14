/*
 * INDI_controller_Cpp_private.h
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

#ifndef RTW_HEADER_INDI_controller_Cpp_private_h_
#define RTW_HEADER_INDI_controller_Cpp_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

extern void LUf_int32_Treal_T(real_T outU[], real_T outP[], int32_T N);
extern uint32_T plook_binpg(real_T u, const real_T bp[], uint32_T maxIndex,
  real_T *fraction, uint32_T *prevIndex);
extern real_T intrp3d_l(const uint32_T bpIndex[], const real_T frac[], const
  real_T table[], const uint32_T stride[]);
extern uint32_T binsearch_u32d_prevIdx(real_T u, const real_T bp[], uint32_T
  startIndex, uint32_T maxIndex);

/* private model entry point functions */
extern void INDI_controller_Cpp_derivatives();

#endif                                 /* RTW_HEADER_INDI_controller_Cpp_private_h_ */
