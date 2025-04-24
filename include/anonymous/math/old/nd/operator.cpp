constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and equalable_to<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>
{
    return std::equal ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and comparable_to<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>
{
    return std::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr array_type auto operator + ( const array_type auto& right )
    requires requires { + std::declval<typename decay<decltype(right)>::value_type>(); }
{
    constexpr int dim  = right.dimension();
    using value_type   = decltype(+std::declval<typename decay<decltype(right)>::value_type>());
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [] ( const auto& a ) { return +a; } );
    return arr;
}

constexpr array_type auto operator - ( const array_type auto& right )
    requires requires { - std::declval<typename decay<decltype(right)>::value_type>(); }
{
    constexpr int dim  = right.dimension();
    using value_type   = decltype(-std::declval<typename decay<decltype(right)>::value_type>());
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [] ( const auto& a ) { return -a; } );
    return arr;
}

constexpr array_type auto operator + ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and addable_to<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>
{
    #ifdef debug
        if ( left.shape() != right.shape() )
            throw value_error("cannot add array of shape {} and array of shape {}: shape must be equal", left.shape(), right.shape());
    #endif

    constexpr int dim  = left.dimension();
    using value_type   = add_result<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), right.begin(), static_cast<base&>(arr).begin(), [] ( const auto& a, const auto& b ) { return a + b; } );
    return arr;
}

constexpr array_type auto operator - ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and minusable_to<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>
{
    #ifdef debug
        if ( left.shape() != right.shape() )
            throw value_error("cannot add array of shape {} and array of shape {}: shape must be equal", left.shape(), right.shape());
    #endif

    constexpr int dim  = left.dimension();
    using value_type   = minus_result<typename decay<decltype(left )>::value_type,typename decay<decltype(right)>::value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), right.begin(), static_cast<base&>(arr).begin(), [] ( const auto& a, const auto& b ) { return a - b; } );
    return arr;
}

constexpr array_type auto operator * ( const array_type auto& left, const auto& right )
    requires ( not array_type<decay<decltype(right)>> ) and multipliable_to<typename decay<decltype(left )>::value_type,decay<decltype(right)>>
{
    constexpr int dim  = left.dimension();
    using value_type   = multiply_result<typename decay<decltype(left )>::value_type,decay<decltype(right)>>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), static_cast<base&>(arr).begin(), [&] ( const auto& a ) { return a * right; } );
    return arr;
}

constexpr array_type auto operator * ( const auto& left, const array_type auto& right )
    requires ( not array_type<decay<decltype(left)>> ) and multipliable_to<decay<decltype(left)>,typename decay<decltype(right)>::value_type>
{
    constexpr int dim  = right.dimension();
    using value_type   = multiply_result<decay<decltype(left)>,typename decay<decltype(right)>::value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [&] ( const auto& b ) { return left * b; } );
    return arr;
}

constexpr array_type auto operator / ( const array_type auto& left, const auto& right )
    requires ( not array_type<decay<decltype(right)>> ) and dividable_to<typename decay<decltype(left )>::value_type,decay<decltype(right)>>
{
    constexpr int dim  = left.dimension();
    using value_type   = divide_result<typename decay<decltype(left )>::value_type,decay<decltype(right)>>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    auto arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), static_cast<base&>(arr).begin(), [&] ( const auto& a ) { return a / right; } );
    return arr;
}

constexpr array_type auto& operator += ( array_type auto& left, const array_type auto& right )
    requires requires { left = left + right; }
{
    constexpr int dim  = left.dimension();
    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 and right.dimension() >= 2 ) or requires ( typename decay<decltype(left )>::value_type a, typename decay<decltype(right)>::value_type b ) { a += b; } )
            left[i] += right[i];
        else
            left[i] = left[i] + right[i];

    return left;
}

constexpr array_type auto&& operator += ( array_type auto&& left, const array_type auto& right )
    requires requires { left = left + right; }
{
    return std::move(left += right);
}

constexpr array_type auto& operator -= ( array_type auto& left, const array_type auto& right )
    requires requires { left = left - right; }
{
    constexpr int dim  = left.dimension();
    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 and right.dimension() >= 2 ) or requires ( typename decay<decltype(left )>::value_type a, typename decay<decltype(right)>::value_type b ) { a -= b; } )
            left[i] -= right[i];
        else
            left[i] = left[i] - right[i];

    return left;
}

constexpr array_type auto&& operator -= ( array_type auto&& left, const array_type auto& right )
    requires requires { left = left - right; }
{
    return std::move(left -= right);
}

constexpr array_type auto& operator *= ( array_type auto& left, const auto& right )
    requires requires { left = left * right; }
{
    if constexpr ( array_type<decay<decltype(right)>> )
        return left = left * right;

    else /* not array_type<decay<decltype(right)>> */
    {
        constexpr int dim  = left.dimension();
        auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

        for ( int i in range(shp_1) )
            if constexpr ( ( left.dimension() >= 2 ) or requires ( typename decay<decltype(left )>::value_type a, decay<decltype(right)> b ) { a *= b; } )
                left[i] *= right;
            else
                left[i] = left[i] * right;

        return left;
    }
}

constexpr array_type auto&& operator *= ( array_type auto&& left, const auto& right )
    requires requires { left = left * right; }
{
    return std::move(left *= right);
}

constexpr array_type auto& operator /= ( array_type auto& left, const auto& right )
    requires requires { left = left / right; }
{
    constexpr int dim  = left.dimension();
    auto shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 ) or requires ( typename decay<decltype(left )>::value_type a, decay<decltype(right)> b ) { a /= b; } )
            left[i] /= right;
        else
            left[i] = left[i] / right;

    return left;
}

constexpr array_type auto&& operator /= ( array_type auto&& left, const auto& right )
    requires requires { left = left / right; }
{
    return std::move(left /= right);
}