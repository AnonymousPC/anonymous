#pragma once

template < class type >
concept mysql_mode = requires { typename type::mysql_mode_tag; };

class mysql_stream
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
        mysql_stream ( ) = default;
        mysql_stream ( url, mysql_mode auto... );

    public: // Interface
        mysql_stream&      connect ( url, mysql_mode auto... );
        mysql_stream&      close   ( );
        matrix<value_type> execute ( string, auto... );

    public: // Modes
        struct username;
        struct password;
        struct database;

    private: // Data
        boost::mysql::any_connection                  handle          = boost::mysql::any_connection(io_context);
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

        struct empty_arg { };
        friend class boost::mysql::formatter<empty_arg>;
};

#include "mysql_stream.ipp"
#if dll
    #include "mysql_stream.cpp"
#endif