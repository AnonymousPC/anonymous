#pragma once

class pipe_stream
    extends public std::iostream
{
    /* Move contructor and operator= of std::iostream is protected */
    /** HAS BUG ON MOVE CONSTRUCTOR AND MOVE ASSIGNMENT. SEE HTTP_STREAM **/

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