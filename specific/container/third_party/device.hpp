#pragma once

#include "cpu/cpu.hpp"
#include "boost_compute/boost_compute.hpp"

#ifdef __HIPCC__
    #include "amd_hip/amd_hip.hpp"
#endif

#ifdef __APPLE__
    #include "apple_mps/apple_mps.hpp"
#endif

#ifdef __INTEL__
    #include "intel_tbb/intel_tbb.hpp"
#endif

#ifdef __NVCC__
    #include "nvidia_cuda/nvidia_cuda.hpp"
#endif