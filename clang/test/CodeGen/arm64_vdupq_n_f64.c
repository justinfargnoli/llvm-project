// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py UTC_ARGS: --version 5
// RUN: %clang_cc1 -triple arm64-apple-ios7 -target-feature +neon -ffreestanding -o - -disable-O0-optnone -emit-llvm %s | opt -S -passes=mem2reg,sroa | FileCheck %s

// REQUIRES: aarch64-registered-target || arm-registered-target

#include <arm_neon.h>

// vdupq_n_f64 -> dup.2d v0, v0[0]
// CHECK-LABEL: define <2 x double> @test_vdupq_n_f64(
// CHECK-SAME: double noundef [[W:%.*]]) #[[ATTR0:[0-9]+]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[VECINIT_I:%.*]] = insertelement <2 x double> poison, double [[W]], i32 0
// CHECK-NEXT:    [[VECINIT1_I:%.*]] = insertelement <2 x double> [[VECINIT_I]], double [[W]], i32 1
// CHECK-NEXT:    ret <2 x double> [[VECINIT1_I]]
//
float64x2_t test_vdupq_n_f64(float64_t w) {
    return vdupq_n_f64(w);
}

// might as well test this while we're here
// vdupq_n_f32 -> dup.4s v0, v0[0]
// CHECK-LABEL: define <4 x float> @test_vdupq_n_f32(
// CHECK-SAME: float noundef [[W:%.*]]) #[[ATTR0]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[VECINIT_I:%.*]] = insertelement <4 x float> poison, float [[W]], i32 0
// CHECK-NEXT:    [[VECINIT1_I:%.*]] = insertelement <4 x float> [[VECINIT_I]], float [[W]], i32 1
// CHECK-NEXT:    [[VECINIT2_I:%.*]] = insertelement <4 x float> [[VECINIT1_I]], float [[W]], i32 2
// CHECK-NEXT:    [[VECINIT3_I:%.*]] = insertelement <4 x float> [[VECINIT2_I]], float [[W]], i32 3
// CHECK-NEXT:    ret <4 x float> [[VECINIT3_I]]
//
float32x4_t test_vdupq_n_f32(float32_t w) {
    return vdupq_n_f32(w);
}

// vdupq_lane_f64 -> dup.2d v0, v0[0]
// CHECK-LABEL: define <2 x double> @test_vdupq_lane_f64(
// CHECK-SAME: <1 x double> noundef [[V:%.*]]) #[[ATTR0]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[TMP0:%.*]] = bitcast <1 x double> [[V]] to i64
// CHECK-NEXT:    [[__S0_SROA_0_0_VEC_INSERT:%.*]] = insertelement <1 x i64> undef, i64 [[TMP0]], i32 0
// CHECK-NEXT:    [[TMP1:%.*]] = bitcast <1 x i64> [[__S0_SROA_0_0_VEC_INSERT]] to <8 x i8>
// CHECK-NEXT:    [[TMP2:%.*]] = bitcast <8 x i8> [[TMP1]] to <1 x double>
// CHECK-NEXT:    [[LANE:%.*]] = shufflevector <1 x double> [[TMP2]], <1 x double> [[TMP2]], <2 x i32> zeroinitializer
// CHECK-NEXT:    ret <2 x double> [[LANE]]
//
float64x2_t test_vdupq_lane_f64(float64x1_t V) {
    return vdupq_lane_f64(V, 0);
}

// vmovq_n_f64 -> dup Vd.2d,X0
// CHECK-LABEL: define <2 x double> @test_vmovq_n_f64(
// CHECK-SAME: double noundef [[W:%.*]]) #[[ATTR0]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[VECINIT_I:%.*]] = insertelement <2 x double> poison, double [[W]], i32 0
// CHECK-NEXT:    [[VECINIT1_I:%.*]] = insertelement <2 x double> [[VECINIT_I]], double [[W]], i32 1
// CHECK-NEXT:    ret <2 x double> [[VECINIT1_I]]
//
float64x2_t test_vmovq_n_f64(float64_t w) {
  return vmovq_n_f64(w);
}

// CHECK-LABEL: define <4 x half> @test_vmov_n_f16(
// CHECK-SAME: ptr noundef [[A1:%.*]]) #[[ATTR0]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[TMP0:%.*]] = load half, ptr [[A1]], align 2
// CHECK-NEXT:    [[VECINIT:%.*]] = insertelement <4 x half> poison, half [[TMP0]], i32 0
// CHECK-NEXT:    [[VECINIT1:%.*]] = insertelement <4 x half> [[VECINIT]], half [[TMP0]], i32 1
// CHECK-NEXT:    [[VECINIT2:%.*]] = insertelement <4 x half> [[VECINIT1]], half [[TMP0]], i32 2
// CHECK-NEXT:    [[VECINIT3:%.*]] = insertelement <4 x half> [[VECINIT2]], half [[TMP0]], i32 3
// CHECK-NEXT:    ret <4 x half> [[VECINIT3]]
//
float16x4_t test_vmov_n_f16(float16_t *a1) {
  return vmov_n_f16(*a1);
}

/*
float64x1_t test_vmov_n_f64(float64_t a1) {
  return vmov_n_f64(a1);
}
*/

// CHECK-LABEL: define <8 x half> @test_vmovq_n_f16(
// CHECK-SAME: ptr noundef [[A1:%.*]]) #[[ATTR0]] {
// CHECK-NEXT:  [[ENTRY:.*:]]
// CHECK-NEXT:    [[TMP0:%.*]] = load half, ptr [[A1]], align 2
// CHECK-NEXT:    [[VECINIT:%.*]] = insertelement <8 x half> poison, half [[TMP0]], i32 0
// CHECK-NEXT:    [[VECINIT1:%.*]] = insertelement <8 x half> [[VECINIT]], half [[TMP0]], i32 1
// CHECK-NEXT:    [[VECINIT2:%.*]] = insertelement <8 x half> [[VECINIT1]], half [[TMP0]], i32 2
// CHECK-NEXT:    [[VECINIT3:%.*]] = insertelement <8 x half> [[VECINIT2]], half [[TMP0]], i32 3
// CHECK-NEXT:    [[VECINIT4:%.*]] = insertelement <8 x half> [[VECINIT3]], half [[TMP0]], i32 4
// CHECK-NEXT:    [[VECINIT5:%.*]] = insertelement <8 x half> [[VECINIT4]], half [[TMP0]], i32 5
// CHECK-NEXT:    [[VECINIT6:%.*]] = insertelement <8 x half> [[VECINIT5]], half [[TMP0]], i32 6
// CHECK-NEXT:    [[VECINIT7:%.*]] = insertelement <8 x half> [[VECINIT6]], half [[TMP0]], i32 7
// CHECK-NEXT:    ret <8 x half> [[VECINIT7]]
//
float16x8_t test_vmovq_n_f16(float16_t *a1) {
  return vmovq_n_f16(*a1);
}
