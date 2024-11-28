#pragma once

constexpr float_type auto normal_distribution ( float_type auto ex, float_type auto dx2 )
{
    return normal_distribution ( ex, dx2, global_random_engine );
}

constexpr float_type auto normal_distribution ( float_type auto ex, float_type auto dx2, random_engine_type auto& e )
{
    using type = common_type<decltype(ex),decltype(dx2)>;

    type x  = 0;
    type y  = 0;
    type r2 = 0;
    do
    {
        x  = type(2) * uniform_distribution(type(0), type(1), e) - 1;
        y  = type(2) * uniform_distribution(type(0), type(1), e) - 1;
        r2 = x * x + y * y;
    }
    while ( r2 > 1 or r2 == 0 );

    let m = sqrt ( - 2 * ln ( r2 ) / r2 );
    return ( x * m ) * sqrt ( dx2 ) + ex;
}