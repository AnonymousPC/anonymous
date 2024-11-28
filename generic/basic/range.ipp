#pragma once

/// Class range (continuous)

// Core

template < class type >
    requires minusable<type>
constexpr range<type,true>::range ( value_type init_high )
    extends range<type,true> ( 1, init_high )
{

}

template < class type >
    requires minusable<type>
constexpr range<type,true>::range ( value_type init_low, value_type init_high )
    extends low  ( init_low  ),
            high ( init_high )
{
    #if debug
        if ( low > high + 1 )
            throw value_error("range from {} to {} does not work", low, high);
    #endif

}

template < class type >
    requires minusable<type>
constexpr range<type,true>::operator range<type,false> ( ) const
{
    return range<type,false> ( min(), max() );
}

// Member

template < class type >
    requires minusable<type>
constexpr typename range<type,true>::iterator range<type,true>::begin ( ) const
{
    return iterator ( low );
}

template < class type >
    requires minusable<type>
constexpr typename range<type,true>::iterator range<type,true>::end ( ) const
{
    return iterator ( high + 1 );
}

template < class type >
    requires minusable<type>
constexpr int range<type,true>::size ( ) const
{
    int num = high - low + 1;
    return num > 0 ? num otherwise 0;
}

template < class type >
    requires minusable<type>
constexpr bool range<type,true>::empty ( ) const
{
    return size() == 0;
}

template < class type >
    requires minusable<type>
constexpr type range<type,true>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
           throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? low + pos - 1 otherwise low + pos + size();
}

template < class type >
    requires minusable<type>
constexpr const type& range<type,true>::min ( ) const
{
    return low;
}

template < class type >
    requires minusable<type>
constexpr const type& range<type,true>::max ( ) const
{
    return high;
}

// Iterator

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator::iterator ( type init_data )
    extends data ( init_data )
{

}

template < class type >
    requires minusable<type>
constexpr type& range<type,true>::iterator::operator * ( )
{
    return data;
}

template < class type >
    requires minusable<type>
constexpr type* range<type,true>::iterator::operator -> ( )
{
    return &data;
}

template < class type >
    requires minusable<type>
constexpr bool range<type,true>::iterator::operator != ( const iterator& right ) const
{
    return self.data < right.data;
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator& range<type,true>::iterator::operator ++ ( )
{
    ++data;
    return self;
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator range<type,true>::iterator::operator ++ ( int )
{
    iterator other = self;
    ++data;
    return other;
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator& range<type,true>::iterator::operator -- ( )
{
    --data;
    return self;
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator range<type,true>::iterator::operator -- ( int )
{
    iterator other = self;
    --data;
    return other;
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator range<type,true>::iterator::operator + ( int right ) const
{
    return iterator ( data + right );
}

template < class type >
    requires minusable<type>
constexpr range<type,true>::iterator range<type,true>::iterator::operator - ( int right ) const
{
    return iterator ( data - right );
}

template < class type >
    requires minusable<type>
constexpr int range<type,true>::iterator::operator - ( const iterator& right ) const
{
    return self.data - right.data;
}











/// Class range (not continuous)

// Core

template < class type >
    requires minusable<type>
constexpr range<type>::range ( value_type init_high )
    extends range<type> ( 1, init_high, 1 )
{

}

template < class type >
    requires minusable<type>
constexpr range<type>::range ( value_type init_low, value_type init_high, difference_type init_step )
    extends low  ( init_low  ),
            high ( init_high ),
            step ( init_step )
{
    #if debug
        if constexpr ( requires { step == 0; low - high != 0; } )
            if ( step == 0 and low - high != 0 )
                throw value_error("range from {} to {} with step {} does not work", low, high, step);

        if constexpr ( requires { step <=> 0; low - high <=> step; } )
            if ( ( step > 0 and low - high > step ) or
                 ( step < 0 and low - high < step ) )
                throw value_error("range from {} to {} with step {} does not work", low, high, step);
    #endif
}

// Member

template < class type >
    requires minusable<type>
constexpr typename range<type>::iterator range<type>::begin ( ) const
{
    return iterator ( low, step );
}

template < class type >
    requires minusable<type>
constexpr typename range<type>::iterator range<type>::end ( ) const
{
    return iterator ( low + size() * step, step );
}

template < class type >
    requires minusable<type>
constexpr int range<type>::size ( ) const
{
    int num = ( high - low ) / step + 1;
    return num > 0 ? num otherwise 0;
}

template < class type >
    requires minusable<type>
constexpr bool range<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
    requires minusable<type>
constexpr typename range<type>::value_type range<type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? low + (pos-1) * step otherwise low + (pos+size()) * step;
}

template < class type >
    requires minusable<type>
constexpr const typename range<type>::value_type& range<type>::min ( ) const
{
    return low;
}

template < class type >
    requires minusable<type>
constexpr const typename range<type>::value_type& range<type>::max ( ) const
{
    return high;
}

template < class type >
    requires minusable<type>
constexpr const typename range<type>::difference_type& range<type>::sep ( ) const
{
    return step;
}



/// Iterator

template < class type >
    requires minusable<type>
constexpr range<type>::iterator::iterator ( value_type init_data, difference_type init_step )
    extends data ( init_data ),
            step ( init_step )
{

}

template < class type >
    requires minusable<type>
constexpr type& range<type>::iterator::operator * ( )
{
    return data;
}

template < class type >
    requires minusable<type>
constexpr type* range<type>::iterator::operator -> ( )
{
    return &data;
}

template < class type >
    requires minusable<type>
constexpr bool range<type>::iterator::operator != ( const iterator& right ) const
{
    return step > 0 ? self.data < right.data otherwise
                      self.data > right.data;
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator& range<type>::iterator::operator ++ ( )
{
    data += step;
    return self;
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator range<type>::iterator::operator ++ ( int )
{
    iterator other = self;
    data += step;
    return other;
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator& range<type>::iterator::operator -- ( )
{
    data -= step;
    return self;
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator range<type>::iterator::operator -- ( int )
{
    iterator other = self;
    data -= step;
    return other;
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator range<type>::iterator::operator + ( int right ) const
{
    return iterator ( data + step * right, step );
}

template < class type >
    requires minusable<type>
constexpr range<type>::iterator range<type>::iterator::operator - ( int right ) const
{
    return iterator ( data - step * right, step );
}

template < class type >
    requires minusable<type>
constexpr int range<type>::iterator::operator - ( const iterator& right ) const
{
    #if debug
        if ( step != right.step )
            throw value_error("subtracting range::iterator with different steps {} and {}", step, right.step);
    #endif

    return ( data - right.data ) / step;
}