template < int min, int max, int stride >
constexpr void for_constexpr ( auto&& operations )
{
    if constexpr ( ( stride > 0 and min <= max ) or
                   ( stride < 0 and min >= max ) )
        operations.template operator()<min>();

    if constexpr ( ( stride > 0 and min <= max - stride ) or 
                   ( stride < 0 and min >= max - stride ) )
        for_constexpr<min+stride,max,stride>(std::forward<decltype(operations)>(operations));
}

template < int min, int max, int stride >
constexpr bool all_of_constexpr ( auto&& preds )
{
    bool result = true;
    for_constexpr<min,max,stride>([&] <int index> { result = result and preds.template operator()<index>(); });
    return result;
}

template < int min, int max, int stride >
constexpr bool any_of_constexpr ( auto&& preds )
{
    bool result = false;
    for_constexpr<min,max,stride>([&] <int index> { result = result or preds.template operator()<index>(); });
    return result;
}

template < int min, int max, int stride >
constexpr bool none_of_constexpr ( auto&& preds )
{
    bool result = true;
    for_constexpr<min,max,stride>([&] <int index> { result = result and not preds.template operator()<index>(); });
    return result;
}