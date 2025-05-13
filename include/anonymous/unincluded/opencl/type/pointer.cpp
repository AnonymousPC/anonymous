template < class type >
constexpr opencl::pointer<type>::pointer ( boost::compute::buffer init_buf, difference_type init_idx )
    extends buf ( init_buf ),
            idx ( init_idx )
{

}

template < class type >
constexpr opencl::pointer<type>::pointer ( const_pointer<type> cvt )
    extends buf ( cvt.get_buffer() ),
            idx ( cvt.get_index()  )
{

}

template < class type >
constexpr opencl::pointer<type>::reference opencl::pointer<type>::operator * ( ) const
{
    return reference(get_buffer(), get_index());
}

template < class type >
constexpr opencl::pointer<type>::reference opencl::pointer<type>::operator [] ( difference_type offset ) const
{
    return reference(get_buffer(), get_index() + offset);
}

template < class type >
constexpr boost::compute::buffer& opencl::pointer<type>::get_buffer ( )
{
    return buf;
}

template < class type >
constexpr const boost::compute::buffer& opencl::pointer<type>::get_buffer ( ) const
{
    return buf;
}

template < class type >
constexpr opencl::pointer<type>::difference_type& opencl::pointer<type>::get_index ( )
{
    return idx;
}

template < class type >
constexpr const opencl::pointer<type>::difference_type& opencl::pointer<type>::get_index ( ) const
{
    return idx;
}

template < class type > 
constexpr opencl::pointer<type>::pointer ( boost::compute::buffer_iterator<type> cvt )
    extends pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
constexpr opencl::pointer<type>::operator boost::compute::buffer_iterator<type> ( ) const
{
    return boost::compute::buffer_iterator<type>(self.get_buffer(), self.get_index());
}

template < class type > 
constexpr opencl::pointer<type>::pointer ( boost::compute::detail::device_ptr<type> cvt )
    extends pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
constexpr opencl::pointer<type>::operator boost::compute::detail::device_ptr<type> ( ) const
{
    return boost::compute::detail::device_ptr<type>(self.get_buffer(), self.get_index());
}

template < class type >
constexpr type opencl::pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return boost::compute::detail::read_single_value<type>(get_buffer(), get_index(), cmd_queue);
}

template < class type >
constexpr void opencl::pointer<type>::write ( const type& val, boost::compute::command_queue& cmd_queue ) const
{
    boost::compute::detail::write_single_value<type>(val, get_buffer(), get_index(), cmd_queue);
}

template < class type >
template < class... expr >
constexpr auto opencl::pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
constexpr auto opencl::pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
constexpr auto opencl::pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
constexpr opencl::const_pointer<type>::const_pointer ( boost::compute::buffer init_buf, difference_type init_idx )
    extends buf ( init_buf ),
            idx ( init_idx )
{

}

template < class type >
constexpr opencl::const_pointer<type>::const_pointer ( pointer<type> cvt )
    extends buf ( cvt.get_buffer() ),
            idx ( cvt.get_index()  )
{

}

template < class type >
constexpr opencl::const_pointer<type>::reference opencl::const_pointer<type>::operator * ( ) const
{
    return reference(get_buffer(), get_index());
}

template < class type >
constexpr opencl::const_pointer<type>::reference opencl::const_pointer<type>::operator [] ( difference_type offset ) const
{
    return reference(get_buffer(), get_index() + offset);
}

template < class type >
constexpr const boost::compute::buffer& opencl::const_pointer<type>::get_buffer ( ) const
{
    return buf;
}

template < class type >
constexpr opencl::const_pointer<type>::difference_type& opencl::const_pointer<type>::get_index ( )
{
    return idx;
}

template < class type >
constexpr const opencl::const_pointer<type>::difference_type& opencl::const_pointer<type>::get_index ( ) const
{
    return idx;
}

template < class type > 
constexpr opencl::const_pointer<type>::const_pointer ( boost::compute::buffer_iterator<type> cvt )
    extends const_pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type > 
constexpr opencl::const_pointer<type>::const_pointer ( boost::compute::detail::device_ptr<type> cvt )
    extends const_pointer ( cvt.get_buffer(), cvt.get_index() )
{

}

template < class type >
constexpr type opencl::const_pointer<type>::read ( boost::compute::command_queue& cmd_queue ) const
{
    return boost::compute::detail::read_single_value<type>(get_buffer(), get_index(), cmd_queue);
}

template < class type >
template < class... expr >
constexpr const auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::meta_kernel_variable<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
constexpr const auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::buffer_iterator_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
template < class... expr >
constexpr const auto opencl::const_pointer<type>::operator [] ( const boost::compute::detail::device_ptr_index_expr<expr...>& idx ) const
{
    return boost::compute::buffer_iterator<type>(get_buffer(), get_index())[idx];
}

template < class type >
constexpr bool operator == ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
constexpr bool operator == ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
constexpr bool operator == ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
constexpr bool operator == ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() and 
           left.get_index()  == right.get_index();
}

template < class type >
constexpr std::partial_ordering operator <=> ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
constexpr std::partial_ordering operator <=> ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
constexpr std::partial_ordering operator <=> ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
constexpr std::partial_ordering operator <=> ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    return left.get_buffer() == right.get_buffer() ? left.get_index() <=> right.get_index() : 
                                                     std::partial_ordering::unordered;
}

template < class type >
constexpr opencl::template pointer<type> operator + ( opencl::template pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template pointer<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
constexpr opencl::template const_pointer<type> operator + ( opencl::template const_pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template const_pointer<type>(left.get_buffer(), left.get_index() + right);
}

template < class type >
constexpr opencl::template pointer<type> operator + ( std::ptrdiff_t left, opencl::template pointer<type> right )
{
    return opencl::template pointer<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
constexpr opencl::template const_pointer<type> operator + ( std::ptrdiff_t left, opencl::template const_pointer<type> right )
{
    return opencl::template const_pointer<type>(right.get_buffer(), left + right.get_index());
}

template < class type >
constexpr opencl::template pointer<type> operator - ( opencl::template pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template pointer<type>(left.get_buffer(), left.get_index() - right);
}

template < class type >
constexpr opencl::template const_pointer<type> operator - ( opencl::template const_pointer<type> left, std::ptrdiff_t right )
{
    return opencl::template const_pointer<type>(left.get_buffer(), left.get_index() - right);
}

template < class type >
constexpr std::ptrdiff_t operator - ( opencl::template pointer<type> left, opencl::template pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
constexpr std::ptrdiff_t operator - ( opencl::template pointer<type> left, opencl::template const_pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
constexpr std::ptrdiff_t operator - ( opencl::template const_pointer<type> left, opencl::template pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());

    return left.get_index() - right.get_index();
}

template < class type >
constexpr std::ptrdiff_t operator - ( opencl::template const_pointer<type> left, opencl::template const_pointer<type> right )
{
    if constexpr ( debug )
        if ( left.get_buffer() != right.get_buffer() )
            throw logic_error("cannot minus pointer (with left.get_buffer() = {}, right.get_buffer() = {}): belongs to different opencl buffers", left.get_buffer(), right.get_buffer());
            
    return left.get_index() - right.get_index();
}

template < class type >
constexpr opencl::template pointer<type>& operator += ( opencl::template pointer<type>& left, std::ptrdiff_t right )
{
    return left = left + right;
}

template < class type >
constexpr opencl::template const_pointer<type>& operator += ( opencl::template const_pointer<type>& left, std::ptrdiff_t right )
{
    return left = left + right;
}

template < class type >
constexpr opencl::template pointer<type>& operator -= ( opencl::template pointer<type>& left, std::ptrdiff_t right )
{
    return left = left - right;
}

template < class type >
constexpr opencl::template const_pointer<type>& operator -= ( opencl::template const_pointer<type>& left, std::ptrdiff_t right )
{
    return left = left - right;
}

template < class type >
constexpr opencl::template pointer<type>& operator ++ ( opencl::template pointer<type>& left )
{
    left.get_index()++;
    return left;
}

template < class type >
constexpr opencl::template const_pointer<type>& operator ++ ( opencl::template const_pointer<type>& left )
{
    left.get_index()++;
    return left;
}

template < class type >
constexpr opencl::template pointer<type> operator ++ ( opencl::template pointer<type>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type >
constexpr opencl::template const_pointer<type> operator ++ ( opencl::template const_pointer<type>& left, int )
{
    auto tmp = left;
    ++left;
    return tmp;
}

template < class type >
constexpr opencl::template pointer<type>& operator -- ( opencl::template pointer<type>& left )
{
    left.get_index()--;
    return left;
}

template < class type >
constexpr opencl::template const_pointer<type>& operator -- ( opencl::template const_pointer<type>& left )
{
    left.get_index()--;
    return left;
}

template < class type >
constexpr opencl::template pointer<type> operator -- ( opencl::template pointer<type>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}

template < class type >
constexpr opencl::template const_pointer<type> operator -- ( opencl::template const_pointer<type>& left, int )
{
    auto tmp = left;
    --left;
    return tmp;
}