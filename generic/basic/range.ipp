#pragma once

/// Class range

// Core

template < class type >
constexpr range<type>::range ( value_type init_high )
    extends range<type> ( 1, init_high, 1 )
{

}

template < class type >
constexpr range<type>::range ( value_type init_low, value_type init_high, value_type init_step )
    extends low  ( init_low  ),
            high ( init_high ),
            step ( init_step )
{
    #if debug
        if constexpr ( requires { step == 0; low - high != 0; } )
            if ( step == 0 and low - high != 0 )
                throw value_error("range from {} to {} with step {} does not work", low, high, step);

        if constexpr ( requires { step <=> 0; low - high <=> step; } )
            if ( ( step > 0 and low - high > 0 ) or
                 ( step < 0 and low - high < 0 ) )
                throw value_error("range from {} to {} with step {} does not work", low, high, step);
    #endif
}

// Member

template < class type >
constexpr typename range<type>::iterator range<type>::begin ( ) const
{
    return iterator ( low, step );
}

template < class type >
constexpr typename range<type>::iterator range<type>::end ( ) const
{
    return iterator ( low + size() * step, step );
}

template < class type >
constexpr int range<type>::size ( ) const
{
    int num = ( high - low ) / step + 1;
    return num > 0 ? num otherwise 0;
}

template < class type >
constexpr bool range<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
constexpr typename range<type>::value_type range<type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? low + (pos-1) * step otherwise low + (pos+size()) * step;
}

template < class type >
constexpr const typename range<type>::value_type& range<type>::min ( ) const
{
    return low;
}

template < class type >
constexpr const typename range<type>::value_type& range<type>::max ( ) const
{
    return high;
}

template < class type >
constexpr const typename range<type>::value_type& range<type>::sep ( ) const
{
    return step;
}



/// Iterator

template < class type >
constexpr range<type>::iterator::iterator ( value_type init_val, value_type init_step )
    extends val  ( init_val  ),
            step ( init_step )
{

}

template < class type >
constexpr type& range<type>::iterator::operator * ( )
{
    return val;
}

template < class type >
constexpr type* range<type>::iterator::operator -> ( )
{
    return &val;
}

template < class type >
constexpr bool range<type>::iterator::operator != ( const iterator& right ) const
{
    return step > 0 ? self.val < right.val otherwise
                      self.val > right.val;
}

template < class type >
constexpr range<type>::iterator& range<type>::iterator::operator ++ ( )
{
    val += step;
    return self;
}

template < class type >
constexpr range<type>::iterator range<type>::iterator::operator ++ ( int )
{
    iterator other = self;
    val += step;
    return other;
}

template < class type >
constexpr range<type>::iterator& range<type>::iterator::operator -- ( )
{
    val -= step;
    return self;
}

template < class type >
constexpr range<type>::iterator range<type>::iterator::operator -- ( int )
{
    iterator other = self;
    val -= step;
    return other;
}

template < class type >
constexpr range<type>::iterator range<type>::iterator::operator + ( int right ) const
{
    return iterator ( val + step * right, step );
}

template < class type >
constexpr range<type>::iterator range<type>::iterator::operator - ( int right ) const
{
    return iterator ( val - step * right, step );
}

template < class type >
constexpr int range<type>::iterator::operator - ( const iterator& right ) const
{
    #if debug
        if ( step != right.step )
            throw value_error("subtracting range::iterator with different steps {} and {}", step, right.step);
    #endif

    return ( val - right.val ) / step;
}