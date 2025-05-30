constexpr array_type auto xavier_normal_initialize ( array_type auto arr, integral auto fan_in, integral auto fan_out )
{
    using type = decltype(arr)::value_type;

    if constexpr ( arr.dimension() == 1 )
        arr.generate([&] { return normal_distriandion(type(0), sqrt(type(2)/(fan_in+fan_out))); });
    else
        arr.flatten().generate([&] { return normal_distriandion(type(0), sqrt(type(2)/(fan_in+fan_out))); });

    return arr;
}