#include <volk/volk_fft_config.h>
#include <volk/volk.h>


void helloworld(int i){
    std::cout << "hello world " << i << std::endl;
    return;
}


fftarch fftalloc(std::string arch, const int vlen){
    char isinverse = 0;    
    fftarch fft_conf;
    fft_conf.size = vlen;
    fft_conf.isinverse = isinverse; 
   
    if (arch=="generic"){        
        fft_conf.generic_arch_cfg = kiss_fft_alloc_float(vlen, isinverse, 0, 0);
        std::cout << "allocated generic fft kernel resources for a " << vlen << " point fft" << std::endl;
    }else{
        fft_conf.generic_arch_cfg = NULL;
    }

    return fft_conf;
}

