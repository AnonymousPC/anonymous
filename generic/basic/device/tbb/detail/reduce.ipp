#pragma once

decltype(auto) tbb::reduce ( auto&&... args )
{
    /* Theoretically, ::tbb::parallel_reduce optimize for all kinds of reduce(...).
     * But we just sadly found that tbb::parallel_reduce has a bug.
     * Try this code and you will get volatile results.
     * ==================================================
     *   auto vct = std::vector<int>(1000, 1);
     *   int result = tbb::parallel_reduce(
     *       tbb::blocked_range<std::vector<int>::iterator>(vct.begin(), vct.end()), 
     *       2, 
     *       [](const tbb::blocked_range<std::vector<int>::iterator>& new_range, int old_value) -> int {
     *           for (auto&& new_value : new_range)
     *               old_value *= new_value;
     *           return old_value;
     *       },
     *       std::multiplies<int>()
     *   );
     * ==================================================
     * So that we can only optimize for those {initial_value = 0, operation = plus} cases.
     */

    if constexpr ( sizeof...(args) == 2 )
    {
        auto&& begin = first_value_of(std::forward<decltype(args)>(args)...);
        auto&& end   = last_value_of (std::forward<decltype(args)>(args)...);

        return ::tbb::parallel_reduce(
                   ::tbb::blocked_range<decay<decltype(begin)>>(begin, end),
                   iter_value<decltype(begin)>(),                                     
                   [&] (const auto& new_range, auto&& old_value)
                   {
                       for ( auto&& new_value in new_range )
                           old_value += new_value;
                       return old_value;
                   },
                   tbb::plus<>()
               );
    }

    else
        return cpu::reduce(std::forward<decltype(args)>(args)...);
    
}