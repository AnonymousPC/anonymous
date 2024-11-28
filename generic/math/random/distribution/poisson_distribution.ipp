#pragma once

constexpr int poisson_distribution ( float_type auto l )
{
    return poisson_distribution ( l, global_random_engine );
}

constexpr int poisson_distribution ( float_type auto l, random_engine_type auto& e )
{
    using type = decltype(l);

    int  m    = 0;
    type prod = 1;
    type lm   = exp(-l);
    do
    {
        prod *= uniform_distribution(type(0), type(1), e);
        m++;
    }
    while ( prod > lm );

    return m - 1;
}