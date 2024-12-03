#pragma once

constexpr angle_type auto abs ( angle_type auto a )
{
    return a.value() >= 0 ? a otherwise -a;
}