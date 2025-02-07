#pragma once

#include "detail.hpp"

#define left_value_type    typename decltype(left  )::value_type
#define left_layout_type   typename decltype(left  )::layout_type
#define right_value_type   typename decltype(right )::value_type
#define right_layout_type  typename decltype(right )::layout_type
#define output_value_type  typename decltype(output)::value_type
#define output_layout_type typename decltype(output)::layout_type

constexpr void opencl::linalg::multiply ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,float16_t> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device" );
    
    if constexpr ( not same_as<left_value_type,output_value_type> or detail::is_strided_layout<left_layout_type> )
    {
        let [left_copy, left_copy_mdspan] = detail::opencl_copy_mdspan<output_value_type>(left);
        return multiply(left_copy_mdspan, right, output);
    }
    else if constexpr ( not same_as<right_value_type,output_value_type> or detail::is_strided_layout<right_layout_type> )
    {
        let [right_copy, right_copy_mdspan] = detail::opencl_copy_mdspan<output_value_type>(right);
        return multiply(left, right_copy_mdspan, output);
    }

    // Run
    else
    {
        let status = 
            clblast::Gemm<detail::opencl_nativize<output_value_type>>(
                clblast::Layout::kColMajor,
                not detail::is_transposed_layout<left_layout_type > ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                not detail::is_transposed_layout<right_layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                left.extents().extent(0), left.extents().extent(1), right.extents().extent(1),
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), left  .extents().extent(0),
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), right .extents().extent(0),
                0,
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extents().extent(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status != clblast::StatusCode::kSuccess )
            throw linalg_error("linalg failed");
    }
}

#undef left_value_type
#undef left_layout_type
#undef right_value_type
#undef right_layout_type
#undef output_value_type
#undef output_layout_type