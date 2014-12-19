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
#include <stdio.h>

#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_float/kiss_fft_float.h>
/*!
  \brief takes fft of aVector and stores it in cVector
  \param cVector The vector where the results will be stored
  \param aVector transform inputs
  \param isinverse: 1=inverse transform on aVector, 0=forward transform
  \param num_points number of elements in the vector to be transformed (transform size)
*/
static inline void volk_32fc_8i_fft_32fc_generic(lv_32fc_t* cVector, const lv_32fc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cfg_float cfg	    = NULL;
    kiss_fft_cpx_float *kout	= (kiss_fft_cpx_float*) cVector;
    kiss_fft_cpx_float *tbuf    = (kiss_fft_cpx_float*) aVector;
	
    cfg = kiss_fft_alloc_float(num_points , isinverse, 0, 0);	
	kiss_fft_float(cfg, tbuf, kout);	
	free(cfg);
/*
    int ii;
    printf("x=[");
	for (ii=0; ii < num_points; ii++){
		printf("%f+%fi;",(float)tbuf[ii].r,(float)tbuf[ii].i);
	}
	printf("];\n");
	
	printf("y=[");
	for (ii=0; ii < num_points; ii++){
		printf("%f+%fi;",(float)kout[ii].r,(float)kout[ii].i);
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
static inline void volk_32fc_8i_fft_32fc_neon(lv_32fc_t* cVector, const lv_32fc_t* aVector, const char isinverse, unsigned int num_points){
    ne10_float32_t* in_neon = (ne10_float32_t*) aVector;
    ne10_float32_t* out_neon = (ne10_float32_t*) cVector;    
    ne10_fft_cfg_float32_t cfg = ne10_fft_alloc_c2c_float32(num_points);    
    
    ne10_fft_c2c_1d_float32_neon( (ne10_fft_cpx_float32_t*) out_neon, (ne10_fft_cpx_float32_t*) in_neon, cfg, (ne10_int32_t) isinverse);

    NE10_FREE(cfg);
/*
    int ii;
    printf("x=[");
    for (ii=0; ii < num_points; ii++){
        printf("%f+%fi;",(float)in_neon[ii*2],(float)in_neon[(ii*2)+1]);
    }
    printf("];\n");
	
    printf("y=[");
    for (ii=0; ii < num_points; ii++){
        printf("%f+%fi;",(float)out_neon[ii*2],(float)out_neon[(ii*2)+1]);
    }
    printf("];\n");
*/
}

#endif /* LV_HAVE_NEON */


#endif /* INCLUDED_volk_32fc_8i_fft_32fc_u_H */
#ifndef INCLUDED_volk_32fc_8i_fft_32fc_a_H
#define INCLUDED_volk_32fc_8i_fft_32fc_a_H

#include <inttypes.h>
#include <stdio.h>

#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_float/kiss_fft_float.h>
/*!
  \brief takes fft of aVector and stores it in cVector
  \param cVector The vector where the results will be stored
  \param aVector transform inputs
  \param num_points number of elements in the vector to be transformed (transform size)
*/
static inline void volk_32fc_8i_fft_32fc_a_generic(lv_32fc_t* cVector, const lv_32fc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cfg_float cfg	    = NULL;
    kiss_fft_cpx_float *kout	= (kiss_fft_cpx_float*) cVector;
    kiss_fft_cpx_float *tbuf    = (kiss_fft_cpx_float*) aVector;
	
    cfg = kiss_fft_alloc_float(num_points , isinverse, 0, 0);	
	kiss_fft_float(cfg, tbuf, kout);	
	free(cfg);
/*
    int ii;
    printf("x=[");
	for (ii=0; ii < num_points; ii++){
		printf("%f+%fi;",(float)tbuf[ii].r,(float)tbuf[ii].i);
	}
	printf("];\n");
	
	printf("y=[");
	for (ii=0; ii < num_points; ii++){
		printf("%f+%fi;",(float)kout[ii].r,(float)kout[ii].i);
	}
	printf("];\n");
*/ 
}
#endif /* LV_HAVE_GENERIC */

#endif /* INCLUDED_volk_32fc_8i_fft_32fc_a_H */
