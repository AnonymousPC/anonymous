#pragma once

constexpr float_type auto exponential_distribution ( float_type auto l )
{
    return exponential_distribution ( l, global_random_engine );
}

constexpr float_type auto exponential_distribution ( float_type auto l, random_engine_type auto& e )
{
    using type = decltype(l);
    return - ln ( uniform_distribution(type(0), type(1), e) ) / l;
}