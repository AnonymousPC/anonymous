#pragma once

constexpr float_type auto chi_squared_distribution ( float_type auto n )
{
    return chi_squared_distribution ( n, random_engine );
}

constexpr float_type auto chi_squared_distribution ( float_type auto n, random_engine_type auto& e )
{
    using type = decltype(n);
    return 2 * gamma_distribution(n/2, type(1), e);
}