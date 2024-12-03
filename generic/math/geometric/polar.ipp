#pragma once

/// Class polar

template < number_type type1, angle_type type2 >
class polar
{
    private: // Data
        type1 r = 0;
        type2 t = type2();

    public: // Typedef
        using value_type = type1;
        using angle_type = type2;
        struct polar_tag { };

    public: // Core
        constexpr polar ( ) = default;
        constexpr polar ( type1 );
        constexpr polar ( type1, type2 );
        constexpr const type1& abs ( ) const;
        constexpr const type2& arg ( ) const;

    public: // Conversion
        constexpr polar ( number_type        auto );
        constexpr polar ( polar_type         auto );
        constexpr polar ( complex_float_type auto ) requires float_type<type1>;
};



/// Template deduction

template < number_type type1 >                   polar ( type1 )        -> polar<type1>;
template < number_type type1, angle_type type2 > polar ( type1, type2 ) -> polar<type1,type2>;



// Core

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( type1 init_r )
    extends r ( init_r )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( type1 init_r, type2 init_t )
    extends r ( init_r ),
            t ( init_t )
{

}

template < number_type type1, angle_type type2 >
constexpr const type1& polar<type1,type2>::abs ( ) const
{
    return r;
}

template < number_type type1, angle_type type2 >
constexpr const type2& polar<type1,type2>::arg ( ) const
{
    return t;
}

// Conversion

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( polar_type auto cvt )
    extends polar ( cvt.abs(), cvt.arg() )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( number_type auto cvt )
    extends polar ( static_cast<type1>(cvt) )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( complex_float_type auto cvt )
    requires float_type<type1>
    extends r ( sqrt ( cvt.real() * cvt.real() + cvt.imag() * cvt.imag() ) )
{
    t = r          == 0 ?   type2 ( 0 )                         otherwise
        cvt.imag() >= 0 ?   type2 ( arccos ( cvt.real() / r ) ) otherwise
                          - type2 ( arccos ( cvt.real() / r ) );
}



/// Global

std::ostream& operator << ( std::ostream& left, const polar_type auto& right )
{
    return left << '[' << right.abs() << ',' << right.arg() << ']';
}

constexpr bool operator == ( const polar_type auto& left, const polar_type auto& right )
{
    return left.abs() == right.abs() and left.arg() == right.arg();
}

constexpr polar_type auto operator + ( const polar_type auto& right )
{
    return polar ( right.abs(), + right.arg() );
}

constexpr polar_type auto operator - ( const polar_type auto& right )
{
    return polar ( right.abs(), - right.arg() );
}

constexpr polar_type auto operator + ( const polar_type auto& left, const polar_type auto& right )
{
    using type1 = common_type<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>;
    using type2 = common_type<typename decay<decltype(left)>::angle_type,typename decay<decltype(right)>::angle_type>;

    if constexpr ( int_type<type1> )
        return polar<type1,type2> ( complex<int_to_float_type<type1>>(polar<int_to_float_type<type1>,type2>(left)) + complex<int_to_float_type<type1>>(polar<int_to_float_type<type1>,type2>(right)) );
    else if constexpr ( float_type<type1> )
        return polar<type1,type2> ( complex<type1>(polar<type1,type2>(left)) + complex<type1>(polar<type1,type2>(right)) );
}

constexpr polar_type auto operator - ( const polar_type auto& left, const polar_type auto& right )
{
    using type1 = common_type<typename decay<decltype(left)>::value_type,typename decay<decltype(right)>::value_type>;
    using type2 = common_type<typename decay<decltype(left)>::angle_type,typename decay<decltype(right)>::angle_type>;

    if constexpr ( int_type<type1> )
        return polar<type1,type2> ( complex<int_to_float_type<type1>>(polar<int_to_float_type<type1>,type2>(left)) - complex<int_to_float_type<type1>>(polar<int_to_float_type<type1>,type2>(right)) );
    else if constexpr ( float_type<type1> )
        return polar<type1,type2> ( complex<type1>(polar<type1,type2>(left)) - complex<type1>(polar<type1,type2>(right)) );
}

constexpr polar_type auto operator * ( const polar_type auto& left, const polar_type auto& right )
{
    return polar ( left.abs() * right.abs(), left.arg() + right.arg() );
}

constexpr polar_type auto operator / ( const polar_type auto& left, const polar_type auto& right )
{
    if ( right.abs() == 0 )
        throw math_error("{} / {}", left, right);

    return polar ( left.abs() / right.abs(), left.arg() - right.arg() );
}

constexpr polar_type auto& operator += ( polar_type auto& left, const polar_type auto& right )
{
    return left = left + right;
}

constexpr polar_type auto& operator -= ( polar_type auto& left, const polar_type auto& right )
{
    return left = left - right;
}

constexpr polar_type auto& operator *= ( polar_type auto& left, const polar_type auto& right )
{
    return left = left * right;
}

constexpr polar_type auto& operator /= ( polar_type auto& left, const polar_type auto& right )
{
    return left = left / right;
}