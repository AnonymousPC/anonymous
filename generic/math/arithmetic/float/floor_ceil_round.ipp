#pragma once

constexpr float_type auto floor ( float_type auto a )
{
    if constexpr ( std::floating_point<decltype(a)> ) // Is built_in float_type.
        return std::floor(a);

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto ceil ( float_type auto a )
{
    if constexpr ( std::floating_point<decltype(a)> ) // Is built_in float_type.
        return std::ceil(a);

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto round ( float_type auto a )
{
    if constexpr ( std::floating_point<decltype(a)> ) // Is built_in float_type.
        return std::round(a);

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}



// Specialize

template < class type >
constexpr fraction<type> floor ( fraction<type> a )
{
    return fraction<type> ( std::floor(float_to_float_type<fraction<type>>(a)) );
}

template < class type >
constexpr fraction<type> ceil ( fraction<type> a )
{
    return fraction<type> ( std::ceil(float_to_float_type<fraction<type>>(a)) );
}

template < class type >
constexpr fraction<type> round ( fraction<type> a )
{
    return fraction<type> ( std::round(float_to_float_type<fraction<type>>(a)) );
}