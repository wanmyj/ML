/*
 * INDI_controller_Cpp_types.h
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

#ifndef RTW_HEADER_INDI_controller_Cpp_types_h_
#define RTW_HEADER_INDI_controller_Cpp_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#ifndef DEFINED_TYPEDEF_FOR_are_
#define DEFINED_TYPEDEF_FOR_are_

typedef struct {
  real_T a;
  real_T r;
  real_T e;
} are;

#endif

#ifndef DEFINED_TYPEDEF_FOR_actCmd_
#define DEFINED_TYPEDEF_FOR_actCmd_

typedef struct {
  real_T ailCMD;
  real_T eleCMD;
  real_T rudCMD;
} actCmd;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_INDI_controller_Cpp_T RT_MODEL_INDI_controller_Cpp_T;

#endif                                 /* RTW_HEADER_INDI_controller_Cpp_types_h_ */
