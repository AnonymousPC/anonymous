#pragma once

constexpr float_type auto uniform_distribution ( float_type auto a, float_type auto b )
{
    return uniform_distribution ( a, b, global_random_engine );
}

constexpr float_type auto uniform_distribution ( float_type auto a, float_type auto b, random_engine_type auto& e )
{
    using floating_point_engine = floating_point_engine<decay<decltype(e)>,common_type<decltype(a),decltype(b)>>;
    return static_cast<floating_point_engine&>(e)() * ( b - a ) + a;
}