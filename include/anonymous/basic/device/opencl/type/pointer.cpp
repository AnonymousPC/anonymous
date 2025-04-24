template < class type >
opencl::pointer<type>::pointer ( boost::compute::buffer cvt_buf, size_t cvt_idx )
    extends buf ( cvt_buf ),
            idx ( cvt_idx )
{

}

template < class type > 
opencl::pointer<type>::pointer ( boost::compute::buffer_iterator<type> cvt )
    extends pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
opencl::pointer<type>::operator boost::compute::buffer_iterator<type> ( ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index());
}

template < class type > 
opencl::pointer<type>::pointer ( boost::compute::detail::device_ptr<type> cvt )
    extends pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
opencl::pointer<type>::operator boost::compute::detail::device_ptr<type> ( ) const
{
    return boost::compute::detail::device_ptr<type>(get_buffer(), get_index());
}

template < class type >
type opencl::pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return boost::compute::detail::read_single_value<type>(get_buffer(), get_index(), cmd_queue);
}

template < class type >
void opencl::pointer<type>::write ( const type& val, boost::compute::command_queue& cmd_queue ) const
{
    boost::compute::detail::write_single_value<type>(val, get_buffer(), get_index(), cmd_queue);
}

template < class type >
template < class... expr >
auto opencl::pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
auto opencl::pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
auto opencl::pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
boost::compute::buffer opencl::pointer<type>::get_buffer ( ) const
{
    return buf;
}

template < class type >
size_t opencl::pointer<type>::get_index ( ) const
{
    return idx;
}





template < class type >
opencl::const_pointer<type>::const_pointer ( boost::compute::buffer cvt_buf, size_t cvt_idx )
    extends buf ( cvt_buf ),
            idx ( cvt_idx )
{

}

template < class type > 
opencl::const_pointer<type>::const_pointer ( boost::compute::buffer_iterator<type> cvt )
    extends const_pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type > 
opencl::const_pointer<type>::const_pointer ( boost::compute::detail::device_ptr<type> cvt )
    extends const_pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
type opencl::const_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return boost::compute::detail::read_single_value<type>(get_buffer(), get_index(), cmd_queue);
}

template < class type >
template < class... expr >
auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
const boost::compute::buffer opencl::const_pointer<type>::get_buffer ( ) const
{
    return buf;
}

template < class type >
size_t opencl::const_pointer<type>::get_index ( ) const
{
    return idx;
}




template < class type >
bool operator == ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
bool operator == ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
bool operator == ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
bool operator == ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
std::partial_ordering operator <=> ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
std::partial_ordering operator <=> ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
std::partial_ordering operator <=> ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
std::partial_ordering operator <=> ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
opencl::template pointer<type> operator + ( opencl::template pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template pointer<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
opencl::template const_pointer<type> operator + ( opencl::template const_pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template const_pointer<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
opencl::template pointer<type> operator + ( std::ptrdiff_t left, opencl::template pointer<type> right )
{
    return opencl::template pointer<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
opencl::template const_pointer<type> operator + ( std::ptrdiff_t left, opencl::template const_pointer<type> right )
{
    return opencl::template const_pointer<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
opencl::template pointer<type> operator - ( opencl::template pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template pointer<type>(left.get_buffer(), left.get_index() - right);
}

template < class type >
opencl::template const_pointer<type> operator - ( opencl::template const_pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template const_pointer<type>(left.get_buffer(), left.get_index() - right);
}

template < class type >
std::ptrdiff_t operator - ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
std::ptrdiff_t operator - ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
std::ptrdiff_t operator - ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
std::ptrdiff_t operator - ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());
            
    return left.get_index() - right.get_index();
}

template < class type >
opencl::template pointer<type>& operator += ( opencl::template pointer<type>& left, std::ptrdiff_t right )
{
    return left = left + right;
}

template < class type >
opencl::template const_pointer<type>& operator += ( opencl::template const_pointer<type>& left, std::ptrdiff_t right )
{
    return left = left + right;
}

template < class type >
opencl::template pointer<type>& operator -= ( opencl::template pointer<type>& left, std::ptrdiff_t right )
{
    return left = left - right;
}

template < class type >
opencl::template const_pointer<type>& operator -= ( opencl::template const_pointer<type>& left, std::ptrdiff_t right )
{
    return left = left - right;
}

template < class type >
opencl::template pointer<type>& operator ++ ( opencl::template pointer<type>& left )
{
    return left = opencl::template pointer<type>(left.get_buffer(), left.get_index() + 1);
}

template < class type >
opencl::template const_pointer<type>& operator ++ ( opencl::template const_pointer<type>& left )
{
    return left = opencl::template const_pointer<type>(left.get_buffer(), left.get_index() + 1);
}

template < class type >
opencl::template pointer<type> operator ++ ( opencl::template pointer<type>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type >
opencl::template const_pointer<type> operator ++ ( opencl::template const_pointer<type>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type >
opencl::template pointer<type>& operator -- ( opencl::template pointer<type>& left )
{
    return left = opencl::template pointer<type>(left.get_buffer(), left.get_index() - 1);
}

template < class type >
opencl::template const_pointer<type>& operator -- ( opencl::template const_pointer<type>& left )
{
    return left = opencl::template const_pointer<type>(left.get_buffer(), left.get_index() - 1);
}

template < class type >
opencl::template pointer<type> operator -- ( opencl::template pointer<type>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

template < class type >
opencl::template const_pointer<type> operator -- ( opencl::template const_pointer<type>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}