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

#ifndef INCLUDED_volk_32fc_8i_fft_32fc_u_H
#define INCLUDED_volk_32fc_8i_fft_32fc_u_H

#include <inttypes.h>
//#include <stdio.h>

#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_float/kiss_fft_float.h>
/*!

*/
static inline void volk_32fc_8i_fft_32fc_generic(lv_32fc_t* cVector, const lv_32fc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cpx_float *kout = (kiss_fft_cpx_float*) cVector;
    kiss_fft_cpx_float *tbuf = (kiss_fft_cpx_float*) aVector;
    static unsigned int num_points_old = 0;
    static char isinverse_old = 0;
    static kiss_fft_cfg_float cfg = NULL;

    if ((num_points_old != num_points) || (isinverse_old != isinverse)){
        num_points_old = num_points;
        isinverse_old = isinverse;
        if (cfg!=NULL){
            free(cfg);    
        }
        cfg = kiss_fft_alloc_float(num_points, isinverse, 0, 0); 
    }

	kiss_fft_float(cfg, tbuf, kout);	

}
#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON
#include <arm_neon.h>
#include <Ne10/NE10.h>
#include <Ne10/NE10_dsp.h>

/*

*/
static inline void volk_32fc_8i_fft_32fc_neon(lv_32fc_t* cVector, const lv_32fc_t* aVector, const char isinverse, unsigned int num_points){
    ne10_float32_t* in_neon = (ne10_float32_t*) aVector;
    ne10_float32_t* out_neon = (ne10_float32_t*) cVector;    
    static ne10_fft_cfg_float32_t cfg = NULL;  
    static unsigned int num_points_old = 0;

    //const bool use_neon = ((num_points != 0) && ((num_points & (~num_points + 1)) == num_points));
    const bool use_neon = (num_points % 4 == 0); // not actually faster

    if (num_points_old != num_points){
        num_points_old = num_points;
        if (use_neon){
            if (cfg!=NULL){
                NE10_FREE(cfg);    
            }
            cfg = ne10_fft_alloc_c2c_float32_neon(num_points); 
        }
    }

    if (!use_neon){ 
        volk_32fc_8i_fft_32fc_generic(cVector, aVector, isinverse, num_points);
    }else{
        ne10_fft_c2c_1d_float32_neon( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg, (ne10_int32_t) isinverse);
    }

}

#endif /* LV_HAVE_NEON */

#endif /* INCLUDED_volk_32fc_8i_fft_32fc_u_H */

