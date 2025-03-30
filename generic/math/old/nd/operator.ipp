#pragma once

constexpr bool operator == ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and equalable_to<left_value_type,right_value_type>
{
    return std::equal ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr auto operator <=> ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and comparable_to<left_value_type,right_value_type>
{
    return std::lexicographical_compare_three_way ( left.begin(), left.end(), right.begin(), right.end() );
}

constexpr array_type auto operator + ( const array_type auto& right )
    requires requires { + std::declval<right_value_type>(); }
{
    constexpr int dim  = right.dimension();
    using value_type   = decltype(+std::declval<right_value_type>());
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [] ( const auto& a ) { return +a; } );
    return arr;
}

constexpr array_type auto operator - ( const array_type auto& right )
    requires requires { - std::declval<right_value_type>(); }
{
    constexpr int dim  = right.dimension();
    using value_type   = decltype(-std::declval<right_value_type>());
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [] ( const auto& a ) { return -a; } );
    return arr;
}

constexpr array_type auto operator + ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and addable_to<left_value_type,right_value_type>
{
    #ifdef debug
        if ( left.shape() != right.shape() )
            throw value_error("cannot add array of shape {} and array of shape {}: shape must be equal", left.shape(), right.shape());
    #endif

    constexpr int dim  = left.dimension();
    using value_type   = add_result<left_value_type,right_value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), right.begin(), static_cast<base&>(arr).begin(), [] ( const auto& a, const auto& b ) { return a + b; } );
    return arr;
}

constexpr array_type auto operator - ( const array_type auto& left, const array_type auto& right )
    requires ( left.dimension() == right.dimension() ) and minusable_to<left_value_type,right_value_type>
{
    #ifdef debug
        if ( left.shape() != right.shape() )
            throw value_error("cannot add array of shape {} and array of shape {}: shape must be equal", left.shape(), right.shape());
    #endif

    constexpr int dim  = left.dimension();
    using value_type   = minus_result<left_value_type,right_value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), right.begin(), static_cast<base&>(arr).begin(), [] ( const auto& a, const auto& b ) { return a - b; } );
    return arr;
}

constexpr array_type auto operator * ( const array_type auto& left, const auto& right )
    requires ( not array_type<right_type> ) and multipliable_to<left_value_type,right_type>
{
    constexpr int dim  = left.dimension();
    using value_type   = multiply_result<left_value_type,right_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), static_cast<base&>(arr).begin(), [&] ( const auto& a ) { return a * right; } );
    return arr;
}

constexpr array_type auto operator * ( const auto& left, const array_type auto& right )
    requires ( not array_type<left_type> ) and multipliable_to<left_type,right_value_type>
{
    constexpr int dim  = right.dimension();
    using value_type   = multiply_result<left_type,right_value_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return right.size(); else return right.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( right.begin(), right.end(), static_cast<base&>(arr).begin(), [&] ( const auto& b ) { return left * b; } );
    return arr;
}

constexpr array_type auto operator / ( const array_type auto& left, const auto& right )
    requires ( not array_type<right_type> ) and dividable_to<left_value_type,right_type>
{
    constexpr int dim  = left.dimension();
    using value_type   = divide_result<left_value_type,right_type>;
    using iterate_type = conditional<abs(dim)==1,value_type,array<value_type,dim-1>>;
    using base         = decltype ( [] { if constexpr ( dim == 1 ) return array<value_type,1>(); else return typename array<value_type,dim>::base(); } () );

    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();
    let arr   = array<value_type,dim> ( shp_1, iterate_type() );
    std::transform ( left.begin(), left.end(), static_cast<base&>(arr).begin(), [&] ( const auto& a ) { return a / right; } );
    return arr;
}

constexpr array_type auto& operator += ( array_type auto& left, const array_type auto& right )
    requires requires { left = left + right; }
{
    constexpr int dim  = left.dimension();
    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 and right.dimension() >= 2 ) or requires ( left_value_type a, right_value_type b ) { a += b; } )
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
    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 and right.dimension() >= 2 ) or requires ( left_value_type a, right_value_type b ) { a -= b; } )
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
    if constexpr ( array_type<right_type> )
        return left = left * right;

    else /* not array_type<right_type> */
    {
        constexpr int dim  = left.dimension();
        let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

        for ( int i in range(shp_1) )
            if constexpr ( ( left.dimension() >= 2 ) or requires ( left_value_type a, right_type b ) { a *= b; } )
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
    let shp_1 = [&] { if constexpr ( abs(dim) == 1 ) return left.size(); else return left.row(); } ();

    for ( int i in range(shp_1) )
        if constexpr ( ( left.dimension() >= 2 ) or requires ( left_value_type a, right_type b ) { a /= b; } )
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