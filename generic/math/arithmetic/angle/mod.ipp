#pragma once

constexpr angle_type auto mod ( angle_type auto a, angle_type auto b )
{
    if constexpr ( ( degree_type<decltype(a)> and degree_type<decltype(b)> ) or
                   ( radian_type<decltype(a)> and radian_type<decltype(b)> ) ) // Is same kine of angle.
        return common_type<decltype(a),decltype(b)> ( mod(a.value(), b.value()) );
    else
    {
        using type = common_type<decltype(a),decltype(b)>;
        return mod(type(a), type(b));
    }
}