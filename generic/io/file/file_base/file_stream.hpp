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

    private: // Detail
        struct mode_type;
        static mode_type          make_mode         (            auto, auto... );
        static mode_type          make_mode         ( mode_type, auto, auto... );
        static std::ios::openmode make_std_openmode ( mode_type );
};

#include "file_stream.ipp"
#if dll
    #include "file_stream.cpp"
#endif

#undef right_type