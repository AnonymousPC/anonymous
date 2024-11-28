#pragma once

/// Class array_flatten_view

// Host

template < class container_type >
constexpr container_type& array_flatten_view<container_type>::host ( )
{
    return arr;
}

template < class container_type >
constexpr const container_type& array_flatten_view<container_type>::host ( ) const
{
    return arr;
}

// Constructor

template < class container_type >
constexpr array_flatten_view<container_type>::array_flatten_view ( container_type& init_arr )
    extends arr ( init_arr )
{

}


// Core

template < class container_type >
constexpr array_flatten_view<container_type>& array_flatten_view<container_type>::operator = ( const array_flatten_view& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.size() != right.size() )
            throw value_error("cannot copy array of shape {} into array of shape {}", right.shape(), self.shape());
    #endif

    std::copy ( right.begin(), right.end(), self.begin() );
}

template < class container_type >
constexpr array_flatten_view<container_type>& array_flatten_view<container_type>::operator = ( const array_type<value_type,1> auto& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.size() != right.size() )
            throw value_error("cannot copy array of shape {} into array of shape {}", right.shape(), self.shape());
    #endif

    std::copy ( right.begin(), right.end(), self.begin() );
}

template < class container_type >
constexpr array_flatten_view<container_type>& array_flatten_view<container_type>::operator = ( array_type<value_type,1> auto&& right )
{
    #if debug
        if ( self.size() != right.size() )
            throw value_error("cannot move array of shape {} into array of shape {}", right.shape(), self.shape());
    #endif

    std::move ( right.begin(), right.end(), self.begin() );
}


// Interface

template < class container_type >
constexpr int array_flatten_view<container_type>::size ( ) const
{
    return host().size();
}

template < class container_type >
constexpr bool array_flatten_view<container_type>::empty ( ) const
{
    return host().empty();
}

template < class container_type >
constexpr array_flatten_view<container_type>::iterator array_flatten_view<container_type>::begin ( )
{
    return iterator ( self, 1 );
}

template < class container_type >
constexpr array_flatten_view<container_type>::iterator array_flatten_view<container_type>::end ( )
{
    return iterator ( self, size() + 1 );
}

template < class container_type >
constexpr array_flatten_view<container_type>::const_iterator array_flatten_view<container_type>::begin ( ) const
{
    return const_iterator ( self, 1 );
}

template < class container_type >
constexpr array_flatten_view<container_type>::const_iterator array_flatten_view<container_type>::end ( ) const
{
    return const_iterator ( self, size() + 1 );
}

template < class container_type >
constexpr decltype(auto) array_flatten_view<container_type>::operator [] ( int pos )
{
    return locate ( host(), decompose ( host().tuple_shape(), pos ) );
}

template < class container_type >
constexpr decltype(auto) array_flatten_view<container_type>::operator [] ( int pos ) const
{
    return locate ( host(), decompose ( host().tuple_shape(), pos ) );
}





// Auxiliary

template < class container_type >
constexpr decltype(auto) array_flatten_view<container_type>::locate ( auto& target, const auto& idx )
{
    if constexpr ( target.dimension() == 1 )
        return target[idx.template get<1>()];
    else
        return locate ( target[idx.template get<1>()], idx.template get<2,-1>() );
}

template < class container_type >
constexpr decltype(auto) array_flatten_view<container_type>::locate ( const auto& target, const auto& idx )
{
    if constexpr ( target.dimension() == 1 )
        return target[idx.template get<1>()];
    else
        return locate ( target[idx.template get<1>()], idx.template get<2,-1>() );
}

template < class container_type >
constexpr auto array_flatten_view<container_type>::decompose ( const auto& shp, int s )
{
    return decompose_aux<1> ( array_coordinate<shp.size()>(), shp, s-1, shp.template get<2,-1>().product() );
}

template < class container_type >
template < int index >
constexpr auto array_flatten_view<container_type>::decompose_aux ( auto&& idx, const auto& shp, int s, int p )
{
    let r = s / p;
    s -= r * p; // s %= p.
    idx.template get<index>() = r + 1;

    if constexpr ( index != idx.size() )
        return decompose_aux<index+1> ( idx, shp, s, p / shp.template get<index+1>() );
    else
        return idx;
}