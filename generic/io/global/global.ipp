#pragma once

namespace detail
{
    struct io_initializer_t
    {
        io_initializer_t ( );

        static string cert_file;
        static string key_file;
        static string dh_file;
    };

    extern io_initializer_t io_initializer;
}