#pragma once

constexpr array_type auto uniform_initialize ( array_type auto arr, float_type auto a, float_type auto b )
{
    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return uniform_distribution(a, b); });
    else
        arr.flatten().generate([&] { return uniform_distribution(a, b); });

    return arr;
}