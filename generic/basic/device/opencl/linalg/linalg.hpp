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

constexpr void opencl::linalg::unary_plus ( const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( right_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(1, right, output);
    else // if constexpr ( right_rank == 2 )
        unary_plus(std::mdspan<const right_value_type, std::dextents<int,1>,typename opencl::layout_type,right_accessor_type >(right .data_handle(), right .size()),
                   std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::unary_minus ( const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( right_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(-1, right, output);
    else // if constexpr ( right_rank == 2 )
        unary_minus(std::mdspan<const right_value_type, std::dextents<int,1>,typename opencl::layout_type,right_accessor_type >(right .data_handle(), right .size()),
                    std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::plus ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, right, output);

    if constexpr ( left_rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(1, right, output);
    }
    else // if constexpr ( left_rank == 2 )
        plus(std::mdspan<const left_value_type,  std::dextents<int,1>,typename opencl::layout_type,left_accessor_type  >(left  .data_handle(), left  .size()),
             std::mdspan<const right_value_type, std::dextents<int,1>,typename opencl::layout_type,right_accessor_type >(right .data_handle(), right .size()),
             std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::minus ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, right, output);

    if constexpr ( left_rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(-1, right, output);
    }
    else // if constexpr ( left_rank == 2 )
        minus(std::mdspan<const left_value_type,  std::dextents<int,1>,typename opencl::layout_type,left_accessor_type  >(left  .data_handle(), left  .size()),
              std::mdspan<const right_value_type, std::dextents<int,1>,typename opencl::layout_type,right_accessor_type >(right .data_handle(), right .size()),
              std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::left_scale ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( right_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(left, right, output);
    else // if constexpr ( right_rank == 2 )
        left_scale(left,
                   std::mdspan<const right_value_type, std::dextents<int,1>,typename opencl::layout_type,right_accessor_type >(right .data_handle(), right .size()),
                   std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::right_scale ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, output);

    if constexpr ( left_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(right, left, output);
    else // if constexpr ( left_rank == 2 )
        right_scale(std::mdspan<const left_value_type,  std::dextents<int,1>,typename opencl::layout_type,left_accessor_type  >(left  .data_handle(), left  .size()),
                    right,
                    std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::multiply ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan_allow_transpose(left, right, output);
    detail::opencl_multiply_matrix_inplace     (left, right, output);
}

constexpr void opencl::linalg::divide ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, output);

    if constexpr ( left_rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(1 / right, left, output); // As right is always float_type (or complex<float_type>).
    else // if constexpr ( left_rank == 2 )
        divide(std::mdspan<const left_value_type,  std::dextents<int,1>,typename opencl::layout_type,left_accessor_type  >(left  .data_handle(), left  .size()),
               right,
               std::mdspan<      output_value_type,std::dextents<int,1>,typename opencl::layout_type,output_accessor_type>(output.data_handle(), output.size()));
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