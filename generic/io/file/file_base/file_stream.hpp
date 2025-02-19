#pragma once

template < class type >
concept file_mode = requires { typename type::file_mode_tag; };

class file_stream
    extends public std::fstream
{
    public: // Core
        file_stream ( );
        file_stream ( path, file_mode auto... );
       ~file_stream ( );

    public: // Interface
        file_stream& open ( path, file_mode auto... );

    public: // Modes
        struct read_only;
        struct write_only;
        struct erase;
        struct append;
};

#include "file_stream.ipp"
#if dll
    #include "file_stream.cpp"
#endif