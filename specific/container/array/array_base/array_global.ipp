#pragma once

// TODO: remove these implemention

std::ostream& operator << ( std::ostream& left, const array_type auto& right )
{
    if constexpr ( decay<decltype(right)>::dimension() == 1 )
        std::ranges::for_each(right, [&] (const auto& val) { left << val << ' '; });
    else
        std::ranges::for_each(right, [&] (const auto& line) { left << line << '\n'; });
    return left;
}

constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
{
    return std::equal(left.begin(), left.end(), right.begin(), right.end());
}

