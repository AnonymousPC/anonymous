#pragma once

constexpr float_type auto gamma_distribution ( float_type auto a, float_type auto b )
{
    return gamma_distribution ( a, b, random_engine );
}

constexpr float_type auto gamma_distribution ( float_type auto a, float_type auto b, random_engine_type auto& e )
{
    using type = common_type<decltype(a),decltype(b)>;

    type ma = a < 1 ? a + 1 otherwise a;
    type a1 = ma - type(1) / 3;
    type a2 = 1 / ( sqrt ( a1 ) * 3 );

    type u = 0;
    type v = 0;
    type n = 0;

    do
    {
        do
        {
            n = normal_distribution(type(0), type(1), e);
            v = 1 + a2 * n;
        } while ( v <= 0 );

        v = v * v * v;
        u = uniform_distribution(type(0), type(1), e);
    } while ( u > 1 - 0.0331 * n * n * n * n and ln ( u ) > 0.5 * n * n + a1 * ( 1 - v + ln ( v ) ) );

    if ( a == ma )
        return a1 * v * b;

    else
    {
        do
            u = uniform_distribution(type(0), type(1), e);
        while ( u == 0 );

        return pow ( u, 1 / a ) * a1 * v * b;
    }
}