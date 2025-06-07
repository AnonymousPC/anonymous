constexpr numeric auto abs ( numeric auto x )
{
    return std::abs(x);
}

constexpr numeric auto mod ( numeric auto x, numeric auto y )
{
    if ( y == 0 )
        throw math_error("{} % {}", x, y);

    if constexpr ( floating_point<decltype(x)> or floating_point<decltype(y)> )
        return std::fmod(x, y);
    else
        return x % y;
}

constexpr floating_point auto hypot ( numeric auto x, numeric auto y )
{
    if constexpr ( floating_point<decltype(x)> or floating_point<decltype(y)> )
        return std::hypot(x, y);
    else
        return std::hypot(double(x), double(y));
}

constexpr floating_point auto pow ( numeric auto x, numeric auto y )
{
    if constexpr ( floating_point<decltype(x)> or floating_point<decltype(y)> )
        return std::pow(x, y);
    else
        return std::pow(double(x), double(y));
}

constexpr floating_point auto exp ( numeric auto x )
{
    if constexpr ( floating_point<decltype(x)> )
        return std::exp(x);
    else
        return std::exp(double(x));
}

constexpr floating_point auto sqrt ( numeric auto x )
{
    if ( x < 0 )
        throw math_error("sqrt({})", x);

    if constexpr ( floating_point<decltype(x)> )
        return std::sqrt(x);
    else
        return std::sqrt(double(x));
}

constexpr floating_point auto cbrt ( numeric auto x )
{
    if constexpr ( floating_point<decltype(x)> )
        return std::cbrt(x);
    else
        return std::cbrt(double(x));
}

constexpr floating_point auto log ( numeric auto x, numeric auto y )
{
    if ( x <= 0 or x == 1 or y <= 0 )
        throw math_error("log({}, {})", x, y);

    if constexpr ( floating_point<decltype(x)> or floating_point<decltype(y)> )
        return std::log(x) / std::log(y);
    else
        return std::log(double(x)) / std::log(double(y));
}

constexpr floating_point auto ln ( numeric auto x )
{
    if ( x <= 0 )
        throw math_error("ln({})", x);

    if constexpr ( floating_point<decltype(x)> )
        return std::log(x);
    else
        return std::log(double(x));
}

constexpr integral auto ceil ( floating_point auto x )
{
    return int(std::ceil(x));
}

constexpr integral auto floor ( floating_point auto x )
{
    return int(std::floor(x));
}

constexpr integral auto round ( floating_point auto x )
{
    return int(std::round(x));
}

