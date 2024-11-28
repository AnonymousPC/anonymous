#pragma once

constexpr int_type auto random ( int_type auto a, int_type auto b )
{
    return random ( a, b, global_random_engine );
}

constexpr int_type auto random ( int_type auto a, int_type auto b, random_engine_type auto& e )
{
    return common_type<decltype(a),decltype(b)> ( ( e() - e.min() ) % ( b - a + 1 ) + a );
}

constexpr char_type auto random ( char_type auto a, char_type auto b )
{
    return random ( a, b, global_random_engine );
}

constexpr char_type auto random ( char_type auto a, char_type auto b, random_engine_type auto& e )
{
    return common_type<decltype(a),decltype(b)> ( ( e() - e.min() ) % ( b - a + 1 ) + a );
}