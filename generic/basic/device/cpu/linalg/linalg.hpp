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

constexpr void cpu::linalg::unary_plus ( const auto right, auto output )
{
    if constexpr ( detail::is_contiguous_layout<right_layout_type > and
                   detail::is_contiguous_layout<output_layout_type> )
        std::transform(right.data_handle(), right.data_handle() + right.size(), output.data_handle(), [] (const auto& a) { return +a; });
    else
        detail::trivial_linalg_unary_operator(right, output, [] (const auto& a) { return +a; });
}

constexpr void cpu::linalg::unary_minus ( const auto right, auto output )
{
    if constexpr ( detail::is_contiguous_layout<right_layout_type > and
                   detail::is_contiguous_layout<output_layout_type> )
        std::transform(right.data_handle(), right.data_handle() + right.size(), output.data_handle(), [] (const auto& a) { return -a; });
    else
        detail::trivial_linalg_unary_operator(right, output, [] (const auto& a) { return -a; });
}

constexpr void cpu::linalg::plus ( const auto left, const auto right, auto output )
{
    if constexpr ( detail::is_contiguous_layout<left_layout_type  > and
                   detail::is_contiguous_layout<right_layout_type > and 
                   detail::is_contiguous_layout<output_layout_type> )
        std::transform(left.data_handle(), left.data_handle() + left.size(), right.data_handle(), output.data_handle(), std::plus<>());
    else
        detail::trivial_linalg_binary_operator(left, right, output, [] (const auto& a, const auto& b) { return a + b; });
}

constexpr void cpu::linalg::minus ( const auto left, const auto right, auto output )
{
    if constexpr ( detail::is_contiguous_layout<left_layout_type  > and
                   detail::is_contiguous_layout<right_layout_type > and 
                   detail::is_contiguous_layout<output_layout_type> )
        std::transform(left.data_handle(), left.data_handle() + left.size(), right.data_handle(), output.data_handle(), std::minus<>());
    else
        detail::trivial_linalg_binary_operator(left, right, output, [] (const auto& a, const auto& b) { return a - b; });
}

constexpr void cpu::linalg::multiply ( const auto left, const auto right, auto output )
{
    if constexpr ( detail::is_mdspan<left_type> and detail::is_mdspan<right_type> )
        detail::trivial_linalg_matrix_multiply(left, right, output);
    else if constexpr ( detail::is_mdspan<left_type> )
        if constexpr ( detail::is_contiguous_layout<left_layout_type  > and
                       detail::is_contiguous_layout<output_layout_type> )
            std::transform(left.data_handle(), left.data_handle() + left.size(), output.data_handle(), [&] (const auto& a) { return a * right; });
        else
            detail::trivial_linalg_unary_operator(left, output, [&] (const auto& a) { return a * right; });
    else if constexpr ( detail::is_mdspan<right_type> )
        if constexpr ( detail::is_contiguous_layout<right_layout_type > and 
                       detail::is_contiguous_layout<output_layout_type> )
            std::transform(right.data_handle(), right.data_handle() + right.size(), output.data_handle(), [&] (const auto& a) { return left * a; });
        else
            detail::trivial_linalg_unary_operator(right, output, [&] (const auto& a) { return left * a; });
    else
        static_assert(false, "invalid parameter");
}

constexpr void cpu::linalg::divide ( const auto left, const auto right, auto output )
{
    if constexpr ( detail::is_contiguous_layout<right_layout_type > and
                   detail::is_contiguous_layout<output_layout_type> )
        std::transform(left.data_handle(), left.data_handle() + left.size(), output.data_handle(), [&] (const auto& a) { return a / right; });
    else
        detail::trivial_linalg_unary_operator(left, output, [&] (const auto& a) { return a / right; });
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