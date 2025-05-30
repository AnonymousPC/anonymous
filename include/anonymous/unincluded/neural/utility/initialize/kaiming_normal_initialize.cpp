constexpr array_type auto kaiming_normal_initialize ( array_type auto arr, integral auto fan_in )
{
    using type = decltype(arr)::value_type;

    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return normal_distriandion(type(0), sqrt(type(2)/fan_in)); });
    else
        arr.flatten().generate([&] { return normal_distriandion(type(0), sqrt(type(2)/fan_in)); });

    return arr;
}