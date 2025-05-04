template < class type, class device >
constexpr detail::array_upper<type,1,device>::array_upper ( array<type,2,device>& init_host, array_attribute init_atr, int init_ofs )
    extends ptr ( &init_host ),
            atr ( init_atr ),
            ofs ( init_ofs )
{

}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::array_upper ( const array<type,2,device>& init_host, array_attribute init_atr, int init_ofs )
    extends ptr ( const_cast<array<type,2,device>*>(&init_host) ),
            atr ( init_atr ),
            ofs ( init_ofs )
{
    
}

template < class type, class device >
constexpr int detail::array_upper<type,1,device>::size ( ) const 
{
    return get_size_axis<1>();
}

template < class type, class device >
constexpr array<int> detail::array_upper<type,1,device>::shape ( ) const 
{
    return { get_shape()[1] };
}

template < class type, class device >
constexpr bool detail::array_upper<type,1,device>::empty ( ) const 
{
    return get_host().empty();
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::pointer detail::array_upper<type,1,device>::data ( )
{
    if constexpr ( debug )
        if ( not contiguous() )
            throw internal_error();

    return get_host().data() + get_offset() * size();
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_pointer detail::array_upper<type,1,device>::data ( ) const
{
    if constexpr ( debug )
        if ( not contiguous() )
            throw internal_error();

    return get_host().data() + get_offset() * size();
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::iterator detail::array_upper<type,1,device>::begin ( )
{
    return contiguous() ? iterator(data(), 1) : iterator(get_pointer(0), get_stride());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_iterator detail::array_upper<type,1,device>::begin ( ) const
{
    return contiguous() ? const_iterator(data(), 1) : const_iterator(get_pointer(0), get_stride());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::iterator detail::array_upper<type,1,device>::end ( )
{
    // Do not use get_pointer(get_size_axis<1>()).
    // Notice get_pointer() calls device::layout_type::mapping().operator()(offsets...), where offsets == get_axis_size<1>() + 1. 
    // But C++ standard treats it as an undefined behavior when offsets are out of range, even though we just need the offset rather than referenced value.
    return contiguous() ? iterator(data() + size(), 1) : iterator(get_pointer(0) + get_size_top(), get_stride());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_iterator detail::array_upper<type,1,device>::end ( ) const
{
    // Do not use get_pointer(get_size_axis<1>()).
    // Notice get_pointer() calls device::layout_type::mapping().operator()(offsets...), where offsets == get_axis_size<1>() + 1. 
    // But C++ standard treats it as an undefined behavior when offsets are out of range, even though we just need the offset rather then referenced value.
    return contiguous() ? const_iterator(data() + size(), 1) : const_iterator(get_pointer(0) + get_size_top(), get_stride());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::reference detail::array_upper<type,1,device>::operator [] ( int offset )
{
    return contiguous() ? data()[offset] : get_value(offset);
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_reference detail::array_upper<type,1,device>::operator [] ( int offset ) const
{
    return contiguous() ? data()[offset] : get_value(offset);
}

template < class type, class device >
constexpr bool detail::array_upper<type,1,device>::ownership ( ) const
{
    [[assume((ptr == nullptr) == (atr == no_attribute))]];
    return ptr == nullptr;
}

template < class type, class device >
constexpr bool detail::array_upper<type,1,device>::contiguous ( ) const
{
    return ( get_attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
           ( get_attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );
}

template < class type, class device >
constexpr detail::array_attribute detail::array_upper<type,1,device>::get_attribute ( ) const
{
    return atr;
}

template < class type, class device >
constexpr int detail::array_upper<type,1,device>::get_offset ( ) const
{   
    return ofs;
}

template < class type, class device >
constexpr array<type,2,device>& detail::array_upper<type,1,device>::get_host ( )
{
    return *ptr;
}

template < class type, class device >
constexpr const array<type,2,device>& detail::array_upper<type,1,device>::get_host ( ) const
{
    return *ptr;
} 

template < class type, class device >
constexpr int detail::array_upper<type,1,device>::get_size_top ( ) const
{
    return get_host().get_size_top();
}

template < class type, class device >
template < int axis >
constexpr int detail::array_upper<type,1,device>::get_size_axis ( ) const
{
    static_assert ( axis == 1 or axis == -1 );
    return get_host().template get_size_axis<2>();
}

template < class type, class device >
constexpr detail::array_shape<1> detail::array_upper<type,1,device>::get_shape ( ) const
{
    return { size() };
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::reference detail::array_upper<type,1,device>::get_value ( int offset )
{
    return get_attribute() == rows_attribute ? get_host().get_value(get_offset(), offset) :
                                               get_host().get_value(offset, get_offset());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_reference detail::array_upper<type,1,device>::get_value ( int offset ) const
{
    return get_attribute() == rows_attribute ? get_host().get_value(get_offset(), offset) :
                                               get_host().get_value(offset, get_offset());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::pointer detail::array_upper<type,1,device>::get_pointer ( int offset )
{
    return get_attribute() == rows_attribute ? get_host().get_pointer(get_offset(), offset) :
                                               get_host().get_pointer(offset, get_offset());
}

template < class type, class device >
constexpr detail::array_upper<type,1,device>::const_pointer detail::array_upper<type,1,device>::get_pointer ( int offset ) const
{
    return get_attribute() == rows_attribute ? get_host().get_pointer(get_offset(), offset) :
                                               get_host().get_pointer(offset, get_offset());
}

template < class type, class device >
constexpr int detail::array_upper<type,1,device>::get_stride ( ) const
{
    return get_size_top() / size();
}
