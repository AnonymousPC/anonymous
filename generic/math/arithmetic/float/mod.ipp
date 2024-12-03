#pragma once

constexpr float_type auto mod ( float_type auto a, float_type auto b )
{
    if constexpr ( std::floating_point<decltype(a)> and std::floating_point<decltype(b)> )
        return std::fmod ( a, b );

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return mod ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated float-type" );
}

constexpr float_type auto mod ( float_type auto a, int_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return mod ( type(a), type(b) );
}

constexpr float_type auto mod ( int_type auto a, float_type auto b )
{
    using type = common_type<decltype(a),decltype(b)>;
    return mod ( type(a), type(b) );
}


// Specialize

template < class type >
constexpr fraction<type> mod ( fraction<type> a, fraction<type> b )
{
    return a - static_cast<type> ( a / b ) * b;
}