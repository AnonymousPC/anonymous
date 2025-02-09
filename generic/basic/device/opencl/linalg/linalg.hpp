#pragma once

#define left_type                     decltype(left  )
#define left_value_type      typename decltype(left  )::value_type
#define left_extents_type    typename decltype(left  )::extents_type
#define left_layout_type     typename decltype(left  )::layout_type
#define left_accessor_type   typename decltype(left  )::accessor_type
#define left_rank                     decltype(left  )::extents_type::rank()
#define right_type                    decltype(right )
#define right_value_type     typename decltype(right )::value_type
#define right_extents_type   typename decltype(right )::extents_type
#define right_layout_type    typename decltype(right )::layout_type
#define right_accessor_type  typename decltype(right )::accessor_type
#define right_rank                    decltype(right )::rank()
#define output_type                   decltype(output)
#define output_value_type    typename decltype(output)::value_type
#define output_layout_type   typename decltype(output)::layout_type
#define output_extents_type  typename decltype(output)::extents_type
#define output_rank                   decltype(output)::rank()
#define output_accessor_type typename decltype(output)::accessor_type

#include "detail.hpp"

constexpr void opencl::linalg::plus ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device: should be one of { half, float, double, complex<float>, complex<double> }" );
    static_assert ( same_as<left_value_type,right_value_type>, 
                    "value_type not supported on this device: should be same" );
    static_assert ( left_rank <= 2 and right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );

    // Run
    if constexpr ( left_rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(1, right, output);
    }
    else if constexpr ( left_rank == 2 )
    {
        if constexpr ( detail::is_contiguous_layout<left_layout_type> and detail::is_contiguous_layout<right_layout_type> )
            plus(std::mdspan<const left_value_type,  std::dextents<int,1>,left_layout_type,  left_accessor_type  >(left  .data_handle(), left  .size()),
                 std::mdspan<const right_value_type, std::dextents<int,1>,right_layout_type, right_accessor_type >(right .data_handle(), right .size()),
                 std::mdspan<      output_value_type,std::dextents<int,1>,output_layout_type,output_accessor_type>(output.data_handle(), output.size()));
        else
            throw opencl_error("plus strided or transposed matrix is not supported on this device");
    }
}

constexpr void opencl::linalg::minus ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device: should be one of { half, float, double, complex<float>, complex<double> }" );
    static_assert ( same_as<left_value_type,right_value_type>, 
                    "value_type not supported on this device: should be same" );
    static_assert ( left_rank <= 2 and right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );

    // Run
    if constexpr ( left_rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(-1, right, output);
    }
    else if constexpr ( left_rank == 2 )
    {
        if constexpr ( detail::is_contiguous_layout<left_layout_type> and detail::is_contiguous_layout<right_layout_type> )
            minus(std::mdspan<const left_value_type,  std::dextents<int,1>,left_layout_type,  left_accessor_type  >(left  .data_handle(), left  .size()),
                  std::mdspan<const right_value_type, std::dextents<int,1>,right_layout_type, right_accessor_type >(right .data_handle(), right .size()),
                  std::mdspan<      output_value_type,std::dextents<int,1>,output_layout_type,output_accessor_type>(output.data_handle(), output.size()));
        else
            throw opencl_error("minus strided or transposed matrix is not supported on this device");
    }
}

constexpr void opencl::linalg::left_scale ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device: should be one of { half, float, double, complex<float>, complex<double> }" );
    static_assert ( right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );

    // Run
    if constexpr ( right_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(left, right, output);
    else if constexpr ( right_rank == 2 )
    {
        if constexpr ( detail::is_contiguous_layout<left_layout_type> )
            left_scale(left,
                       std::mdspan<const right_value_type, std::dextents<int,1>,right_layout_type, right_accessor_type >(right .data_handle(), right .size()),
                       std::mdspan<      output_value_type,std::dextents<int,1>,output_layout_type,output_accessor_type>(output.data_handle(), output.size()));
        else
            throw opencl_error("left_scale strided or transposed matrix is not supported on this device");
    }
}

constexpr void opencl::linalg::right_scale ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device: should be one of { half, float, double, complex<float>, complex<double> }" );
    static_assert ( left_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );

    // Run
    if constexpr ( left_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(right, left, output);
    else if constexpr ( left_rank == 2 )
    {
        if constexpr ( detail::is_contiguous_layout<left_layout_type> )
            right_scale(std::mdspan<const left_value_type,  std::dextents<int,1>,left_layout_type,  left_accessor_type  >(left  .data_handle(), left  .size()),
                        right,
                        std::mdspan<      output_value_type,std::dextents<int,1>,output_layout_type,output_accessor_type>(output.data_handle(), output.size()));
        else
            throw opencl_error("right_scale strided or transposed matrix is not supported on this device");
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
    static_assert ( same_as<left_value_type,right_value_type>, 
                    "value_type not supported on this device: should be same" );
    
    if constexpr ( ( detail::is_contiguous_layout<left_layout_type>  or detail::is_transposed_layout<left_layout_type>  ) and 
                   ( detail::is_contiguous_layout<right_layout_type> or detail::is_transposed_layout<right_layout_type> ) )
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
            throw opencl_error("clblast error (with code = {}, message = {})", int(status), detail::clblast_error_message(status));
    }
    else
        throw opencl_error("multiply strided matrix is not supported on this device");
}

constexpr void opencl::linalg::divide ( const auto left, const auto right, auto output )
{
    // Check
    static_assert ( same_as<output_value_type,cl_half> or 
                    same_as<output_value_type,float32_t> or
                    same_as<output_value_type,float64_t> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float32_t>> or
                    same_as<detail::opencl_nativize<output_value_type>,std::complex<float64_t>>,
                    "value_type not supported on this device: should be one of { half, float, double, complex<float>, complex<double> }" );
    static_assert ( left_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );

    // Run
    if constexpr ( left_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(1 / right, left, output); // As right is always float_type (or complex<float_type>).
    else if constexpr ( left_rank == 2 )
    {
        if constexpr ( detail::is_contiguous_layout<left_layout_type> )
            divide(std::mdspan<const left_value_type,  std::dextents<int,1>,left_layout_type,  left_accessor_type  >(left  .data_handle(), left  .size()),
                   right,
                   std::mdspan<      output_value_type,std::dextents<int,1>,output_layout_type,output_accessor_type>(output.data_handle(), output.size()));
        else
            throw opencl_error("divide strided or transposed matrix is not supported on this device");
    }
}

#undef left_type
#undef left_value_type
#undef left_extents_type
#undef left_layout_type
#undef left_accessor_type
#undef left_rank
#undef right_type
#undef right_value_type
#undef right_extents_type
#undef right_layout_type
#undef right_accessor_type
#undef right_rank
#undef output_type
#undef output_value_type
#undef output_extents_type
#undef output_layout_type
#undef output_accessor_type
#undef output_rank