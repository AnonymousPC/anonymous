#pragma once
#include "../../generic/basic/interface.hpp"

namespace ap
{
    #ifdef __GNUC__
    #define universal
    #elifdef __NVCC__
    #define universal __host__ __device__
    #endif

    namespace experimental
    {
        struct cpu;
        struct gpu;
        struct npu;
        struct dsp;
        struct fpga;

        template < class type, int dim = 1, class device = cpu > class array;



        #include "array/array_class/array_1d.hpp"
    }
}
