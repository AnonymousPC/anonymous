#pragma once

namespace detail
{
    template < class input_type >
    struct opencl_nativize_helper
    {
        using type = input_type;
    };

    template < complex_type input_type >
    struct opencl_nativize_helper<input_type>
    {
        using type = std::complex<typename input_type::value_type>;
    };

    template < class type >
    using opencl_nativize = opencl_nativize_helper<type>::type;

    template < class type >
    auto opencl_copy_mdspan ( auto mds )
    {
        using vector_type = opencl::template vector<type>;
        using mdspan_type = std::mdspan<type,std::dextents<int,2>,typename opencl::layout_type,conditional<is_non_const_accessor<typename decltype(mds)::accessor_type>,opencl::template accessor_type<type>,opencl::template const_accessor_type<type>>>;
        
        let result = std::pair<vector_type,mdspan_type>();
        result.first.resize(mds.size());
        if constexpr ( detail::is_contiguous_layout<typename decltype(mds)::layout_type> )
            opencl::copy(mds.data_handle(), mds.size(), result.first.data());
        else // if constexpr ( detail::is_strided_layout<typename decltype(mds)::layout_type> )
            opencl::copy(opencl::template const_stride_pointer<typename decltype(mds)::value_type>(mds.data_handle(), mds.stride(0)),
                         opencl::template const_stride_pointer<typename decltype(mds)::value_type>(mds.data_handle(), mds.stride(0)) + mds.size(),
                         result.first.data());
        result.second = mdspan_type(result.first.data(), mds.extents());
        return result;
    }

} // namespace detail
