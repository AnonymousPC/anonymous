#pragma once

template < class      engine_type,
           float_type type
         >
class floating_point_engine
    extends public engine_type
{
    public: // Typedef
        using result_type = type;

    public: // Member
        using engine_type::engine_type;
        constexpr        type operator() ( );
        constexpr static type min        ( );
        constexpr static type max        ( );
};



// Class floating_point_engine

template < class engine_type, float_type type >
constexpr type floating_point_engine<engine_type,type>::operator() ( )
{
    long double r     = static_cast<long double>(engine_type::max()) - static_cast<long double>(engine_type::min()) + 1;
    int         log2r = log ( type(2), r );
    int         m     = std::max ( 1, ( std::numeric_limits<type>::digits + log2r - 1 ) / log2r );

    type sum = 0;
    type tmp = 1;

    for ( int _ in range(m) )
    {
        sum += ( static_cast<type>(engine_type::operator()()) - static_cast<type>(engine_type::min()) ) * tmp;
        tmp *= r;
    }

    return sum / tmp;
}

template < class engine_type, float_type type >
constexpr type floating_point_engine<engine_type,type>::min ( )
{
    return 0;
}

template < class engine_type, float_type type >
constexpr type floating_point_engine<engine_type,type>::max ( )
{
    return 1;
}