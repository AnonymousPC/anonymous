template < derived_from<std::exception> type >
detail::all_attempts_failed<type>::all_attempts_failed ( input_range auto&& r )
    requires same_as<range_value<decltype(r)>,type>
{
    int try_count = 0;
    error_what = detail::red + "all attempts failed (with attempts_count = {}, attempts_info = [[see_below]])"s.format(r.size()) + detail::white + '\n' +
               ( r 
               | std::views::transform([&] (const auto& e) { return std::format("attempt {} failed", ++try_count) + ' ' + detail::format_nested_exception(typeid(e), e.what()); })
               | std::views::join_with('\n')
               | std::ranges::to<string>()
               );
}

template < derived_from<std::exception> type >
const char* detail::all_attempts_failed<type>::what ( ) const noexcept
{
    return error_what.c_str();
}