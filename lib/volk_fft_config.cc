
#include <volk/volk_fft_config.h>
#include <volk/volk.h>
#include <cstring>

void fftalloc(fftarch* fft_conf, const char* arch, const volk_fft_inputsig* inputsig, const int vlen, const bool isinverse){
    fft_conf->size = vlen;
    fft_conf->isinverse = isinverse; 
    fft_conf->arch = (char *)arch;

    fft_conf->generic_arch_cfg_float = NULL;
    fft_conf->generic_arch_cfg_int32 = NULL;
    fft_conf->generic_arch_cfg_int16 = NULL;

#if defined(__arm__)
    fft_conf->neon_arch_cfg_float = NULL;
    fft_conf->neon_arch_cfg_int32 = NULL;
    fft_conf->neon_arch_cfg_int16 = NULL;
#endif

    if (strcmp(arch,"generic") == 0){   
        if (inputsig->is_float){ 
            //printf("allocating kissfft float\n");    
            fft_conf->generic_arch_cfg_float = kiss_fft_alloc_float(vlen, (char) isinverse, 0, 0);
            //printf("allocated kissfft float\n");
        }else{
            if (inputsig->size == 4){
                //printf("allocating kissfft int32\n");
                fft_conf->generic_arch_cfg_int32 = kiss_fft_alloc_int32(vlen, (char) isinverse, 0, 0);                
                //printf("allocated kissfft int32\n");
            }else if (inputsig->size == 2){
                //printf("allocating kissfft int16\n");
                fft_conf->generic_arch_cfg_int16 = kiss_fft_alloc_int16(vlen, (char) isinverse, 0, 0);
                //printf("allocated kissfft int16\n");
            }else{
                //throw "non-standard size input fft input signature size requested";
            }        
        }        
    }else if (strcmp(arch,"neon") == 0) {
#if defined(__arm__)
        if (inputsig->is_float){ 
            //printf("allocating neon float32\n");
            fft_conf->neon_arch_cfg_float = ne10_fft_alloc_c2c_float32_neon(vlen);
            //printf("allocated neon float32\n");
        }else{
            if (inputsig->size == 4){
                //printf("allocating neon int32\n");
                fft_conf->neon_arch_cfg_int32 = ne10_fft_alloc_c2c_int32(vlen);
                //printf("allocated neon int32\n");
            }else if (inputsig->size == 2){
                //printf("allocating neon int16\n");
                fft_conf->neon_arch_cfg_int16 = ne10_fft_alloc_c2c_int16(vlen);
                //printf("allocated neon int16\n");
            }else{
                //throw "non-standard size input fft input signature size requested";
            }
        }
#else
        //throw "unsupported neon fft arch requested"; 
#endif  
    }else{
        //throw "unsupported fft arch requested"; 
    }      

}
