#ifndef VOLK_FFT_CONFIG_H
#define VOLK_FFT_CONFIG_H

#include <kissfft/kissfft_float/kiss_fft_float.h>
#include <iostream>
#include <string>

typedef struct{
    int size;
    int isinverse;
    int arch;
    kiss_fft_cfg_float generic_arch_cfg;
} fftarch;


void helloworld(int i);
fftarch fftalloc(std::string arch, int vlen);



#endif //VOLK_FFT_CONFIG_H
