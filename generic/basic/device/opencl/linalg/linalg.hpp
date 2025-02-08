#pragma once

#define left_type                    decltype(left  )
#define left_value_type     typename decltype(left  )::value_type
#define left_extents_type   typename decltype(left  )::extents_type
#define left_layout_type    typename decltype(left  )::layout_type
#define left_rank                    decltype(left  )::extents_type::rank()
#define right_type                   decltype(right )
#define right_value_type    typename decltype(right )::value_type
#define right_extents_type  typename decltype(right )::extents_type
#define right_layout_type   typename decltype(right )::layout_type
#define right_rank                   decltype(right )::rank()
#define output_type                  decltype(output)
#define output_value_type   typename decltype(output)::value_type
#define output_layout_type  typename decltype(output)::layout_type
#define output_extents_type typename decltype(output)::extents_type
#define output_rank                  decltype(output)::rank()

#include "detail.hpp"

// constexpr void opencl::linalg::unary_plus ( const auto right, auto output )
// {
//     // Check
//     static_assert ( same_as<output_value_type,cl_half> or 
//                     same_as<output_value_type,float32_t> or
//                     same_as<output_value_type,float64_t> or
//                     same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
//                     same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
//                     "value_type not supported on this device" );

//     // Run 
//     if constexpr ( not same_as)
// }

constexpr void opencl::linalg::plus ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device" );
    static_assert ( same_as<left_value_type,right_value_type>, 
                    "not supported on this device" )
    static_assert ( left_rank <= 2 and right_rank <= 2,
                    "not supported on this device" );

    // Run
    if constexpr ( left_rank == 1 )
    {
        let status1 =
            clblast::Copy<detail::opencl_nativize<output_value_type>>(
                left.size(),
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), not detail::is_strided_layout<left_layout_type> ? 1 otherwise left.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status1 != clblast::StatusCode::kSuccess )
            throw opencl_error("clblast error (with code = {}, message = {})", int(status1), detail::clblast_error_message(status1));

        let status2 = 
            clblast::Axpy<detail::opencl_nativize<output_value_type>>(
                left.size(), 
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), not detail::is_strided_layout<left_layout_type> ? 1 otherwise left.stride(0),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), 1,
                &opencl::execution_context.command_queue().get()
            );
        if ( status2 != clblast::StatusCode::kSuccess )
            throw opencl_error("clblast error (with code = {}, message = {})", int(status2), detail::clblast_error_message(status2));
    }
    else if constexpr ( left_rank == 2 )
    {
        if constexpr ( detail::is_strided_layout<left_layout_type > or  
                       detail::is_strided_layout<right_layout_type> )
            throw opencl_error("plus strided matrix is not supported on this device");

        if constexpr ( not detail::is_transposed_layout<left_value_type > and
                       not detail::is_transposed_layout<right_value_type> )
            plus ( std::mdspan<left_value_type,)

        let status1 = 
            clblast::Omatcopy<detail::opencl_nativize<output_value_type>>(
                clblast::Layout::kColMajor,
                not detail::is_transposed_layout<left_layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                left.extents().extent(0), left.extents().extent(1),
                1,
                left  .data_handle().get_buffer().get(), left  .data_handle().get_index(), not detail::is_transposed_layout<left_layout_type> ? left.extents().extent(0) otherwise left.extents().extent(1),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extents().extent(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status1 != clblast::StatusCode::kSuccess )
            throw opencl_error("clblast error (with code = {}, message = {})", int(status1), detail::clblast_error_message(status1));

        let status2 = 
            clblast::Omatcopy<detail::opencl_nativize<output_value_type>>(
                clblast::Layout::kColMajor,
                not detail::is_transposed_layout<right_layout_type> ? clblast::Transpose::kNo otherwise clblast::Transpose::kYes,
                right.extents().extent(0), left.extents().extent(1),
                1,
                right .data_handle().get_buffer().get(), right .data_handle().get_index(), not detail::is_transposed_layout<right_layout_type> ? right.extents().extent(0) otherwise right.extents().extent(1),
                output.data_handle().get_buffer().get(), output.data_handle().get_index(), output.extents().extent(0),
                &opencl::execution_context.command_queue().get()
            );
        if ( status2 != clblast::StatusCode::kSuccess )
            throw opencl_error("clblast error (with code = {}, message = {})", int(status2), detail::clblast_error_message(status2));
    }
}

constexpr void opencl::linalg::multiply ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device" );
    
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
        throw opencl_error("clblast error (with code = {}, message = {})", int(status), detail::clblast_error_message(status));
}

#undef left_type
#undef left_value_type
#undef left_extents_type
#undef left_layout_type
#undef left_rank
#undef right_type
#undef right_value_type
#undef right_extents_type
#undef right_layout_type
#undef right_rank
#undef output_type
#undef output_value_type
#undef output_extents_type
#undef output_layout_type
#undef output_rank