#pragma once

decltype(auto) tbb::inclusive_scan ( auto&&... args )
{
    if constexpr ( sizeof...(args) == 3 )
    {
        let length = std::distance(first_value_of(args...), second_value_of(args...))
        ::tbb::parallel_scan(
            ::tbb::blocked_range(0, length),
            iter_value<decay<first_type_of<decltype(args)...>>>(),
            [&] (const auto& idx_range, auto&& old_value, bool final_loop)
            {
                for ( size_t idx = idx_range.begin(); idx != idx_range.end(); idx++ )
                {
                    old_value = operation(old_value, begin[idx]);
                    if ( final_loop )
                        output[idx] = old_value;
                }
                return old_value;
            },
            tbb::plus<>()
        );
        return second_value_of(std::forward<decltype(args)>(args)...) + length;
    }

    else 
        return cpu::inclusive_scan(std::forward<decltype(args)>(args)...);
}