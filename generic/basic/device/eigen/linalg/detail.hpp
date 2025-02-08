#pragma once

namespace detail
{

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

    template < class type = void >
    constexpr auto eigen_map ( auto mds )
    {
        using value_type    = decltype(mds)::value_type;
        using extents_type  = decltype(mds)::extents_type;
        using layout_type   = decltype(mds)::layout_type;
        using accessor_type = decltype(mds)::accessor_type; 

        if constexpr ( is_void<type> or same_as<type,value_type> )
            if constexpr ( extents_type::rank() == 1 )
                if constexpr ( is_contiguous_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
                    else  
                        return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
                else // if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Aligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
                    else
                        return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Aligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
            else if constexpr ( extents_type::rank() == 2 )
                if constexpr ( is_contiguous_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1));
                    else 
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1));
                else if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Aligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
                    else
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Aligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
                else // if constexpr ( is_transposed_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0)).transpose();
                    else
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0)).transpose();
            else // if constexpr ( extents_type::rank() >= 3 )
                static_assert(false, "cannot map a mdspan with dimension >= 3 to eigen");

        else   
            if constexpr ( extents_type::rank() == 1 )
                if constexpr ( is_contiguous_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size()).template cast<type>();
                    else  
                        return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size()).template cast<type>();
                else // if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Aligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0)).template cast<type>();
                    else
                        return Eigen::Map<const Eigen::Vector<eigen_nativize<value_type>,Eigen::Dynamic>,Eigen::Aligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0)).template cast<type>();
            else if constexpr ( extents_type::rank() == 2 )
                if constexpr ( is_contiguous_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1)).template cast<type>();
                    else 
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1)).template cast<type>();
                else if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Aligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1))).template cast<type>();
                    else
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Aligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1))).template cast<type>();
                else // if constexpr ( is_transposed_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0)).template cast<type>().transpose();
                    else
                        return Eigen::Map<const Eigen::Matrix<eigen_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0)).template cast<type>().transpose();
            else // if constexpr ( extents_type::rank() >= 3 )
                static_assert(false, "cannot map a mdspan with dimension >= 3 to eigen");
    }
    
} // namespace detail