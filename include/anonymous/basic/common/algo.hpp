template < int min, int max, int stride >
constexpr void for_constexpr ( auto&& operations )
{
    static_assert ( ( stride > 0 and min <= max ) or
                    ( stride < 0 and min >= max ),
                    "invalid for-clause" );

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

template < int min, int max, int stride >
constexpr auto accumulate_constexpr ( auto&& vals, auto&& init )
{
    return accumulate_constexpr<min,max,stride>(std::forward<decltype(vals)>(vals), std::forward<decltype(init)>(init), std::plus<>());
}

template < int min, int max, int stride >
constexpr auto accumulate_constexpr ( auto&& vals, auto&& init, auto&& op )
{
    auto result = init;
    for_constexpr<min,max,stride>([&] <int index> { result = op(result, vals.template operator()<index>()); });
    return result;
}