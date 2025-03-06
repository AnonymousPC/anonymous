#pragma once

template < class type >
constexpr range<type>::range ( value_type init_high )
    requires int_type<type>
    extends range ( 1, init_high )
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
        if ( ( step > 0 and low - high > step ) or
             ( step < 0 and low - high < step ) )
            throw value_error("range from {} to {} with step {} is invalid", low, high, step);
    #endif
}

template < class type >
template < class type2 >
constexpr range<type>::range ( range<type2> cvt )
    requires ( int_type  <type> and int_type  <type2> ) or
             ( float_type<type> and float_type<type2> )
    extends low  ( cvt.low  ),
            high ( cvt.high ),
            step ( cvt.step )
{

}

template < class type >
constexpr typename range<type>::const_iterator range<type>::begin ( ) const
{
    return const_iterator ( low, step );
}

template < class type >
constexpr typename range<type>::const_iterator range<type>::end ( ) const
{
    return const_iterator ( low + ( ( high - low ) / step + 1 ) * step, step );
}

template < class type >
constexpr int range<type>::size ( ) const
{
    return (high - low) / step + 1;
}



/// Iterator

template < class type >
class range<type>::const_iterator
{
    public: // Typedef
        using iterator_concept  = std::random_access_iterator_tag;
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = range<type>::value_type;
        using pointer           = value_type*;
        using reference         = value_type&;

    private: // Data
        value_type val  = value_type();
        value_type step = value_type();

    public: // Core
        constexpr const_iterator ( ) = default;

        constexpr const_iterator ( value_type init_val, value_type init_step )   
            extends val  ( init_val  ),
                    step ( init_step )
        {

        }

    public: // Member
        constexpr type& operator * ( )
        {
            return val;
        }

        constexpr type* operator -> ( )
        {
            return &val;
        }
        
        constexpr friend bool operator == ( const const_iterator& left, const const_iterator& right )
        {
            return left.val == right.val;
        }

        constexpr friend auto operator <=> ( const const_iterator& left, const const_iterator& right )
        {
            [[assume(left.step == right.step)]];
            return left.step > 0 ? left.val <=> right.val otherwise right.val <=> left.val;
        }

        constexpr friend const_iterator operator + ( const const_iterator& left, int right )
        {
            return const_iterator ( left.val + left.step * right, left.step );
        }

        constexpr friend const_iterator operator + ( int left, const const_iterator& right )
        {
            return const_iterator ( right.val + left * right.step, right.step );
        }

        constexpr friend const_iterator operator - ( const const_iterator& left, int right )
        {
            return const_iterator ( left.val - left.step * right, left.step );
        }

        constexpr friend int operator - ( const const_iterator& left, const const_iterator& right )
        {
            [[assume(left.step == right.step)]];
            return ( left.val - right.val ) / left.step;
        }

        constexpr friend const_iterator& operator ++ ( const_iterator& left )
        {
            left.val += left.step;
            return left;
        }

        constexpr friend const_iterator operator ++ ( const_iterator& left, int )
        {
            let other = left;
            ++left;
            return other;
        }

        constexpr friend const_iterator& operator -- ( const_iterator& left )
        {
            left.val -= left.step;
            return left;
        }

        constexpr friend const_iterator operator -- ( const_iterator& left, int )
        {
            let other = left;
            --left;
            return other;
        }
};


