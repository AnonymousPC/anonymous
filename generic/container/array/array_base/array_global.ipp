#pragma once

/// Global ( For linear math, see "root/math/linear". )

namespace aux
{
    // Specialize one of these to create custom formatters.
    auto stringalize_array ( auto&, const auto& );
    auto stringalize_array ( auto&, const auto&, const auto& ); // Use custom stringalizer.
    void align_array       ( auto& );
    void print_array       ( auto&, const auto&, int = 1 );
}



constexpr std::ostream& operator << ( std::ostream& left, const array_type auto& right )
    requires printable<right_value_type>
{
    let strarr = aux::stringalize_array(left, right);
    aux::align_array(strarr);
    aux::print_array(left, strarr);

    return left;
}

auto aux::stringalize_array ( auto& left, const auto& right )
{
    return stringalize_array ( left, right, [&] ( const auto& item ) { let stream = std::stringstream(); stream.copyfmt(left); stream.setf(left.flags()); stream << item; return string(stream.view()); } );
}

auto aux::stringalize_array ( auto& left, const auto& right, const auto& stringalizer )
{
    if constexpr ( right.dimension() == 1 or right.dimension() == -1 )
        return array<string,right.dimension()> ( right.size(), [&] ( int i ) { return stringalizer(right[i]); } );
    else
        return array<string,right.dimension()> ( right.row(), [&] ( int i ) { return stringalize_array(left,right[i],stringalizer); } );
}

void aux::align_array ( auto& right )
{
    if constexpr ( right.dimension() == 1 or right.dimension() == -1 )
    {
        let align = right.empty() ? 0 otherwise right.max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();
        right.each([&] (auto& str) { str.left_justify(align); });
    }
    else
    {
        let align = right.empty() ? 0 otherwise right.flatten().max([] (const auto& str1, const auto& str2) { return str1.size() < str2.size(); }).size();
        right.flatten().each([&] (auto& str) { str.left_justify(align); });
    }
}

void aux::print_array ( auto& left, const auto& right, int depth /* =1 */ )
{
    left << '{';

    if constexpr ( right.dimension() == 1 or right.dimension() == -1 )
        for ( int i in range ( right.size() ) )
        {
            if ( i != 1 )
                left << ' ';
            left << right[i];
        }

    else
        for ( int i in range ( right.row() ) )
        {
            if ( i != 1 )
            {
                left << ' ';
                for ( int _ in range ( right.dimension() - 1 ) )
                    left << '\n';
                for ( int _ in range ( depth ) )
                    left << ' ';
            }
            print_array ( left, right[i], depth + 1 );
        }

    left << '}';

    if constexpr ( right.dimension() == -1 )
        left << 'T';
}