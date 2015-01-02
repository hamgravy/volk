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

#ifndef INCLUDED_volk_16ic_8i_fft_16ic_u_H
#define INCLUDED_volk_16ic_8i_fft_16ic_u_H

#include <inttypes.h>
#include <stdio.h>

#include <limits.h>
#include <stdlib.h>
#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_int16/kiss_fft_int16.h>
/*!

*/
static inline void volk_16ic_8i_fft_16ic_generic(lv_16sc_t* cVector, const lv_16sc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cpx_int16 *kout = (kiss_fft_cpx_int16*) cVector;
    kiss_fft_cpx_int16 *tbuf = (kiss_fft_cpx_int16*) aVector;
    static unsigned int num_points_old = 0;
    static char isinverse_old = 0;
    static kiss_fft_cfg_int16 cfg = NULL;

    if ((num_points_old != num_points) || (isinverse_old != isinverse)){
        num_points_old = num_points;
        isinverse_old = isinverse;
        if (cfg != NULL){
            free(cfg);
        }
        cfg = kiss_fft_alloc_int16(num_points, isinverse, 0, 0);
    }  

	kiss_fft_int16(cfg, tbuf, kout);
/*
    int ii;
    printf("x=[");
	for (ii=0; ii < num_points; ii++){
		printf("%d+%di;",(int16_t)tbuf[ii].r,(int16_t)tbuf[ii].i);
	}
	printf("];\n");
	
	printf("y=[");
	for (ii=0; ii < num_points; ii++){
		printf("%d+%di;",(int16_t)kout[ii].r,(int16_t)kout[ii].i);
	}
	printf("];\n");
*/		 
}
#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON
#include <arm_neon.h>
#include <Ne10/NE10.h>
#include <Ne10/NE10_dsp.h>
/*

*/
static inline void volk_16ic_8i_fft_16ic_neon(lv_16sc_t* cVector, const lv_16sc_t* aVector, const char isinverse, unsigned int num_points){
    ne10_int16_t* in_neon = (ne10_int16_t*) aVector;
    ne10_int16_t* out_neon = (ne10_int16_t*) cVector;    
    static ne10_fft_cfg_int16_t cfg = NULL;
    ne10_int16_t isscaled = 1;
    
    if (cfg == NULL){
        cfg = ne10_fft_alloc_c2c_int16(num_points);
    }else if (cfg->nfft != num_points){
        NE10_FREE(cfg);    
        cfg = ne10_fft_alloc_c2c_int16(num_points);
    }

    ne10_fft_c2c_1d_int16_neon( (ne10_fft_cpx_int16_t*) out_neon, (ne10_fft_cpx_int16_t*) in_neon, cfg, (ne10_int16_t) isinverse, isscaled);

}

#endif /* LV_HAVE_NEON */


#endif /* INCLUDED_volk_16ic_8i_fft_16ic_u_H */
#ifndef INCLUDED_volk_16ic_8i_fft_16ic_a_H
#define INCLUDED_volk_16ic_8i_fft_16ic_a_H

#include <inttypes.h>
#include <stdio.h>

#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_int16/kiss_fft_int16.h>
/*!

*/
static inline void volk_16ic_8i_fft_16ic_a_generic(lv_16sc_t* cVector, const lv_16sc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cpx_int16 *kout = (kiss_fft_cpx_int16*) cVector;
    kiss_fft_cpx_int16 *tbuf = (kiss_fft_cpx_int16*) aVector;
    static unsigned int num_points_old = 0;
    static char isinverse_old = 0;
    static kiss_fft_cfg_int16 cfg = NULL;

    if ((num_points_old != num_points) || (isinverse_old != isinverse)){
        num_points_old = num_points;
        isinverse_old = isinverse;
        if (cfg != NULL){
            free(cfg);
        }
        cfg = kiss_fft_alloc_int16(num_points, isinverse, 0, 0);
    }  

	kiss_fft_int16(cfg, tbuf, kout);
		  
}
#endif /* LV_HAVE_GENERIC */

#endif /* INCLUDED_volk_16ic_8i_fft_16ic_a_H */

