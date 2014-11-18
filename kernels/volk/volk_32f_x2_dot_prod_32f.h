/* -*- c++ -*- */
/*
 * Copyright 2012, 2014 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_volk_32f_x2_dot_prod_32f_u_H
#define INCLUDED_volk_32f_x2_dot_prod_32f_u_H

#include <volk/volk_common.h>
#include<stdio.h>


#ifdef LV_HAVE_GENERIC


static inline void volk_32f_x2_dot_prod_32f_generic(float * result, const float * input, const float * taps, unsigned int num_points) {

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr=  taps;
  unsigned int number = 0;

  for(number = 0; number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_GENERIC*/


#ifdef LV_HAVE_SSE


static inline void volk_32f_x2_dot_prod_32f_u_sse( float* result, const  float* input, const  float* taps, unsigned int num_points) {

  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 a0Val, a1Val, a2Val, a3Val;
  __m128 b0Val, b1Val, b2Val, b3Val;
  __m128 c0Val, c1Val, c2Val, c3Val;

  __m128 dotProdVal0 = _mm_setzero_ps();
  __m128 dotProdVal1 = _mm_setzero_ps();
  __m128 dotProdVal2 = _mm_setzero_ps();
  __m128 dotProdVal3 = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm_loadu_ps(aPtr);
    a1Val = _mm_loadu_ps(aPtr+4);
    a2Val = _mm_loadu_ps(aPtr+8);
    a3Val = _mm_loadu_ps(aPtr+12);
    b0Val = _mm_loadu_ps(bPtr);
    b1Val = _mm_loadu_ps(bPtr+4);
    b2Val = _mm_loadu_ps(bPtr+8);
    b3Val = _mm_loadu_ps(bPtr+12);

    c0Val = _mm_mul_ps(a0Val, b0Val);
    c1Val = _mm_mul_ps(a1Val, b1Val);
    c2Val = _mm_mul_ps(a2Val, b2Val);
    c3Val = _mm_mul_ps(a3Val, b3Val);

    dotProdVal0 = _mm_add_ps(c0Val, dotProdVal0);
    dotProdVal1 = _mm_add_ps(c1Val, dotProdVal1);
    dotProdVal2 = _mm_add_ps(c2Val, dotProdVal2);
    dotProdVal3 = _mm_add_ps(c3Val, dotProdVal3);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal1);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal2);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal3);

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];

  _mm_store_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;

}

#endif /*LV_HAVE_SSE*/

#ifdef LV_HAVE_SSE3

#include <pmmintrin.h>

static inline void volk_32f_x2_dot_prod_32f_u_sse3(float * result, const float * input, const float * taps, unsigned int num_points) {
  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 a0Val, a1Val, a2Val, a3Val;
  __m128 b0Val, b1Val, b2Val, b3Val;
  __m128 c0Val, c1Val, c2Val, c3Val;

  __m128 dotProdVal0 = _mm_setzero_ps();
  __m128 dotProdVal1 = _mm_setzero_ps();
  __m128 dotProdVal2 = _mm_setzero_ps();
  __m128 dotProdVal3 = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm_loadu_ps(aPtr);
    a1Val = _mm_loadu_ps(aPtr+4);
    a2Val = _mm_loadu_ps(aPtr+8);
    a3Val = _mm_loadu_ps(aPtr+12);
    b0Val = _mm_loadu_ps(bPtr);
    b1Val = _mm_loadu_ps(bPtr+4);
    b2Val = _mm_loadu_ps(bPtr+8);
    b3Val = _mm_loadu_ps(bPtr+12);

    c0Val = _mm_mul_ps(a0Val, b0Val);
    c1Val = _mm_mul_ps(a1Val, b1Val);
    c2Val = _mm_mul_ps(a2Val, b2Val);
    c3Val = _mm_mul_ps(a3Val, b3Val);

    dotProdVal0 = _mm_add_ps(dotProdVal0, c0Val);
    dotProdVal1 = _mm_add_ps(dotProdVal1, c1Val);
    dotProdVal2 = _mm_add_ps(dotProdVal2, c2Val);
    dotProdVal3 = _mm_add_ps(dotProdVal3, c3Val);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal1);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal2);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal3);

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];
  _mm_store_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_SSE3*/

#ifdef LV_HAVE_SSE4_1

#include <smmintrin.h>

static inline void volk_32f_x2_dot_prod_32f_u_sse4_1(float * result, const float * input, const float* taps, unsigned int num_points) {
  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 aVal1, bVal1, cVal1;
  __m128 aVal2, bVal2, cVal2;
  __m128 aVal3, bVal3, cVal3;
  __m128 aVal4, bVal4, cVal4;

  __m128 dotProdVal = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    aVal1 = _mm_loadu_ps(aPtr); aPtr += 4;
    aVal2 = _mm_loadu_ps(aPtr); aPtr += 4;
    aVal3 = _mm_loadu_ps(aPtr); aPtr += 4;
    aVal4 = _mm_loadu_ps(aPtr); aPtr += 4;

    bVal1 = _mm_loadu_ps(bPtr); bPtr += 4;
    bVal2 = _mm_loadu_ps(bPtr); bPtr += 4;
    bVal3 = _mm_loadu_ps(bPtr); bPtr += 4;
    bVal4 = _mm_loadu_ps(bPtr); bPtr += 4;

    cVal1 = _mm_dp_ps(aVal1, bVal1, 0xF1);
    cVal2 = _mm_dp_ps(aVal2, bVal2, 0xF2);
    cVal3 = _mm_dp_ps(aVal3, bVal3, 0xF4);
    cVal4 = _mm_dp_ps(aVal4, bVal4, 0xF8);

    cVal1 = _mm_or_ps(cVal1, cVal2);
    cVal3 = _mm_or_ps(cVal3, cVal4);
    cVal1 = _mm_or_ps(cVal1, cVal3);

    dotProdVal = _mm_add_ps(dotProdVal, cVal1);
  }

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];
  _mm_store_ps(dotProductVector, dotProdVal); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints * 16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_SSE4_1*/

#ifdef LV_HAVE_AVX

#include <immintrin.h>

static inline void volk_32f_x2_dot_prod_32f_u_avx( float* result, const  float* input, const  float* taps, unsigned int num_points) {

  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m256 a0Val, a1Val;
  __m256 b0Val, b1Val;
  __m256 c0Val, c1Val;

  __m256 dotProdVal0 = _mm256_setzero_ps();
  __m256 dotProdVal1 = _mm256_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm256_loadu_ps(aPtr);
    a1Val = _mm256_loadu_ps(aPtr+8);
    b0Val = _mm256_loadu_ps(bPtr);
    b1Val = _mm256_loadu_ps(bPtr+8);

    c0Val = _mm256_mul_ps(a0Val, b0Val);
    c1Val = _mm256_mul_ps(a1Val, b1Val);

    dotProdVal0 = _mm256_add_ps(c0Val, dotProdVal0);
    dotProdVal1 = _mm256_add_ps(c1Val, dotProdVal1);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm256_add_ps(dotProdVal0, dotProdVal1);

  __VOLK_ATTR_ALIGNED(32) float dotProductVector[8];

  _mm256_storeu_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];
  dotProduct += dotProductVector[4];
  dotProduct += dotProductVector[5];
  dotProduct += dotProductVector[6];
  dotProduct += dotProductVector[7];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;

}

#endif /*LV_HAVE_AVX*/

#endif /*INCLUDED_volk_32f_x2_dot_prod_32f_u_H*/
#ifndef INCLUDED_volk_32f_x2_dot_prod_32f_a_H
#define INCLUDED_volk_32f_x2_dot_prod_32f_a_H

#include <volk/volk_common.h>
#include<stdio.h>


#ifdef LV_HAVE_GENERIC


static inline void volk_32f_x2_dot_prod_32f_a_generic(float * result, const float * input, const float * taps, unsigned int num_points) {

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr=  taps;
  unsigned int number = 0;

  for(number = 0; number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_GENERIC*/


#ifdef LV_HAVE_SSE


static inline void volk_32f_x2_dot_prod_32f_a_sse( float* result, const  float* input, const  float* taps, unsigned int num_points) {

  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 a0Val, a1Val, a2Val, a3Val;
  __m128 b0Val, b1Val, b2Val, b3Val;
  __m128 c0Val, c1Val, c2Val, c3Val;

  __m128 dotProdVal0 = _mm_setzero_ps();
  __m128 dotProdVal1 = _mm_setzero_ps();
  __m128 dotProdVal2 = _mm_setzero_ps();
  __m128 dotProdVal3 = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm_load_ps(aPtr);
    a1Val = _mm_load_ps(aPtr+4);
    a2Val = _mm_load_ps(aPtr+8);
    a3Val = _mm_load_ps(aPtr+12);
    b0Val = _mm_load_ps(bPtr);
    b1Val = _mm_load_ps(bPtr+4);
    b2Val = _mm_load_ps(bPtr+8);
    b3Val = _mm_load_ps(bPtr+12);

    c0Val = _mm_mul_ps(a0Val, b0Val);
    c1Val = _mm_mul_ps(a1Val, b1Val);
    c2Val = _mm_mul_ps(a2Val, b2Val);
    c3Val = _mm_mul_ps(a3Val, b3Val);

    dotProdVal0 = _mm_add_ps(c0Val, dotProdVal0);
    dotProdVal1 = _mm_add_ps(c1Val, dotProdVal1);
    dotProdVal2 = _mm_add_ps(c2Val, dotProdVal2);
    dotProdVal3 = _mm_add_ps(c3Val, dotProdVal3);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal1);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal2);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal3);

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];

  _mm_store_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;

}

#endif /*LV_HAVE_SSE*/

#ifdef LV_HAVE_SSE3

#include <pmmintrin.h>

static inline void volk_32f_x2_dot_prod_32f_a_sse3(float * result, const float * input, const float * taps, unsigned int num_points) {
  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 a0Val, a1Val, a2Val, a3Val;
  __m128 b0Val, b1Val, b2Val, b3Val;
  __m128 c0Val, c1Val, c2Val, c3Val;

  __m128 dotProdVal0 = _mm_setzero_ps();
  __m128 dotProdVal1 = _mm_setzero_ps();
  __m128 dotProdVal2 = _mm_setzero_ps();
  __m128 dotProdVal3 = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm_load_ps(aPtr);
    a1Val = _mm_load_ps(aPtr+4);
    a2Val = _mm_load_ps(aPtr+8);
    a3Val = _mm_load_ps(aPtr+12);
    b0Val = _mm_load_ps(bPtr);
    b1Val = _mm_load_ps(bPtr+4);
    b2Val = _mm_load_ps(bPtr+8);
    b3Val = _mm_load_ps(bPtr+12);

    c0Val = _mm_mul_ps(a0Val, b0Val);
    c1Val = _mm_mul_ps(a1Val, b1Val);
    c2Val = _mm_mul_ps(a2Val, b2Val);
    c3Val = _mm_mul_ps(a3Val, b3Val);

    dotProdVal0 = _mm_add_ps(dotProdVal0, c0Val);
    dotProdVal1 = _mm_add_ps(dotProdVal1, c1Val);
    dotProdVal2 = _mm_add_ps(dotProdVal2, c2Val);
    dotProdVal3 = _mm_add_ps(dotProdVal3, c3Val);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal1);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal2);
  dotProdVal0 = _mm_add_ps(dotProdVal0, dotProdVal3);

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];
  _mm_store_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_SSE3*/

#ifdef LV_HAVE_SSE4_1

#include <smmintrin.h>

static inline void volk_32f_x2_dot_prod_32f_a_sse4_1(float * result, const float * input, const float* taps, unsigned int num_points) {
  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m128 aVal1, bVal1, cVal1;
  __m128 aVal2, bVal2, cVal2;
  __m128 aVal3, bVal3, cVal3;
  __m128 aVal4, bVal4, cVal4;

  __m128 dotProdVal = _mm_setzero_ps();

  for(;number < sixteenthPoints; number++){

    aVal1 = _mm_load_ps(aPtr); aPtr += 4;
    aVal2 = _mm_load_ps(aPtr); aPtr += 4;
    aVal3 = _mm_load_ps(aPtr); aPtr += 4;
    aVal4 = _mm_load_ps(aPtr); aPtr += 4;

    bVal1 = _mm_load_ps(bPtr); bPtr += 4;
    bVal2 = _mm_load_ps(bPtr); bPtr += 4;
    bVal3 = _mm_load_ps(bPtr); bPtr += 4;
    bVal4 = _mm_load_ps(bPtr); bPtr += 4;

    cVal1 = _mm_dp_ps(aVal1, bVal1, 0xF1);
    cVal2 = _mm_dp_ps(aVal2, bVal2, 0xF2);
    cVal3 = _mm_dp_ps(aVal3, bVal3, 0xF4);
    cVal4 = _mm_dp_ps(aVal4, bVal4, 0xF8);

    cVal1 = _mm_or_ps(cVal1, cVal2);
    cVal3 = _mm_or_ps(cVal3, cVal4);
    cVal1 = _mm_or_ps(cVal1, cVal3);

    dotProdVal = _mm_add_ps(dotProdVal, cVal1);
  }

  __VOLK_ATTR_ALIGNED(16) float dotProductVector[4];
  _mm_store_ps(dotProductVector, dotProdVal); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];

  number = sixteenthPoints * 16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;
}

#endif /*LV_HAVE_SSE4_1*/

#ifdef LV_HAVE_AVX

#include <immintrin.h>

static inline void volk_32f_x2_dot_prod_32f_a_avx( float* result, const  float* input, const  float* taps, unsigned int num_points) {

  unsigned int number = 0;
  const unsigned int sixteenthPoints = num_points / 16;

  float dotProduct = 0;
  const float* aPtr = input;
  const float* bPtr = taps;

  __m256 a0Val, a1Val;
  __m256 b0Val, b1Val;
  __m256 c0Val, c1Val;

  __m256 dotProdVal0 = _mm256_setzero_ps();
  __m256 dotProdVal1 = _mm256_setzero_ps();

  for(;number < sixteenthPoints; number++){

    a0Val = _mm256_load_ps(aPtr);
    a1Val = _mm256_load_ps(aPtr+8);
    b0Val = _mm256_load_ps(bPtr);
    b1Val = _mm256_load_ps(bPtr+8);

    c0Val = _mm256_mul_ps(a0Val, b0Val);
    c1Val = _mm256_mul_ps(a1Val, b1Val);

    dotProdVal0 = _mm256_add_ps(c0Val, dotProdVal0);
    dotProdVal1 = _mm256_add_ps(c1Val, dotProdVal1);

    aPtr += 16;
    bPtr += 16;
  }

  dotProdVal0 = _mm256_add_ps(dotProdVal0, dotProdVal1);

  __VOLK_ATTR_ALIGNED(32) float dotProductVector[8];

  _mm256_store_ps(dotProductVector,dotProdVal0); // Store the results back into the dot product vector

  dotProduct = dotProductVector[0];
  dotProduct += dotProductVector[1];
  dotProduct += dotProductVector[2];
  dotProduct += dotProductVector[3];
  dotProduct += dotProductVector[4];
  dotProduct += dotProductVector[5];
  dotProduct += dotProductVector[6];
  dotProduct += dotProductVector[7];

  number = sixteenthPoints*16;
  for(;number < num_points; number++){
    dotProduct += ((*aPtr++) * (*bPtr++));
  }

  *result = dotProduct;

}

#endif /*LV_HAVE_AVX*/

#ifdef LV_HAVE_NEON
#include <arm_neon.h>

static inline void volk_32f_x2_dot_prod_32f_neonopts(float * result, const float * input, const float * taps, unsigned int num_points) {

    unsigned int quarter_points = num_points / 16;
    float dotProduct = 0;
    const float* aPtr = input;
    const float* bPtr=  taps;
    unsigned int number = 0;

    float32x4x4_t a_val, b_val, accumulator0;
    accumulator0.val[0] = vdupq_n_f32(0);
    accumulator0.val[1] = vdupq_n_f32(0);
    accumulator0.val[2] = vdupq_n_f32(0);
    accumulator0.val[3] = vdupq_n_f32(0);
    // factor of 4 loop unroll with independent accumulators
    // uses 12 out of 16 neon q registers
    for( number = 0; number < quarter_points; ++number) {
        a_val = vld4q_f32(aPtr);
        b_val = vld4q_f32(bPtr);
        accumulator0.val[0] = vmlaq_f32(accumulator0.val[0], a_val.val[0], b_val.val[0]);
        accumulator0.val[1] = vmlaq_f32(accumulator0.val[1], a_val.val[1], b_val.val[1]);
        accumulator0.val[2] = vmlaq_f32(accumulator0.val[2], a_val.val[2], b_val.val[2]);
        accumulator0.val[3] = vmlaq_f32(accumulator0.val[3], a_val.val[3], b_val.val[3]);
        aPtr += 16;
        bPtr += 16;
    }
    accumulator0.val[0] = vaddq_f32(accumulator0.val[0], accumulator0.val[1]);
    accumulator0.val[2] = vaddq_f32(accumulator0.val[2], accumulator0.val[3]);
    accumulator0.val[0] = vaddq_f32(accumulator0.val[2], accumulator0.val[0]);
    __VOLK_ATTR_ALIGNED(32) float accumulator[4];
    vst1q_f32(accumulator, accumulator0.val[0]);
    dotProduct = accumulator[0] + accumulator[1] + accumulator[2] + accumulator[3];

    for(number = quarter_points*16; number < num_points; number++){
      dotProduct += ((*aPtr++) * (*bPtr++));
    }

    *result = dotProduct;
}

#endif




#ifdef LV_HAVE_NEON
static inline void volk_32f_x2_dot_prod_32f_neon(float * result, const float * input, const float * taps, unsigned int num_points) {

    unsigned int quarter_points = num_points / 8;
    float dotProduct = 0;
    const float* aPtr = input;
    const float* bPtr=  taps;
    unsigned int number = 0;

    float32x4x2_t a_val, b_val, accumulator_val;
    accumulator_val.val[0] = vdupq_n_f32(0);
    accumulator_val.val[1] = vdupq_n_f32(0);
    // factor of 2 loop unroll with independent accumulators
    for( number = 0; number < quarter_points; ++number) {
        a_val = vld2q_f32(aPtr);
        b_val = vld2q_f32(bPtr);
        accumulator_val.val[0] = vmlaq_f32(accumulator_val.val[0], a_val.val[0], b_val.val[0]);
        accumulator_val.val[1] = vmlaq_f32(accumulator_val.val[1], a_val.val[1], b_val.val[1]);
        aPtr += 8;
        bPtr += 8;
    }
    accumulator_val.val[0] = vaddq_f32(accumulator_val.val[0], accumulator_val.val[1]);
    __VOLK_ATTR_ALIGNED(32) float accumulator[4];
    vst1q_f32(accumulator, accumulator_val.val[0]);
    dotProduct = accumulator[0] + accumulator[1] + accumulator[2] + accumulator[3];

    for(number = quarter_points*8; number < num_points; number++){
      dotProduct += ((*aPtr++) * (*bPtr++));
    }

    *result = dotProduct;
}

#endif /* LV_HAVE_NEON */

#ifdef LV_HAVE_NEON
extern void volk_32f_x2_dot_prod_32f_neonasm(float* cVector, const float* aVector, const float* bVector, unsigned int num_points);
#endif /* LV_HAVE_NEON */

#ifdef LV_HAVE_NEON
extern void volk_32f_x2_dot_prod_32f_neonasm_opts(float* cVector, const float* aVector, const float* bVector, unsigned int num_points);
#endif /* LV_HAVE_NEON */

#endif /*INCLUDED_volk_32f_x2_dot_prod_32f_a_H*/
