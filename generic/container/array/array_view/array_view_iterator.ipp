#pragma once

/// Class array_view_iterator

// Host

template < class array_view_type >
constexpr array_view_type& array_view_iterator<array_view_type>::host ( ) const
{
    return *arr_ptr;
}

// Core

template < class array_view_type >
constexpr array_view_iterator<array_view_type>::array_view_iterator ( array_view_type& init_arr, int init_pos )
    extends arr_ptr ( &init_arr ),
            pos     ( init_pos )
{
    #if debug
        if ( init_pos < 0 )
            throw index_error();
    #endif
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type>& array_view_iterator<array_view_type>::operator = ( const array_view_iterator<array_view_type>& right )
{
    if ( self.arr_ptr == right.arr_ptr ) [[likely]]
        pos = right.pos;

    else
    {
        #if debug
            if ( arr_ptr != nullptr )
                throw value_error();
        #endif

        arr_ptr = right.arr_ptr;
        pos     = right.pos;
    }

    return self;
}

// Operator

template < class array_view_type >
constexpr decltype(auto) array_view_iterator<array_view_type>::operator * ( ) const
{
    #if debug
        if constexpr ( array_view_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error();
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error();
    #endif

    return host()[pos];
}

template < class array_view_type >
constexpr decltype(auto) array_view_iterator<array_view_type>::operator -> ( ) const
{
    #if debug
        if constexpr ( array_view_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error();
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error();
    #endif

    return &host()[pos]; // If host()[pos] returns a rvalue, it's bad.
}

template < class array_view_type >
constexpr decltype(auto) array_view_iterator<array_view_type>::operator [] ( int offset ) const
{
    return *( self + offset );
}

template < class array_view_type >
constexpr bool array_view_iterator<array_view_type>::operator == ( const array_view_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &self.host() != &right.host() )
            throw value_error();
    #endif

    return pos == right.pos;
}

template < class array_view_type >
constexpr std::strong_ordering array_view_iterator<array_view_type>::operator <=> ( const array_view_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &self.host() != &right.host() )
            throw value_error();
    #endif

    return pos <=> right.pos;
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type> array_view_iterator<array_view_type>::operator + ( int val ) const
{
    return array_view_iterator<array_view_type> ( host(), pos + val );
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type> array_view_iterator<array_view_type>::operator - ( int val ) const
{
    return array_view_iterator<array_view_type> ( host(), pos - val );
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type>::difference_type array_view_iterator<array_view_type>::operator - ( const array_view_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &host() != &right.host() )
            throw value_error();
    #endif

    return pos - right.pos;
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type>& array_view_iterator<array_view_type>::operator ++ ( )
{
    self.pos ++;
    return self;
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type> array_view_iterator<array_view_type>::operator ++ ( int )
{
    auto it = self;
    self.pos ++;
    return it;
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type>& array_view_iterator<array_view_type>::operator -- ( )
{
    self.pos --;
    return self;
}

template < class array_view_type >
constexpr array_view_iterator<array_view_type> array_view_iterator<array_view_type>::operator -- ( int )
{
    auto it = self;
    self.pos --;
    return it;
}



/// Class array_view_const_iterator

// Host

template < class array_view_type >
constexpr const array_view_type& array_view_const_iterator<array_view_type>::host ( ) const
{
    return *arr_ptr;
}

// Core

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type>::array_view_const_iterator ( const array_view_type& init_arr, int init_pos )
    extends arr_ptr ( &init_arr ),
            pos     ( init_pos )
{
    #if debug
        if ( init_pos < 0 )
            throw index_error();
    #endif
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type>& array_view_const_iterator<array_view_type>::operator = ( const array_view_const_iterator<array_view_type>& right )
{
    if ( self.arr_ptr == right.arr_ptr ) [[likely]]
        pos = right.pos;

    else
    {
        #if debug
            if ( arr_ptr != nullptr )
                throw value_error();
        #endif

        arr_ptr = right.arr_ptr;
        pos     = right.pos;
    }
    return self;
}

// Operator

template < class array_view_type >
constexpr decltype(auto) array_view_const_iterator<array_view_type>::operator * ( ) const
{
    #if debug
        if constexpr ( array_view_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error();
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error();
    #endif

    return host()[pos];
}

template < class array_view_type >
constexpr decltype(auto) array_view_const_iterator<array_view_type>::operator -> ( ) const
{
    #if debug
        if constexpr ( array_view_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error();
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error();
    #endif

    return &host()[pos]; // If host()[pos] returns a rvalue, it's bad.
}

template < class array_view_type >
constexpr decltype(auto) array_view_const_iterator<array_view_type>::operator [] ( int offset ) const
{
    return *( self + offset );
}

template < class array_view_type >
constexpr bool array_view_const_iterator<array_view_type>::operator == ( const array_view_const_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &self.host() != &right.host() )
            throw value_error();
    #endif

    return pos == right.pos;
}

template < class array_view_type >
constexpr std::strong_ordering array_view_const_iterator<array_view_type>::operator <=> ( const array_view_const_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &self.host() != &right.host() )
            throw value_error();
    #endif

    return pos <=> right.pos;
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type> array_view_const_iterator<array_view_type>::operator + ( int val ) const
{
    return array_view_const_iterator<array_view_type> ( host(), pos + val );
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type> array_view_const_iterator<array_view_type>::operator - ( int val ) const
{
    return array_view_const_iterator<array_view_type> ( host(), pos - val );
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type>::difference_type array_view_const_iterator<array_view_type>::operator - ( const array_view_const_iterator<array_view_type>& right ) const
{
    #if debug
        if ( &host() != &right.host() )
            throw value_error();
    #endif

    return pos - right.pos;
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type>& array_view_const_iterator<array_view_type>::operator ++ ( )
{
    self.pos ++;
    return self;
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type> array_view_const_iterator<array_view_type>::operator ++ ( int )
{
    auto it = self;
    self.pos ++;
    return it;
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type>& array_view_const_iterator<array_view_type>::operator -- ( )
{
    self.pos --;
    return self;
}

template < class array_view_type >
constexpr array_view_const_iterator<array_view_type> array_view_const_iterator<array_view_type>::operator -- ( int )
{
    auto it = self;
    self.pos --;
    return it;
}