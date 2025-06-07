constexpr random_access_range auto range ( integral auto high )
{
    return std::views::iota(1, high + 1);
}

constexpr random_access_range auto range ( integral auto low, integral auto high )
{
    return std::views::iota(low, high + 1);
}

constexpr random_access_range auto range ( integral auto low, integral auto high, integral auto step )
{
    return std::views::iota     (0)
         | std::views::take     ((high - low + step) / step)
         | std::views::transform([=] (integral auto n) { return low + n * step; });
}
