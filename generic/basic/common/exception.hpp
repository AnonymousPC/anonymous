#pragma once

/// Exceptions list

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
            class mysql_error;
        class device_error;
            class cuda_error;
            class opencl_error;
            class tbb_error;
        class math_error;
            class linalg_error;

    class signal;
        class abort_signal;
        class floating_point_exception_signal;
        class illegal_instruction_signal;
        class interrupt_signal;
        class segmentation_violation_signal;
        class terminate_signal;

#include "exception.ipp"
#ifdef dll
    #include "exception.cpp"
#endif