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

#ifndef INCLUDED_volk_16ic_fft_16ic_a_H
#define INCLUDED_volk_16ic_fft_16ic_a_H

#include <volk/volk_complex.h>
#include <stdio.h>
#include <volk/volk_16ic_8i_fft_16ic.h>


#ifdef LV_HAVE_GENERIC

static inline void volk_16ic_fft_16ic_generic(lv_16sc_t* outVector, const lv_16sc_t* inVector, unsigned int num_points){
    int16_t* in_generic = (int16_t*) inVector;
    static int16_t* in_scaled = NULL;
    static unsigned int num_points_old = 0;
    int ii;        
 
    if (num_points != num_points_old){
        num_points_old = num_points;        
        if(in_scaled != NULL){
            free(in_scaled);    
        }
        in_scaled = (int16_t*) malloc (num_points * 2 *  sizeof (int16_t));       
        for(ii = 0; ii < num_points*2; ii++){
            in_scaled[ii] = in_generic[ii] >> 1;
        }
    }

    volk_16ic_8i_fft_16ic_generic(outVector, (lv_16sc_t*)in_scaled, 0, num_points);
}

#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON

static inline void volk_16ic_fft_16ic_neon(lv_16sc_t* outVector, const lv_16sc_t* inVector, unsigned int num_points){
    ne10_int16_t* in_neon = (ne10_int16_t*) inVector;
    static ne10_int16_t* in_scaled = NULL;
    static unsigned int num_points_old = 0;
    int ii;

    if (num_points != num_points_old){
        num_points_old = num_points;  
      
        if(in_scaled != NULL){
            free(in_scaled);    
        }
        in_scaled = (ne10_int16_t*) malloc (num_points * 2 *  sizeof (ne10_int16_t));       
        for(ii = 0; ii < num_points*2; ii++){
            in_scaled[ii] = in_neon[ii] >> 1;
        }
    }

    volk_16ic_8i_fft_16ic_neon(outVector, (lv_16sc_t*)in_scaled, 0, num_points);   

}

#endif /* LV_HAVE_NEON */

#endif /* INCLUDED_volk_16ic_fft_16ic_a_H */
