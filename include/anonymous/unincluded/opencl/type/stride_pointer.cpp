DEVICE_STRIDE_POINTER_IMPLEMENTION(opencl, std::partial_ordering)

template < class type >
constexpr type opencl::stride_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return ptr.read(cmd_queue);
}

template < class type >
constexpr void opencl::stride_pointer<type>::write ( const type& val, boost::compute::command_queue& cmd_queue ) const
{
    ptr.write(val, cmd_queue);
}

template < class type >
template < class index >
struct opencl::stride_pointer<type>::index_expr
{
    stride_pointer ptr;
    index          idx; 

    using result_type = type;

    friend boost::compute::detail::meta_kernel& operator << ( boost::compute::detail::meta_kernel& left, const index_expr& right )
    {
        return left << left.get_buffer_identifier<type>(right.ptr.get_pointer().get_buffer(), boost::compute::memory_object::global_memory)
                        << '[' << right.ptr.get_index() << '+' << right.ptr.get_stride() << "*(" << right.idx << ")]";
    }                    
};

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& var ) const
{
    return index_expr<boost::compute::detail::meta_kernel_variable<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::buffer_iterator_index_expr<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}

template < class type >
template < class... expr >
constexpr auto opencl::stride_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::device_ptr_index_expr<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}

template < class type >
constexpr type opencl::const_stride_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
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
    index                  var; 

    using result_type = type;

    friend boost::compute::detail::meta_kernel& operator << ( boost::compute::detail::meta_kernel& left, const index_expr& right )
    {
        return left << left.get_buffer_identifier<type>(right.buf, boost::compute::memory_object::global_memory)
                        << '[' << right.idx << '+' << right.stp << "*(" << right.var << ")]";
    }                    
};

template < class type >
template < class... expr >
constexpr const auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& var ) const
{
    return index_expr<boost::compute::detail::meta_kernel_variable<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}

template < class type >
template < class... expr >
constexpr const auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::buffer_iterator_index_expr<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}

template < class type >
template < class... expr >
constexpr const auto opencl::const_stride_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& var ) const
{
    return index_expr<boost::compute::detail::device_ptr_index_expr<expr...>>(get_pointer().get_buffer(), get_pointer().get_index(), get_stride(), var);
}