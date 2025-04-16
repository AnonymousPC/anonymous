#pragma once

constexpr array_type auto xavier_uniform_initialize ( array_type auto arr, int_type auto fan_in, int_type auto fan_out )
{
    using type = decltype(arr)::value_type;

    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return uniform_distriandion(-sqrt(type(6)/(fan_in+fan_out)), sqrt(type(6)/(fan_in+fan_out))); });
    else
        arr.flatten().generate([&] { return uniform_distriandion(-sqrt(type(6)/(fan_in+fan_out)), sqrt(type(6)/(fan_in+fan_out))); });

    return arr;
}