#pragma once

constexpr float_type auto student_t_distribution ( float_type auto n )
{
    return student_t_distribution ( n, global_random_engine );
}

constexpr float_type auto student_t_distribution ( float_type auto n, random_engine_type auto& e )
{
    using type = decltype(n);
    return normal_distribution(type(0), type(1), e) / sqrt ( chi_squared_distribution(n, e) / n );
}