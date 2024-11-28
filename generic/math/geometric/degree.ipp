#pragma once

/// Class degree

template < float_type type >
class degree
{
    private: // Data
        type t = 0;

    public: // Typedef
        using value_type = type;
        struct angle_tag  { };
        struct degree_tag { };

    public: // Core
        constexpr degree ( ) = default;
        constexpr degree ( type );
        constexpr const type& value ( ) const;

    public: // Conversion
        constexpr degree ( degree_type auto );
        constexpr degree ( radian_type auto );

    public: // Operator
        constexpr bool operator ==  ( const degree& ) const = default;
        constexpr auto operator <=> ( const degree& ) const = default;
};

template < int_type   type > degree ( type )         -> degree<>;
template < float_type type > degree ( type )         -> degree<type>;
template < float_type type > degree ( radian<type> ) -> degree<type>;

// Core

template < float_type type >
constexpr degree<type>::degree ( type init )
    extends t ( init )
{

}

template < float_type type >
constexpr const type& degree<type>::value ( ) const
{
    return t;
}

// Conversion

template < float_type type >
constexpr degree<type>::degree ( degree_type auto cvt )
    extends degree ( cvt.value() )
{

}

template < float_type type >
constexpr degree<type>::degree ( radian_type auto cvt )
    extends degree ( static_cast<type> ( cvt.value() * 360 / ( 2 * constants::pi ) ) )
{

}



/// Global

std::ostream& operator << ( std::ostream& left, const degree_type auto& right )
{
    return left << right.value() << "deg";
}

constexpr degree_type auto operator + ( const degree_type auto& right )
{
    return degree ( + right.value() );
}

constexpr degree_type auto operator - ( const degree_type auto& right )
{
    return degree ( - right.value() );
}

constexpr degree_type auto operator + ( const degree_type auto& left, const degree_type auto& right )
{
    return degree ( left.value() + right.value() );
}

constexpr degree_type auto operator - ( const degree_type auto& left, const degree_type auto& right )
{
    return degree ( left.value() - right.value() );
}

constexpr degree_type auto operator * ( const degree_type auto& left, const number_type auto& right )
{
    return degree ( left.value() * right );
}

constexpr degree_type auto operator * ( const number_type auto& left, const degree_type auto& right )
{
    return degree ( left * right.value() );
}

constexpr float_type auto operator / ( const degree_type auto& left, const degree_type auto& right )
{
    if ( right.value() == 0 )
        throw math_error("{} / {}", left, right);

    return left.value() / right.value();
}

constexpr degree_type auto operator / ( const degree_type auto& left, const number_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return degree ( left.value() / right );
}

constexpr degree_type auto& operator += ( degree_type auto& left, const degree_type auto& right )
{
    return left = left + right;
}

constexpr degree_type auto& operator -= ( degree_type auto& left, const degree_type auto& right )
{
    return left = left - right;
}

constexpr degree_type auto& operator *= ( degree_type auto& left, const number_type auto& right )
{
    return left = left * right;
}

constexpr degree_type auto& operator /= ( degree_type auto& left, const number_type auto& right )
{
    return left = left / right;
}