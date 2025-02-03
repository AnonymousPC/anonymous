#pragma once

template < class type >
type opencl::stride_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return ptr.read(cmd_queue);
}

template < class type >
void opencl::stride_pointer<type>::write ( const type& val, boost::compute::command_queue& cmd_queue ) const
{
    ptr.write(val, cmd_queue);
}

template < class type >
template < class index >
struct opencl::stride_pointer<type>::index_expr
{
    boost::compute::buffer buf;
    size_t                 idx;
    int                    stp;
    index                  ex; 

    friend boost::compute::detail::meta_kernel& operator << ( boost::compute::detail::meta_kernel& left, const index_expr& right )
    {
        return left << left.get_buffer_identifier<type>(right.buf, boost::compute::memory_object::global_memory)
                        << '[' << right.idx << '+' << right.stp << "*(" << right.ex << ")]";
    }                    
};

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& var ) const
{
    return index_expr<boost::compute::detail::meta_kernel_variable<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::buffer_iterator_index_expr<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::device_ptr_index_expr<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}






template < class type >
type opencl::const_stride_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return ptr.read(cmd_queue);
}



template < class type >
template < class index >
struct opencl::const_stride_pointer<type>::index_expr
{
    boost::compute::buffer buf;
    size_t                 idx;
    int                    stp;
    index                  ex; 

    friend boost::compute::detail::meta_kernel& operator << ( boost::compute::detail::meta_kernel& left, const index_expr& right )
    {
        return left << left.get_buffer_identifier<type>(right.buf, boost::compute::memory_object::global_memory)
                        << '[' << right.idx << '+' << right.stp << "*(" << right.ex << ")]";
    }                    
};

template < class type >
template < class... expr >
constexpr auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& var ) const
{
    return index_expr<boost::compute::detail::meta_kernel_variable<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}

template < class type >
template < class... expr >
constexpr auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::buffer_iterator_index_expr<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}

template < class type >
template < class... expr >
constexpr auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::device_ptr_index_expr<expr...>>(ptr.get_buffer(), ptr.get_index(), step, var);
}