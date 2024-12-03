#pragma once

constexpr bool bernoulli_distribution ( float_type auto p )
{
    return bernoulli_distribution ( p, global_random_engine );
}

constexpr bool bernoulli_distribution ( float_type auto p, random_engine_type auto& e )
{
    using type = decltype(p);
    return uniform_distribution(type(0), type(1), e) < p;
}