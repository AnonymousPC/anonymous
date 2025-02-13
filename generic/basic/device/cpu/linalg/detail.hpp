#pragma once

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






    template < class input_type >
    struct eigen_nativize_helper
    {
        using type = input_type;
    };

    template < complex_type input_type >
    struct eigen_nativize_helper<input_type>
    {
        using type = std::complex<typename input_type::value_type>;
    };

    template < class type >
    using eigen_nativize = eigen_nativize_helper<type>::type;






    constexpr auto eigen_make_extents ( const auto& extents )
    {
        constexpr int rank = decay<decltype(extents)>::rank();
        let arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = extents.extent(index); });
        return arr;
    }

    constexpr auto eigen_make_strided_full_extents ( const auto& extents, const auto& mapping )
    {
        constexpr int rank = decay<decltype(extents)>::rank();
        let arr = std::array<int,rank+1>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = extents.extent(index); });
        arr[rank] = mapping.stride(0);
        return arr;
    }

    constexpr auto eigen_make_stride ( const auto& mapping )
    {
        constexpr int rank = decay<decltype(mapping)>::extents_type::rank();
        let arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = mapping.stride(index); });
        return arr;
    }

    constexpr auto eigen_make_transpose_extents ( const auto& extents )
    {
        constexpr int rank = decay<decltype(extents)>::rank();
        let arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = extents.extent(rank-index-1); });
        return arr;
    }

    template < int rank >
    constexpr auto eigen_make_transpose_shuffle ( )
    {
        let arr = std::array<int,rank>();
        for_constexpr<0,rank-1>([&] <int index> { arr[index] = rank - index - 1; });
        return arr;
    }







    constexpr auto eigen_map_helper ( const auto& mds )
    {
        using value_type    = decay<decltype(mds)>::value_type;
        using extents_type  = decay<decltype(mds)>::extents_type;
        using layout_type   = decay<decltype(mds)>::layout_type;
        using accessor_type = decay<decltype(mds)>::accessor_type; 

        static_assert ( same_as<typename cpu::layout_type,std::layout_right> );

        if constexpr ( extents_type::rank() == 1 )
            if constexpr ( is_contiguous_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
                else  
                    return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
            else // if constexpr ( is_strided_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
                else
                    return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
        else if constexpr ( extents_type::rank() == 2 )
            if constexpr ( is_contiguous_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extent(0), mds.extent(1));
                else 
                    return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extent(0), mds.extent(1));
            else if constexpr ( is_strided_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extent(0), mds.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
                else
                    return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extent(0), mds.extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
            else // if constexpr ( is_transposed_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extent(1), mds.extent(0)).transpose();
                else
                    return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extent(1), mds.extent(0)).transpose();
        else // if constexpr ( extents_type::rank() >= 3 )
            if constexpr ( is_contiguous_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )   
                    return Eigen::TensorMap<      Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank(),Eigen::RowMajor>>(mds.data_handle(), eigen_make_extents(mds.extents()));
                else
                    return Eigen::TensorMap<const Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank(),Eigen::RowMajor>>(mds.data_handle(), eigen_make_extents(mds.extents()));
            else if constexpr ( is_strided_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank()+1,Eigen::RowMajor>>(mds.data_handle(), eigen_make_strided_full_extents(mds.extents(), mds.mapping())).template chip<extents_type::rank()>(0).shuffle(eigen_make_transpose_shuffle<extents_type::rank()>());
                else
                    return Eigen::TensorMap<const Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank()+1,Eigen::RowMajor>>(mds.data_handle(), eigen_make_strided_full_extents(mds.extents(), mds.mapping())).template chip<extents_type::rank()>(0).shuffle(eigen_make_transpose_shuffle<extents_type::rank()>());
            else // if constexpr ( is_transposed_layout<layout_type> )
                if constexpr ( is_non_const_accessor<accessor_type> )
                    return Eigen::TensorMap<      Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank(),Eigen::RowMajor>>(mds.data_handle(), eigen_make_transpose_extents(mds.extents())).shuffle(eigen_make_transpose_shuffle<extents_type::rank()>());
                else 
                    return Eigen::TensorMap<const Eigen::Tensor<eigen_nativize<value_type>,extents_type::rank(),Eigen::RowMajor>>(mds.data_handle(), eigen_make_transpose_extents(mds.extents())).shuffle(eigen_make_transpose_shuffle<extents_type::rank()>());
    }

    template < class type = void >
    constexpr auto eigen_map ( const auto& mds )
    {
        using value_type = decay<decltype(mds)>::value_type;

        if constexpr ( is_void<type> or same_as<type,value_type> )
            return eigen_map_helper(mds);
        else
            return eigen_map_helper(mds).template cast<type>();
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
 *    rank = extents.rank() + 1, starting with mds.data_handle(), shape = {extents()..., strides[1]}
 * 2. chip<last_dimension()[1]
 * 3. transpose it.
 * 
 * We need these guarantees:
 * 1. is_strided_layout == true if and only if array.get_attribute() == columns_attribute.
 */
