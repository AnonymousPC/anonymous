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
    struct cpu_nativize_helper
    {
        using type = input_type;
    };

    template < complex_type input_type >
    struct cpu_nativize_helper<input_type>
    {
        using type = std::complex<typename input_type::value_type>;
    };

    template < class type >
    using cpu_nativize = cpu_nativize_helper<type>::type;

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
                        return Eigen::Map<      Eigen::Vector<cpu_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
                    else  
                        return Eigen::Map<const Eigen::Vector<cpu_nativize<value_type>,Eigen::Dynamic>>(mds.data_handle(), mds.size());
                else // if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Vector<cpu_nativize<value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
                    else
                        return Eigen::Map<const Eigen::Vector<cpu_nativize<value_type>,Eigen::Dynamic>,Eigen::Unaligned,Eigen::InnerStride<Eigen::Dynamic>>(mds.data_handle(), mds.size(), mds.stride(0));
            else if constexpr ( extents_type::rank() == 2 )
                if constexpr ( is_contiguous_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1));
                    else 
                        return Eigen::Map<const Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1));
                else if constexpr ( is_strided_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
                    else
                        return Eigen::Map<const Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>,Eigen::Unaligned,Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>>(mds.data_handle(), mds.extents().extent(0), mds.extents().extent(1), Eigen::Stride<Eigen::Dynamic,Eigen::Dynamic>(mds.stride(0), mds.stride(1)));
                else // if constexpr ( is_transposed_layout<layout_type> )
                    if constexpr ( is_non_const_accessor<accessor_type> )
                        return Eigen::Map<      Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::ColMajor>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0));
                    else
                        return Eigen::Map<const Eigen::Matrix<cpu_nativize<value_type>,Eigen::Dynamic,Eigen::Dynamic,Eigen::ColMajor>>(mds.data_handle(), mds.extents().extent(1), mds.extents().extent(0));
            else // if constexpr ( extents_type::rank() >= 3 )
                static_assert(false, "cannot map a mdspan with dimension >= 3 to eigen");

        else   
            static_assert(false, "cast<T>");
    }
    
} // namespace detail