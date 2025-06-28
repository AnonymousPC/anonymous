constexpr array_type auto zeros_initialize ( array_type auto arr )
{
    if constexpr ( arr.dimension() == 1 )
        arr.fill(0);
    else
        arr.flatten().fill(0);

    return arr;
}