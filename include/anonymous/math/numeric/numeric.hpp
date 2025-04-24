constexpr number_type auto abs ( number_type auto x )
{
    return std::abs(x);
}

constexpr number_type auto mod ( number_type auto x, number_type auto y )
{
    if ( y == 0 )
        throw math_error("{} % {}", x, y);

    if constexpr ( float_type<decltype(x)> or float_type<decltype(y)> )
        return std::fmod(x, y);
    else
        return x % y;
}

constexpr float_type auto hypot ( number_type auto x, number_type auto y )
{
    if constexpr ( float_type<decltype(x)> or float_type<decltype(y)> )
        return std::hypot(x, y);
    else
        return std::hypot(double(x), double(y));
}

constexpr float_type auto pow ( number_type auto x, number_type auto y )
{
    if constexpr ( float_type<decltype(x)> or float_type<decltype(y)> )
        return std::pow(x, y);
    else
        return std::pow(double(x), double(y));
}

constexpr float_type auto exp ( number_type auto x )
{
    if constexpr ( float_type<decltype(x)> )
        return std::exp(x);
    else
        return std::exp(double(x));
}

constexpr float_type auto sqrt ( number_type auto x )
{
    if ( x < 0 )
        throw math_error("sqrt({})", x);

    if constexpr ( float_type<decltype(x)> )
        return std::sqrt(x);
    else
        return std::sqrt(double(x));
}

constexpr float_type auto cbrt ( number_type auto x )
{
    if constexpr ( float_type<decltype(x)> )
        return std::cbrt(x);
    else
        return std::cbrt(double(x));
}

constexpr float_type auto log ( number_type auto x, number_type auto y )
{
    if ( x <= 0 or x == 1 or y <= 0 )
        throw math_error("log({}, {})", x, y);

    if constexpr ( float_type<decltype(x)> or float_type<decltype(y)> )
        return std::log(x) / std::log(y);
    else
        return std::log(double(x)) / std::log(double(y));
}

constexpr float_type auto ln ( number_type auto x )
{
    if ( x <= 0 )
        throw math_error("ln({})", x);

    if constexpr ( float_type<decltype(x)> )
        return std::log(x);
    else
        return std::log(double(x));
}

constexpr int_type auto ceil ( float_type auto x )
{
    return int(std::ceil(x));
}

constexpr int_type auto floor ( float_type auto x )
{
    return int(std::floor(x));
}

constexpr int_type auto round ( float_type auto x )
{
    return int(std::round(x));
}

