#include "detail/mapping.cpp"

constexpr void opencl::linalg::unary_plus ( const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( decltype(right )::rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(1, right, output);
    else // if constexpr ( decltype(right )::rank == 2 )
        unary_plus(std::mdspan<const typename decltype(right )::value_type, std::dextents<int,1>,typename opencl::layout_type,typename decltype(right )::accessor_type >(right .data_handle(), right .size()),
                   std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::unary_minus ( const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( decltype(right )::rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(-1, right, output);
    else // if constexpr ( decltype(right )::rank == 2 )
        unary_minus(std::mdspan<const typename decltype(right )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(right )::accessor_type>(right .data_handle(), right .size()),
                    std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::plus ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, right, output);

    if constexpr ( decltype(left  )::rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(1, right, output);
    }
    else // if constexpr ( decltype(left  )::rank == 2 )
        plus(std::mdspan<const typename decltype(left  )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(left  )::accessor_type>(left  .data_handle(), left  .size()),
             std::mdspan<const typename decltype(right )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(right )::accessor_type>(right .data_handle(), right .size()),
             std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::minus ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, right, output);

    if constexpr ( decltype(left  )::rank == 1 )
    {
        detail::opencl_copy_mdspan(left, output);
        detail::opencl_add_scaled_mdspan_inplace(-1, right, output);
    }
    else // if constexpr ( decltype(left  )::rank == 2 )
        minus(std::mdspan<const typename decltype(left  )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(left  )::accessor_type>(left  .data_handle(), left  .size()),
              std::mdspan<const typename decltype(right )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(right )::accessor_type>(right .data_handle(), right .size()),
              std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::left_scale ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(right, output);

    if constexpr ( decltype(right )::rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(left, right, output);
    else // if constexpr ( decltype(right )::rank == 2 )
        left_scale(left,
                   std::mdspan<const typename decltype(right )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(right )::accessor_type>(right .data_handle(), right .size()),
                   std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::right_scale ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, output);

    if constexpr ( decltype(left  )::rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(right, left, output);
    else // if constexpr ( decltype(left  )::rank == 2 )
        right_scale(std::mdspan<const typename decltype(left  )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(left  )::accessor_type>(left  .data_handle(), left  .size()),
                    right,
                    std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}

constexpr void opencl::linalg::multiply ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan_allow_transpose(left, right, output);
    detail::opencl_multiply_matrix_inplace     (left, right, output);
}

constexpr void opencl::linalg::divide ( const auto left, const auto right, auto output )
{
    detail::opencl_check_mdspan(left, output);

    if constexpr ( decltype(left  )::rank == 1 )
        detail::opencl_add_scaled_mdspan_inplace(1 / right, left, output); // As right is always float_type (or complex<float_type>).
    else // if constexpr ( decltype(left  )::rank == 2 )
        divide(std::mdspan<const typename decltype(left  )::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(left  )::accessor_type>(left  .data_handle(), left  .size()),
               right,
               std::mdspan<      typename decltype(output)::value_type,std::dextents<int,1>,typename opencl::layout_type,typename decltype(output)::accessor_type>(output.data_handle(), output.size()));
}