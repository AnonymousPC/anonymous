constexpr auto&& first_value_of ( auto&&... args )
{
    return args...[0];
}

constexpr auto&& last_value_of ( auto&&... args )
{
    return args...[sizeof...(args)-1];
}

template < int index >
constexpr auto&& index_value_of ( auto&&... args )
{
    return args...[index >= 0 ? index-1 : index+sizeof...(args)];
}

template < int min, int max, int stride >
constexpr void for_constexpr ( auto&& ops )
{
    if constexpr ( ( stride > 0 and min <= max ) or
                   ( stride < 0 and min >= max ) )
        ops.template operator()<min>();

    if constexpr ( ( stride > 0 and min <= max - stride ) or 
                   ( stride < 0 and min >= max - stride ) )
        for_constexpr<min+stride,max,stride>(std::forward<decltype(ops)>(ops));
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