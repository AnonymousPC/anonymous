constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( left. dimension() == 1 ) and ( number_type<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 1 ) and ( number_type<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    using type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;

    auto n = 1;
    while ( n < left.size() + right.size() - 1 )
        n *= 2;

    if ( n <= 64 + 64 - 1 ) // Needs retesting.
    {
        auto v = array<type> ( left.size() + right.size() - 1 );
        for ( int i in range ( left.size() ) )
            for ( int j in range ( right.size() ) )
                v[i+j-1] += left[i] * right[j];
        return v;
    }

    else
    {
        auto a = fft(array(left ).resize(n));
        auto b = fft(array(right).resize(n));
        auto c = array(a.size(), [&] (int i) { return a[i] * b[i]; });
        auto d = ifft(c).resize(left.size() + right.size() - 1);

        if constexpr ( int_type<type> )
            return array<type> ( d.size(), [&] (int i) { return type(round(d[i].real())); });
        else if constexpr ( float_type<type> )
            return array<type> ( d.size(), [&] (int i) { return d[i].real(); });
        else if constexpr ( complex_int_type<type> )
            return array<type> ( d.size(), [&] (int i) { return type(round(d[i])); });
        else if constexpr ( complex_float_type<type> )
            return array<type> ( d );
    }
}