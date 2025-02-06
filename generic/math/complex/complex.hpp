#pragma once

template < number_type type >
class complex
    extends public std::complex<type>
{
    public: // Typedef
        using  value_type = type;
        struct complex_tag { };

    public: // Core
        constexpr complex ( ) = default;
        constexpr complex ( type );
        constexpr complex ( type, type );

    public: // Member
        constexpr       type& real ( );
        constexpr const type& real ( ) const;
        constexpr       type& imag ( );
        constexpr const type& imag ( ) const;
};







template < number_type type >
constexpr complex<type>::complex ( type r )
    extends std::complex<type> ( std::move(r) )
{

}

template < number_type type >
constexpr complex<type>::complex ( type r, type i )
    extends std::complex<type> ( std::move(r), std::move(i) )
{

}

template < number_type type >
constexpr type& complex<type>::real ( )
{
    struct raw_complex { type r; type i; };
    return reinterpret_cast<raw_complex&>(self).r;
}

template < number_type type >
constexpr const type& complex<type>::real ( ) const
{
    struct raw_complex { type r; type i; }; 
    return reinterpret_cast<const raw_complex&>(self).r;
}

template < number_type type >
constexpr type& complex<type>::imag ( )
{
    struct raw_complex { type r; type i; };
    return reinterpret_cast<raw_complex&>(self).i;
}

template < number_type type >
constexpr const type& complex<type>::imag ( ) const
{
    struct raw_complex { type r; type i; };
    return reinterpret_cast<const raw_complex&>(self).i;
}





inline namespace constants
{
    constexpr const complex<double> i = complex<double>(0, 1);
}







constexpr std::ostream& operator << ( std::ostream& left, const complex_type auto& right )
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
    return complex(+right.real(), +right.imag());
}

constexpr complex_type auto operator - ( const complex_type auto& right )
{
    return complex(-right.real(), -right.imag());
}

constexpr complex_type auto operator + ( const complex_type auto& left, const complex_type auto& right )
{
    return complex(left.real() + right.real(), left.imag() + right.imag());
}

constexpr complex_type auto operator + ( const complex_type auto& left, const number_type auto& right )
{
    return complex(left.real() + right, left.imag());
}

constexpr complex_type auto operator + ( const number_type auto& left, const complex_type auto& right )
{
    return complex(left + right.real(), right.imag());
}

constexpr complex_type auto operator - ( const complex_type auto& left, const complex_type auto& right )
{
    return complex(left.real() - right.real(), left.imag() - right.imag());
}

constexpr complex_type auto operator - ( const complex_type auto& left, const number_type auto& right )
{
    return complex(left.real() - right, left.imag());
}

constexpr complex_type auto operator - ( const number_type auto& left, const complex_type auto& right )
{
    return complex(left - right.real(), - right.imag());
}

constexpr complex_type auto operator * ( const complex_type auto& left, const complex_type auto& right )
{
    return complex(left.real() * right.real() - left.imag() * right.imag(),
                   left.real() * right.imag() + left.imag() * right.real());
}

constexpr complex_type auto operator * ( const complex_type auto& left, const number_type auto& right )
{
    return complex(left.real() * right, left.imag() * right);
}

constexpr complex_type auto operator * ( const number_type auto& left, const complex_type auto& right )
{
    return complex(left * right.real(), left * right.imag());
}

constexpr complex_type auto operator / ( const complex_type auto& left, const complex_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    let div = right.real() * right.real() + right.imag() * right.imag();

    return complex((left.real() * right.real() + left.imag() * right.imag()) / div,
                   (left.imag() * right.real() - left.real() * right.imag()) / div);
}

constexpr complex_type auto operator / ( const complex_type auto& left, const number_type auto& right )
{
    if ( right == 0 )
        throw math_error("{} / {}", left, right);

    return complex(left.real() / right, left.imag() / right);
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





constexpr float_type auto abs ( complex_type auto x )
{
    return hypot(x.real(), x.imag());
}

constexpr complex_type auto pow ( complex_type auto x, complex_type auto y )
{
    return exp(y * ln(x));
}

constexpr complex_type auto exp ( complex_type auto x )
{
    return exp(x.real()) * (std::cos(x.imag()) + i * std::sin(x.imag()));
}

constexpr complex_type auto sqrt ( complex_type auto x )
{
    let r = abs(x);
    let t = x.real() > 0 ?                std::atan(x.imag() / x.real())      otherwise
            x.real() < 0 ? x.imag() > 0 ? std::atan(x.imag() / x.real()) + pi otherwise
                                          std::atan(x.imag() / x.real()) - pi otherwise
         /*x.real() == 0*/ x.imag() > 0 ?  pi / 2                             otherwise
                           x.imag() < 0 ? -pi / 2                             otherwise
                         /*x.imag() == 0*/ 0;
    return complex(std::sqrt(r) * std::cos(t / 2), 
                   std::sqrt(r) * std::sin(t / 2));
}

constexpr complex_type auto ln ( complex_type auto x )
{
    let r = abs(x);
    let t = x.real() > 0 ?                std::atan(x.imag() / x.real())      otherwise
            x.real() < 0 ? x.imag() > 0 ? std::atan(x.imag() / x.real()) + pi otherwise
                                          std::atan(x.imag() / x.real()) - pi otherwise
         /*x.real() == 0*/ x.imag() > 0 ?  pi / 2                             otherwise
                           x.imag() < 0 ? -pi / 2                             otherwise
                         /*x.imag() == 0*/ 0;
    return ln(r) + i * t;
}

constexpr complex_type auto conj ( complex_type auto x )
{
    return complex(x.real(), -x.imag());
}



