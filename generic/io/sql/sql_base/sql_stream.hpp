#pragma once

template < class type >
concept sql_mode = requires { typename type::sql_mode_tag; };

class sql_stream
{
    public: // Typedef
        using value_type = string;

    public: // Core
        sql_stream ( ) = default;
        sql_stream ( url, sql_mode auto... );

    public: // Interface
        sql_stream&        connect ( url, sql_mode auto... );
        sql_stream&        close   ( );
        matrix<value_type> execute ( string, auto... );

    public: // Modes
        struct username;
        struct password;
        struct database;

    private: // Data
        boost::mysql::any_connection sql_handle = boost::mysql::any_connection(io_context);
};

// TODO: two tables, server_statement_pool(map), client_statement_pool(set)
// hash<string>...
#include "sql_stream.ipp"