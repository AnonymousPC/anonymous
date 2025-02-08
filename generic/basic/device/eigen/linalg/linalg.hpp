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

constexpr void eigen::linalg::unary_plus ( const auto right, auto output )
{
    static_assert ( number_type<right_value_type> or complex_type<right_value_type>,
                    "value_type not supported on this device: should be a number" );
    static_assert ( right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );
    detail::eigen_map(output) = + detail::eigen_map<output_value_type>(right);
}

constexpr void eigen::linalg::unary_minus ( const auto right, auto output )
{
    static_assert ( number_type<right_value_type> or complex_type<right_value_type>,
                    "value_type not supported on this device: should be a number" );
    static_assert ( right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );
    detail::eigen_map(output) = - detail::eigen_map<output_value_type>(right);
}

constexpr void eigen::linalg::plus ( const auto left, const auto right, auto output )
{
    static_assert ( ( number_type<left_value_type > or complex_type<left_value_type > ) and
                    ( number_type<right_value_type> or complex_type<right_value_type> ),
                    "value_type not supported on this device: should be a number" );
    static_assert ( left_rank <= 2 and right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );
    detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) + detail::eigen_map<output_value_type>(right);
}

constexpr void eigen::linalg::minus ( const auto left, const auto right, auto output )
{
    static_assert ( ( number_type<left_value_type > or complex_type<left_value_type > ) and
                    ( number_type<right_value_type> or complex_type<right_value_type> ),
                    "value_type not supported on this device: should be a number" );
    static_assert ( left_rank <= 2 and right_rank <= 2,
                    "dimension not supported on this device: should be no more than matrix" );
    detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) - detail::eigen_map<output_value_type>(right);
}

constexpr void eigen::linalg::multiply ( const auto left, const auto right, auto output )
{
    if constexpr ( detail::is_mdspan<left_type> and detail::is_mdspan<right_type> )
    {
        static_assert ( ( number_type<left_value_type > or complex_type<left_value_type > ) and
                        ( number_type<right_value_type> or complex_type<right_value_type> ) and 
                        "value_type not supported on this device: should be a number" );
        static_assert ( left_rank <= 2 and right_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );
        detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) * detail::eigen_map<output_value_type>(right);
    }
    else if constexpr ( detail::is_mdspan<left_type> )
    {
        static_assert ( ( number_type<left_value_type> or complex_type<left_value_type> ) and
                        ( number_type<right_type     > or complex_type<right_type>      ),
                        "value_type not supported on this device: should be a number" );
        static_assert ( left_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );
        detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) * right;
    }

    else if constexpr ( detail::is_mdspan<right_type> )
    {
        static_assert ( ( number_type<left_type       > or complex_type<left_type       > ) and
                        ( number_type<right_value_type> or complex_type<right_value_type> ) and
                        "value_type not supported on this device: should be a number" );
        static_assert ( right_rank <= 2,
                        "dimension not supported on this device: should be no more than matrix" );
        detail::eigen_map(output) = left * detail::eigen_map<output_value_type>(right);
    }
    else 
        static_assert(false, "invalid parameter");
}

constexpr void eigen::linalg::divide ( const auto left, const auto right, auto output )
{
    static_assert ( ( number_type<left_value_type > or complex_type<left_value_type > ) and
                    ( number_type<right_type      > or complex_type<right_type      > ) 
                    ( left_rank <= 2 ), 
                    "not supported on this device" );
    detail::eigen_map(output) = detail::eigen_map<output_value_type>(left) / right;
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



