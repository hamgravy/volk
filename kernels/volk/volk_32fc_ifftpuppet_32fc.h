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

#ifndef INCLUDED_volk_32fc_ifftpuppet_32fc_a_H
#define INCLUDED_volk_32fc_ifftpuppet_32fc_a_H

#include <volk/volk_complex.h>
#include <stdio.h>
#include <volk/volk_32fc_8i_fft_32fc.h>


#ifdef LV_HAVE_GENERIC

static inline void volk_32fc_ifftpuppet_32fc_generic(lv_32fc_t* outVector, const lv_32fc_t* inVector, unsigned int num_points){

    volk_32fc_8i_fft_32fc_generic(outVector, inVector, 1, num_points);
    
}

#endif /* LV_HAVE_GENERIC */

#ifdef LV_HAVE_NEON

static inline void volk_32fc_ifftpuppet_32fc_neon(lv_32fc_t* outVector, const lv_32fc_t* inVector, unsigned int num_points){

    volk_32fc_8i_fft_32fc_neon(outVector, inVector, 1, num_points);
    
}

#endif /* LV_HAVE_NEON */

#endif /* INCLUDED_volk_32fc_ifftpuppet_32fc_a_H */
