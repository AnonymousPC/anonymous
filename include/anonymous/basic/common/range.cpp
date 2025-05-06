constexpr auto range ( int_type auto high )
{
    return std::views::iota(1, high + 1);
}

constexpr auto range ( int_type auto low, int_type auto high )
{
    return std::views::iota(low, high + 1);
}

constexpr auto range ( int_type auto low, int_type auto high, int_type auto step )
{
    if constexpr ( debug )
    {
        if ( ( step == 0 ) or
             ( step >  0 and low > high + step ) or
             ( step <  0 and low < high + step ) )
             throw value_error("cannot create range (with low = {}, high = {}, step = {}): range is infinite", low, high, step);
    }

    return std::views::iota     (0)
         | std::views::take     ((high - low + step) / step)
         | std::views::transform([=] (int_type auto n) { return low + n * step; });
}
