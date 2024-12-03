#pragma once

/// Declaration

template < class engine_type,
           int   p
         >
class shuffle_order_engine
    extends public engine_type
{
    private: // Data
        using data_type = random_engine_algo::array<typename engine_type::result_type,p>;
        data_type x = data_type();
        int       k = 0;

    public: // Member
        constexpr shuffle_order_engine ( engine_type::result_type = engine_type::default_seed );
        constexpr engine_type::result_type operator() ( );
};



/// Class shuffle_order_engine

template < class engine_type, int p >
constexpr shuffle_order_engine<engine_type,p>::shuffle_order_engine ( engine_type::result_type seed )
    extends engine_type ( seed )
{
    for ( int i in range ( 0, p - 1 ) )
        x[i] = engine_type::operator()();

    k = engine_type::operator()();
}

template < class engine_type, int p >
constexpr engine_type::result_type shuffle_order_engine<engine_type,p>::operator() ( )
{
    let r = ( k - engine_type::min() ) / ( engine_type::max() - engine_type::min() + static_cast<long double>(1) );
    let i = p * r;

    k = x[i];
    x[i] = engine_type::operator()();

    return k;
}