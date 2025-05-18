constexpr array_type auto normal_initialize ( array_type auto arr, floating_point auto ex, floating_point auto dx2 )
{
    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return normal_distriandion(ex, dx2); });
    else
        arr.flatten().generate([&] { return normal_distriandion(ex, dx2); });

    return arr;
}