#pragma once

constexpr float_type auto fisher_f_distribution ( float_type auto m, float_type auto n )
{
    return fisher_f_distribution ( m, n, global_random_engine );
}

constexpr float_type auto fisher_f_distribution ( float_type auto m, float_type auto n, random_engine_type auto& e )
{
    return ( chi_squared_distribution(m, e) * n ) / ( chi_squared_distribution(n, e) * m );
}