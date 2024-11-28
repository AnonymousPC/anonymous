#pragma once

constexpr int_type auto mod ( int_type auto a, int_type auto b )
{
    if constexpr ( std::integral<decltype(a)> and std::integral<decltype(b)> )
        return a % b;

    else if constexpr ( not std::same_as<decltype(a),decltype(b)> )
    {
        using type = common_type<decltype(a),decltype(b)>;
        return mod ( type(a), type(b) );
    }

    else
        static_assert ( false, "unsolvable, try to overload this function to dedicated int-type" );
}