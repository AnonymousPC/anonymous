#pragma once

constexpr array_type auto normal_initialize ( array_type auto arr, float_type auto ex, float_type auto dx2 )
{
    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return normal_distriandion(ex, dx2); });
    else
        arr.flatten().generate([&] { return normal_distriandion(ex, dx2); });

    return arr;
}