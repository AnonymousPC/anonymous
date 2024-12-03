#pragma once

constexpr float_type auto pow ( float_type auto a, float_type auto b )
{
    if constexpr ( std::floating_point<decltype(a)> and std::floating_point<decltype(b)> )
        return std::pow ( a, b );

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return pow ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto pow ( float_type auto a, int_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return pow ( type(a), type(b) );
}

constexpr float_type auto pow ( int_type auto a, float_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return pow ( type(a), type(b) );
}

constexpr float_type auto sqrt ( float_type auto a )
{
    if ( a < 0 )
        throw math_error("sqrt({}) is out of domain: sqrt(x) requires x >= 0", a);

    if constexpr ( std::is_floating_point<decltype(a)>::value )
        return std::sqrt ( a );

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto exp ( float_type auto a )
{
    using constants::e;
    return pow ( e, a );
}

constexpr float_type auto exp2 ( float_type auto a )
{
    return pow ( 2, a );
}




// Specialize

template < class type >
constexpr fraction<type> pow ( fraction<type> a, fraction<type> b )
{
    if ( b.den() == 1 ) // b is integer.
        if ( b.num() > 0 ) // b is positive => num^x / den^x.
            return fraction ( pow(a.num(), b.num()), pow(a.den(), b.num()) );
        else if ( b.num() < 0 ) // b is negative => den^(-x) / num^(-x).
            return pow ( 1 / a, - b );
        else // b == 0.
            return fraction<type>(1);

    else
        return fraction<type> ( pow(float_to_float_type<fraction<type>>(a), float_to_float_type<fraction<type>>(b)) );
}

template < int_type type >
constexpr fraction<type> sqrt ( fraction<type> a )
{
    if ( a < 0 )
        throw math_error("sqrt({}) is out of domain: sqrt(x) requires x >= 0", a);

    let is_sqrtable = [] ( type n ) { type r = round(sqrt(typename float_to_float_type<fraction<type>>::type(n))); return n == r * r; };

    if ( is_sqrtable(a.num()) and is_sqrtable(a.den()) )
        return fraction<type> ( sqrt(a.num()), sqrt(a.den()) );
    else
        return fraction<type> ( sqrt(float_to_float_type<fraction<type>>(a.num()) / float_to_float_type<fraction<type>>(a.den())) );
}