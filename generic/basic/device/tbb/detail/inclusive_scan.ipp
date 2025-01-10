#pragma once

decltype(auto) tbb::inclusive_scan ( auto&&... args )
{
    if constexpr ( sizeof...(args) == 3 )
    {
        auto&& begin    = first_value_of (std::forward<decltype(args)>(args)...);
        auto&& end      = second_value_of(std::forward<decltype(args)>(args)...);
        auto&& output   = last_value_of  (std::forward<decltype(args)>(args)...);
        auto   distance = std::distance  (begin, end);

        ::tbb::parallel_scan(
            ::tbb::blocked_range(0, distance),
            iter_value<decay<decltype(begin)>>(),
            [&] (const auto& idx_range, auto&& old_value, bool final_loop)
            {
                for ( size_t idx = idx_range.begin(); idx != idx_range.end(); idx++ )
                {
                    old_value+= begin[idx];
                    if ( final_loop )
                        output[idx] = old_value;
                }
                return old_value;
            },
            tbb::plus<>()
        );

        return end + distance;
    }

    else 
        return cpu::inclusive_scan(std::forward<decltype(args)>(args)...);
}