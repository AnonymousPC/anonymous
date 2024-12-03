#pragma once

constexpr float_type auto sin ( angle_type auto t )
{
    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::sin(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::sin(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto cos ( angle_type auto t )
{
    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::cos(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::cos(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto tan ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(90) )
        throw math_error("tan({}) is out of domain: tan(x) requires x != (2k+1) * 90deg for any in k in N", t);

    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::tan(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::tan(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto cot ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(0) )
        throw math_error("cot({}) is out of domain: cot(x) requires x != (2k) * 90deg for any k in N", t);

    return 1 / tan(t);
}

constexpr float_type auto sec ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(90) )
        throw math_error("sec({}) is out of domain: sec(x) requires x != (2k+1) * 90deg for any in k in N", t);

    return 1 / cos(t);
}

constexpr float_type auto csc ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(0) )
        throw math_error("csc({}) is out of domain: csc(x) requires x != (2k) * 90deg for any k in N", t);

    return 1 / sin(t);
}