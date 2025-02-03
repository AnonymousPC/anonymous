#pragma once

namespace detail
{
    template < class type >
    concept opencl_kernel_inputable = 
        requires ( boost::compute::detail::meta_kernel& k, type t ) { k << t; };
    
} // namespace detail


template < class type >
class opencl::plus
    extends public boost::compute::plus<type>,
            public std::plus<type>
{
    public:
        constexpr decltype(auto) operator() ( const type& a, const type& b )
        {
            return std::plus<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b )
        {
            return boost::compute::plus<type>::operator()(a, b);
        }
};