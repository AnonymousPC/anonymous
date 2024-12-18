#pragma once

#include "cpu/cpu.hpp"

#ifdef __NVCC__
    #include "cuda/cuda.hpp"
#endif

#ifdef __HIPCC__
    #include "hip/hip.hpp"
#endif

#ifdef __APPLE__
    #include "mps/mps.hpp"
#endif

#ifdef __INTEL__
    #include "tbb/tbb.hpp"
#endif