#pragma once

template < class type >
boost::compute::buffer_iterator<type> operator + ( boost::compute::buffer_iterator<type> left, int right )
{
    return boost::compute::buffer_iterator<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
boost::compute::buffer_iterator<type> operator + ( int left, boost::compute::buffer_iterator<type> right )
{
    return boost::compute::buffer_iterator<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
boost::compute::buffer_iterator<type> operator - ( boost::compute::buffer_iterator<type> left, int right )
{
    return boost::compute::buffer_iterator<type>(left.get_buffer(), left.get_index() - right);
}