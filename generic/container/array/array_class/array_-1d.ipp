#pragma once

/// Class array

// Core

template < class type >
constexpr array<type,-1>::array ( array<type> init )
    extends array<type,1> ( std::move ( init ) )
{

}

template < class type >
constexpr int array<type,-1>::dimension ( )
{
    return -1;
}

// Member

template < class type >
constexpr auto& array<type,-1>::resize ( int new_size )
{
    array<type>::resize ( new_size );
    return self;
}

template < class type >
constexpr auto& array<type,-1>::operator [] ( int pos )
{
    return array<type>::operator[] ( pos );
}

template < class type >
constexpr const auto& array<type,-1>::operator [] ( int pos ) const
{
    return array<type>::operator[] ( pos );
}
template < class type >
constexpr auto array<type,-1>::operator [] ( int from, int to )
{
    return array_range_view ( self, from, to );
}

template < class type >
constexpr const auto array<type,-1>::operator [] ( int from, int to ) const
{
    return array_range_view ( const_cast<array&>(self), from, to );
}

template < class type >
constexpr auto array<type,-1>::operator [] ( int from, int to, int step )
{
    return array_range_view ( self, from, to, step );
}

template < class type >
constexpr const auto array<type,-1>::operator [] ( int from, int to, int step ) const
{
    return array_range_view ( const_cast<array&>(self), from, to, step );
}

template < class type >
constexpr auto array<type,-1>::operator [] ( unary_pred<type> auto pred )
{
    return array_filter_view ( self, pred );
}

template < class type >
constexpr const auto array<type,-1>::operator [] ( unary_pred<type> auto pred ) const
{
    return array_filter_view ( const_cast<array&>(self), pred );
}