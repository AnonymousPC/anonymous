#pragma once

class pipe_stream
    extends public std::iostream
{
    /* Move contructor and move assigner of std::iostream is protected */
    /* Move contructor of std::iostream does not moves rdbuf(), and leaves constructed stream.rdbuf() == nullptr */
    /* Move assigner   of std::iostream does not moves rdbuf(), and leaves constructed and moved stream.rdbuf() not changed */

    public: // Core
        pipe_stream  ( );
        pipe_stream  ( path, pipe_mode auto... );
        pipe_stream  ( pipe_stream&& );
       ~pipe_stream  ( );
        pipe_stream& operator = ( pipe_stream&& );

    public: // Interface
        void open       ( path, pipe_mode auto... );
        void close      ( );
        bool is_open    ( ) const;
        bool is_running ( ) const;

    public: // Override
        std::ostream& flush ( );

    public: // Modes
        using environment     = pipe_buf::environment;
        using param           = pipe_buf::param;
        using start_directory = pipe_buf::start_directory;

    private: // Data
        pipe_buf buff = pipe_buf();
};

#include "pipe_stream.ipp"
#if dll
    #include "pipe_stream.cpp"
#endif