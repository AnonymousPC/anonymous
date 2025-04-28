namespace detail
{
    template < class input_type >
    struct opencl_nativize_helper
    {
        using type = input_type;
    };

    template < complex_type input_type >
    struct opencl_nativize_helper<input_type>
    {
        using type = std::complex<typename input_type::value_type>;
    };

    template < class type >
    using opencl_nativize = opencl_nativize_helper<type>::type;

    void opencl_check_mdspan ( const auto left, auto output )
    {
        static_assert ( same_as<output_value_type,float16_t> or 
                        same_as<output_value_type,float32_t> or
                        same_as<output_value_type,float64_t> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float32_t>> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float64_t>>,
                        "value_type not supported on this device: should be one of { float16_t, float32_t, float64_t, complex<float32_t>, complex<float64_t> }" );
        static_assert ( left.rank() <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( not is_contiguous_layout<left_layout_type> )
            throw opencl_error("operation not supported: layout should be contiguous");
    }

    void opencl_check_mdspan ( const auto left, const auto right, auto output )
    {
        static_assert ( same_as<output_value_type,float16_t> or 
                        same_as<output_value_type,float32_t> or
                        same_as<output_value_type,float64_t> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float32_t>> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float64_t>>,
                        "value_type not supported on this device: should be one of { float16_t, float32_t, float64_t, complex<float32_t>, complex<float64_t> }" );
        static_assert ( same_as<left_value_type,right_value_type>, 
                        "value_type not supported on this device: should be same" );
        static_assert ( left.rank() <= 2 and right.rank() <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( not is_contiguous_layout<left_layout_type> or not is_contiguous_layout<right_layout_type> )
            throw opencl_error("operation not supported: layout should be contiguous");
    }

    void opencl_check_mdspan_allow_transpose ( const auto left, const auto right, auto output )
    {
        static_assert ( same_as<output_value_type,float16_t> or 
                        same_as<output_value_type,float32_t> or
                        same_as<output_value_type,float64_t> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float32_t>> or
                        same_as<opencl_nativize<output_value_type>,std::complex<float64_t>>,
                        "value_type not supported on this device: should be one of { float16_t, float32_t, float64_t, complex<float32_t>, complex<float64_t> }" );
        static_assert ( same_as<left_value_type,right_value_type>, 
                        "value_type not supported on this device: should be same" );
        static_assert ( left.rank() <= 2 and right.rank() <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( not ( is_contiguous_layout<left_layout_type>  or is_transposed_layout<left_layout_type> ) or
                       not ( is_contiguous_layout<right_layout_type> or is_transposed_layout<right_layout_type> ) )
            throw opencl_error("operation not supported: layout should be contiguous or transposed");
    }

    std::string clblast_error_message ( clblast::StatusCode c )
    {
        switch ( c )
        {
            // Status codes in common with the OpenCL standard
            case clblast::StatusCode::kSuccess:                    return "CL_SUCCESS";
            case clblast::StatusCode::kOpenCLCompilerNotAvailable: return "CL_COMPILER_NOT_AVAILABLE";
            case clblast::StatusCode::kTempBufferAllocFailure:     return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
            case clblast::StatusCode::kOpenCLOutOfResources:       return "CL_OUT_OF_RESOURCES";
            case clblast::StatusCode::kOpenCLOutOfHostMemory:      return "CL_OUT_OF_HOST_MEMORY";
            case clblast::StatusCode::kOpenCLBuildProgramFailure:  return "CL_BUILD_PROGRAM_FAILURE";
            case clblast::StatusCode::kInvalidValue:               return "CL_INVALID_VALUE";
            case clblast::StatusCode::kInvalidCommandQueue:        return "CL_INVALID_COMMAND_QUEUE";
            case clblast::StatusCode::kInvalidMemObject:           return "CL_INVALID_MEM_OBJECT";
            case clblast::StatusCode::kInvalidBinary:              return "CL_INVALID_BINARY";
            case clblast::StatusCode::kInvalidBuildOptions:        return "CL_INVALID_BUILD_OPTIONS";
            case clblast::StatusCode::kInvalidProgram:             return "CL_INVALID_PROGRAM";
            case clblast::StatusCode::kInvalidProgramExecutable:   return "CL_INVALID_PROGRAM_EXECUTABLE";
            case clblast::StatusCode::kInvalidKernelName:          return "CL_INVALID_KERNEL_NAME";
            case clblast::StatusCode::kInvalidKernelDefinition:    return "CL_INVALID_KERNEL_DEFINITION";
            case clblast::StatusCode::kInvalidKernel:              return "CL_INVALID_KERNEL";
            case clblast::StatusCode::kInvalidArgIndex:            return "CL_INVALID_ARG_INDEX";
            case clblast::StatusCode::kInvalidArgValue:            return "CL_INVALID_ARG_VALUE";
            case clblast::StatusCode::kInvalidArgSize:             return "CL_INVALID_ARG_SIZE";
            case clblast::StatusCode::kInvalidKernelArgs:          return "CL_INVALID_KERNEL_ARGS";
            case clblast::StatusCode::kInvalidLocalNumDimensions:  return "CL_INVALID_WORK_DIMENSION";
            case clblast::StatusCode::kInvalidLocalThreadsTotal:   return "CL_INVALID_WORK_GROUP_SIZE";
            case clblast::StatusCode::kInvalidLocalThreadsDim:     return "CL_INVALID_WORK_ITEM_SIZE";
            case clblast::StatusCode::kInvalidGlobalOffset:        return "CL_INVALID_GLOBAL_OFFSET";
            case clblast::StatusCode::kInvalidEventWaitList:       return "CL_INVALID_EVENT_WAIT_LIST";
            case clblast::StatusCode::kInvalidEvent:               return "CL_INVALID_EVENT";
            case clblast::StatusCode::kInvalidOperation:           return "CL_INVALID_OPERATION";
            case clblast::StatusCode::kInvalidBufferSize:          return "CL_INVALID_BUFFER_SIZE";
            case clblast::StatusCode::kInvalidGlobalWorkSize:      return "CL_INVALID_GLOBAL_WORK_SIZE";

            // Status codes in common with the clBLAS library
            case clblast::StatusCode::kNotImplemented:             return "Routine or functionality not implemented yet";
            case clblast::StatusCode::kInvalidMatrixA:             return "Matrix A is not a valid OpenCL buffer";
            case clblast::StatusCode::kInvalidMatrixB:             return "Matrix B is not a valid OpenCL buffer";
            case clblast::StatusCode::kInvalidMatrixC:             return "Matrix C is not a valid OpenCL buffer";
            case clblast::StatusCode::kInvalidVectorX:             return "Vector X is not a valid OpenCL buffer";
            case clblast::StatusCode::kInvalidVectorY:             return "Vector Y is not a valid OpenCL buffer";
            case clblast::StatusCode::kInvalidDimension:           return "Dimensions M, N, and K have to be larger than zero";
            case clblast::StatusCode::kInvalidLeadDimA:            return "LD of A is smaller than the matrix's first dimension";
            case clblast::StatusCode::kInvalidLeadDimB:            return "LD of B is smaller than the matrix's first dimension";
            case clblast::StatusCode::kInvalidLeadDimC:            return "LD of C is smaller than the matrix's first dimension";
            case clblast::StatusCode::kInvalidIncrementX:          return "Increment of vector X cannot be zero";
            case clblast::StatusCode::kInvalidIncrementY:          return "Increment of vector Y cannot be zero";
            case clblast::StatusCode::kInsufficientMemoryA:        return "Matrix A's OpenCL buffer is too small";
            case clblast::StatusCode::kInsufficientMemoryB:        return "Matrix B's OpenCL buffer is too small";
            case clblast::StatusCode::kInsufficientMemoryC:        return "Matrix C's OpenCL buffer is too small";
            case clblast::StatusCode::kInsufficientMemoryX:        return "Vector X's OpenCL buffer is too small";
            case clblast::StatusCode::kInsufficientMemoryY:        return "Vector Y's OpenCL buffer is too small";

            // Custom additional status codes for CLBlast
            case clblast::StatusCode::kInsufficientMemoryTemp:     return "Temporary buffer provided to GEMM routine is too small";
            case clblast::StatusCode::kInvalidBatchCount:          return "The batch count needs to be positive";
            case clblast::StatusCode::kInvalidOverrideKernel:      return "Trying to override parameters for an invalid kernel";
            case clblast::StatusCode::kMissingOverrideParameter:   return "Missing override parameter(s) for the target kernel";
            case clblast::StatusCode::kInvalidLocalMemUsage:       return "Not enough local memory available on this device";
            case clblast::StatusCode::kNoHalfPrecision:            return "Half precision (16-bits) not supported by the device";
            case clblast::StatusCode::kNoDoublePrecision:          return "Double precision (64-bits) not supported by the device";
            case clblast::StatusCode::kInvalidVectorScalar:        return "The unit-sized vector is not a valid OpenCL buffer";
            case clblast::StatusCode::kInsufficientMemoryScalar:   return "The unit-sized vector's OpenCL buffer is too small";
            case clblast::StatusCode::kDatabaseError:              return "Entry for the device was not found in the database";
            case clblast::StatusCode::kUnknownError:               return "A catch-all error code representing an unspecified error";
            case clblast::StatusCode::kUnexpectedError:            return "A catch-all error code representing an unexpected exception";
        
            // Default case
            default:                                               return "[[unknown clblast error]]";
        }
    }

    void opencl_copy_mdspan ( const auto& left, auto& output )
    {
        auto status =
            clblast::Copy<opencl_nativize<output_value_type>>(
                left.size(),
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), is_contiguous_layout<left_layout_type> ? 1 : left.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("calculation failed (with code = {}, message = {})", int(status), clblast_error_message(status));
    }

    void opencl_add_scaled_mdspan_inplace ( auto scale, const auto right, auto output )
    {
        static_assert(is_contiguous_layout<right_layout_type>, "internal error");

        auto status = 
            clblast::Axpy<opencl_nativize<output_value_type>>(
                right.size(), 
                scale,
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), not is_strided_layout<right_layout_type> ? 1 : right.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("calculation failed (with code = {}, message = {})", int(status), clblast_error_message(status));
    }

    void opencl_multiply_matrix_inplace ( const auto& left, const auto& right, auto& output )
    {
        auto status = 
            clblast::Gemm<opencl_nativize<output_value_type>>(
                clblast::Layout::kColMajor,
                is_contiguous_layout<left_layout_type > ? clblast::Transpose::kNo : clblast::Transpose::kYes,
                is_contiguous_layout<right_layout_type> ? clblast::Transpose::kNo : clblast::Transpose::kYes,
                left.extent(0), right.extent(1), left.extent(1),
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), is_contiguous_layout<left_layout_type > ? left .extent(0) : left .extent(1),
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), is_contiguous_layout<right_layout_type> ? right.extent(0) : right.extent(1),
                0,
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extent(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("calculation failed (with code = {}, message = {})", int(status), clblast_error_message(status));
    }

} // namespace detail
