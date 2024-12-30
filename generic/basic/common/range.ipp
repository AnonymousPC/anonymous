#pragma once

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
                throw value_error("range from {} to {} with step {} is invalid", low, high, step);

        if constexpr ( requires { step <=> 0; low - high <=> step; } )
            if ( ( step > 0 and low - high > 0 ) or
                 ( step < 0 and low - high < 0 ) )
                throw value_error("range from {} to {} with step {} is invalid", low, high, step);
    #endif
}

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

template < class type >
constexpr typename range<type>::value_type range<type>::operator [] ( int pos ) const
{
    #if debug
        if ( pos < -size() or pos == 0 or pos > size() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    return pos > 0 ? low + (pos-1) * step otherwise low + (pos+size()) * step;
}



/// Iterator

template < class type >
class range<type>::iterator
{
    public: // Typedef
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = range<type>::value_type;
        using pointer           = value_type*;
        using reference         = value_type&;

    private: // Data
        value_type val  = value_type();
        value_type step = value_type();

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( value_type, value_type );

    public: // Member
        constexpr        type&     operator *   ( );
        constexpr        type*     operator ->  ( );
        constexpr friend bool      operator ==  ( const iterator&, const iterator& );
        constexpr friend auto      operator <=> ( const iterator&, const iterator& );
        constexpr friend iterator  operator  +  ( const iterator&,       int       );
        constexpr friend iterator  operator  +  (       int,       const iterator& );
        constexpr friend iterator  operator  -  ( const iterator&,       int       );
        constexpr friend int       operator  -  ( const iterator&, const iterator& );
        constexpr friend iterator& operator ++  (       iterator&                  );
        constexpr friend iterator  operator ++  (       iterator&, int             );
        constexpr friend iterator& operator --  (       iterator&                  );
        constexpr friend iterator  operator --  (       iterator&, int             );
};

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
constexpr bool operator == ( const typename range<type>::iterator& left, const typename range<type>::iterator& right )
{
    #if debug
        if ( left.step != right.step )
            throw value_error("range::iterator not equalable (with left = {}, right = {})", left, right);
    #endif

    return left.step > 0 ? left.val < right.val otherwise left.val > right.val;
}

template < class type >
constexpr auto operator <=> ( const typename range<type>::iterator& left, const typename range<type>::iterator& right )
{
    #if debug
        if ( left.step != right.step )
            throw value_error("range::iterator not comparable (with left = {}, right = {})", left, right);
    #endif

    return left.step > 0 ? left.val <=> right.val otherwise - ( left.val <=> right.val );
}

template < class type >
constexpr range<type>::iterator operator + ( const typename range<type>::iterator& left, int right )
{
    return range<type>::iterator ( left.val + left.step * right, left.step );
}

template < class type >
constexpr range<type>::iterator operator + ( int left, const typename range<type>::iterator& right )
{
    return range<type>::iterator ( right.val + left * right.step, right.step );
}


template < class type >
constexpr range<type>::iterator operator - ( const typename range<type>::iterator& left, int right ) 
{
    return range<type>::iterator ( left.val - left.step * right, left.step );
}

template < class type >
constexpr int operator - ( const typename range<type>::iterator& left, const typename range<type>::iterator& right )
{
    #if debug
        if ( left.step != right.step )
            throw value_error("range::iterator not minusable (with left = {}, right = {})", left, right);
    #endif

    return ( left.val - right.val ) / left.step;
}

template < class type >
constexpr range<type>::iterator& operator ++ ( typename range<type>::iterator& left )
{
    left.val += left.step;
    return left;
}

template < class type >
constexpr range<type>::iterator operator ++ ( typename range<type>::iterator& left, int )
{
    let other = left;
    ++left;
    return other;
}

template < class type >
constexpr range<type>::iterator& operator -- ( typename range<type>::iterator& left )
{
    left.val -= left.step;
    return left;
}

template < class type >
constexpr range<type>::iterator operator -- ( typename range<type>::iterator& left, int )
{
    let other = left;
    --left;
    return other;
}



