#pragma once

constexpr void opencl::linalg::multiply ( auto left, auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,float16_t> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device" );
    
    if constexpr ( not same_as<left_value_type,output_value_type> or detail::is_layout_stride<left_layout_type> )
    {
        vector<output_value_type> left_copy;
        if constexpr ( not detail::is_layout_stride<left_layout_type> )
            copy(left.data_handle(), left.size(), left_copy.data());
        else
            copy(stride_pointer(left.data_handle(), left.stride(0)), stride_pointer(left.data_handle() + left.size() * left.stride(0)), left_copy.data());
        return multiply(std::mdspan<output_value_type,std::dextents<2,int>>,layout_type,accessor_type<output_value_type>>(left_copy.data(), left.extents()), right, output);
    }
    else if constexpr ( not same_as<right_value_type,output_value_type> or detail::is_layout_stride<right_layout_type> )
    {
        vector<output_value_type> right_copy;
        if constexpr ( not detail::is_layout_stride<right_layout_type> )
            copy(right.data_handle(), right.size(), right_copy.data());
        else
            copy(stride_pointer(right.data_handle(), right.stride(0)), stride_pointer(right.data_handle() + right.size() * right.stride(0)), right_copy.data());
        return multiply(left, std::mdspan<output_value_type,std::dextents<2,int>>,layout_type,accessor_type<output_value_type>>(right_copy.data(), right.extents()), output);
    }

    // Run
    else
    {
        let status = 
            clblast::Gemm<detail::opencl_nativize<output_value_type>>(
                clblast::layout::kColMajor,
                not detail::is_layout_transpose<left_layout_type > ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                not detail::is_layout_transpose<right_layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                left.row(), left.column(), right.row(),
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), left  .extents(0),
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), right .extents(0),
                0,
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extents(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw linalg_error("linalg failed");
    }
}