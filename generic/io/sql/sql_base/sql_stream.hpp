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
        sql_stream&        open    ( url, sql_mode auto... );
        sql_stream&        close   ( );
        matrix<value_type> execute ( string, auto... );

    public: // Modes
        struct username;
        struct password;
        struct database;

    private: // Data
        boost::mysql::any_connection                  sql_handle      = boost::mysql::any_connection(io_context);
        unordered_map<string,boost::mysql::statement> server_stmtpool = {};
        unordered_set<string>                         client_stmtpool = {};

    private: // Detail
        matrix<value_type> execute_client_stmt     ( string, auto... );
        matrix<value_type> try_execute_server_stmt ( string, auto... );
        static auto        make_stmt_arg           ( const auto& );
};

#include "sql_stream.ipp"