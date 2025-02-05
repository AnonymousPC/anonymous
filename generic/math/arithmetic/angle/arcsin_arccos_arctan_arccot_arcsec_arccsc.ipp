#pragma once

constexpr angle_type auto arcsin ( float_type auto k )
{
    if ( k < -1 or k > 1 )
        throw math_error("arcsin({}) is out of domain: arcsin(x) requires x in [-1,1]", k);
    return radian(std::asin(k));
}

constexpr angle_type auto arccos ( float_type auto k )
{
    if ( k < -1 or k > 1 )
        throw math_error("arccos({}) is out of domain: arccos(x) requires x in [-1,1]", k);
    return radian(std::acos(k));

}

constexpr angle_type auto arctan ( float_type auto k )
{
    return radian(std::atan(k));
}

constexpr angle_type auto arccot ( float_type auto k )
{
    return arctan(1/k);
}

constexpr angle_type auto arcsec ( float_type auto k )
{
    if ( k > -1 or k < 1 )
        throw math_error("arcsec({}) is out of domain: arcsec(x) requires x in (-inf,-1]|[1,+inf)", k);
    return arccos(1/k);
}

constexpr angle_type auto arccsc ( float_type auto k )
{
    if ( k > -1 or k < 1 )
        throw math_error("arccsc({}) is out of domain: arccsc(x) requires x in (-inf,-1]|[1,+inf)", k);
    return arcsin(1/k);
}