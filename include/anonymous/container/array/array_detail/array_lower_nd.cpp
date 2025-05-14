template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>::array_lower ( )
    extends transpose_view ( static_cast<array<type,dim,device>&>(self) )
{
    
}

template < class type, int dim, class device > 
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>::iterator detail::array_lower<type,dim,device>::begin ( )
{
    return get_rows<dim-1>().first;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>::const_iterator detail::array_lower<type,dim,device>::begin ( ) const
{
    return get_rows<dim-1>().first;
}

template < class type, int dim, class device > 
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>::iterator detail::array_lower<type,dim,device>::end ( )
{
    return get_rows<dim-1>().second;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>::const_iterator detail::array_lower<type,dim,device>::end ( ) const
{
    return get_rows<dim-1>().second;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim-1,device>& detail::array_lower<type,dim,device>::operator [] ( int offset )
{
    return begin()[offset];
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim-1,device>& detail::array_lower<type,dim,device>::operator [] ( int offset ) const
{
    return begin()[offset];
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr detail::array_lower<type,dim,device>& detail::array_lower<type,dim,device>::clear ( )
{
    rows_view   .clear();
    columns_view.clear();
    return self;
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr array<type,dim,device>& detail::array_lower<type,dim,device>::transpose ( )
{
    return static_cast<array<type,dim,device>&>(transpose_view);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr const array<type,dim,device>& detail::array_lower<type,dim,device>::transpose ( ) const
{
    return static_cast<const array<type,dim,device>&>(transpose_view);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr pair<detail::array_upper<type,dim2,device>*> detail::array_lower<type,dim,device>::get_rows ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return rows_view.template value<rows_attribute,dim2>(static_cast<array<type,dim,device>&>(self).get_shape(), offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr pair<const detail::array_upper<type,dim2,device>*> detail::array_lower<type,dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return rows_view.template value<rows_attribute,dim2>(static_cast<const array<type,dim,device>&>(self).get_shape(), offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr pair<detail::array_upper<type,dim2,device>*> detail::array_lower<type,dim,device>::get_columns ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return columns_view.template value<columns_attribute,dim2>(static_cast<array<type,dim,device>&>(self).get_shape(), offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
template < int dim2 >
constexpr pair<const detail::array_upper<type,dim2,device>*> detail::array_lower<type,dim,device>::get_columns ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < dim );
    static_assert ( sizeof...(offsets) == dim - dim2 - 1 );
    return columns_view.template value<columns_attribute,dim2>(static_cast<const array<type,dim,device>&>(self).get_shape(), offsets...);
}

template < class type, int dim, class device >
    requires ( dim >= 2 )
constexpr void detail::array_lower<type,dim,device>::set_resize ( detail::array_shape<dim> new_shape )
{
    rows_view   .template resize<rows_attribute   >(new_shape, static_cast<array<type,dim,device>&>(self));
    columns_view.template resize<columns_attribute>(new_shape, static_cast<array<type,dim,device>&>(self));
}







