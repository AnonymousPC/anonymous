namespace detail
{
    template < class type >
    concept is_contiguous_layout = same_as<type,std::layout_right> or same_as<type,std::layout_left>;

    template < class type >
    concept is_strided_layout = same_as<type,std::layout_stride>;

    template < class type >
    concept is_transposed_layout = same_as<type,std::layout_transpose<std::layout_right>> or same_as<type,std::layout_transpose<std::layout_left>>;

    template < class type >
    concept is_non_const_accessor = requires ( type::reference r, type::element_type e ) { r = e; };




    enum { eigen_map_default,
           eigen_map_vector,
           eigen_map_matrix,
           eigen_map_tensor };

    constexpr auto eigen_make_extents ( auto extents )
    {
        auto arr = std::array<int,extents.rank()>();
        for_constexpr<0,extents.rank()-1>([&] <int index> { arr[index] = extents.extent(index); });
        return arr;
    }

    constexpr auto eigen_make_stride_extents ( auto extents, auto mapping )
    {
        auto arr = std::array<int,extents.rank()+1>();
        for_constexpr<0,extents.rank()-1>([&] <int index> { arr[index] = extents.extent(index); });
        arr[extents.rank()] = mapping.stride(0);
        return arr;
    }

    constexpr auto eigen_make_transpose_extents ( auto extents )
    {
        auto arr = std::array<int,extents.rank()>();
        for_constexpr<0,extents.rank()-1>([&] <int index> { arr[index] = extents.extent(extents.rank()-index-1); });
        return arr;
    }

    template < int rank >
    constexpr auto eigen_make_transpose_shuffle ( )
    {
        auto arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = rank - index - 1; });
        return arr;
    }

    template < auto mode >
    constexpr auto eigen_map_helper ( auto mdspan )
    {
        static_assert ( same_as<typename cpu::layout_type,std::layout_right> );

        if constexpr ( ( mode == eigen_map_default and mdspan.rank() == 1 ) or mode == eigen_map_vector )
            if constexpr ( is_contiguous_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::Map<      Eigen::Vector<mdspan_value_type,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size());
                else  
                    return Eigen::Map<const Eigen::Vector<mdspan_value_type,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size());
            else // if constexpr ( is_strided_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::Map<      Eigen::Vector<mdspan_value_type,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size(), mdspan.stride(0));
                else
                    return Eigen::Map<const Eigen::Vector<mdspan_value_type,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mdspan.data_handle(), mdspan.size(), mdspan.stride(0));
        else if constexpr ( ( mode == eigen_map_default and mdspan.rank() == 2 ) or mode == eigen_map_matrix )
            if constexpr ( is_contiguous_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1));
                else 
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1));
            else if constexpr ( is_strided_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mdspan.stride(0), mdspan.stride(1)));
                else
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mdspan.data_handle(), mdspan.extent(0), mdspan.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mdspan.stride(0), mdspan.stride(1)));
            else // if constexpr ( is_transposed_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(1), mdspan.extent(0)).transpose();
                else
                    return Eigen::Map<const Eigen::Matrix<mdspan_value_type,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mdspan.data_handle(), mdspan.extent(1), mdspan.extent(0)).transpose();
        else // if constexpr ( ( mode == eigen_map_default and mdspan.rank() >= 3 ) or mode == eigen_map_tensor )
            if constexpr ( is_contiguous_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )   
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents()));
                else
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_extents(mdspan.extents()));
            else if constexpr ( is_strided_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank()+1,Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_strided_full_extents(mdspan.extents(), mdspan.mapping())).template chip<mdspan.rank()>(0).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
                else
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank()+1,Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_strided_full_extents(mdspan.extents(), mdspan.mapping())).template chip<mdspan.rank()>(0).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
            else // if constexpr ( is_transposed_layout<mdspan_layout_type> )
                if constexpr ( is_non_const_accessor<mdspan_accessor_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_transpose_extents(mdspan.extents())).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
                else 
                    return Eigen::TensorMap<const Eigen::Tensor<mdspan_value_type,mdspan.rank(),Eigen::RowMajor>>(mdspan.data_handle(), eigen_make_transpose_extents(mdspan.extents())).shuffle(eigen_make_transpose_shuffle<mdspan.rank()>());
    }

    template < class type = void, auto mode = eigen_map_default >
    constexpr auto eigen_map ( auto mdspan )
    {
        if constexpr ( is_void<type> or same_as<type,mdspan_value_type> )
            return eigen_map_helper<mode>(mdspan);
        else
            return eigen_map_helper<mode>(mdspan).template cast<type>();
    }





    template < int rank >
    constexpr auto eigen_make_convolve_full_dims ( )
    {
        auto arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = index; });
        return arr;
    }

} // namespace detail




/* Case: rank() >= 3, is_strided_layout
 * Eigen::TensorMap does not provides Eigen::Stride template,
 * so that it's essential for us to manual map data into Eigen.
 * 
 * Consider this array<int,5> (with shape = {2, 2, 2, 2, 2}):
 * {{{{{1  2 } 
 *     {3  4 }} 
 *
 *    {{5  6 } 
 *     {7  8 }}} 
 *
 *
 *   {{{9  10} 
 *     {11 12}} 
 *
 *    {{13 14} 
 *     {15 16}}}} 
 *
 *
 *
 *  {{{{17 18} 
 *     {19 20}} 
 * 
 *    {{21 22} 
 *     {23 24}}} 
 * 
 * 
 *   {{{25 26} 
 *     {27 28}} 
 * 
 *    {{29 30} 
 *     {31 32}}}}}
 * 
 * whose flatten() =
 * {1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32}
 * 
 * and whose transpose()[1][1] =
 * {{{1  17} 
 *   {9  25}} 
 * 
 *  {{5  21} 
 *   {13 29}}}
 * with extents() = {2, 2, 2}, strides = {4, 8, 16}
 * 
 * We wanna map the latter one into Eigen::TensorMap. Obviously, The total size should be 32,
 * which equals to extents().product() * strides[1].
 * 
 * Overall, all we need to do is:
 * 1. Create a full Eigen::TensorMap with full size (of whole mapped array), 
 *    rank = extents.rank() + 1, starting with mdspan.data_handle(), shape = {extents()..., strides[1]}
 * 2. chip<last_dimension()[1]
 * 3. transpose it.
 * 
 * We need these guarantees:
 * 1. is_strided_layout == true if and only if array.get_attribute() == columns_attribute.
 */
