#pragma once

constexpr array_type auto ones_initialize ( array_type auto arr )
{
    if constexpr ( arr.dimension() == 1 )
        arr.fill(1);
    else
        arr.flatten().fill(1);

    return arr;
}