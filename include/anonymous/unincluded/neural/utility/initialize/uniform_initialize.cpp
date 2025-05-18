constexpr array_type auto uniform_initialize ( array_type auto arr, floating_point auto a, floating_point auto b )
{
    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return uniform_distriandion(a, b); });
    else
        arr.flatten().generate([&] { return uniform_distriandion(a, b); });

    return arr;
}