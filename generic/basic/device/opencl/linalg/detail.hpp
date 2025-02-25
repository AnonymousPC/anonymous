#pragma once

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
        static_assert ( left_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( is_contiguous_layout<left_layout_type> )
            return;
        else
            throw opencl_error("layout not supported on this device: should be contiguous");
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
        static_assert ( left_rank <= 2 and right_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( is_contiguous_layout<left_layout_type> and is_contiguous_layout<right_layout_type> )
            return;
        else
            throw opencl_error("layout not supported on this deivce: should be contiguous");
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
        static_assert ( left_rank <= 2 and right_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );

        if constexpr ( ( is_contiguous_layout<left_layout_type>  or is_transposed_layout<left_layout_type> ) and
                       ( is_contiguous_layout<right_layout_type> or is_transposed_layout<right_layout_type> ) )
            return;
        else
            throw opencl_error("layout not supported on this deivce: should be contiguous or transpose");
    }




    ///////////////////////////////////////////////////
    // 1. output_value_type -> decay<decltype(output)::value_type
    // 2. copy/scaled might allow strided.

    std::string clblast_error_message ( clblast::StatusCode ); // See detail.cpp

    void opencl_copy_mdspan ( const auto& left, auto& output )
    {
        let status =
            clblast::Copy<detail::opencl_nativize<output_value_type>>(
                left.size(),
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), is_contiguous_layout<left_layout_type> ? 1 otherwise left.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("linalg calculation failed (with device = {}, backend = {}, error_code = {}, message = {})",
                               typeid(opencl), "clblast", int(status), clblast_error_message(status));
    }

    void opencl_add_scaled_mdspan_inplace ( auto scale, const auto right, auto output )
    {
        static_assert(is_contiguous_layout<typename decay<decltype(right)::layout_type>, "internal error");

        let status = 
            clblast::Axpy<detail::opencl_nativize<output_value_type>>(
                right.size(), 
                scale,
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), not detail::is_strided_layout<right_layout_type> ? 1 otherwise right.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("linalg opencl/clblast backend throws an error (with code = {}, message = {})", int(status), clblast_error_message(status));
    }

    void opencl_multiply_matrix_inplace ( const auto& left, const auto& right, auto& output )
    {
        let status = 
            clblast::Gemm<detail::opencl_nativize<typename decay<decltype(output)>::value_type>>(
                clblast::Layout::kColMajor,
                detail::is_contiguous_layout<typename decay<decltype(left )::layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                detail::is_contiguous_layout<typename decay<decltype(right)::layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                left.extent(0), right.extent(1), left.extent(1),
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), detail::is_contiguous_layout<typename decay<decltype(left )::layout_type> ? left .extent(0) otherwise left .extent(1),
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), detail::is_contiguous_layout<typename decay<decltype(right)::layout_type> ? right.extent(0) otherwise right.extent(1),
                0,
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extent(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw opencl_error("linalg opencl/clblast backend throws an error (with code = {}, message = {})", int(status), detail::clblast_error_message(status));
    }



} // namespace detail

#if dll
    #include "detail.cpp"
#endif
