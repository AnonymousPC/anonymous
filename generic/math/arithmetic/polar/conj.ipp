#pragma once

constexpr polar_type auto conj ( polar_type auto a )
{
    return polar ( a.abs(), - a.arg() );
}