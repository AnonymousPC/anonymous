template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::array_upper ( array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
    extends ptr1 ( &init_host ),
            atr  ( init_atr ),
            ofs  ( init_ofs )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::array_upper ( const array<type,dim+1,device>& init_host, array_attribute init_atr, int init_ofs )
    extends ptr1 ( &const_cast<detail::array_upper<type,dim+1,device>&>(init_host) ),
            atr  ( init_atr ),
            ofs  ( init_ofs )
{
    
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::array_upper ( array<type,dim,device>& init_host )
    extends ptr2 ( &init_host ),
            atr  ( transpose_attribute )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::array_upper ( const array<type,dim,device>& init_host )
    extends ptr2 ( &const_cast<detail::array_upper<type,dim,device>&>(init_host) ),
            atr  ( transpose_attribute )
{

}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::size ( ) const
{
    return get_attribute() == rows_attribute    ? get_host<1>().size() / get_host().template get_size_axis<1>() :
           get_attribute() == columns_attribute ? (get_host<1>().ownership() ? get_host<1>().size() / get_host<1>().template get_size_axis<-1>() : get_host<1>().size() / get_host<1>().template get_size_axis<1>()) :
                                                  get_host<2>().size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<int> detail::array_upper<type,dim,device>::shape ( ) const
{
    return get_attribute() == rows_attribute    ? get_host<1>().shape().pop(1) : 
           get_attribute() == columns_attribute ? 
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::row ( ) const
{
    return get_size_axis<1>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::column ( ) const    
    requires ( dim == 2 )
{
    return get_size_axis<2>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool detail::array_upper<type,dim,device>::empty ( ) const
{
    return get_attribute() == rows_attribute or get_attribute() == columns_attribute ? get_host<1>().empty() :
                                                                                       get_host<2>().empty();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::pointer detail::array_upper<type,dim,device>::data ( )
{
    if constexpr ( debug )
        if ( not contiguous() )
            throw internal_error();

    return get_host<1>().data() + get_offset() * size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::const_pointer detail::array_upper<type,dim,device>::data ( ) const
{
    if constexpr ( debug )
        if ( not contiguous() )
            throw internal_error();

    return get_host<1>().data() + get_offset() * size();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::iterator detail::array_upper<type,dim,device>::begin ( )
{
    return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset()).begin() :
           get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset()).begin() : 
                                                  get_host<2>().template get_columns<dim-1>().begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::const_iterator detail::array_upper<type,dim,device>::begin ( ) const
{
    return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset()).begin() :
           get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset()).begin() : 
                                                  get_host<2>().template get_columns<dim-1>().begin();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::iterator detail::array_upper<type,dim,device>::end ( )
{
    return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset() + 1).begin() : // TODO: use get_rows<dim-1>(get_offset()).end() ?
           get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset() + 1).begin() :
                                                  get_host<2>().template get_columns<dim-1>().end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::const_iterator detail::array_upper<type,dim,device>::end ( ) const
{
    return get_attribute() == rows_attribute    ? get_host<1>().template get_rows   <dim-1>(get_offset() + 1).begin() :
           get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim-1>(get_offset() + 1).begin() :
                                                  get_host<2>().template get_columns<dim-1>().end();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr array<type,dim-1,device>& detail::array_upper<type,dim,device>::operator [] ( int offset )
{
    return get_attribute() == rows_attribute    ? static_cast<array<type,dim-1,device>&>(get_host<1>().template get_rows   <dim-1>(get_offset())[offset]) :
           get_attribute() == columns_attribute ? static_cast<array<type,dim-1,device>&>(get_host<1>().template get_columns<dim-1>(get_offset())[offset]) : 
                                                  static_cast<array<type,dim-1,device>&>(get_host<2>().template get_columns<dim-1>()[offset]);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr const array<type,dim-1,device>& detail::array_upper<type,dim,device>::operator [] ( int offset ) const
{
    return get_attribute() == rows_attribute    ? static_cast<const array<type,dim-1,device>&>(get_host<1>().template get_rows   <dim-1>(get_offset())[offset]) :
           get_attribute() == columns_attribute ? static_cast<const array<type,dim-1,device>&>(get_host<1>().template get_columns<dim-1>(get_offset())[offset]) : 
                                                  static_cast<const array<type,dim-1,device>&>(get_host<2>().template get_columns<dim-1>()[offset]);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool detail::array_upper<type,dim,device>::ownership ( ) const
{
    [[assume((ptr1 == nullptr and ptr2 == nullptr) == (atr == no_attribute))]];
    return ptr1 == nullptr and ptr2 == nullptr;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr bool detail::array_upper<type,dim,device>::contiguous ( ) const
{
    return ( get_attribute() == rows_attribute    and same_as<typename device::layout_type,std::layout_right> ) or 
           ( get_attribute() == columns_attribute and same_as<typename device::layout_type,std::layout_left > );

    /* Transpose-view is never considered contiguous.
     * A contiguous array means that:
     * - std::mdspan can directly apply on array.data() (with correct device::layout_type).
     * - Two array which equals to each other are both contiguous must be memcpy-able.
     */
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_attribute detail::array_upper<type,dim,device>::get_attribute ( ) const
{
    return atr;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::get_offset ( ) const
{
    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )   
            throw internal_error();

    return ofs;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int attr >
constexpr array<type,dim+1,device>& detail::array_upper<type,dim,device>::get_host ( )
    requires ( attr == 1 )
{
    return *ptr1;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int attr >
constexpr const array<type,dim+1,device>& detail::array_upper<type,dim,device>::get_host ( ) const
    requires ( attr == 1 )
{
    return *ptr1;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int attr >
constexpr array<type,dim,device>& detail::array_upper<type,dim,device>::get_host ( )
    requires ( attr == 2 )
{
    return *ptr2;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int attr >
constexpr const array<type,dim,device>& detail::array_upper<type,dim,device>::get_host ( ) const
    requires ( attr == 2 )
{
    return *ptr2;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::get_size_top ( ) const
{
    return get_attribute() == rows_attribute or get_attribute() == columns_attribute ? get_host<1>().get_size_top() :
                                                                                       get_host<2>().get_size_top();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int axis >
constexpr int detail::array_upper<type,dim,device>::get_size_axis ( ) const
{
    static_assert ( axis >= 1 and axis <= dim );
    return get_attribute() == rows_attribute    ? get_host<1>().template get_size_axis<axis+1>() :
           get_attribute() == columns_attribute ? (get_host<1>().ownership() ? get_host<1>().template get_size_axis<dim-axis+1>() : get_host<1>().template get_size_axis<axis+1>()) :
                                                  get_host<2>().template get_size_axis<dim-axis+1>();
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_shape<dim> detail::array_upper<type,dim,device>::get_shape ( ) const
{
    auto shp = detail::array_shape<dim>();
    for_constexpr<1,dim>([&] <int index> { shp[index] = get_size_axis<index>(); });
    return shp;
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> detail::array_upper<type,dim,device>::get_rows ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    
    if constexpr ( debug )
        if ( get_attribute() == columns_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().template get_rows   <dim2>(get_offset(), offsets...) :
                                               get_host<2>().template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> detail::array_upper<type,dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );

    if constexpr ( debug )
        if ( get_attribute() == columns_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().template get_rows   <dim2>(get_offset(), offsets...) :
                                               get_host<2>().template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr std::span<detail::array_upper<type,dim2,device>> detail::array_upper<type,dim,device>::get_columns ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );

    if constexpr ( debug )
        if ( get_attribute() == rows_attribute )
            throw internal_error();

    return get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim2>(offsets..., get_offset()) :
                                                  get_host<2>().template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
template < int dim2 >
constexpr const std::span<detail::array_upper<type,dim2,device>> detail::array_upper<type,dim,device>::get_columns ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );

    if constexpr ( debug )
        if ( get_attribute() == rows_attribute )
            throw internal_error();

    return get_attribute() == columns_attribute ? get_host<1>().template get_columns<dim2>(offsets..., get_offset()) :
                                                  get_host<2>().template get_columns<dim2>(offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::reference detail::array_upper<type,dim,device>::get_value ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );

    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().get_value(get_offset(), offsets...) :
                                               get_host<1>().get_value(offsets..., get_offset());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::const_reference detail::array_upper<type,dim,device>::get_value ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );

    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().get_value(get_offset(), offsets...) :
                                               get_host<1>().get_value(offsets..., get_offset());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::pointer detail::array_upper<type,dim,device>::get_pointer ( int_type auto... offsets )
{
    static_assert ( sizeof...(offsets) == dim );

    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().get_pointer(get_offset(), offsets...) :
                                               get_host<1>().get_pointer(offsets..., get_offset());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr detail::array_upper<type,dim,device>::const_pointer detail::array_upper<type,dim,device>::get_pointer ( int_type auto... offsets ) const
{
    static_assert ( sizeof...(offsets) == dim );

    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )
            throw internal_error();

    return get_attribute() == rows_attribute ? get_host<1>().get_pointer(get_offset(), offsets...) :
                                               get_host<1>().get_pointer(offsets..., get_offset());
}

template < class type, int dim, class device >
    requires ( dim >= 2 and dim <= max_dim - 1 )
constexpr int detail::array_upper<type,dim,device>::get_stride ( ) const
{
    if constexpr ( debug )
        if ( get_attribute() == transpose_attribute )
            throw internal_error();

    return get_size_top() / size();
}

