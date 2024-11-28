#pragma once

/// Class fraction

template < int_type type >
class fraction
{
    private: // Data
        type x = 0;
        type y = 1;

    public: // Typedef
        using value_type = type;
        struct float_tag    { };
        struct fraction_tag { };

    public: // Core
        constexpr fraction ( ) = default;
        constexpr fraction ( type );
        constexpr fraction ( type, type );
        constexpr const type& num ( ) const;
        constexpr const type& den ( ) const;

    public: // Conversion
        template < fraction_type type2 > constexpr fraction ( type2 )                        requires ( not std::same_as<fraction,type2> );
        template < int_type      type2 > constexpr fraction ( type2 );
        template < float_type    type2 > constexpr fraction ( type2 )         [[deprecated]] requires ( not fraction_type<type2> );
        template < number_type   type2 > constexpr operator   type2 ( ) const                requires ( not fraction_type<type2> );

    public: // Operator
        constexpr bool operator == ( const fraction& ) const = default;
        constexpr bool operator != ( const fraction& ) const = default;

    private: // Auxiliary
        constexpr static void reduce ( int_type auto&, int_type auto& );
        constexpr static void expand ( int_type auto&, int_type auto&, float_type auto& );
};

// Core

template < int_type type >
constexpr fraction<type>::fraction ( type a )
    extends x ( a )
{

}

template < int_type type >
constexpr fraction<type>::fraction ( type a, type b )
{
    if ( b == 0 )
        throw math_error("{} / {}", a, b);

    if ( a != 0 )
    {
        reduce ( a, b );

        x = b > 0 ? a otherwise -a;
        y = b > 0 ? b otherwise -b;
    }
}

template < int_type type >
constexpr const type& fraction<type>::num ( ) const
{
    return x;
}

template < int_type type >
constexpr const type& fraction<type>::den ( ) const
{
    return y;
}

// Conversion

template < int_type      type  >
template < fraction_type type2 >
constexpr fraction<type>::fraction ( type2 cvt )
    requires ( not std::same_as<fraction,type2> )
{
    let a = cvt.num();
    let b = cvt.den();
    reduce ( a, b );

    x = a;
    y = b;
}

template < int_type type  >
template < int_type type2 >
constexpr fraction<type>::fraction ( type2 cvt )
{
    x = type(cvt);
    y = 1;
}

template < int_type   type  >
template < float_type type2 >
constexpr fraction<type>::fraction ( type2 cvt )
[[deprecated]]
    requires ( not fraction_type<type2> )
{
    expand ( x, y, cvt );
    reduce ( x, y );
}

template < int_type type >
template < number_type type2 >
constexpr fraction<type>::operator type2 ( ) const
    requires ( not fraction_type<type2> )
{
    return type2(num()) / type2(den());
}



// Auxiliary

template < int_type type >
constexpr void fraction<type>::reduce ( int_type auto& a, int_type auto& b )
{
    type c = std::gcd ( a, b );
    a /= c;
    b /= c;

    while ( abs(a) > std::numeric_limits<type>::max() or
            abs(b) > std::numeric_limits<type>::max() )
    {
        a /= 2;
        b /= 2;
        c = std::gcd ( a, b );
        a /= c;
        b /= c;

        if ( a == 0 )
            b = 1;
    }
}

template < int_type type >
constexpr void fraction<type>::expand ( int_type auto& a, int_type auto& b, float_type auto& c )
{
    while ( mod ( c, 1 ) >= std::numeric_limits<type>::epsilon() and
            abs(b) <= std::numeric_limits<type>::max() / 2 and
            abs(c) <= std::numeric_limits<type>::max() / 2 )
    {
        b *= 2;
        c *= 2;
    }

    a = c;
}








/// Global

namespace aux
{
    template < int_type type >
    class double_size_int; // Used below to handle overflow.
}




std::ostream& operator << ( std::ostream& left, const fraction_type auto& right )
{
    if ( right.den() == 1 )
        return left << right.num();
    else
        return left << right.num() << '/' << right.den();
}

constexpr auto operator == ( const fraction_type auto& left, const fraction_type auto& right )
{
    return left.num() == right.num() and left.den() == right.den();
}

constexpr auto operator <=> ( const fraction_type auto& left, const fraction_type auto& right )
{
    using type = common_type<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>;
    using double_size_int = aux::double_size_int<type>;
    return double_size_int(left.num()) * right.den() <=> double_size_int(right.num()) * left.den();
}

constexpr auto operator <=> ( const fraction_type auto& left, const number_type auto& right )
{
    using type = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return type(left) <=> type(right);
}

constexpr auto operator <=> ( const number_type auto& left, const fraction_type auto& right )
{
    using type = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return type(left) <=> type(right);
}

constexpr fraction_type auto operator + ( const fraction_type auto& right )
{
    return fraction ( + right.num(), right.den() );
}

constexpr fraction_type auto operator - ( const fraction_type auto& right )
{
    return fraction ( - right.num(), right.den() );
}

constexpr fraction_type auto operator + ( const fraction_type auto& left, const fraction_type auto& right )
{
    using type = common_type<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>;
    using double_size_int = aux::double_size_int<type>;

    let reduce = [] ( double_size_int& m, double_size_int& n )
    {
        while ( m.high != 0 or m.low >= std::numeric_limits<type>::max() or
                n.high != 0 or n.low >= std::numeric_limits<type>::max() )
        {
            m.divide_2();
            n.divide_2();
        }
    };

    type gcd = std::gcd ( left.den(), right.den() );
    type t1  = left .den() / gcd;
    type t2  = right.den() / gcd;

    double_size_int num = double_size_int(left.num()) * t2 + double_size_int(right.num()) * t1;
    double_size_int den = double_size_int(gcd) * t1 * t2;

    reduce ( num, den );

    return fraction ( type(num), type(den) );
}

constexpr fraction_type auto operator + ( const fraction_type auto& left, const number_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) + common(right);
}

constexpr fraction_type auto operator + ( const number_type auto& left, const fraction_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) + common(right);
}

constexpr fraction_type auto operator - ( const fraction_type auto& left, const fraction_type auto& right )
{
    return left + ( - right );
}

constexpr fraction_type auto operator - ( const fraction_type auto& left, const number_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) - common(right);
}

constexpr fraction_type auto operator - ( const number_type auto& left, const fraction_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) - common(right);
}

constexpr fraction_type auto operator * ( const fraction_type auto& left, const fraction_type auto& right )
{
    using type = common_type<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>;
    using double_size_int = aux::double_size_int<type>;

    let reduce = [] ( double_size_int& m, double_size_int& n )
    {
        while ( m.high != 0 or m.low >= std::numeric_limits<type>::max() or
                n.high != 0 or n.low >= std::numeric_limits<type>::max() )
        {
            m.divide_2();
            n.divide_2();
        }
    };

    type gcd_ad = std::gcd ( left .num(), right.den() );
    type gcd_bc = std::gcd ( right.num(), left .den() );

    double_size_int num = double_size_int ( left.num() / gcd_ad ) * double_size_int ( right.num() / gcd_bc );
    double_size_int den = double_size_int ( left.den() / gcd_bc ) * double_size_int ( right.den() / gcd_ad );

    reduce ( num, den );
    return fraction ( type(num), type(den) );
}

constexpr fraction_type auto operator * ( const fraction_type auto& left, const number_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) * common(right);
}

constexpr fraction_type auto operator * ( const number_type auto& left, const fraction_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) * common(right);
}

constexpr fraction_type auto operator / ( const fraction_type auto& left, const fraction_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return left * fraction ( right.den(), right.num() );
}

constexpr fraction_type auto operator / ( const fraction_type auto& left, const number_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) / common(right);
}

constexpr fraction_type auto operator / ( const number_type auto& left, const fraction_type auto& right )
{
    using common = common_type<decay<decltype(left)>,decay<decltype(right)>>;
    return common(left) / common(right);
}

constexpr fraction_type auto& operator += ( fraction_type auto& left, const number_type auto& right )
{
    return left = left + right;
}

constexpr fraction_type auto& operator -= ( fraction_type auto& left, const number_type auto& right )
{
    return left = left - right;
}

constexpr fraction_type auto& operator *= ( fraction_type auto& left, const number_type auto& right )
{
    return left = left * right;
}

constexpr fraction_type auto& operator /= ( fraction_type auto& left, const number_type auto& right )
{
    return left = left / right;
}











/// Auxiliary

namespace aux
{

template < int_type type >
class double_size_int
{
    public: // Data
        using unsigned_type = std::make_unsigned<type>::type;
        bool          sign = true; // True if >= 0.
        unsigned_type high = 0;
        unsigned_type low  = 0;

    public: // Core
        constexpr double_size_int ( type );
        constexpr double_size_int ( bool, std::same_as<unsigned_type> auto, std::same_as<unsigned_type> auto );
        constexpr explicit operator type ( ) const;

        constexpr bool                  operator ==  ( const double_size_int& ) const = default;
        constexpr std::strong_ordering  operator <=> ( const double_size_int& ) const;
        constexpr double_size_int<type> operator  -  (                        ) const;
        constexpr double_size_int<type> operator  +  ( const double_size_int& ) const;
        constexpr double_size_int<type> operator  -  ( const double_size_int& ) const;
        constexpr double_size_int<type> operator  *  ( const double_size_int& ) const;
        constexpr void                  divide_2     ( );
};

template < int_type type >
std::ostream& operator << ( std::ostream& left, const aux::double_size_int<type>& right )
{
    return left << '[' << ( right.sign ? "" otherwise "-" ) << right.high << '_' << right.low << ']';
}


template < int_type type >
constexpr double_size_int<type>::double_size_int ( type init )
    extends sign ( init >= 0 ),
            low  ( abs ( init ) )
{

}

template < int_type type >
constexpr double_size_int<type>::double_size_int ( bool init_sign, std::same_as<unsigned_type> auto init_high, std::same_as<unsigned_type> auto init_low )
    extends sign ( init_sign ),
            high ( init_high ),
            low  ( init_low  )
{

}

template < int_type type >
constexpr double_size_int<type>::operator type ( ) const
{
    return sign ? type(low) otherwise -type(low);
}

template < int_type type >
constexpr std::strong_ordering double_size_int<type>::operator <=> ( const double_size_int& other ) const
{
    if ( self.sign != other.sign )
        return self.sign <=> other.sign;

    if ( sign == true )
        if ( self.high != other.high )
            return self.high <=> other.high;
        else
            return self.low <=> other.low;

    else
        if ( self.high != other.high )
            return other.high <=> self.high;
        else
            return other.low <=> self.low;
}

template < int_type type >
constexpr double_size_int<type> double_size_int<type>::operator - ( ) const
{
    return double_size_int<type> ( not sign, high, low );
}

template < int_type type >
constexpr double_size_int<type> double_size_int<type>::operator + ( const double_size_int& other ) const
{
    if ( self.sign != other.sign )
        return self - ( - other );

    unsigned_type a = self.high + other.high;
    unsigned_type b = self.low  + other.low;

    if ( b < self.low )
        a++;

    return double_size_int<type> ( sign, a, b );
}

template < int_type type >
constexpr double_size_int<type> double_size_int<type>::operator - ( const double_size_int& other ) const
{
    if ( self.sign != other.sign )
        return self + ( - other );

    if ( abs(self) < abs(other) )
        return - ( other - self );

    unsigned_type a = self.high - other.high;
    unsigned_type b = self.low  - other.low;

    if ( b > self.low )
        a--;

    return double_size_int<type> ( sign, a, b );
}

template < int_type type >
constexpr double_size_int<type> double_size_int<type>::operator * ( const double_size_int& other ) const
{
    // Only handles 2 low-only integer.
    #if debug
        if ( self.high != 0 or other.high != 0 )
            throw math_error("multiplying double size int with non-empty high part");
    #endif

    let cut_high = [] ( unsigned_type n ) { return n                        >> ( std::numeric_limits<unsigned_type>::digits / 2 );         };
    let cut_low  = [] ( unsigned_type n ) { return n & ( ( unsigned_type(1) << ( std::numeric_limits<unsigned_type>::digits / 2 ) ) - 1 ); };

    unsigned_type x = self .low;
    unsigned_type y = other.low;

    unsigned_type p1 = cut_high(x) * cut_high(y);
    unsigned_type p2 = cut_high(x) * cut_low (y);
    unsigned_type p3 = cut_low (x) * cut_high(y);
    unsigned_type p4 = cut_low (x) * cut_low (y);
    unsigned_type carry = cut_high ( cut_low(p2) + cut_low(p3) + cut_high(p4) );

    unsigned_type h = p1 + cut_high(p2) + cut_high(p3) + carry;
    unsigned_type l = x * y;

    return double_size_int<type> ( self.sign == other.sign, h, l );
}

template < int_type type >
constexpr double_size_int<type> abs ( double_size_int<type> n )
{
    return double_size_int<type> ( true, n.high, n.low );
}

template < int_type type >
constexpr void double_size_int<type>::divide_2 ( )
{
    bool carry = ( high % 2 != 0 );

    high /= 2;
    low  /= 2;

    if ( carry )
        low += ( unsigned_type(1) << ( std::numeric_limits<unsigned_type>::digits - 1 ) );
}

} // namespace aux