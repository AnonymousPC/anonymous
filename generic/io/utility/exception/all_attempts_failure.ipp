#pragma once

template < class type >
    requires derived_from<type,std::exception>
detail::all_attempts_failure<type>::all_attempts_failure ( input_range auto&& r )
    requires same_as<range_value<decltype(r)>,type>
{
    int try_count = 0;
    error_what = string(detail::red) + "all attempts failed" + detail::white + '\n' +
               ( r 
               | std::views::transform([&] (const auto& e) { return std::format("try {} failed", ++try_count) + ' ' + detail::format_nested_exception(typeid(e), e.what()); })
               | std::views::join_with('\n')
               | std::ranges::to<string>()
               );
}

template < class type >
    requires derived_from<type,std::exception>
const char* detail::all_attempts_failure<type>::what ( ) const noexcept
{
    return error_what.c_str();
}