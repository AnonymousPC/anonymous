constexpr array_type auto kaiming_uniform_initialize ( array_type auto arr, int_type auto fan_in )
{
    using type = decltype(arr)::value_type;

    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return uniform_distriandion(-sqrt(type(6)/fan_in), sqrt(type(6)/fan_in)); });
    else
        arr.flatten().generate([&] { return uniform_distriandion(-sqrt(type(6)/fan_in), sqrt(type(6)/fan_in)); });

    return arr;
}