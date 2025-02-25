#pragma once

constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( left. dimension() == 1 ) and ( number_type<left_value_type > or complex_type<left_value_type > ) and
             ( right.dimension() == 1 ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{
    using type = common_type<left_value_type,right_value_type>;

    let n = 1;
    while ( n < left.size() + right.size() - 1 )
        n *= 2;

    if ( n <= 64 + 64 - 1 ) // Needs retesting.
    {
        let v = array<type> ( left.size() + right.size() - 1 );
        for ( int i in range ( left.size() ) )
            for ( int j in range ( right.size() ) )
                v[i+j-1] += left[i] * right[j];
        return v;
    }

    else
    {
        let a = fft(array(left ).resize(n));
        let b = fft(array(right).resize(n));
        let c = array(a.size(), [&] (int i) { return a[i] * b[i]; });
        let d = ifft(c).resize(left.size() + right.size() - 1);

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