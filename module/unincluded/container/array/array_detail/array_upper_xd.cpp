template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::array_upper ( array<type,max_dim,device>& init_host )
    extends ptr ( &init_host )
{

}

template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::array_upper ( const array<type,max_dim,device>& init_host )
    extends ptr ( &const_cast<detail::array_upper<type,max_dim,device>&>(init_host) )
{
    
}

template < class type, class device >
constexpr int detail::array_upper<type,max_dim,device>::size ( ) const
{
    return get_host<transpose_attribute>().size();
}

template < class type, class device >
constexpr array<int> detail::array_upper<type,max_dim,device>::shape ( ) const
{
    return get_host<transpose_attribute>().shape().reverse();
}

template < class type, class device >
constexpr int detail::array_upper<type,max_dim,device>::row ( ) const
{
    return get_size_axis<1>();
}

template < class type, class device >
constexpr int detail::array_upper<type,max_dim,device>::column ( ) const    
    requires ( max_dim == 2 )
{
    return get_size_axis<2>();
}

template < class type, class device >
constexpr bool detail::array_upper<type,max_dim,device>::empty ( ) const
{
    return get_host<transpose_attribute>().empty();
}

template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::iterator detail::array_upper<type,max_dim,device>::begin ( )
{
    return get_host<transpose_attribute>().template get_columns<max_dim-1>().first;
}

template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::const_iterator detail::array_upper<type,max_dim,device>::begin ( ) const
{
    return get_host<transpose_attribute>().template get_columns<max_dim-1>().first;
}

template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::iterator detail::array_upper<type,max_dim,device>::end ( )
{
    return get_host<transpose_attribute>().template get_columns<max_dim-1>().first;
}

template < class type, class device >
constexpr detail::array_upper<type,max_dim,device>::const_iterator detail::array_upper<type,max_dim,device>::end ( ) const
{
    return get_host<transpose_attribute>().template get_columns<max_dim-1>().first;
}

template < class type, class device >
constexpr array<type,max_dim-1,device>& detail::array_upper<type,max_dim,device>::operator [] ( int offset )
{
    return begin()[offset];
}

template < class type, class device >
constexpr const array<type,max_dim-1,device>& detail::array_upper<type,max_dim,device>::operator [] ( int offset ) const
{
    return begin()[offset];
}

template < class type, class device >
constexpr bool detail::array_upper<type,max_dim,device>::ownership ( ) const
{
    return ptr == nullptr;
}

template < class type, class device >
template < auto attr >
constexpr array<type,max_dim,device>& detail::array_upper<type,max_dim,device>::get_host ( )
    requires ( attr == transpose_attribute )
{
    return *ptr;
}

template < class type, class device >
template < auto attr >
constexpr const array<type,max_dim,device>& detail::array_upper<type,max_dim,device>::get_host ( ) const
    requires ( attr == transpose_attribute )
{
    return *ptr;
}

template < class type, class device >
constexpr int detail::array_upper<type,max_dim,device>::get_size_top ( ) const
{
    return get_host<transpose_attribute>().get_size_top();
}

template < class type, class device >
template < int axis >
constexpr int detail::array_upper<type,max_dim,device>::get_size_axis ( ) const
{
    static_assert ( ( axis >= -max_dim and axis <= -1 ) or ( axis >= 1 and axis <= max_dim ) );

    if constexpr ( axis >= 0 )
        return get_host<transpose_attribute>().template get_size_axis<max_dim-axis+1>();
    else
        return get_size_axis<axis+max_dim+1>();
}

template < class type, class device >
constexpr detail::array_shape<max_dim> detail::array_upper<type,max_dim,device>::get_shape ( ) const
{
    auto shp = detail::array_shape<max_dim>();
    for_constexpr<1,max_dim>([&] <int index> { shp[index] = get_size_axis<index>(); });
    return shp;
}

template < class type, class device >
template < int dim2 >
constexpr pair<detail::array_upper<type,dim2,device>*> detail::array_upper<type,max_dim,device>::get_rows ( integral auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host<transpose_attribute>().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr pair<const detail::array_upper<type,dim2,device>*> detail::array_upper<type,max_dim,device>::get_rows ( integral auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host<transpose_attribute>().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr pair<detail::array_upper<type,dim2,device>*> detail::array_upper<type,max_dim,device>::get_columns ( integral auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host<transpose_attribute>().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr pair<const detail::array_upper<type,dim2,device>*> detail::array_upper<type,max_dim,device>::get_columns ( integral auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host<transpose_attribute>().template get_columns<dim2>(offsets...);
}
