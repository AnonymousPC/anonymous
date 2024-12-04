#pragma once

constexpr int_type auto binomial_distribution ( int_type auto n, float_type auto p )
{
    return binomial_distribution ( n, p, random_engine );
}

constexpr int_type auto binomial_distribution ( int_type auto n, float_type auto p, random_engine_type auto& e )
{
    using type = decltype(n);

    type m = 0;
    for ( auto _ in range(n) )
        if ( not bernoulli_distribution(p, e) )
            m++;

    return m;
}
