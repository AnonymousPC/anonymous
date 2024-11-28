#pragma once

/// Class array_reshape_view

// Host

template < class container_type, int dim, int dim_to_fill >
constexpr container_type& array_reshape_view<container_type,dim,dim_to_fill>::host ( )
{
    return arr;
}

template < class container_type, int dim, int dim_to_fill >
constexpr const container_type& array_reshape_view<container_type,dim,dim_to_fill>::host ( ) const
{
    return arr;
}

// Constructor

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::array_reshape_view ( container_type& init_arr, const coor_type& init_new_shape, const coor_type& init_new_index )
    extends arr       ( init_arr ),
            new_shape ( init_new_shape ),
            new_index ( init_new_index )
{
    #if debug
        if ( dim_to_fill == 1 and new_shape.product() != host().size() )
            throw value_error();
    #endif
}

// N-dimension

template < class container_type, int dim, int dim_to_fill >
constexpr int array_reshape_view<container_type,dim,dim_to_fill>::dimension ( )
{
    return dim - dim_to_fill + 1;
}

template < class container_type, int dim, int dim_to_fill >
constexpr array<int> array_reshape_view<container_type,dim,dim_to_fill>::shape ( ) const
{
    return array<int> ( tuple_shape() );
}

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::coor_type array_reshape_view<container_type,dim,dim_to_fill>::tuple_shape ( ) const
{
    return new_shape;
}

template < class container_type, int dim, int dim_to_fill >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::reshape ( int_type auto... args )
    requires ( ( dim == 1 and sizeof...(args) >= 2 ) or ( dim >= 2 and sizeof...(args) >= 1 ) )
{
    return host().reshape(args...); // Directly forward into new shape.
}


template < class container_type, int dim, int dim_to_fill >
constexpr const auto array_reshape_view<container_type,dim,dim_to_fill>::reshape ( int_type auto... args ) const
    requires ( ( dim == 1 and sizeof...(args) >= 2 ) or ( dim >= 2 and sizeof...(args) >= 1 ) )
{
    return host().reshape(args...); // Directly forward into new shape.
}


// Interface

template < class container_type, int dim, int dim_to_fill >
constexpr int array_reshape_view<container_type,dim,dim_to_fill>::row ( ) const
    requires ( dimension() >= 2 )
{
    return new_shape.template get<dim_to_fill>();
}

template < class container_type, int dim, int dim_to_fill >
constexpr int array_reshape_view<container_type,dim,dim_to_fill>::size ( ) const
{
    return new_shape.template get<dim_to_fill,-1>().product();
}

template < class container_type, int dim, int dim_to_fill >
constexpr bool array_reshape_view<container_type,dim,dim_to_fill>::empty ( ) const
{
    return size() == 0;
}

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::iterator array_reshape_view<container_type,dim,dim_to_fill>::begin ( )
{
    return iterator ( self, 1 );
}

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::const_iterator array_reshape_view<container_type,dim,dim_to_fill>::begin ( ) const
{
    return const_iterator ( self, 1 );
}

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::iterator array_reshape_view<container_type,dim,dim_to_fill>::end ( )
{
    if constexpr ( dimension() == 1 )
        return iterator ( self, size() + 1 );
    else
        return iterator ( self, row() + 1 );
}

template < class container_type, int dim, int dim_to_fill >
constexpr array_reshape_view<container_type,dim,dim_to_fill>::const_iterator array_reshape_view<container_type,dim,dim_to_fill>::end ( ) const
{
    if constexpr ( dimension() == 1 )
        return const_iterator ( self, size() + 1 );
    else
        return const_iterator ( self, row() + 1 );
}

template < class container_type, int dim, int dim_to_fill >
constexpr decltype(auto) array_reshape_view<container_type,dim,dim_to_fill>::operator [] ( int pos )
    requires ( dimension() == 1 )
{
    let complete_index = new_index;
        complete_index.template get<-1>() = pos;
    let old_shape      = host().tuple_shape();
    let old_index      = decompose ( old_shape, compose ( complete_index, new_shape ) );

    return self.at ( old_index );
}

template < class container_type, int dim, int dim_to_fill >
constexpr decltype(auto) array_reshape_view<container_type,dim,dim_to_fill>::operator [] ( int pos ) const
    requires ( dimension() == 1 )
{
    let complete_index = new_index;
        complete_index.template get<-1>() = pos;
    let old_shape      = host().tuple_shape();
    let old_index      = decompose ( old_shape, compose ( complete_index, new_shape ) );

    return self.at ( old_index );
}

template < class container_type, int dim, int dim_to_fill >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::operator [] ( int pos )
    requires ( dimension() >= 2 )
{
    let filled_index = new_index;
    filled_index.template get<dim_to_fill>() = pos;

    return array_reshape_view<container_type,dim,dim_to_fill+1> ( host(), new_shape, filled_index );
}

template < class container_type, int dim, int dim_to_fill >
constexpr const auto array_reshape_view<container_type,dim,dim_to_fill>::operator [] ( int pos ) const
    requires ( dimension() >= 2 )
{
    let filled_index = new_index;
    filled_index.template get<dim_to_fill>() = pos;

    return array_reshape_view<container_type,dim,dim_to_fill+1> ( const_cast<container_type&>(host()), new_shape, filled_index );
}



// Auxiliary

template < class container_type, int dim, int dim_to_fill >
constexpr decltype(auto) array_reshape_view<container_type,dim,dim_to_fill>::at ( const auto& index )
{
    if constexpr ( container_type::dimension() == 1 )
        return host()[index.template get<1>()];
    else
        return array_reshape_view<typename std::decay<decltype(host())>::type::iterate_type,dim,dim_to_fill+1> ( host()[index.template get<1>()], new_shape ) .at ( index.template get<2,-1>() );
}

template < class container_type, int dim, int dim_to_fill >
constexpr decltype(auto) array_reshape_view<container_type,dim,dim_to_fill>::at ( const auto& index ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return host()[index.template get<1>()];
    else
        return array_reshape_view<typename std::decay<decltype(host())>::type::iterate_type,dim,dim_to_fill+1> ( host()[index.template get<1>()], new_shape ) .at ( index.template get<2,-1>() );
}

template < class container_type, int dim, int dim_to_fill >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::compose ( const auto& index, const auto& shp )
{
    if constexpr ( shp.size() == 1 )
        return index.template get<1>();
    else
        return compose_aux<-1> ( index, shp, 0, 1 ) + 1;
}

template < class container_type, int dim, int dim_to_fill >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::decompose ( const auto& shp, int s )
{
    if constexpr ( shp.size() == 1 )
        return array_coordinate<shp.size()>(s);
    else
        return decompose_aux<1> ( array_coordinate<shp.size()>(), shp, s-1, shp.template get<2,-1>().product() );
}

template < class container_type, int dim, int dim_to_fill >
template < int index >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::compose_aux ( const auto& idx, const auto& shp, int s, int p )
{
    s += ( idx.template get<index>() - 1 ) * p;

    if constexpr ( index != -idx.size() )
        return compose_aux<index-1> ( idx, shp, s, p * shp.template get<index>() );
    else
        return s;
}

template < class container_type, int dim, int dim_to_fill >
template < int index >
constexpr auto array_reshape_view<container_type,dim,dim_to_fill>::decompose_aux ( auto&& idx, const auto& shp, int s, int p )
{
    let r = s / p;
    s -= r * p; // s %= p.
    idx.template get<index>() = r + 1;

    if constexpr ( index != idx.size() )
        return decompose_aux<index+1> ( idx, shp, s, p / shp.template get<index+1>() );
    else
        return idx;
}