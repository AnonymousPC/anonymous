template < class type, class device >
constexpr array_upper<type,max_dim,device>::array_upper ( array<type,max_dim,device>& init_host )
    extends ptr ( &init_host )
{

}

template < class type, class device >
constexpr array_upper<type,max_dim,device>::array_upper ( const array<type,max_dim,device>& init_host )
    extends ptr ( &const_cast<array_upper<type,max_dim,device>&>(init_host) )
{
    
}

template < class type, class device >
constexpr int array_upper<type,max_dim,device>::size ( ) const
{
    return get_host().size();
}

template < class type, class device >
constexpr static_array<int,max_dim> array_upper<type,max_dim,device>::shape ( ) const
{
    auto s1 = get_host().shape();
    auto s2 = static_array<int,max_dim>();
    for_constexpr<1,max_dim>([&] <int index> { s2[index] = s1[-index]; });
    return s2;
}

template < class type, class device >
constexpr int array_upper<type,max_dim,device>::row ( ) const
{
    return get_host().shape()[-1]; 
}

template < class type, class device >
constexpr int array_upper<type,max_dim,device>::column ( ) const    
    requires ( max_dim == 2 )
{
    return get_host().shape()[1]; 
}

template < class type, class device >
constexpr bool array_upper<type,max_dim,device>::empty ( ) const
{
    return get_host().empty();
}

template < class type, class device >
constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::begin ( )
{
    return get_host().template get_columns<max_dim-1>().begin();
}

template < class type, class device >
constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::begin ( ) const
{
    return get_host().template get_columns<max_dim-1>().begin();
}

template < class type, class device >
constexpr array_upper<type,max_dim,device>::iterator array_upper<type,max_dim,device>::end ( )
{
    return get_host().template get_columns<max_dim-1>().end();
}

template < class type, class device >
constexpr array_upper<type,max_dim,device>::const_iterator array_upper<type,max_dim,device>::end ( ) const
{
    return get_host().template get_columns<max_dim-1>().end();
}

template < class type, class device >
constexpr array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int offset )
{
    return static_cast<array<type,max_dim-1,device>&>(get_host().template get_columns<max_dim-1>()[offset]);
}

template < class type, class device >
constexpr const array<type,max_dim-1,device>& array_upper<type,max_dim,device>::operator [] ( int offset ) const
{
    return static_cast<const array<type,max_dim-1,device>&>(get_host().template get_columns<max_dim-1>()[offset]);
}

template < class type, class device >
constexpr bool array_upper<type,max_dim,device>::ownership ( ) const
{
    return ptr == nullptr;
}

template < class type, class device >
constexpr array<type,max_dim,device>& array_upper<type,max_dim,device>::get_host ( )
{
    return *ptr;
}

template < class type, class device >
constexpr const array<type,max_dim,device>& array_upper<type,max_dim,device>::get_host ( ) const
{
    return *ptr;
}

template < class type, class device >
template < int axis >
constexpr int array_upper<type,max_dim,device>::get_size_axis ( ) const
{
    static_assert ( axis >= 1 and axis <= max_dim );
    return get_host().template get_size_axis<max_dim-axis+1>();
}

template < class type, class device >
template < int dim2 >
constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_rows ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_rows ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_columns ( int_type auto... offsets )
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host().template get_columns<dim2>(offsets...);
}

template < class type, class device >
template < int dim2 >
constexpr const std::span<array_upper<type,dim2,device>> array_upper<type,max_dim,device>::get_columns ( int_type auto... offsets ) const
{
    static_assert ( dim2 > 0 and dim2 < max_dim );
    static_assert ( sizeof...(offsets) == max_dim - dim2 - 1 );
    return get_host().template get_columns<dim2>(offsets...);
}
