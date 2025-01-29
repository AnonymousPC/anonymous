#pragma once

} // Out of namespace ap

namespace boost::compute
{
    template < class type >
    struct is_device_iterator<ap::opencl::template pointer<type>>
        extends public boost::true_type
    {

    };

    template < class type >
    struct is_device_iterator<ap::opencl::template const_pointer<type>>
        extends public boost::true_type
    {

    };
} // namespace boost::compute

namespace ap { // Back into namespace ap


