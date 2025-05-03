[[deprecated("if your code depends on this function, probably you should review your code as it's time-complexity == O(N^4)...")]]
constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( left. dimension() == 2 ) and ( number_type<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 2 ) and ( number_type<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    using type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;

    auto a = array<type,2> ( left.row() + right.row() - 1, left.column() + right.column() - 1 );
    for ( int i in range ( left.row() ) )
        for ( int j in range ( right.row() ) )
            for ( int m in range ( left.column() ) )
                for ( int n in range ( right.column() ) )
                    a[i+j-1][m+n-1] += left[i][m] * right[j][n];
    return a;
}

constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( left. dimension() == 2 ) and ( number_type<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == 1 ) and ( number_type<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    using type = common_type<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;

    auto a = array<type,2> ( left.row(), left.column() + right.size() - 1,
                            [&] (int i) { return convolve ( left[i], right ); } );
}

constexpr array_type auto convolve ( const array_type auto& left, const array_type auto& right )
    requires ( left. dimension() ==  2 ) and ( number_type<typename decay<decltype(left )>::value_type > or complex_type<typename decay<decltype(left )>::value_type > ) and
             ( right.dimension() == -1 ) and ( number_type<typename decay<decltype(right)>::value_type> or complex_type<typename decay<decltype(right)>::value_type> )
{
    return transpose ( convolve ( transpose(left), transpose(right) ) );
}