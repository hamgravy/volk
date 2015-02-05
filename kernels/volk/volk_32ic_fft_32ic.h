/* -*- c++ -*- */
/*
 * Copyright 2012, 2013, 2014 Free Software Foundation, Inc.
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

#ifndef INCLUDED_volk_32ic_fft_32ic_a_H
#define INCLUDED_volk_32ic_fft_32ic_a_H

#include <volk/volk_complex.h>
#include <stdio.h>
#include <volk/volk_fft_config.h>


#ifdef LV_HAVE_GENERIC

static inline void volk_32ic_fft_32ic_generic(lv_32sc_t* outVector, const lv_32sc_t* inVector, const fftarch* cfg, unsigned int num_points){
    kiss_fft_cpx_int32 *kout	= (kiss_fft_cpx_int32*) outVector;
    kiss_fft_cpx_int32 *tbuf    = (kiss_fft_cpx_int32*) inVector;    
    kiss_fft_int32(cfg->generic_arch_cfg_int32, tbuf, kout);
    /*
    int ii;
    printf("x=[");
    for (ii=0; ii < num_points; ii++){
	    printf("%d+%di;",(int32_t)tbuf[ii].r,(int32_t)tbuf[ii].i);
    }
    printf("];\n");

    printf("y=[");
    for (ii=0; ii < num_points; ii++){
	    printf("%d+%di;",(int32_t)kout[ii].r,(int32_t)kout[ii].i);
    }
    printf("];\n");
    */
}

#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON

#include <Ne10/NE10.h>

static inline void volk_32ic_fft_32ic_neon(lv_32sc_t* outVector, const lv_32sc_t* inVector, const fftarch* cfg, unsigned int num_points){ 
    ne10_int32_t* in_neon = (ne10_int32_t*) inVector;
    ne10_int32_t* out_neon = (ne10_int32_t*) outVector; 
    const ne10_int32_t isscaled = 1;
    //const bool use_neon = ((num_points != 0) && ((num_points & (~num_points + 1)) == num_points));

    ne10_fft_c2c_1d_int32_neon( (ne10_fft_cpx_int32_t*) out_neon, \
                                (ne10_fft_cpx_int32_t*) in_neon, \
                                cfg->neon_arch_cfg_int32, \
                                cfg->isinverse, \
                                isscaled);
    /*
    int ii;
    printf("x=[");
    for (ii=0; ii < num_points; ii++){
	    printf("%d+%di;",(int32_t)in_neon[ii*2],(int32_t)in_neon[(ii*2)+1]);
    }
    printf("];\n");

    printf("y=[");
    for (ii=0; ii < num_points; ii++){
	    printf("%d+%di;",(int32_t)out_neon[ii*2],(int32_t)out_neon[(ii*2)+1]);
    }
    printf("];\n");
    */
}

#endif /* LV_HAVE_NEON */

#endif /* INCLUDED_volk_32ic_fft_32ic_a_H */
