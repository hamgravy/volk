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

#ifndef INCLUDED_volk_32ic_8i_fft_32ic_u_H
#define INCLUDED_volk_32ic_8i_fft_32ic_u_H

#include <inttypes.h>
#include <stdio.h>

#include <limits.h>
#include <stdlib.h>
#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_int32/kiss_fft_int32.h>
/*

*/
static inline void volk_32ic_8i_fft_32ic_generic(lv_32sc_t* cVector, const lv_32sc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cpx_int32 *kout = (kiss_fft_cpx_int32*) cVector;
    kiss_fft_cpx_int32 *tbuf = (kiss_fft_cpx_int32*) aVector;
    static kiss_fft_cfg_int32 cfg = NULL;
    static unsigned int num_points_old = 0;
    static unsigned char isinverse_old = 0;

    if ((num_points_old != num_points) || (isinverse_old != isinverse)){
        num_points_old = num_points;
        isinverse_old = isinverse;
        if (cfg!=NULL){
            free(cfg);    
        }
        cfg = kiss_fft_alloc_int32(num_points, isinverse, 0, 0); 
    }

	kiss_fft_int32(cfg, tbuf, kout);

}
#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON
#include <arm_neon.h>
#include <Ne10/NE10.h>
#include <Ne10/NE10_dsp.h>
/*

*/
static inline void volk_32ic_8i_fft_32ic_neon(lv_32sc_t* cVector, const lv_32sc_t* aVector, const char isinverse, unsigned int num_points){
    ne10_int32_t* in_neon = (ne10_int32_t*) aVector;
    ne10_int32_t* out_neon = (ne10_int32_t*) cVector;    
    static ne10_fft_cfg_int32_t cfg = NULL;
    static unsigned int num_points_old = 0;
    const ne10_int32_t isscaled = 1;

    if (num_points_old != num_points){
        num_points_old = num_points;
        if (cfg!=NULL){
            NE10_FREE(cfg);    
        }
        cfg = ne10_fft_alloc_c2c_int32(num_points); // returns NULL if a non-power-of-two transform size is requested
    }

    if (cfg == NULL){ 
        volk_32ic_8i_fft_32ic_generic(cVector, aVector, isinverse, num_points);
    }else{
        ne10_fft_c2c_1d_int32_neon( (ne10_fft_cpx_int32_t*) out_neon, (ne10_fft_cpx_int32_t*) in_neon, cfg, (ne10_int32_t) isinverse, isscaled);
    }

}

#endif /* LV_HAVE_NEON */

#endif /* INCLUDED_volk_32ic_8i_fft_32ic_u_H */

