#pragma once

/// Class complex

template < number_type type >
class complex
{
    private: // Data
        type x = 0;
        type y = 0;

    public: // Typedef
        using value_type = type;
        struct complex_tag { };

    public: // Core
        constexpr complex ( ) = default;
        constexpr complex ( type );
        constexpr complex ( type, type );
        constexpr const type& real ( ) const;
        constexpr const type& imag ( ) const;

    public: // Conversion
        constexpr complex ( number_type      auto );
        constexpr complex ( complex_type     auto );
        constexpr complex ( polar_float_type auto ) requires float_type<type>;
};

// Core

template < number_type type >
constexpr complex<type>::complex ( type init_x )
    extends x ( init_x )
{

}

template < number_type type >
constexpr complex<type>::complex ( type init_x, type init_y )
    extends x ( init_x ),
            y ( init_y )
{

}

template < number_type type >
constexpr const type& complex<type>::real ( ) const
{
    return x;
}

template < number_type type >
constexpr const type& complex<type>::imag ( ) const
{
    return y;
}

// Conversion

template < number_type type >
constexpr complex<type>::complex ( number_type auto cvt )
    extends complex ( static_cast<type> ( cvt ) )
{

}

template < number_type type >
constexpr complex<type>::complex ( complex_type auto cvt )
    extends complex ( static_cast<type> ( cvt.real() ), static_cast<type> ( cvt.imag() ) )
{

}

template < number_type type >
constexpr complex<type>::complex ( polar_float_type auto cvt )
    requires float_type<type>
    extends complex ( cvt.abs() * cos ( cvt.arg() ), cvt.abs() * sin ( cvt.arg() ) )
{

}





/// Global

std::ostream& operator << ( std::ostream& left, const complex_type auto& right )
{
    if ( right.real() == 0 )
        if ( right.imag() == 0 )
            return left << right.real();
        else if ( right.imag() == 1 )
            return left << 'i';
        else if ( right.imag() == -1 )
            return left << "-i";
        else
            return left << right.imag() << 'i';

    else
        if ( right.imag() == 0 )
            return left << right.real();
        else if ( right.imag() == 1 )
            return left << right.real() << "+i";
        else if ( right.imag() == -1 )
            return left << right.real() << "-i";
        else if ( right.imag() > 0 )
            return left << right.real() << '+' << right.imag() << 'i';
        else
            return left << right.real() << right.imag() << 'i';
}

constexpr bool operator == ( const complex_type auto& left, const complex_type auto& right )
{
    return left.real() == right.real() and left.imag() == right.imag();
}

constexpr bool operator == ( const complex_type auto& left, const number_type auto& right )
{
    return left.real() == right and left.imag() == 0;
}

constexpr bool operator == ( const number_type auto& left, const complex_type auto& right )
{
    return left == right.real() and 0 == right.imag();
}

constexpr complex_type auto operator + ( const complex_type auto& right )
{
    return complex ( + right.real(), + right.imag() );
}

constexpr complex_type auto operator - ( const complex_type auto& right )
{
    return complex ( - right.real(), - right.imag() );
}

constexpr complex_type auto operator + ( const complex_type auto& left, const complex_type auto& right )
{
    return complex ( left.real() + right.real(), left.imag() + right.imag() );
}

constexpr complex_type auto operator + ( const complex_type auto& left, const number_type auto& right )
{
    return complex ( left.real() + right, left.imag() );
}

constexpr complex_type auto operator + ( const number_type auto& left, const complex_type auto& right )
{
    return complex ( left + right.real(), right.imag() );
}

constexpr complex_type auto operator - ( const complex_type auto& left, const complex_type auto& right )
{
    return complex ( left.real() - right.real(), left.imag() - right.imag() );
}

constexpr complex_type auto operator - ( const complex_type auto& left, const number_type auto& right )
{
    return complex ( left.real() - right, left.imag() );
}

constexpr complex_type auto operator - ( const number_type auto& left, const complex_type auto& right )
{
    return complex ( left - right.real(), - right.imag() );
}

constexpr complex_type auto operator * ( const complex_type auto& left, const complex_type auto& right )
{
    return complex ( left.real() * right.real() - left.imag() * right.imag(),
                     left.real() * right.imag() + left.imag() * right.real() );
}

constexpr complex_type auto operator * ( const complex_type auto& left, const number_type auto& right )
{
    return complex ( left.real() * right, left.imag() * right );
}

constexpr complex_type auto operator * ( const number_type auto& left, const complex_type auto& right )
{
    return complex ( left * right.real(), left * right.imag() );
}

constexpr complex_type auto operator / ( const complex_type auto& left, const complex_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    let div = right.real() * right.real() + right.imag() * right.imag();

    return complex ( ( left.real() * right.real() + left.imag() * right.imag() ) / div,
                     ( left.imag() * right.real() - left.real() * right.imag() ) / div );
}

constexpr complex_type auto operator / ( const complex_type auto& left, const number_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return complex ( left.real() / right, left.imag() / right );
}

constexpr complex_type auto operator / ( const number_type auto& left, const complex_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return complex(left) / right;
}

constexpr complex_type auto& operator += ( complex_type auto& left, const complex_type auto& right )
{
    return left = left + right;
}

constexpr complex_type auto& operator += ( complex_type auto& left, const number_type auto& right )
{
    return left = left + right;
}

constexpr complex_type auto& operator -= ( complex_type auto& left, const complex_type auto& right )
{
    return left = left - right;
}

constexpr complex_type auto& operator -= ( complex_type auto& left, const number_type auto& right )
{
    return left = left - right;
}

constexpr complex_type auto& operator *= ( complex_type auto& left, const complex_type auto& right )
{
    return left = left * right;
}

constexpr complex_type auto& operator *= ( complex_type auto& left, const number_type auto& right )
{
    return left = left * right;
}

constexpr complex_type auto& operator /= ( complex_type auto& left, const complex_type auto& right )
{
    return left = left / right;
}

constexpr complex_type auto& operator /= ( complex_type auto& left, const number_type auto& right )
{
    return left = left / right;
}