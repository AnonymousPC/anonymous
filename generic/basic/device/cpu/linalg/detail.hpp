#pragma once

namespace detail
{
    template < class type >
    struct is_mdspan_helper
    {
        constexpr static const bool value = false;
    };

    template < class type, class extents_type, class layout_type, class accessor_type >
    struct is_mdspan_helper<std::mdspan<type,extents_type,layout_type,accessor_type>>
    {
        constexpr static const bool value = true;
    };

    template < class type >
    concept is_mdspan = is_mdspan_helper<remove_cvref<type>>::value;

    template < class type >
    concept is_contiguous_layout = same_as<type,std::layout_right> or same_as<type,std::layout_left>;

    template < class type >
    concept is_strided_layout = same_as<type,std::layout_stride>;

    template < class type >
    concept is_transposed_layout = same_as<type,std::layout_transpose<std::layout_right>> or same_as<type,std::layout_transpose<std::layout_left>>;

    template < class type >
    concept is_non_const_accessor = requires ( type::reference r, type::element_type e ) { r = e; };

    constexpr void trivial_linalg_unary_operator ( const auto right, auto output, auto op, int_type auto... idx )
    {
        if constexpr ( sizeof...(idx) == right_rank )   
            output[idx...] = op(right[idx...]);
        else
            for ( int i in range(0, right.extents().extent(sizeof...(idx))-1) )
                trivial_linalg_unary_operator(right, output, op, i);   
    }

    constexpr void trivial_linalg_binary_operator ( const auto left, const auto right, auto output, auto op, int_type auto... idx )
    {
        if constexpr ( sizeof...(idx) == left_rank )
            output[idx...] = op(left[idx...], right[idx...]);
        else
            for ( int i in range(0, left.extents().extent(sizeof...(idx))-1) )
                trivial_linalg_binary_operator(left, right, output, op, i);
    }

    constexpr void trivial_linalg_matrix_multiply ( const auto left, const auto right, auto output )
    {
        static_assert ( left_rank == 2 and right_rank == 2 and output_rank == 2 );
        for ( int i in range(0, left.extents().extent(0)-1) )
            for ( int j in range(0, right.extents().extent(0)-1) )
                for ( int k in range(0, left.extents().extent(1)-1) )
                    output[i, j] += left[i, k] * right[k, j];            
    }

    
} // namespace detail
