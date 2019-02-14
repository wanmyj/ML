/*
 * INDI_controller_Cpp.cpp
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

#include "INDI_controller_Cpp.h"
#include "INDI_controller_Cpp_private.h"
#include <iostream>
using namespace std;

const actCmd INDI_controller_Cpp_rtZactCmd = {
  0.0,                                 /* ailCMD */
  0.0,                                 /* eleCMD */
  0.0                                  /* rudCMD */
} ;                                    /* actCmd ground */

uint32_T plook_binpg(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                     *fraction, uint32_T *prevIndex)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Use previous index: 'on'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'on'
   */
  if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d_prevIdx(u, bp, *prevIndex, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex - 1U;
    *fraction = (u - bp[maxIndex - 1U]) / (bp[maxIndex] - bp[maxIndex - 1U]);
  }

  *prevIndex = bpIndex;
  return bpIndex;
}

real_T intrp3d_l(const uint32_T bpIndex[], const real_T frac[], const real_T
                 table[], const uint32_T stride[])
{
  real_T yL_2d;
  uint32_T offset_2d;
  real_T yL_1d;
  uint32_T offset_0d;

  /* Interpolation 3-D
     Interpolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'wrapping'
   */
  offset_2d = (bpIndex[2U] * stride[2U] + bpIndex[1U] * stride[1U]) + bpIndex[0U];
  yL_1d = (table[offset_2d + 1U] - table[offset_2d]) * frac[0U] +
    table[offset_2d];
  offset_0d = offset_2d + stride[1U];
  yL_2d = (((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
            table[offset_0d]) - yL_1d) * frac[1U] + yL_1d;
  offset_2d += stride[2U];
  yL_1d = (table[offset_2d + 1U] - table[offset_2d]) * frac[0U] +
    table[offset_2d];
  offset_0d = offset_2d + stride[1U];
  return (((((table[offset_0d + 1U] - table[offset_0d]) * frac[0U] +
             table[offset_0d]) - yL_1d) * frac[1U] + yL_1d) - yL_2d) * frac[2U]
    + yL_2d;
}

uint32_T binsearch_u32d_prevIdx(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIndex;
  uint32_T iRght;
  uint32_T iLeft;
  uint32_T found;

  /* Binary Search using Previous Index */
  bpIndex = startIndex;
  iLeft = 0U;
  iRght = maxIndex;
  found = 0U;
  while (found == 0U) {
    if (u < bp[bpIndex]) {
      iRght = bpIndex - 1U;
      bpIndex = (iRght + iLeft) >> 1U;
    } else if (u < bp[bpIndex + 1U]) {
      found = 1U;
    } else {
      iLeft = bpIndex + 1U;
      bpIndex = (iRght + iLeft) >> 1U;
    }
  }

  return bpIndex;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void INDI_controller_CppModelClass::rt_ertODEUpdateContinuousStates
  (RTWSolverInfo *si )
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
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  INDI_controller_Cpp_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  INDI_controller_Cpp_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  INDI_controller_Cpp_derivatives();

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

void LUf_int32_Treal_T(real_T outU[], real_T outP[], int32_T N)
{
  int32_T k;
  int32_T c;
  int32_T r;
  int32_T idx1;
  int32_T p;
  real_T mTmp1;
  boolean_T isDiagZero;
  real_T mAccum;
  int32_T idx1_tmp;
  int32_T tmp;

  /* S-Function (sdsplu2): '<S9>/LU Factorization' */
  /* initialize row-pivot indices */
  for (k = 0; k < N; k++) {
    outP[k] = (real_T)k + 1.0;
  }

  for (k = 0; k < N; k++) {
    p = k;

    /* Scan the lower triangular part of this column only. */
    /* Record row of largest value */
    idx1_tmp = k * N;
    mTmp1 = outU[idx1_tmp + k];
    if (outU[idx1_tmp + k] < 0.0) {
      mTmp1 = -outU[idx1_tmp + k];
    }

    for (r = k + 1; r < N; r++) {
      mAccum = outU[idx1_tmp + r];
      if (outU[idx1_tmp + r] < 0.0) {
        mAccum = -outU[idx1_tmp + r];
      }

      if (mAccum > mTmp1) {
        p = r;
        mTmp1 = mAccum;
      }
    }

    /* swap rows if required */
    if (p != k) {
      for (c = 0; c < N; c++) {
        idx1 = c * N;
        r = idx1 + p;
        mTmp1 = outU[r];
        tmp = idx1 + k;
        outU[r] = outU[tmp];
        outU[tmp] = mTmp1;
      }

      /* swap pivot row indices */
      mTmp1 = outP[p];
      outP[p] = outP[k];
      outP[k] = mTmp1;
    }

    idx1 = k * N + k;
    isDiagZero = false;
    if (outU[idx1] == 0.0) {
      isDiagZero = true;
    }

    if (!isDiagZero) {
      for (r = k + 1; r < N; r++) {
        tmp = idx1_tmp + r;
        outU[tmp] /= outU[idx1];
      }

      for (c = k + 1; c < N; c++) {
        idx1 = c * N;
        for (r = k + 1; r < N; r++) {
          tmp = idx1 + r;
          outU[tmp] -= outU[idx1_tmp + r] * outU[idx1 + k];
        }
      }
    }
  }

  /* End of S-Function (sdsplu2): '<S9>/LU Factorization' */
}

/* Model step function */
void INDI_controller_CppModelClass::step()
{
  cout << "step function start" << endl;
  /* local block i/o variables */
  real_T rtb_C_m_u[9];
  int32_T j;
  int32_T idxB;
  int32_T idxLU;
  real_T c;
  real_T scale;
  real_T absxk;
  real_T t;
  uint32_T rtb_d_c_e_o1_o;
  real_T rtb_d_o_e_CrUsingPrelookup5;
  uint32_T rtb_beta_o1_c;
  uint32_T rtb_alpha_o1_i;
  real_T rtb_d_o_e_CrUsingPrelookup4_e;
  uint32_T rtb_alpha_o1_e;
  uint32_T rtb_nonbeta_o1_e;
  uint32_T rtb_alpha_o1_c;
  real_T rtb_d_o_e_CnUsingPrelookup5;
  real_T rtb_d_o_e_CnUsingPrelookup4_g;
  real_T rtb_d_o_e_CnUsingPrelookup5_f;
  uint32_T rtb_nonbeta_o1;
  real_T rtb_nonbeta_o2;
  uint32_T rtb_d_o_a_o1;
  uint32_T rtb_d_c_e1_o1;
  real_T rtb_d_o_e_CnUsingPrelookup2;
  uint32_T rtb_alpha_o1;
  real_T rtb_d_o_e_CnUsingPrelookup6;
  uint32_T rtb_d_c_e_o1;
  real_T rtb_d_o_e_CnUsingPrelookup3;
  uint32_T rtb_beta_o1;
  real_T rtb_beta_o2;
  real_T rtb_v_b[3];
  real_T rtb_alpha;
  real_T rtb_beta;
  real_T rtb_VectorConcatenate[9];
  real_T rtb_Sum_h[3];
  real_T rtb_d_o_e_CrUsingPrelookup4;
  real_T rtb_Add6[6];
  real_T frac[3];
  uint32_T bpIndex[3];
  real_T rtb_d_o_e_CrUsingPrelookup3;
  real_T frac_0[3];
  uint32_T bpIndex_0[3];
  real_T frac_1[3];
  uint32_T bpIndex_1[3];
  real_T frac_2[3];
  uint32_T bpIndex_2[3];
  real_T frac_3[3];
  uint32_T bpIndex_3[3];
  real_T frac_4[3];
  uint32_T bpIndex_4[3];
  real_T frac_5[3];
  uint32_T bpIndex_5[3];
  real_T frac_6[3];
  uint32_T bpIndex_6[3];
  real_T frac_7[3];
  uint32_T bpIndex_7[3];
  real_T frac_8[3];
  uint32_T bpIndex_8[3];
  real_T frac_9[3];
  uint32_T bpIndex_9[3];
  real_T frac_a[3];
  uint32_T bpIndex_a[3];
  real_T frac_b[3];
  uint32_T bpIndex_b[3];
  real_T frac_c[3];
  uint32_T bpIndex_c[3];
  real_T frac_d[3];
  uint32_T bpIndex_d[3];
  real_T frac_e[3];
  uint32_T bpIndex_e[3];
  real_T rtb_d_o_e_CnUsingPrelookup5_h;
  real_T frac_f[3];
  uint32_T bpIndex_f[3];
  real_T rtb_d_o_e_CnUsingPrelookup1;
  real_T frac_g[3];
  uint32_T bpIndex_g[3];
  real_T frac_h[3];
  uint32_T bpIndex_h[3];
  real_T frac_i[3];
  uint32_T bpIndex_i[3];
  real_T frac_j[3];
  uint32_T bpIndex_j[3];
  real_T frac_k[3];
  uint32_T bpIndex_k[3];
  real_T frac_l[3];
  uint32_T bpIndex_l[3];
  real_T frac_m[3];
  uint32_T bpIndex_m[3];
  real_T frac_n[3];
  uint32_T bpIndex_n[3];
  real_T frac_o[3];
  uint32_T bpIndex_o[3];
  real_T frac_p[3];
  uint32_T bpIndex_p[3];
  real_T frac_q[3];
  uint32_T bpIndex_q[3];
  real_T frac_r[3];
  uint32_T bpIndex_r[3];
  real_T frac_s[3];
  uint32_T bpIndex_s[3];
  real_T frac_t[3];
  uint32_T bpIndex_t[3];
  real_T frac_u[3];
  uint32_T bpIndex_u[3];
  real_T frac_v[3];
  uint32_T bpIndex_v[3];
  real_T rtb_d_o_e_CMUsingPrelookup2_a;
  real_T frac_w[3];
  uint32_T bpIndex_w[3];
  real_T rtb_d_o_e_CMUsingPrelookup6_a;
  real_T frac_x[3];
  uint32_T bpIndex_x[3];
  real_T rtb_d_o_e_CMUsingPrelookup4_c;
  real_T frac_y[3];
  uint32_T bpIndex_y[3];
  real_T rtb_d_o_e_CMUsingPrelookup5_e;
  real_T frac_z[3];
  uint32_T bpIndex_z[3];
  real_T frac_10[3];
  uint32_T bpIndex_10[3];
  real_T frac_11[3];
  uint32_T bpIndex_11[3];
  real_T frac_12[3];
  uint32_T bpIndex_12[3];
  real_T frac_13[3];
  uint32_T bpIndex_13[3];
  real_T frac_14[3];
  uint32_T bpIndex_14[3];
  real_T frac_15[3];
  uint32_T bpIndex_15[3];
  real_T frac_16[3];
  uint32_T bpIndex_16[3];
  real_T frac_17[3];
  uint32_T bpIndex_17[3];
  real_T frac_18[3];
  uint32_T bpIndex_18[3];
  real_T frac_19[3];
  uint32_T bpIndex_19[3];
  real_T frac_1a[3];
  uint32_T bpIndex_1a[3];
  real_T frac_1b[3];
  uint32_T bpIndex_1b[3];
  real_T frac_1c[3];
  uint32_T bpIndex_1c[3];
  real_T rtb_BackwardSubstitution[9];
  int32_T k;
  real_T rtb_d_o_e_CnUsingPrelookup1_0[6];
  int32_T rtb_C_m_u_tmp;
  cout << "step function check positon 1" << endl;
  
  if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
    /* set solver stop time */
    if (!((&INDI_controller_Cpp_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&INDI_controller_Cpp_M)->solverInfo,
                            (((&INDI_controller_Cpp_M)->Timing.clockTickH0 + 1) *
        (&INDI_controller_Cpp_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&INDI_controller_Cpp_M)->solverInfo,
                            (((&INDI_controller_Cpp_M)->Timing.clockTick0 + 1) *
        (&INDI_controller_Cpp_M)->Timing.stepSize0 + (&INDI_controller_Cpp_M)
        ->Timing.clockTickH0 * (&INDI_controller_Cpp_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&INDI_controller_Cpp_M))) {
    (&INDI_controller_Cpp_M)->Timing.t[0] = rtsiGetT(&(&INDI_controller_Cpp_M)
      ->solverInfo);
  }

  /* MATLAB Function: '<Root>/MATLAB Function' */
  /* MATLAB Function 'MATLAB Function': '<S5>:1' */
  /* '<S5>:1:3' X_A_B = v_b / norm(v_b); */
  c = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 3; k++) {
    /* Product: '<Root>/Product' incorporates:
     *  Inport: '<Root>/DCMbe'
     *  Inport: '<Root>/v_ned'
     */
    rtb_d_o_e_CnUsingPrelookup5 = INDI_controller_Cpp_U.DCMbe[k + 6] *
      INDI_controller_Cpp_U.v_ned[2] + (INDI_controller_Cpp_U.DCMbe[k + 3] *
      INDI_controller_Cpp_U.v_ned[1] + INDI_controller_Cpp_U.DCMbe[k] *
      INDI_controller_Cpp_U.v_ned[0]);

    /* MATLAB Function: '<Root>/MATLAB Function' */
    absxk = std::abs(rtb_d_o_e_CnUsingPrelookup5);
    if (absxk > scale) {
      t = scale / absxk;
      c = c * t * t + 1.0;
      scale = absxk;
    } else {
      t = absxk / scale;
      c += t * t;
    }

    /* Product: '<Root>/Product' */
    rtb_v_b[k] = rtb_d_o_e_CnUsingPrelookup5;
  }

  /* MATLAB Function: '<Root>/MATLAB Function' */
  c = scale * std::sqrt(c);
  rtb_v_b[0] /= c;
  rtb_v_b[1] /= c;
  rtb_d_o_e_CnUsingPrelookup5 = rtb_v_b[2] / c;

  /* '<S5>:1:5' v2 = X_A_B(2); */
  /* '<S5>:1:6' v3 = X_A_B(3); */
  /* '<S5>:1:8' c = norm(X_A_B(1:2)); */
  scale = 3.3121686421112381E-170;
  absxk = std::abs(rtb_v_b[0]);
  if (absxk > 3.3121686421112381E-170) {
    c = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.3121686421112381E-170;
    c = t * t;
  }

  absxk = std::abs(rtb_v_b[1]);
  if (absxk > scale) {
    t = scale / absxk;
    c = c * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    c += t * t;
  }

  c = scale * std::sqrt(c);
        cout << "step function check positon 2" << endl;


  /* '<S5>:1:9' alpha = asind(v3/c); */
  /* '<S5>:1:10' beta = asind(v2); */
  rtb_alpha = std::asin(rtb_d_o_e_CnUsingPrelookup5 / c) * 57.295779513082323;
  rtb_beta = 57.295779513082323 * std::asin(rtb_v_b[1]);

  /* PreLookup: '<S2>/alpha' */
  rtb_d_c_e_o1_o = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1,
    14U, &rtb_d_o_e_CrUsingPrelookup5, &INDI_controller_Cpp_DW.alpha_DWORK1);

  /* PreLookup: '<S2>/non beta' */
  rtb_beta_o1_c = plook_binpg(rtb_beta, INDI_controller_Cpp_ConstP.pooled2, 8U,
    &c, &INDI_controller_Cpp_DW.nonbeta_DWORK1);

  /* Bias: '<Root>/Bias2' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_o_e_CrUsingPrelookup4_e = INDI_controller_Cpp_U.ctrlsfc.a + 0.2;

  /* PreLookup: '<S2>/d_o_a' incorporates:
   *  Bias: '<Root>/Bias2'
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_alpha_o1_i = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.a + 0.2,
    INDI_controller_Cpp_ConstP.pooled4, 6U, &rtb_d_o_e_CrUsingPrelookup4_e,
    &INDI_controller_Cpp_DW.d_o_a_DWORK1);

  /* Interpolation_n-D: '<S2>/d_o_a_Cr Using Prelookup4' */
  frac[0] = rtb_d_o_e_CrUsingPrelookup5;
  frac[1] = c;
  frac[2] = rtb_d_o_e_CrUsingPrelookup4_e;
  bpIndex[0] = rtb_d_c_e_o1_o;
  bpIndex[1] = rtb_beta_o1_c;
  bpIndex[2] = rtb_alpha_o1_i;
  rtb_d_o_e_CrUsingPrelookup3 = intrp3d_l(bpIndex, frac,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);

  /* Bias: '<Root>/Bias3' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  scale = INDI_controller_Cpp_U.ctrlsfc.r + 0.2;

  /* PreLookup: '<S2>/d_c_e1' incorporates:
   *  Bias: '<Root>/Bias3'
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_alpha_o1_e = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.r + 0.2,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &scale,
    &INDI_controller_Cpp_DW.d_c_e1_DWORK1);

  /* Interpolation_n-D: '<S2>/d_o_r_Cr Using Prelookup6' */
  frac_0[0] = rtb_d_o_e_CrUsingPrelookup5;
  frac_0[1] = c;
  frac_0[2] = scale;
  bpIndex_0[0] = rtb_d_c_e_o1_o;
  bpIndex_0[1] = rtb_beta_o1_c;
  bpIndex_0[2] = rtb_alpha_o1_e;
  rtb_beta_o2 = intrp3d_l(bpIndex_0, frac_0, INDI_controller_Cpp_ConstP.pooled7,
    INDI_controller_Cpp_ConstP.pooled29);

  /* Abs: '<Root>/Abs' incorporates:
   *  Abs: '<Root>/Abs1'
   *  Abs: '<S4>/Abs'
   */
  rtb_d_o_e_CMUsingPrelookup2_a = std::abs(rtb_beta);
  absxk = rtb_d_o_e_CMUsingPrelookup2_a;

  /* PreLookup: '<S2>/beta' incorporates:
   *  Abs: '<Root>/Abs'
   */
  rtb_nonbeta_o1_e = plook_binpg(rtb_d_o_e_CMUsingPrelookup2_a,
    INDI_controller_Cpp_ConstP.pooled8, 4U, &absxk,
    &INDI_controller_Cpp_DW.beta_DWORK1);

  /* Bias: '<Root>/Bias' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  t = INDI_controller_Cpp_U.ctrlsfc.e + 0.2;

  /* PreLookup: '<S2>/d_c_e' incorporates:
   *  Bias: '<Root>/Bias'
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_alpha_o1_c = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.e + 0.2,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &t,
    &INDI_controller_Cpp_DW.d_c_e_DWORK1);

  /* Interpolation_n-D: '<S2>/d_o_e_CM Using Prelookup2' */
  frac_1[0] = rtb_d_o_e_CrUsingPrelookup5;
  frac_1[1] = absxk;
  frac_1[2] = t;
  bpIndex_1[0] = rtb_d_c_e_o1_o;
  bpIndex_1[1] = rtb_nonbeta_o1_e;
  bpIndex_1[2] = rtb_alpha_o1_c;
  absxk = intrp3d_l(bpIndex_1, frac_1, INDI_controller_Cpp_ConstP.pooled9,
                    INDI_controller_Cpp_ConstP.pooled30);

      cout << "step function check positon 4" << endl;

  /* Interpolation_n-D: '<S2>/d_o_e_Cn Using Prelookup5' */
  frac_2[0] = rtb_d_o_e_CrUsingPrelookup5;
  frac_2[1] = c;
  frac_2[2] = rtb_d_o_e_CrUsingPrelookup4_e;
  bpIndex_2[0] = rtb_d_c_e_o1_o;
  bpIndex_2[1] = rtb_beta_o1_c;
  bpIndex_2[2] = rtb_alpha_o1_i;
  rtb_d_o_e_CrUsingPrelookup4_e = intrp3d_l(bpIndex_2, frac_2,
    INDI_controller_Cpp_ConstP.pooled10, INDI_controller_Cpp_ConstP.pooled29);

      cout << "step function check positon 6" << endl;

  /* Interpolation_n-D: '<S2>/d_o_e_Cn Using Prelookup6' */
  frac_3[0] = rtb_d_o_e_CrUsingPrelookup5;
  frac_3[1] = c;
  frac_3[2] = scale;
  bpIndex_3[0] = rtb_d_c_e_o1_o;
  bpIndex_3[1] = rtb_beta_o1_c;
  bpIndex_3[2] = rtb_alpha_o1_e;
  rtb_d_o_e_CrUsingPrelookup5 = intrp3d_l(bpIndex_3, frac_3,
    INDI_controller_Cpp_ConstP.pooled11, INDI_controller_Cpp_ConstP.pooled29);

  /* PreLookup: '<S3>/alpha' */
  rtb_alpha_o1_c = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1,
    14U, &t, &INDI_controller_Cpp_DW.alpha_DWORK1_k);

  /* PreLookup: '<S3>/non beta' */
  rtb_nonbeta_o1_e = plook_binpg(rtb_beta, INDI_controller_Cpp_ConstP.pooled2,
    8U, &scale, &INDI_controller_Cpp_DW.nonbeta_DWORK1_d);
      cout << "step function check positon 8" << endl;

  /* Bias: '<Root>/Bias4' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  c = INDI_controller_Cpp_U.ctrlsfc.a + -0.2;
      cout << "step function check positon 10" << endl;

  /* PreLookup: '<S3>/d_o_a' incorporates:
   *  Bias: '<Root>/Bias4'
   *  Inport: '<Root>/ctrlsfc'
   */
  cout << c << endl;
  cout << INDI_controller_Cpp_DW.d_o_a_DWORK1_b << endl;
  rtb_alpha_o1_e = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.a + -0.2,
    INDI_controller_Cpp_ConstP.pooled4, 6U, &c,
    &INDI_controller_Cpp_DW.d_o_a_DWORK1_b);
      cout << "step function check positon 9" << endl;

  /* Interpolation_n-D: '<S3>/d_o_a_Cr Using Prelookup4' */
  frac_4[0] = t;
  frac_4[1] = scale;
  frac_4[2] = c;
  bpIndex_4[0] = rtb_alpha_o1_c;
  bpIndex_4[1] = rtb_nonbeta_o1_e;
  bpIndex_4[2] = rtb_alpha_o1_e;
  rtb_d_o_e_CrUsingPrelookup4 = intrp3d_l(bpIndex_4, frac_4,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);
      cout << "step function check positon 7" << endl;

  /* Bias: '<Root>/Bias5' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_o_e_CnUsingPrelookup5 = INDI_controller_Cpp_U.ctrlsfc.r + -0.2;

  /* PreLookup: '<S3>/d_c_e1' incorporates:
   *  Bias: '<Root>/Bias5'
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_alpha_o1_i = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.r + -0.2,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &rtb_d_o_e_CnUsingPrelookup5,
    &INDI_controller_Cpp_DW.d_c_e1_DWORK1_g);


  /* Interpolation_n-D: '<S3>/d_o_r_Cr Using Prelookup6' */
  frac_5[0] = t;
  frac_5[1] = scale;
  frac_5[2] = rtb_d_o_e_CnUsingPrelookup5;
  bpIndex_5[0] = rtb_alpha_o1_c;
  bpIndex_5[1] = rtb_nonbeta_o1_e;
  bpIndex_5[2] = rtb_alpha_o1_i;
  rtb_d_o_e_CnUsingPrelookup3 = intrp3d_l(bpIndex_5, frac_5,
    INDI_controller_Cpp_ConstP.pooled7, INDI_controller_Cpp_ConstP.pooled29);
      cout << "step function check positon 5" << endl;

  /* Abs: '<Root>/Abs1' */
  rtb_d_o_e_CnUsingPrelookup4_g = rtb_d_o_e_CMUsingPrelookup2_a;

  /* PreLookup: '<S3>/beta' */
  rtb_beta_o1_c = plook_binpg(rtb_d_o_e_CMUsingPrelookup2_a,
    INDI_controller_Cpp_ConstP.pooled8, 4U, &rtb_d_o_e_CnUsingPrelookup4_g,
    &INDI_controller_Cpp_DW.beta_DWORK1_c);

  /* Bias: '<Root>/Bias1' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_o_e_CnUsingPrelookup5_f = INDI_controller_Cpp_U.ctrlsfc.e + -0.2;

  /* PreLookup: '<S3>/d_c_e' incorporates:
   *  Bias: '<Root>/Bias1'
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_c_e_o1_o = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.e + -0.2,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &rtb_d_o_e_CnUsingPrelookup5_f,
    &INDI_controller_Cpp_DW.d_c_e_DWORK1_i);

  /* Interpolation_n-D: '<S3>/d_o_e_CM Using Prelookup2' */
  frac_6[0] = t;
  frac_6[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_6[2] = rtb_d_o_e_CnUsingPrelookup5_f;
  bpIndex_6[0] = rtb_alpha_o1_c;
  bpIndex_6[1] = rtb_beta_o1_c;
  bpIndex_6[2] = rtb_d_c_e_o1_o;
  rtb_d_o_e_CnUsingPrelookup4_g = intrp3d_l(bpIndex_6, frac_6,
    INDI_controller_Cpp_ConstP.pooled9, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S3>/d_o_e_Cn Using Prelookup5' */
  frac_7[0] = t;
  frac_7[1] = scale;
  frac_7[2] = c;
  bpIndex_7[0] = rtb_alpha_o1_c;
  bpIndex_7[1] = rtb_nonbeta_o1_e;
  bpIndex_7[2] = rtb_alpha_o1_e;
  c = intrp3d_l(bpIndex_7, frac_7, INDI_controller_Cpp_ConstP.pooled10,
                INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S3>/d_o_e_Cn Using Prelookup6' */
  frac_8[0] = t;
  frac_8[1] = scale;
  frac_8[2] = rtb_d_o_e_CnUsingPrelookup5;
  bpIndex_8[0] = rtb_alpha_o1_c;
  bpIndex_8[1] = rtb_nonbeta_o1_e;
  bpIndex_8[2] = rtb_alpha_o1_i;
  t = intrp3d_l(bpIndex_8, frac_8, INDI_controller_Cpp_ConstP.pooled11,
                INDI_controller_Cpp_ConstP.pooled29);

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn1' incorporates:
   *  Gain: '<Root>/cal_M5coeff'
   *  Sum: '<Root>/Subtract'
   */
  rtb_VectorConcatenate[0] = (rtb_d_o_e_CrUsingPrelookup3 -
    rtb_d_o_e_CrUsingPrelookup4) * 2.5;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn2' incorporates:
   *  Constant: '<Root>/M5coeff0'
   */
  rtb_VectorConcatenate[1] = 0.0;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn3' incorporates:
   *  Gain: '<Root>/cal_M5coeff'
   *  Sum: '<Root>/Subtract'
   */
  rtb_VectorConcatenate[2] = (rtb_d_o_e_CrUsingPrelookup4_e - c) * 2.5;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn4' incorporates:
   *  Constant: '<Root>/M5coeff0'
   */
  rtb_VectorConcatenate[3] = 0.0;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn5' incorporates:
   *  Gain: '<Root>/cal_M5coeff'
   *  Sum: '<Root>/Subtract'
   */
  rtb_VectorConcatenate[4] = (absxk - rtb_d_o_e_CnUsingPrelookup4_g) * 2.5;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn6' incorporates:
   *  Constant: '<Root>/M5coeff0'
   */
  rtb_VectorConcatenate[5] = 0.0;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn7' incorporates:
   *  Gain: '<Root>/cal_M5coeff'
   *  Sum: '<Root>/Subtract'
   */
  rtb_VectorConcatenate[6] = (rtb_beta_o2 - rtb_d_o_e_CnUsingPrelookup3) * 2.5;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn8' incorporates:
   *  Constant: '<Root>/M5coeff0'
   */
  rtb_VectorConcatenate[7] = 0.0;

  /* SignalConversion: '<S7>/ConcatBufferAtVector ConcatenateIn9' incorporates:
   *  Gain: '<Root>/cal_M5coeff'
   *  Sum: '<Root>/Subtract'
   */
  rtb_VectorConcatenate[8] = (rtb_d_o_e_CrUsingPrelookup5 - t) * 2.5;

  /* Gain: '<Root>/Sref' incorporates:
   *  Inport: '<Root>/qbar'
   *  Product: '<Root>/qbarMcoeff5'
   */
  for (k = 0; k < 9; k++) {
    rtb_VectorConcatenate[k] = INDI_controller_Cpp_U.abar *
      rtb_VectorConcatenate[k] * 1.3573;
  }

  /* End of Gain: '<Root>/Sref' */

  /* Product: '<Root>/Mtp_Cmu' incorporates:
   *  Constant: '<Root>/bcb'
   */
    cout << "step function check positon 3" << endl;

  for (k = 0; k < 3; k++) {
    for (j = 0; j < 3; j++) {
      rtb_C_m_u_tmp = j + 3 * k;
      rtb_C_m_u[rtb_C_m_u_tmp] = 0.0;
      rtb_C_m_u[rtb_C_m_u_tmp] = rtb_C_m_u[3 * k + j] + rtb_VectorConcatenate[3 *
        k] * INDI_controller_Cpp_ConstP.bcb_Value[j];
      rtb_C_m_u[rtb_C_m_u_tmp] = rtb_VectorConcatenate[3 * k + 1] *
        INDI_controller_Cpp_ConstP.bcb_Value[j + 3] + rtb_C_m_u[3 * k + j];
      rtb_C_m_u[rtb_C_m_u_tmp] = rtb_VectorConcatenate[3 * k + 2] *
        INDI_controller_Cpp_ConstP.bcb_Value[j + 6] + rtb_C_m_u[3 * k + j];
    }
  }

  /* End of Product: '<Root>/Mtp_Cmu' */

  /* S-Function (sdsplu2): '<S9>/LU Factorization' */
  memcpy(&rtb_VectorConcatenate[0], &rtb_C_m_u[0], 9U * sizeof(real_T));
  LUf_int32_Treal_T(rtb_VectorConcatenate, rtb_Sum_h, 3);

  /* S-Function (sdspperm2): '<S9>/Permute Matrix' */
  for (k = 0; k < 3; k++) {
    j = (int32_T)std::floor(rtb_Sum_h[k]) - 1;
    if (j < 0) {
      j = 0;
    } else {
      if (j >= 3) {
        j = 2;
      }
    }

    rtb_BackwardSubstitution[k] = INDI_controller_Cpp_B.IdentityMatrix[j];
    rtb_BackwardSubstitution[3 + k] = INDI_controller_Cpp_B.IdentityMatrix[3 + j];
    rtb_BackwardSubstitution[6 + k] = INDI_controller_Cpp_B.IdentityMatrix[6 + j];
  }

  /* End of S-Function (sdspperm2): '<S9>/Permute Matrix' */

  /* S-Function (sdspfbsub2): '<S9>/Forward Substitution' */
  for (j = 0; j < 3; j++) {
    rtb_C_m_u_tmp = j * 3;
    idxLU = 1;
    idxB = rtb_C_m_u_tmp + 1;
    c = rtb_BackwardSubstitution[idxB];
    k = 0;
    while (k < 1) {
      c -= rtb_VectorConcatenate[idxLU] * rtb_BackwardSubstitution[rtb_C_m_u_tmp];
      idxLU += 3;
      k = 1;
    }

    rtb_BackwardSubstitution[idxB] = c;
    idxLU = 2;
    idxB = rtb_C_m_u_tmp + 2;
    c = rtb_BackwardSubstitution[idxB];
    for (k = 0; k < 2; k++) {
      c -= rtb_BackwardSubstitution[rtb_C_m_u_tmp + k] *
        rtb_VectorConcatenate[idxLU];
      idxLU += 3;
    }

    rtb_BackwardSubstitution[idxB] = c;
  }

  /* End of S-Function (sdspfbsub2): '<S9>/Forward Substitution' */
  for (j = 0; j < 3; j++) {
    /* S-Function (sdspfbsub2): '<S9>/Backward Substitution' */
    rtb_C_m_u_tmp = j * 3;
    rtb_BackwardSubstitution[rtb_C_m_u_tmp + 2] /= rtb_VectorConcatenate[8];
    idxLU = 7;
    idxB = rtb_C_m_u_tmp + 1;
    c = rtb_BackwardSubstitution[idxB];
    k = 2;
    while (k > 1) {
      c -= rtb_BackwardSubstitution[rtb_C_m_u_tmp + 2] *
        rtb_VectorConcatenate[idxLU];
      idxLU -= 3;
      k = 1;
    }

    rtb_BackwardSubstitution[idxB] = c / rtb_VectorConcatenate[idxLU];
    idxLU = 6;
    c = rtb_BackwardSubstitution[rtb_C_m_u_tmp];
    for (k = 2; k > 0; k--) {
      c -= rtb_BackwardSubstitution[rtb_C_m_u_tmp + k] *
        rtb_VectorConcatenate[idxLU];
      idxLU -= 3;
    }

    rtb_BackwardSubstitution[rtb_C_m_u_tmp] = c / rtb_VectorConcatenate[idxLU];

    /* End of S-Function (sdspfbsub2): '<S9>/Backward Substitution' */

    /* Sum: '<Root>/Sum1' incorporates:
     *  Inport: '<Root>/pqr'
     *  Inport: '<Root>/pqr_des'
     */
    INDI_controller_Cpp_B.e_pqr[j] = INDI_controller_Cpp_U.pqr_des[j] -
      INDI_controller_Cpp_U.pqr[j];

    /* Gain: '<S6>/Filter Coefficient' incorporates:
     *  Gain: '<S6>/Derivative Gain'
     *  Integrator: '<S6>/Filter'
     *  Sum: '<S6>/SumD'
     */
    INDI_controller_Cpp_B.FilterCoefficient[j] = (0.0 -
      INDI_controller_Cpp_X.Filter_CSTATE[j]) * 100.0;
  }

  /* PreLookup: '<S13>/alpha' */
  rtb_alpha_o1_c = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1,
    14U, &rtb_d_o_e_CnUsingPrelookup5_f, &INDI_controller_Cpp_DW.alpha_DWORK1_kx);

  /* PreLookup: '<S13>/non beta' */
  rtb_nonbeta_o1_e = plook_binpg(rtb_beta, INDI_controller_Cpp_ConstP.pooled2,
    8U, &rtb_d_o_e_CnUsingPrelookup4_g, &INDI_controller_Cpp_DW.nonbeta_DWORK1_n);

  /* Interpolation_n-D: '<S13>/d_o_e_Cr Using Prelookup4' */
  frac_9[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_9[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_9[2] = 0.0;
  bpIndex_9[0] = rtb_alpha_o1_c;
  bpIndex_9[1] = rtb_nonbeta_o1_e;
  bpIndex_9[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup3 = intrp3d_l(bpIndex_9, frac_9,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);

  /* PreLookup: '<S15>/alpha' */
  rtb_alpha_o1_e = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1,
    14U, &rtb_d_o_e_CnUsingPrelookup5, &INDI_controller_Cpp_DW.alpha_DWORK1_b);

  /* Interpolation_n-D: '<S15>/d_o_e_Cr Using Prelookup4' */
  frac_a[0] = rtb_d_o_e_CnUsingPrelookup5;
  frac_a[1] = 0.0;
  frac_a[2] = 0.0;
  bpIndex_a[0] = rtb_alpha_o1_e;
  bpIndex_a[1] = 4U;
  bpIndex_a[2] = 0U;
  rtb_d_o_e_CrUsingPrelookup4 = intrp3d_l(bpIndex_a, frac_a,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);

  /* Sum: '<S19>/Add' */
  t = rtb_d_o_e_CnUsingPrelookup3 - rtb_d_o_e_CrUsingPrelookup4;

  /* PreLookup: '<S14>/alpha' */
  rtb_alpha_o1_i = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1,
    14U, &absxk, &INDI_controller_Cpp_DW.alpha_DWORK1_n);

  /* Abs: '<S4>/Abs' */
  rtb_beta_o2 = rtb_d_o_e_CMUsingPrelookup2_a;

  /* PreLookup: '<S14>/beta' */
  rtb_beta_o1_c = plook_binpg(rtb_d_o_e_CMUsingPrelookup2_a,
    INDI_controller_Cpp_ConstP.pooled8, 4U, &scale,
    &INDI_controller_Cpp_DW.beta_DWORK1_g);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup1' */
  frac_b[0] = absxk;
  frac_b[1] = scale;
  frac_b[2] = 0.0;
  bpIndex_b[0] = rtb_alpha_o1_i;
  bpIndex_b[1] = rtb_beta_o1_c;
  bpIndex_b[2] = 6U;
  rtb_d_o_e_CrUsingPrelookup3 = intrp3d_l(bpIndex_b, frac_b,
    INDI_controller_Cpp_ConstP.pooled15, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup2' */
  frac_c[0] = absxk;
  frac_c[1] = scale;
  frac_c[2] = 0.0;
  bpIndex_c[0] = rtb_alpha_o1_i;
  bpIndex_c[1] = rtb_beta_o1_c;
  bpIndex_c[2] = 6U;
  rtb_d_o_e_CrUsingPrelookup4_e = intrp3d_l(bpIndex_c, frac_c,
    INDI_controller_Cpp_ConstP.pooled16, INDI_controller_Cpp_ConstP.pooled30);

  /* PreLookup: '<S14>/d_c_e' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_c_e_o1_o = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.e,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &c,
    &INDI_controller_Cpp_DW.d_c_e_DWORK1_j);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup3' */
  frac_d[0] = absxk;
  frac_d[1] = scale;
  frac_d[2] = c;
  bpIndex_d[0] = rtb_alpha_o1_i;
  bpIndex_d[1] = rtb_beta_o1_c;
  bpIndex_d[2] = rtb_d_c_e_o1_o;
  rtb_d_o_e_CrUsingPrelookup5 = intrp3d_l(bpIndex_d, frac_d,
    INDI_controller_Cpp_ConstP.pooled17, INDI_controller_Cpp_ConstP.pooled30);

  /* PreLookup: '<S14>/non beta' */
  rtb_nonbeta_o1 = plook_binpg(rtb_beta, INDI_controller_Cpp_ConstP.pooled2, 8U,
    &rtb_nonbeta_o2, &INDI_controller_Cpp_DW.nonbeta_DWORK1_eg);

  /* PreLookup: '<S14>/d_o_a' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_o_a_o1 = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.a,
    INDI_controller_Cpp_ConstP.pooled4, 6U, &rtb_beta,
    &INDI_controller_Cpp_DW.d_o_a_DWORK1_f);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup4' */
  frac_e[0] = absxk;
  frac_e[1] = rtb_nonbeta_o2;
  frac_e[2] = rtb_beta;
  bpIndex_e[0] = rtb_alpha_o1_i;
  bpIndex_e[1] = rtb_nonbeta_o1;
  bpIndex_e[2] = rtb_d_o_a_o1;
  rtb_d_o_e_CnUsingPrelookup5_h = intrp3d_l(bpIndex_e, frac_e,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup5' */
  frac_f[0] = absxk;
  frac_f[1] = rtb_nonbeta_o2;
  frac_f[2] = 0.0;
  bpIndex_f[0] = rtb_alpha_o1_i;
  bpIndex_f[1] = rtb_nonbeta_o1;
  bpIndex_f[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup1 = intrp3d_l(bpIndex_f, frac_f,
    INDI_controller_Cpp_ConstP.pooled18, INDI_controller_Cpp_ConstP.pooled29);

  /* PreLookup: '<S14>/d_c_e1' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_c_e1_o1 = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.r,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &rtb_d_o_e_CnUsingPrelookup2,
    &INDI_controller_Cpp_DW.d_c_e1_DWORK1_o);

  /* Interpolation_n-D: '<S14>/d_o_e_Cr Using Prelookup6' */
  frac_g[0] = absxk;
  frac_g[1] = rtb_nonbeta_o2;
  frac_g[2] = rtb_d_o_e_CnUsingPrelookup2;
  bpIndex_g[0] = rtb_alpha_o1_i;
  bpIndex_g[1] = rtb_nonbeta_o1;
  bpIndex_g[2] = rtb_d_c_e1_o1;
  rtb_d_o_e_CnUsingPrelookup6 = intrp3d_l(bpIndex_g, frac_g,
    INDI_controller_Cpp_ConstP.pooled7, INDI_controller_Cpp_ConstP.pooled29);

  /* Sum: '<S19>/Add5' */
  rtb_Add6[0] = rtb_d_o_e_CrUsingPrelookup3 - rtb_d_o_e_CnUsingPrelookup3;
  rtb_Add6[1] = rtb_d_o_e_CrUsingPrelookup4_e - rtb_d_o_e_CnUsingPrelookup3;
  rtb_Add6[2] = rtb_d_o_e_CrUsingPrelookup5 - rtb_d_o_e_CnUsingPrelookup3;
  rtb_Add6[3] = rtb_d_o_e_CnUsingPrelookup5_h - rtb_d_o_e_CnUsingPrelookup3;
  rtb_Add6[4] = rtb_d_o_e_CnUsingPrelookup1 - rtb_d_o_e_CnUsingPrelookup3;
  rtb_Add6[5] = rtb_d_o_e_CnUsingPrelookup6 - rtb_d_o_e_CnUsingPrelookup3;

  /* PreLookup: '<S16>/alpha' */
  rtb_alpha_o1 = plook_binpg(rtb_alpha, INDI_controller_Cpp_ConstP.pooled1, 14U,
    &rtb_d_o_e_CnUsingPrelookup6, &INDI_controller_Cpp_DW.alpha_DWORK1_p);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup1' */
  frac_h[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_h[1] = 0.0;
  frac_h[2] = 0.0;
  bpIndex_h[0] = rtb_alpha_o1;
  bpIndex_h[1] = 0U;
  bpIndex_h[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup1 = intrp3d_l(bpIndex_h, frac_h,
    INDI_controller_Cpp_ConstP.pooled15, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup2' */
  frac_i[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_i[1] = 0.0;
  frac_i[2] = 0.0;
  bpIndex_i[0] = rtb_alpha_o1;
  bpIndex_i[1] = 0U;
  bpIndex_i[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup5_h = intrp3d_l(bpIndex_i, frac_i,
    INDI_controller_Cpp_ConstP.pooled16, INDI_controller_Cpp_ConstP.pooled30);

  /* PreLookup: '<S16>/d_c_e' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  rtb_d_c_e_o1 = plook_binpg(INDI_controller_Cpp_U.ctrlsfc.e,
    INDI_controller_Cpp_ConstP.pooled6, 12U, &rtb_d_o_e_CnUsingPrelookup3,
    &INDI_controller_Cpp_DW.d_c_e_DWORK1_d);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup3' */
  frac_j[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_j[1] = 0.0;
  frac_j[2] = rtb_d_o_e_CnUsingPrelookup3;
  bpIndex_j[0] = rtb_alpha_o1;
  bpIndex_j[1] = 0U;
  bpIndex_j[2] = rtb_d_c_e_o1;
  rtb_d_o_e_CrUsingPrelookup3 = intrp3d_l(bpIndex_j, frac_j,
    INDI_controller_Cpp_ConstP.pooled17, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup4' */
  frac_k[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_k[1] = 0.0;
  frac_k[2] = 0.0;
  bpIndex_k[0] = rtb_alpha_o1;
  bpIndex_k[1] = 4U;
  bpIndex_k[2] = 0U;
  rtb_d_o_e_CrUsingPrelookup4_e = intrp3d_l(bpIndex_k, frac_k,
    INDI_controller_Cpp_ConstP.pooled5, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup5' */
  frac_l[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_l[1] = 0.0;
  frac_l[2] = 0.0;
  bpIndex_l[0] = rtb_alpha_o1;
  bpIndex_l[1] = 4U;
  bpIndex_l[2] = 0U;
  rtb_d_o_e_CrUsingPrelookup5 = intrp3d_l(bpIndex_l, frac_l,
    INDI_controller_Cpp_ConstP.pooled18, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S16>/d_o_e_Cr Using Prelookup6' */
  frac_m[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_m[1] = 0.0;
  frac_m[2] = 0.0;
  bpIndex_m[0] = rtb_alpha_o1;
  bpIndex_m[1] = 4U;
  bpIndex_m[2] = 6U;
  rtb_alpha = intrp3d_l(bpIndex_m, frac_m, INDI_controller_Cpp_ConstP.pooled7,
                        INDI_controller_Cpp_ConstP.pooled29);

  /* Sum: '<S19>/Add6' */
  rtb_d_o_e_CnUsingPrelookup1_0[0] = rtb_d_o_e_CnUsingPrelookup1;
  rtb_d_o_e_CnUsingPrelookup1_0[1] = rtb_d_o_e_CnUsingPrelookup5_h;
  rtb_d_o_e_CnUsingPrelookup1_0[2] = rtb_d_o_e_CrUsingPrelookup3;
  rtb_d_o_e_CnUsingPrelookup1_0[3] = rtb_d_o_e_CrUsingPrelookup4_e;
  rtb_d_o_e_CnUsingPrelookup1_0[4] = rtb_d_o_e_CrUsingPrelookup5;
  rtb_d_o_e_CnUsingPrelookup1_0[5] = rtb_alpha;
  for (k = 0; k < 6; k++) {
    rtb_Add6[k] = (rtb_Add6[k] - rtb_d_o_e_CnUsingPrelookup1_0[k]) +
      rtb_d_o_e_CrUsingPrelookup4;
  }

  /* End of Sum: '<S19>/Add6' */

  /* Sum: '<S19>/CY' */
  t = (((((t + rtb_Add6[0]) + rtb_Add6[1]) + rtb_Add6[2]) + rtb_Add6[3]) +
       rtb_Add6[4]) + rtb_Add6[5];

  /* PreLookup: '<S13>/beta' */
  rtb_beta_o1 = plook_binpg(rtb_d_o_e_CMUsingPrelookup2_a,
    INDI_controller_Cpp_ConstP.pooled8, 4U, &rtb_beta_o2,
    &INDI_controller_Cpp_DW.beta_DWORK1_h);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup3' */
  frac_n[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_n[1] = rtb_beta_o2;
  frac_n[2] = 0.0;
  bpIndex_n[0] = rtb_alpha_o1_c;
  bpIndex_n[1] = rtb_beta_o1;
  bpIndex_n[2] = 6U;
  rtb_alpha = intrp3d_l(bpIndex_n, frac_n, INDI_controller_Cpp_ConstP.pooled19,
                        INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup1' */
  frac_o[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_o[1] = rtb_beta_o2;
  frac_o[2] = 0.0;
  bpIndex_o[0] = rtb_alpha_o1_c;
  bpIndex_o[1] = rtb_beta_o1;
  bpIndex_o[2] = 6U;
  rtb_d_o_e_CrUsingPrelookup5 = intrp3d_l(bpIndex_o, frac_o,
    INDI_controller_Cpp_ConstP.pooled20, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup2' */
  frac_p[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_p[1] = rtb_beta_o2;
  frac_p[2] = 0.0;
  bpIndex_p[0] = rtb_alpha_o1_c;
  bpIndex_p[1] = rtb_beta_o1;
  bpIndex_p[2] = 6U;
  rtb_d_o_e_CrUsingPrelookup4_e = intrp3d_l(bpIndex_p, frac_p,
    INDI_controller_Cpp_ConstP.pooled9, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup6' */
  frac_q[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_q[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_q[2] = 0.0;
  bpIndex_q[0] = rtb_alpha_o1_c;
  bpIndex_q[1] = rtb_nonbeta_o1_e;
  bpIndex_q[2] = 0U;
  rtb_beta_o2 = intrp3d_l(bpIndex_q, frac_q, INDI_controller_Cpp_ConstP.pooled21,
    INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup4' */
  frac_r[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_r[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_r[2] = 0.0;
  bpIndex_r[0] = rtb_alpha_o1_c;
  bpIndex_r[1] = rtb_nonbeta_o1_e;
  bpIndex_r[2] = 0U;
  rtb_d_o_e_CrUsingPrelookup3 = intrp3d_l(bpIndex_r, frac_r,
    INDI_controller_Cpp_ConstP.pooled22, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S13>/d_o_e_CM Using Prelookup5' */
  frac_s[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_s[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_s[2] = 0.0;
  bpIndex_s[0] = rtb_alpha_o1_c;
  bpIndex_s[1] = rtb_nonbeta_o1_e;
  bpIndex_s[2] = 6U;
  rtb_d_o_e_CrUsingPrelookup4 = intrp3d_l(bpIndex_s, frac_s,
    INDI_controller_Cpp_ConstP.pooled23, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup3' */
  frac_t[0] = absxk;
  frac_t[1] = scale;
  frac_t[2] = 0.0;
  bpIndex_t[0] = rtb_alpha_o1_i;
  bpIndex_t[1] = rtb_beta_o1_c;
  bpIndex_t[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup5_h = intrp3d_l(bpIndex_t, frac_t,
    INDI_controller_Cpp_ConstP.pooled19, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup1' */
  frac_u[0] = absxk;
  frac_u[1] = scale;
  frac_u[2] = 0.0;
  bpIndex_u[0] = rtb_alpha_o1_i;
  bpIndex_u[1] = rtb_beta_o1_c;
  bpIndex_u[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup1 = intrp3d_l(bpIndex_u, frac_u,
    INDI_controller_Cpp_ConstP.pooled20, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup2' */
  frac_v[0] = absxk;
  frac_v[1] = scale;
  frac_v[2] = c;
  bpIndex_v[0] = rtb_alpha_o1_i;
  bpIndex_v[1] = rtb_beta_o1_c;
  bpIndex_v[2] = rtb_d_c_e_o1_o;
  rtb_d_o_e_CMUsingPrelookup2_a = intrp3d_l(bpIndex_v, frac_v,
    INDI_controller_Cpp_ConstP.pooled9, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup6' */
  frac_w[0] = absxk;
  frac_w[1] = rtb_nonbeta_o2;
  frac_w[2] = rtb_beta;
  bpIndex_w[0] = rtb_alpha_o1_i;
  bpIndex_w[1] = rtb_nonbeta_o1;
  bpIndex_w[2] = rtb_d_o_a_o1;
  rtb_d_o_e_CMUsingPrelookup6_a = intrp3d_l(bpIndex_w, frac_w,
    INDI_controller_Cpp_ConstP.pooled21, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup4' */
  frac_x[0] = absxk;
  frac_x[1] = rtb_nonbeta_o2;
  frac_x[2] = 0.0;
  bpIndex_x[0] = rtb_alpha_o1_i;
  bpIndex_x[1] = rtb_nonbeta_o1;
  bpIndex_x[2] = 0U;
  rtb_d_o_e_CMUsingPrelookup4_c = intrp3d_l(bpIndex_x, frac_x,
    INDI_controller_Cpp_ConstP.pooled22, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_CM Using Prelookup5' */
  frac_y[0] = absxk;
  frac_y[1] = rtb_nonbeta_o2;
  frac_y[2] = rtb_d_o_e_CnUsingPrelookup2;
  bpIndex_y[0] = rtb_alpha_o1_i;
  bpIndex_y[1] = rtb_nonbeta_o1;
  bpIndex_y[2] = rtb_d_c_e1_o1;
  rtb_d_o_e_CMUsingPrelookup5_e = intrp3d_l(bpIndex_y, frac_y,
    INDI_controller_Cpp_ConstP.pooled23, INDI_controller_Cpp_ConstP.pooled29);

  /* Outputs for Atomic SubSystem: '<S4>/formulation 1 for (CL CD CM)CM' */
  /* Sum: '<S17>/minus' */
  rtb_alpha = rtb_d_o_e_CnUsingPrelookup5_h - rtb_alpha;
  rtb_d_o_e_CrUsingPrelookup5 = rtb_d_o_e_CnUsingPrelookup1 -
    rtb_d_o_e_CrUsingPrelookup5;

  /* End of Outputs for SubSystem: '<S4>/formulation 1 for (CL CD CM)CM' */

  /* Interpolation_n-D: '<S13>/d_o_e_Cn Using Prelookup5' */
  frac_z[0] = rtb_d_o_e_CnUsingPrelookup5_f;
  frac_z[1] = rtb_d_o_e_CnUsingPrelookup4_g;
  frac_z[2] = 0.0;
  bpIndex_z[0] = rtb_alpha_o1_c;
  bpIndex_z[1] = rtb_nonbeta_o1_e;
  bpIndex_z[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup5_f = intrp3d_l(bpIndex_z, frac_z,
    INDI_controller_Cpp_ConstP.pooled10, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S15>/d_o_e_Cn Using Prelookup5' */
  frac_10[0] = rtb_d_o_e_CnUsingPrelookup5;
  frac_10[1] = 0.0;
  frac_10[2] = 0.0;
  bpIndex_10[0] = rtb_alpha_o1_e;
  bpIndex_10[1] = 4U;
  bpIndex_10[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup5 = intrp3d_l(bpIndex_10, frac_10,
    INDI_controller_Cpp_ConstP.pooled10, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup2' */
  frac_11[0] = absxk;
  frac_11[1] = scale;
  frac_11[2] = 0.0;
  bpIndex_11[0] = rtb_alpha_o1_i;
  bpIndex_11[1] = rtb_beta_o1_c;
  bpIndex_11[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup1 = intrp3d_l(bpIndex_11, frac_11,
    INDI_controller_Cpp_ConstP.pooled24, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup1' */
  frac_12[0] = absxk;
  frac_12[1] = scale;
  frac_12[2] = 0.0;
  bpIndex_12[0] = rtb_alpha_o1_i;
  bpIndex_12[1] = rtb_beta_o1_c;
  bpIndex_12[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup5_h = intrp3d_l(bpIndex_12, frac_12,
    INDI_controller_Cpp_ConstP.pooled25, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup3' */
  frac_13[0] = absxk;
  frac_13[1] = scale;
  frac_13[2] = c;
  bpIndex_13[0] = rtb_alpha_o1_i;
  bpIndex_13[1] = rtb_beta_o1_c;
  bpIndex_13[2] = rtb_d_c_e_o1_o;
  scale = intrp3d_l(bpIndex_13, frac_13, INDI_controller_Cpp_ConstP.pooled26,
                    INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup5' */
  frac_14[0] = absxk;
  frac_14[1] = rtb_nonbeta_o2;
  frac_14[2] = rtb_beta;
  bpIndex_14[0] = rtb_alpha_o1_i;
  bpIndex_14[1] = rtb_nonbeta_o1;
  bpIndex_14[2] = rtb_d_o_a_o1;
  rtb_beta = intrp3d_l(bpIndex_14, frac_14, INDI_controller_Cpp_ConstP.pooled10,
                       INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup4' */
  frac_15[0] = absxk;
  frac_15[1] = rtb_nonbeta_o2;
  frac_15[2] = 0.0;
  bpIndex_15[0] = rtb_alpha_o1_i;
  bpIndex_15[1] = rtb_nonbeta_o1;
  bpIndex_15[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup4_g = intrp3d_l(bpIndex_15, frac_15,
    INDI_controller_Cpp_ConstP.pooled27, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S14>/d_o_e_Cn Using Prelookup6' */
  frac_16[0] = absxk;
  frac_16[1] = rtb_nonbeta_o2;
  frac_16[2] = rtb_d_o_e_CnUsingPrelookup2;
  bpIndex_16[0] = rtb_alpha_o1_i;
  bpIndex_16[1] = rtb_nonbeta_o1;
  bpIndex_16[2] = rtb_d_c_e1_o1;
  absxk = intrp3d_l(bpIndex_16, frac_16, INDI_controller_Cpp_ConstP.pooled11,
                    INDI_controller_Cpp_ConstP.pooled29);

  /* Sum: '<S18>/Add5' */
  rtb_Add6[0] = rtb_d_o_e_CnUsingPrelookup1 - rtb_d_o_e_CnUsingPrelookup5_f;
  rtb_Add6[1] = rtb_d_o_e_CnUsingPrelookup5_h - rtb_d_o_e_CnUsingPrelookup5_f;
  rtb_Add6[2] = scale - rtb_d_o_e_CnUsingPrelookup5_f;
  rtb_Add6[3] = rtb_beta - rtb_d_o_e_CnUsingPrelookup5_f;
  rtb_Add6[4] = rtb_d_o_e_CnUsingPrelookup4_g - rtb_d_o_e_CnUsingPrelookup5_f;
  rtb_Add6[5] = absxk - rtb_d_o_e_CnUsingPrelookup5_f;

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup2' */
  frac_17[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_17[1] = 0.0;
  frac_17[2] = 0.0;
  bpIndex_17[0] = rtb_alpha_o1;
  bpIndex_17[1] = 0U;
  bpIndex_17[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup2 = intrp3d_l(bpIndex_17, frac_17,
    INDI_controller_Cpp_ConstP.pooled24, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup1' */
  frac_18[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_18[1] = 0.0;
  frac_18[2] = 0.0;
  bpIndex_18[0] = rtb_alpha_o1;
  bpIndex_18[1] = 0U;
  bpIndex_18[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup1 = intrp3d_l(bpIndex_18, frac_18,
    INDI_controller_Cpp_ConstP.pooled25, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup3' */
  frac_19[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_19[1] = 0.0;
  frac_19[2] = rtb_d_o_e_CnUsingPrelookup3;
  bpIndex_19[0] = rtb_alpha_o1;
  bpIndex_19[1] = 0U;
  bpIndex_19[2] = rtb_d_c_e_o1;
  rtb_d_o_e_CnUsingPrelookup3 = intrp3d_l(bpIndex_19, frac_19,
    INDI_controller_Cpp_ConstP.pooled26, INDI_controller_Cpp_ConstP.pooled30);

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup5' */
  frac_1a[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_1a[1] = 0.0;
  frac_1a[2] = 0.0;
  bpIndex_1a[0] = rtb_alpha_o1;
  bpIndex_1a[1] = 4U;
  bpIndex_1a[2] = 0U;
  rtb_d_o_e_CnUsingPrelookup5_h = intrp3d_l(bpIndex_1a, frac_1a,
    INDI_controller_Cpp_ConstP.pooled10, INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup4' */
  frac_1b[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_1b[1] = 0.0;
  frac_1b[2] = 0.0;
  bpIndex_1b[0] = rtb_alpha_o1;
  bpIndex_1b[1] = 4U;
  bpIndex_1b[2] = 0U;
  rtb_beta = intrp3d_l(bpIndex_1b, frac_1b, INDI_controller_Cpp_ConstP.pooled27,
                       INDI_controller_Cpp_ConstP.pooled29);

  /* Interpolation_n-D: '<S16>/d_o_e_Cn Using Prelookup6' */
  frac_1c[0] = rtb_d_o_e_CnUsingPrelookup6;
  frac_1c[1] = 0.0;
  frac_1c[2] = 0.0;
  bpIndex_1c[0] = rtb_alpha_o1;
  bpIndex_1c[1] = 4U;
  bpIndex_1c[2] = 6U;
  rtb_d_o_e_CnUsingPrelookup6 = intrp3d_l(bpIndex_1c, frac_1c,
    INDI_controller_Cpp_ConstP.pooled11, INDI_controller_Cpp_ConstP.pooled29);

  /* Sum: '<S18>/Add6' */
  rtb_d_o_e_CnUsingPrelookup1_0[0] = rtb_d_o_e_CnUsingPrelookup2;
  rtb_d_o_e_CnUsingPrelookup1_0[1] = rtb_d_o_e_CnUsingPrelookup1;
  rtb_d_o_e_CnUsingPrelookup1_0[2] = rtb_d_o_e_CnUsingPrelookup3;
  rtb_d_o_e_CnUsingPrelookup1_0[3] = rtb_d_o_e_CnUsingPrelookup5_h;
  rtb_d_o_e_CnUsingPrelookup1_0[4] = rtb_beta;
  rtb_d_o_e_CnUsingPrelookup1_0[5] = rtb_d_o_e_CnUsingPrelookup6;
  for (k = 0; k < 6; k++) {
    rtb_Add6[k] = (rtb_Add6[k] - rtb_d_o_e_CnUsingPrelookup1_0[k]) +
      rtb_d_o_e_CnUsingPrelookup5;
  }

  /* End of Sum: '<S18>/Add6' */

  /* Outputs for Atomic SubSystem: '<S4>/formulation 1 for (CL CD CM)CM' */
  /* SignalConversion: '<Root>/TmpSignal ConversionAtMtp_MInport2' incorporates:
   *  Sum: '<S17>/CL'
   *  Sum: '<S17>/minus'
   *  Sum: '<S18>/Add'
   *  Sum: '<S18>/CY'
   */
  c = (((((rtb_beta_o2 + rtb_alpha) + rtb_d_o_e_CrUsingPrelookup5) +
         (rtb_d_o_e_CMUsingPrelookup2_a - rtb_d_o_e_CrUsingPrelookup4_e)) +
        (rtb_d_o_e_CMUsingPrelookup6_a - rtb_beta_o2)) +
       (rtb_d_o_e_CMUsingPrelookup4_c - rtb_d_o_e_CrUsingPrelookup3)) +
    (rtb_d_o_e_CMUsingPrelookup5_e - rtb_d_o_e_CrUsingPrelookup4);

  /* End of Outputs for SubSystem: '<S4>/formulation 1 for (CL CD CM)CM' */
  scale = ((((((rtb_d_o_e_CnUsingPrelookup5_f - rtb_d_o_e_CnUsingPrelookup5) +
               rtb_Add6[0]) + rtb_Add6[1]) + rtb_Add6[2]) + rtb_Add6[3]) +
           rtb_Add6[4]) + rtb_Add6[5];

  /* Product: '<Root>/Mtp_M' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Inport: '<Root>/qbar'
   *  SignalConversion: '<Root>/TmpSignal ConversionAtMtp_MInport2'
   */
  for (k = 0; k < 3; k++) {
    rtb_v_b[k] = INDI_controller_Cpp_ConstP.Gain1_Gain[k + 6] *
      INDI_controller_Cpp_U.abar * scale +
      (INDI_controller_Cpp_ConstP.Gain1_Gain[k + 3] * INDI_controller_Cpp_U.abar
       * c + INDI_controller_Cpp_ConstP.Gain1_Gain[k] *
       INDI_controller_Cpp_U.abar * t);
  }

  /* End of Product: '<Root>/Mtp_M' */

  /* MATLAB Function: '<S8>/MATLAB Function' incorporates:
   *  Inport: '<Root>/pqr'
   */
  /* MATLAB Function 'pqr_est_blk/MATLAB Function': '<S20>:1' */
  /* '<S20>:1:3' Ixx = inertia(1,1); */
  /* '<S20>:1:4' Ixz = -inertia(3,1); */
  /* '<S20>:1:5' Iyy = inertia(2,2); */
  /* '<S20>:1:6' Izz = inertia(3,3); */
  /* '<S20>:1:8' M_x = M(1); */
  /* '<S20>:1:9' M_y = M(2); */
  /* '<S20>:1:10' M_z = M(3); */
  /* '<S20>:1:11' p = pqr(1); */
  /* '<S20>:1:12' q = pqr(2); */
  /* '<S20>:1:13' r = pqr(3); */
  /* '<S20>:1:14' qr = q*r; */
  c = INDI_controller_Cpp_U.pqr[1] * INDI_controller_Cpp_U.pqr[2];

  /* '<S20>:1:15' pq = p*q; */
  scale = INDI_controller_Cpp_U.pqr[0] * INDI_controller_Cpp_U.pqr[1];

  /* '<S20>:1:17' denominator = Ixx*Izz - Ixz^2; */
  /* '<S20>:1:18' p_dot_numerator = Izz*M_x + Ixz*M_z - (Ixz^2+Izz^2-Iyy*Izz)*qr + (Ixx-Iyy+Izz)*Ixz*pq; */
  /* '<S20>:1:19' r_dot_numerator = Ixz*M_x + Ixx*M_z + (Ixx^2+Ixz^2-Iyy*Ixx)*pq - (Ixx-Iyy+Izz)*Ixz*qr; */
  /* '<S20>:1:20' q_dot = (M_y - (Ixx-Izz)*q*r - (p^2-r^2)*Ixz)/Iyy; */
  /* '<S20>:1:21' p_dot = p_dot_numerator/denominator; */
  /* '<S20>:1:22' r_dot = r_dot_numerator/denominator; */
  /* '<S20>:1:24' pqr_dot_obpm = [p_dot, q_dot, r_dot]'; */
  if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
    /* DiscreteIntegrator: '<S8>/w_ddot_int' */
    INDI_controller_Cpp_B.w_ddot_int[0] =
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[0];
    INDI_controller_Cpp_B.w_ddot_int[1] =
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[1];
    INDI_controller_Cpp_B.w_ddot_int[2] =
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[2];
  }

  /* Sum: '<S8>/Sum10' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  INDI_controller_Cpp_B.w_dot_est[0] = (((10.7149 * rtb_v_b[0] + 10.0 * rtb_v_b
    [2]) - 140.29445293999999 * c) + 138.76 * scale) / 8.3854994599999912 +
    INDI_controller_Cpp_B.w_ddot_int[0];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S6>/Proportional Gain'
   *  Gain: '<S8>/Gain'
   *  Integrator: '<S6>/Integrator'
   *  Product: '<Root>/Mtp_u_des'
   *  Sum: '<S6>/Sum'
   */
  t = ((10.0 * INDI_controller_Cpp_B.e_pqr[0] +
        INDI_controller_Cpp_X.Integrator_CSTATE[0]) +
       INDI_controller_Cpp_B.FilterCoefficient[0]) - 0.04 *
    INDI_controller_Cpp_B.w_dot_est[0];

  /* Sum: '<S8>/Sum10' incorporates:
   *  Inport: '<Root>/pqr'
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  INDI_controller_Cpp_B.w_dot_est[1] = ((rtb_v_b[1] - -0.59950000000000081 *
    INDI_controller_Cpp_U.pqr[1] * INDI_controller_Cpp_U.pqr[2]) -
    (INDI_controller_Cpp_U.pqr[0] * INDI_controller_Cpp_U.pqr[0] -
     INDI_controller_Cpp_U.pqr[2] * INDI_controller_Cpp_U.pqr[2]) * 10.0) /
    6.9543 + INDI_controller_Cpp_B.w_ddot_int[1];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S6>/Proportional Gain'
   *  Gain: '<S8>/Gain'
   *  Integrator: '<S6>/Integrator'
   *  Product: '<Root>/Mtp_u_des'
   *  Sum: '<S6>/Sum'
   */
  absxk = ((10.0 * INDI_controller_Cpp_B.e_pqr[1] +
            INDI_controller_Cpp_X.Integrator_CSTATE[1]) +
           INDI_controller_Cpp_B.FilterCoefficient[1]) - 0.04 *
    INDI_controller_Cpp_B.w_dot_est[1];

  /* Sum: '<S8>/Sum10' incorporates:
   *  MATLAB Function: '<S8>/MATLAB Function'
   */
  INDI_controller_Cpp_B.w_dot_est[2] = (((10.0 * rtb_v_b[0] + 10.1154 * rtb_v_b
    [2]) + 131.97579093999997 * scale) - 138.76 * c) / 8.3854994599999912 +
    INDI_controller_Cpp_B.w_ddot_int[2];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<S6>/Proportional Gain'
   *  Gain: '<S8>/Gain'
   *  Integrator: '<S6>/Integrator'
   *  Product: '<Root>/Mtp_u_des'
   *  Sum: '<S6>/Sum'
   */
  c = ((10.0 * INDI_controller_Cpp_B.e_pqr[2] +
        INDI_controller_Cpp_X.Integrator_CSTATE[2]) +
       INDI_controller_Cpp_B.FilterCoefficient[2]) - 0.04 *
    INDI_controller_Cpp_B.w_dot_est[2];

  /* Product: '<Root>/Mtp_u_des' incorporates:
   *  Constant: '<Root>/Constant4'
   */
  for (k = 0; k < 3; k++) {
    rtb_v_b[k] = INDI_controller_Cpp_ConstP.pooled14[k + 6] * c +
      (INDI_controller_Cpp_ConstP.pooled14[k + 3] * absxk +
       INDI_controller_Cpp_ConstP.pooled14[k] * t);
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Inport: '<Root>/ctrlsfc'
   */
  frac[0] = INDI_controller_Cpp_U.ctrlsfc.a;
  frac[1] = INDI_controller_Cpp_U.ctrlsfc.e;
  frac[2] = INDI_controller_Cpp_U.ctrlsfc.r;
  for (k = 0; k < 3; k++) {
    /* Sum: '<Root>/Sum' incorporates:
     *  Product: '<Root>/Mtp_u_des'
     */
    rtb_Sum_h[k] = (rtb_BackwardSubstitution[k + 6] * rtb_v_b[2] +
                    (rtb_BackwardSubstitution[k + 3] * rtb_v_b[1] +
                     rtb_BackwardSubstitution[k] * rtb_v_b[0])) + frac[k];
  }

  /* Outport: '<Root>/actCMD' incorporates:
   *  BusCreator: '<Root>/Bus Creator'
   */
  INDI_controller_Cpp_Y.actCMD.ailCMD = rtb_Sum_h[0];
  INDI_controller_Cpp_Y.actCMD.eleCMD = rtb_Sum_h[1];
  INDI_controller_Cpp_Y.actCMD.rudCMD = rtb_Sum_h[2];
  if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
    /* DiscreteIntegrator: '<S8>/w_dot_int' */
    INDI_controller_Cpp_B.w_dot_int[0] =
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[0];

    /* Gain: '<S8>/xiwn' */
    INDI_controller_Cpp_B.xiwn[0] = 40.0 * INDI_controller_Cpp_B.w_ddot_int[0];

    /* DiscreteIntegrator: '<S8>/w_dot_int' */
    INDI_controller_Cpp_B.w_dot_int[1] =
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[1];

    /* Gain: '<S8>/xiwn' */
    INDI_controller_Cpp_B.xiwn[1] = 40.0 * INDI_controller_Cpp_B.w_ddot_int[1];

    /* DiscreteIntegrator: '<S8>/w_dot_int' */
    INDI_controller_Cpp_B.w_dot_int[2] =
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[2];

    /* Gain: '<S8>/xiwn' */
    INDI_controller_Cpp_B.xiwn[2] = 40.0 * INDI_controller_Cpp_B.w_ddot_int[2];
  }

  /* Sum: '<S8>/Sum2' incorporates:
   *  Gain: '<S8>/wn_sq'
   *  Inport: '<Root>/pqr'
   *  Sum: '<S8>/Sum11'
   */
  INDI_controller_Cpp_B.Sum2[0] = (INDI_controller_Cpp_U.pqr[0] -
    INDI_controller_Cpp_B.w_dot_int[0]) * 625.0 - INDI_controller_Cpp_B.xiwn[0];
  INDI_controller_Cpp_B.Sum2[1] = (INDI_controller_Cpp_U.pqr[1] -
    INDI_controller_Cpp_B.w_dot_int[1]) * 625.0 - INDI_controller_Cpp_B.xiwn[1];
  INDI_controller_Cpp_B.Sum2[2] = (INDI_controller_Cpp_U.pqr[2] -
    INDI_controller_Cpp_B.w_dot_int[2]) * 625.0 - INDI_controller_Cpp_B.xiwn[2];
  if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
    if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
      /* Update for DiscreteIntegrator: '<S8>/w_ddot_int' */
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[0] += 0.0005 *
        INDI_controller_Cpp_B.Sum2[0];

      /* Update for DiscreteIntegrator: '<S8>/w_dot_int' */
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[0] += 0.0005 *
        INDI_controller_Cpp_B.w_dot_est[0];

      /* Update for DiscreteIntegrator: '<S8>/w_ddot_int' */
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[1] += 0.0005 *
        INDI_controller_Cpp_B.Sum2[1];

      /* Update for DiscreteIntegrator: '<S8>/w_dot_int' */
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[1] += 0.0005 *
        INDI_controller_Cpp_B.w_dot_est[1];

      /* Update for DiscreteIntegrator: '<S8>/w_ddot_int' */
      INDI_controller_Cpp_DW.w_ddot_int_DSTATE[2] += 0.0005 *
        INDI_controller_Cpp_B.Sum2[2];

      /* Update for DiscreteIntegrator: '<S8>/w_dot_int' */
      INDI_controller_Cpp_DW.w_dot_int_DSTATE[2] += 0.0005 *
        INDI_controller_Cpp_B.w_dot_est[2];
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&INDI_controller_Cpp_M))) {
    rt_ertODEUpdateContinuousStates(&(&INDI_controller_Cpp_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&INDI_controller_Cpp_M)->Timing.clockTick0)) {
      ++(&INDI_controller_Cpp_M)->Timing.clockTickH0;
    }

    (&INDI_controller_Cpp_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&INDI_controller_Cpp_M)->solverInfo);

    {
      /* Update absolute timer for sample time: [0.0005s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.0005, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&INDI_controller_Cpp_M)->Timing.clockTick1++;
      if (!(&INDI_controller_Cpp_M)->Timing.clockTick1) {
        (&INDI_controller_Cpp_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void INDI_controller_CppModelClass::INDI_controller_Cpp_derivatives()
{
  XDot_INDI_controller_Cpp_T *_rtXdot;
  _rtXdot = ((XDot_INDI_controller_Cpp_T *) (&INDI_controller_Cpp_M)->derivs);

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = INDI_controller_Cpp_B.e_pqr[0];

  /* Derivatives for Integrator: '<S6>/Filter' */
  _rtXdot->Filter_CSTATE[0] = INDI_controller_Cpp_B.FilterCoefficient[0];

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = INDI_controller_Cpp_B.e_pqr[1];

  /* Derivatives for Integrator: '<S6>/Filter' */
  _rtXdot->Filter_CSTATE[1] = INDI_controller_Cpp_B.FilterCoefficient[1];

  /* Derivatives for Integrator: '<S6>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = INDI_controller_Cpp_B.e_pqr[2];

  /* Derivatives for Integrator: '<S6>/Filter' */
  _rtXdot->Filter_CSTATE[2] = INDI_controller_Cpp_B.FilterCoefficient[2];
}

/* Model initialize function */
void INDI_controller_CppModelClass::initialize()
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)(&INDI_controller_Cpp_M), 0,
                sizeof(RT_MODEL_INDI_controller_Cpp_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&INDI_controller_Cpp_M)->solverInfo,
                          &(&INDI_controller_Cpp_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&INDI_controller_Cpp_M)->solverInfo, &rtmGetTPtr
                ((&INDI_controller_Cpp_M)));
    rtsiSetStepSizePtr(&(&INDI_controller_Cpp_M)->solverInfo,
                       &(&INDI_controller_Cpp_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&INDI_controller_Cpp_M)->solverInfo, &(&INDI_controller_Cpp_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&INDI_controller_Cpp_M)->solverInfo, (real_T **)
                         &(&INDI_controller_Cpp_M)->contStates);
    rtsiSetNumContStatesPtr(&(&INDI_controller_Cpp_M)->solverInfo,
      &(&INDI_controller_Cpp_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&INDI_controller_Cpp_M)->solverInfo,
      &(&INDI_controller_Cpp_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&INDI_controller_Cpp_M)->solverInfo, &(
      &INDI_controller_Cpp_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&INDI_controller_Cpp_M)->solverInfo,
      &(&INDI_controller_Cpp_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&INDI_controller_Cpp_M)->solverInfo,
                          (&rtmGetErrorStatus((&INDI_controller_Cpp_M))));
    rtsiSetRTModelPtr(&(&INDI_controller_Cpp_M)->solverInfo,
                      (&INDI_controller_Cpp_M));
  }

  rtsiSetSimTimeStep(&(&INDI_controller_Cpp_M)->solverInfo, MAJOR_TIME_STEP);
  (&INDI_controller_Cpp_M)->intgData.y = (&INDI_controller_Cpp_M)->odeY;
  (&INDI_controller_Cpp_M)->intgData.f[0] = (&INDI_controller_Cpp_M)->odeF[0];
  (&INDI_controller_Cpp_M)->intgData.f[1] = (&INDI_controller_Cpp_M)->odeF[1];
  (&INDI_controller_Cpp_M)->intgData.f[2] = (&INDI_controller_Cpp_M)->odeF[2];
  getRTM()->contStates = ((X_INDI_controller_Cpp_T *) &INDI_controller_Cpp_X);
  rtsiSetSolverData(&(&INDI_controller_Cpp_M)->solverInfo, (void *)
                    &(&INDI_controller_Cpp_M)->intgData);
  rtsiSetSolverName(&(&INDI_controller_Cpp_M)->solverInfo,"ode3");
  rtmSetTPtr(getRTM(), &(&INDI_controller_Cpp_M)->Timing.tArray[0]);
  (&INDI_controller_Cpp_M)->Timing.stepSize0 = 0.0005;

  /* block I/O */
  (void) memset(((void *) &INDI_controller_Cpp_B), 0,
                sizeof(B_INDI_controller_Cpp_T));

  /* states (continuous) */
  {
    (void) memset((void *)&INDI_controller_Cpp_X, 0,
                  sizeof(X_INDI_controller_Cpp_T));
  }

  /* states (dwork) */
  (void) memset((void *)&INDI_controller_Cpp_DW, 0,
                sizeof(DW_INDI_controller_Cpp_T));

  /* external inputs */
  (void)memset((void *)&INDI_controller_Cpp_U, 0, sizeof
               (ExtU_INDI_controller_Cpp_T));

  /* external outputs */
  INDI_controller_Cpp_Y.actCMD = INDI_controller_Cpp_rtZactCmd;

  /* Start for S-Function (sdspeye): '<S1>/Identity Matrix' */
  memset(&INDI_controller_Cpp_B.IdentityMatrix[0], 0, 9U * sizeof(real_T));

  /* Fill in 1's on the diagonal. */
  INDI_controller_Cpp_B.IdentityMatrix[0] = 1.0;
  INDI_controller_Cpp_B.IdentityMatrix[4] = 1.0;
  INDI_controller_Cpp_B.IdentityMatrix[8] = 1.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  INDI_controller_Cpp_X.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Filter' */
  INDI_controller_Cpp_X.Filter_CSTATE[0] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_ddot_int' */
  INDI_controller_Cpp_DW.w_ddot_int_DSTATE[0] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_dot_int' */
  INDI_controller_Cpp_DW.w_dot_int_DSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  INDI_controller_Cpp_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Filter' */
  INDI_controller_Cpp_X.Filter_CSTATE[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_ddot_int' */
  INDI_controller_Cpp_DW.w_ddot_int_DSTATE[1] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_dot_int' */
  INDI_controller_Cpp_DW.w_dot_int_DSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  INDI_controller_Cpp_X.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Filter' */
  INDI_controller_Cpp_X.Filter_CSTATE[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_ddot_int' */
  INDI_controller_Cpp_DW.w_ddot_int_DSTATE[2] = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S8>/w_dot_int' */
  INDI_controller_Cpp_DW.w_dot_int_DSTATE[2] = 0.0;
}

/* Model terminate function */
void INDI_controller_CppModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
INDI_controller_CppModelClass::INDI_controller_CppModelClass()
{
  cout << 3 << endl;
  initialize();
  cout << 4 << endl;

}

/* Destructor */
INDI_controller_CppModelClass::~INDI_controller_CppModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_INDI_controller_Cpp_T * INDI_controller_CppModelClass::getRTM()
{
  return (&INDI_controller_Cpp_M);
}

int main()
{
  cout<< 1 << endl;
  ExtU_INDI_controller_Cpp_T test;
  test.abar = 30;
  cout<< test.abar << endl;
  cout<< 2 << endl;
  INDI_controller_CppModelClass test2;
  cout<< test2.INDI_controller_Cpp_Y.actCMD.ailCMD << endl;
  double DCM[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  memcpy(test2.INDI_controller_Cpp_U.DCMbe, DCM, sizeof(DCM));
  cout << test2.INDI_controller_Cpp_U.DCMbe[0] << endl;
  double v[3] = {29, 0, 0};
  memcpy(test2.INDI_controller_Cpp_U.v_ned, v, sizeof(v));
  double pqrdes[3] = {1/53.7, 0, 0}; 
  memcpy(test2.INDI_controller_Cpp_U.pqr_des, pqrdes, sizeof(pqrdes) );
  cout << test2.INDI_controller_Cpp_U.pqr_des[0] << endl;
  test2.INDI_controller_Cpp_U.ctrlsfc.a = 0;
  test2.INDI_controller_Cpp_U.ctrlsfc.e = 2.07;
  test2.INDI_controller_Cpp_U.ctrlsfc.r = 0;
  
  test2.step();
  cout << 5 << endl;
  cout<< test2.INDI_controller_Cpp_Y.actCMD.ailCMD << endl;
  cout << test2.INDI_controller_Cpp_U.abar<< endl;
  cout << "DCMbe"<< endl;

  return 0;
}