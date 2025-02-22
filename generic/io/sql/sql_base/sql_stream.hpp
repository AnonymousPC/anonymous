#pragma once

template < class type >
concept sql_mode = requires { typename type::sql_mode_tag; };

class sql_stream
{
    public: // Typedef
        using value_type =
            variant<int64_t,
                    uint64_t,
                    float32_t,
                    float64_t,
                    string,
                    vector<char>,
                    time_point,
                    duration,
                    std::nullptr_t
                   >;

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
        matrix<value_type>        execute_client_stmt ( string, auto... );
        matrix<value_type>        execute_server_stmt ( string, auto... );
        static matrix<value_type> execute_result      ( const boost::mysql::results& );
        string                    format_client_stmt  ( const boost::mysql::error_with_diagnostics&, const string&, const auto&... ) const;
        string                    format_server_stmt  ( const boost::mysql::error_with_diagnostics&, const string&, const auto&... ) const;
        static auto               make_stmt_arg       ( const auto& );
        static value_type         make_result_arg     ( const boost::mysql::field_view& );
};

#include "sql_stream.ipp"
#if dll
    #include "sql_stream.cpp"
#endif