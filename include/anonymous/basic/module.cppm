module;
#include <csignal>

export module anonymous.basic;
import anonymous.std;
import std;
import stdexec;
import boost;
import Eigen;
import tbb;
import clblast;

export namespace anonymous
{
    /// Common.abi
    std::string demangle ( const std::type_info& );

    /// Common.concept
    // See concept.h.

    /// Common.exception
    class exception;
        class logic_error;
            class value_error;
                class index_error;
                class key_error;
            class type_error;
        class runtime_error;
            class string_error;
                class encode_error;
                class format_error;
                class parse_error;
                class regex_error;
            class io_error;
                class file_error;
                class pipe_error;
                class serial_port_error;
                class network_error;
            class device_error;
                class cuda_error;
                class opencl_error;
                class tbb_error;
            class math_error;
                class linalg_error;

    /// Common.range
    template < class type > class range;

    /// Device
    class cpu;
    class cuda;
    class hip;
    class mps;
    class opencl;
    class system;
    class tbb;

    /// Include
    #include "common/common.hpp"
    #include "device/device.hpp"
    #include "init/init.hpp"

    /// Global
    constexpr           detail::print_t           print             = detail::print_t();
    inline              exec::static_thread_pool& execution_context = cpu::execution_context;
    inline thread_local std::mt19937&             random_context    = cpu::random_context;

} // namespace anonymous
