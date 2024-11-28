#pragma once

/// Declaration

template < class engine_type,
           int   p,
           int   r
         >
class discard_block_engine
    extends public engine_type
{
    private: // Data
        int k = 0;

    public: // Member
        using engine_type::engine_type;
        constexpr engine_type::result_type operator() ( );
};



/// Class discard_block_engine

template < class engine_type, int p, int r >
constexpr engine_type::result_type discard_block_engine<engine_type,p,r>::operator() ( )
{
    if ( k == r )
    {
        for ( int _ in range(p-r) )
            engine_type::operator()();
        k = 0;
    }

    k++;
    return engine_type::operator()();
}