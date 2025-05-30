template < numeric auto num >
constexpr /*value_type*/ auto norm ( const array_type auto& vector )
    requires ( vector.dimension() == 1 ) and ( numeric<vector_value_type> or complex_type<vector_value_type> )
{
    if constexpr ( num == 1 )
        return vector.sum([] (const auto& n) { return abs(n); });

    else if constexpr ( num == 2 )
    {
        if constexpr ( integral<vector_value_type> )
            return sqrt ( int_to_float_type<vector_value_type>(vector.sum([] (const auto& n) { return n * n; })) );

        else if constexpr ( floating_point<vector_value_type> )
            return sqrt ( vector.sum([] (const auto& n) { return n * n; }) );

        else if constexpr ( complex_int_type<vector_value_type> )
            return sqrt ( int_to_float_type<vector_value_type::value_type>(vector.sum([] (const auto& n) { return n * conj(n); }).real()) );

        else if constexpr ( complex_float_type<vector_value_type> )
            return sqrt ( vector.sum([] (const auto& n) { return n * conj(n); }).real() );
    }

    else if constexpr ( num == std::numeric_limits<decltype(num)>::infinity() )
        return vector.max();

    else
    {
        if constexpr ( integral<decltype(num)> )
            return pow ( vector.sum([] (const auto& n) { return pow(n, int_to_float_type<decltype(num)>(num)); }), 1 / int_to_float_type<decltype(num)>(num) );

        else if constexpr ( floating_point<decltype(num)> )
            return pow ( vector.sum([] (const auto& n) { return pow(n, num); }), 1 / num );
    }
}