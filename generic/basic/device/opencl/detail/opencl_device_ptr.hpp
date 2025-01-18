#pragma once

template < class type >
boost::compute::detail::device_ptr<type> operator + ( boost::compute::detail::device_ptr<type> left, int right )
{
    return boost::compute::detail::device_ptr<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
boost::compute::detail::device_ptr<type> operator + ( int left, boost::compute::detail::device_ptr<type> right )
{
    return boost::compute::detail::device_ptr<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
boost::compute::detail::device_ptr<type> operator - ( boost::compute::detail::device_ptr<type> left, int right )
{
    return boost::compute::detail::device_ptr<type>(left.get_buffer(), left.get_index() - right);
}