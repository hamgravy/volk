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
  \brief takes fft of aVector and stores it in cVector
  \param cVector The vector where the results will be stored
  \param aVector transform inputs
  \param num_points number of elements in the vector to be transformed (transform size)
*/
static inline void volk_16ic_8i_fft_16ic_generic(lv_16sc_t* cVector, const lv_16sc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cfg_int16 cfg	    = NULL;
    kiss_fft_cpx_int16 *kout	= (kiss_fft_cpx_int16*) cVector;
    kiss_fft_cpx_int16 *tbuf    = (kiss_fft_cpx_int16*) aVector;
	
    cfg = kiss_fft_alloc_int16(num_points, isinverse, 0, 0);
    kiss_fft_int16(cfg, tbuf, kout);	
	free(cfg);
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

#endif /* INCLUDED_volk_16ic_8i_fft_16ic_u_H */
#ifndef INCLUDED_volk_16ic_8i_fft_16ic_a_H
#define INCLUDED_volk_16ic_8i_fft_16ic_a_H

#include <inttypes.h>
#include <stdio.h>

#ifdef LV_HAVE_GENERIC
#include <kissfft/kissfft_int16/kiss_fft_int16.h>
/*!
  \brief takes fft of aVector and stores it in cVector
  \param cVector The vector where the results will be stored
  \param aVector transform inputs
  \param num_points number of elements in the vector to be transformed (transform size)
*/
static inline void volk_16ic_8i_fft_16ic_a_generic(lv_16sc_t* cVector, const lv_16sc_t* aVector, const char isinverse, unsigned int num_points){
    kiss_fft_cfg_int16 cfg	    = NULL;
    kiss_fft_cpx_int16 *kout	= (kiss_fft_cpx_int16*) cVector;
    kiss_fft_cpx_int16 *tbuf    = (kiss_fft_cpx_int16*) aVector;
	
    cfg = kiss_fft_alloc_int16(num_points, isinverse, 0, 0);
    kiss_fft_int16(cfg, tbuf, kout);	
	free(cfg);
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

#endif /* INCLUDED_volk_16ic_8i_fft_16ic_a_H */

