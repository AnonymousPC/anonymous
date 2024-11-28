#pragma once

#define right_type typename std::decay<decltype(right)>::type

class file_stream
    extends public std::fstream
{
    public: // Core
        file_stream ( );
        file_stream ( path, file_mode auto... );
       ~file_stream ( );

    public: // Open
        void open   ( path, file_mode auto... );

    public: // Modes
        struct mode_base;

        struct read_only;
        struct write_only;
        struct erase;
        struct append;

    private: // Typedef
        struct mode_type;

    private: // Auxiliary
        static mode_type          make_mode         (            auto, auto... );
        static mode_type          make_mode         ( mode_type, auto, auto... );
        static std::ios::openmode make_std_openmode ( mode_type );
};







// Subclass

struct file_stream::mode_base
{
    bool value = false;
    constexpr mode_base ( bool );
};

struct file_stream::read_only  extends public file_stream::mode_base { using mode_base::mode_base; struct file_mode_tag{}; };
struct file_stream::write_only extends public file_stream::mode_base { using mode_base::mode_base; struct file_mode_tag{}; };
struct file_stream::erase      extends public file_stream::mode_base { using mode_base::mode_base; struct file_mode_tag{}; };
struct file_stream::append     extends public file_stream::mode_base { using mode_base::mode_base; struct file_mode_tag{}; };

#include "file_stream.ipp"
#if dll
    #include "file_stream.cpp"
#endif

#undef right_type