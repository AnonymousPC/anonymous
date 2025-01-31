#pragma once

namespace detail
{
    template < class type >
    struct is_opencl_reference_type
    {
        constexpr static const bool value = false;
    };

    template < class type >
    struct is_opencl_reference_type<opencl::template reference<type>>
    {
        constexpr static const bool value = true;
    };

    template < class type >
    struct is_opencl_reference_type<opencl::template const_reference<type>>
    {
        constexpr static const bool value = true;
    };
    
    template < class type >
    concept opencl_reference_type = is_opencl_reference_type<type>::value;

} // namespace detail
} // Out of namespace ap

namespace boost::compute
{
    template < class type >
        requires requires ( type it ) { { *it } -> ap::detail::opencl_reference_type; } and
                 requires ( type it, detail::meta_kernel_variable<type> v ) { it[v]; }
    struct is_device_iterator<type>
        extends public boost::true_type
    {
        
    };
} // namespace boost::compute

namespace ap { // Back into namespace ap


