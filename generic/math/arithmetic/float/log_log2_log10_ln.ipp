#pragma once

constexpr float_type auto log ( float_type auto a, float_type auto b )
{
    if ( a <= 0 or a == 1 or b <= 0 )
        throw math_error("log({}, {}) is out of domain: log(x, y) requires x > 0, x != 1, y > 0", a, b);

    if constexpr ( std::floating_point<decltype(a)> and std::floating_point<decltype(b)> )
        return std::log (b) / std::log (a);

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return log ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto log ( float_type auto a, int_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return log ( type(a), type(b) );
}

constexpr float_type auto log ( int_type auto a, float_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return log ( type(a), type(b) );
}

constexpr float_type auto log2 ( float_type auto a )
{
    return log ( 2, a );
}

constexpr float_type auto log10 ( float_type auto a )
{
    return log ( 10, a );
}

constexpr float_type auto ln ( float_type auto a )
{
    using constants::e;
    return log ( e, a );
}



// Specialize

template < class type >
constexpr fraction<type> log ( fraction<type> a, fraction<type> b )
{
    if ( not ( a > 0 and a != 1 and b > 0 ) )
        throw math_error("log({}, {}) is out of domain: log(x, y) requires x > 0, x != 1, y > 0", a, b);

    return fraction<type> ( log(float_to_float_type<fraction<type>>(a), float_to_float_type<fraction<type>>(b)) );
}