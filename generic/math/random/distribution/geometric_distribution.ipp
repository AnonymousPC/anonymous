#pragma once

constexpr int geometric_distribution ( float_type auto p )
{
    return geometric_distribution ( p, global_random_engine );
}

constexpr int geometric_distribution ( float_type auto p, random_engine_type auto& e )
{
    int m = 0;
    do
        m++;
    while ( not bernoulli_distribution(p, e) );

    return m;
}