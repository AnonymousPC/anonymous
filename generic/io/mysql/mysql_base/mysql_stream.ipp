#pragma once

struct mysql_stream::username extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct mysql_mode_tag { }; };
struct mysql_stream::password extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct mysql_mode_tag { }; };
struct mysql_stream::database extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct mysql_mode_tag { }; };

mysql_stream::mysql_stream ( url mysql_server, mysql_mode auto... args )
{
    connect(mysql_server, std::forward<decltype(args)>(args)...);
}

mysql_stream& mysql_stream::connect ( url mysql_server, mysql_mode auto... args )
{
    // Params
    static_assert ( ( same_as<username,decltype(args)> or ... ) and
                    ( same_as<password,decltype(args)> or ... ),
                    "you should provide both username and password" );
    let params = boost::mysql::connect_params();
    params.server_address.emplace_host_and_port(mysql_server.host().c_str(), mysql_server.port() != "" ? int(mysql_server.port()) otherwise 3306);
    params.username = detail::value_of_same_type   <username>(args...)            .value.c_str();
    params.password = detail::value_of_same_type   <password>(args...)            .value.c_str();
    params.database = detail::value_of_same_type_or<database>(args..., database()).value.c_str();

    // Connect
    try
    {
        handle.connect(params);
   }
    catch ( const boost::mysql::error_with_diagnostics& e )
    {
        throw network_error("failed to connect mysql server (with server_url = {})", mysql_server).from(detail::mysql_error_with_diagnostics(e));
    }
    
    return self;
}

matrix<typename mysql_stream::value_type> mysql_stream::execute ( string str, auto... args )
{
    return detail::get_format_mode(str.c_str()) == detail::explicit_mode ?
               execute_client_stmt(str, args...) otherwise
               execute_server_stmt(str, args...);
}

matrix<typename mysql_stream::value_type> mysql_stream::execute_client_stmt ( string str, auto... args )
{
    // Execute statement.
    try
    {
        let results = boost::mysql::results();
        detail::get_format_mode(str.c_str()) == detail::explicit_mode ?
            handle.execute(boost::mysql::with_params(boost::mysql::runtime(("{0}" + str).c_str()), empty_arg(), make_stmt_arg(args)...), results) otherwise
            handle.execute(boost::mysql::with_params(boost::mysql::runtime(         str .c_str()),              make_stmt_arg(args)...), results);
        return execute_result(results);
    }
    catch ( const boost::mysql::error_with_diagnostics& e )
    {
        throw sql_error("failed to execute mysql statement (with statement = {})", format_client_stmt(e, str, args...)).from(detail::mysql_error_with_diagnostics(e));
    }
}

matrix<typename mysql_stream::value_type> mysql_stream::execute_server_stmt ( string str, auto... args )
{
    // If has been proved that this statement cannot be composed on server (for example: er_unsupported_ps)
    if ( client_stmtpool.contains(str) )
        return execute_client_stmt(std::move(str), std::forward<decltype(args)>(args)...);
    
    // Try to prepare a server statement. If failed, then fallback into client statement.
    let& statement = server_stmtpool[str];
    if ( not statement.valid() )
    {
        let error = boost::system::error_code();
        let diag  = boost::mysql::diagnostics();
        statement = handle.prepare_statement(string(str).replace("{}", '?').c_str(), error, diag);
        if ( error != boost::system::error_code() )
        {
            client_stmtpool.push(str);
            return execute_client_stmt(str, std::forward<decltype(args)>(args)...);
        }
    }
    
    // Execute statement.
    try
    {
        let results = boost::mysql::results();
        handle.execute(statement.bind(make_stmt_arg(args)...), results);
        return execute_result(results);
    }
    catch ( const boost::mysql::error_with_diagnostics& e )
    {
        throw sql_error("failed to execute mysql statement (with statement = {})", format_server_stmt(e, str, args...)).from(detail::mysql_error_with_diagnostics(e));
    }
}

string mysql_stream::format_client_stmt ( const boost::mysql::error_with_diagnostics& e, const string& str, const auto&... args ) const
{
    return e.code() != boost::mysql::client_errc::unformattable_value             and
           e.code() != boost::mysql::client_errc::format_string_invalid_specifier and
           e.code() != boost::mysql::client_errc::format_string_invalid_syntax    and
           e.code() != boost::mysql::client_errc::format_string_manual_auto_mix   and
           e.code() != boost::mysql::client_errc::format_arg_not_found ?
               detail::get_format_mode(str.c_str()) == detail::explicit_mode ?
                   boost::mysql::format_sql(handle.format_opts().value(), boost::mysql::runtime(("{0}" + str).c_str()), empty_arg(), make_stmt_arg(args)...).c_str() otherwise
                   boost::mysql::format_sql(handle.format_opts().value(), boost::mysql::runtime(         str .c_str()),              make_stmt_arg(args)...).c_str() otherwise
               "[[cannot format string \"{}\" with args {}]]"s.format(str, tuple(args...));
}

string mysql_stream::format_server_stmt ( const boost::mysql::error_with_diagnostics&, const string& str, const auto&... args ) const
{
    try
    {
        return detail::get_format_mode(str.c_str()) == detail::explicit_mode ?
            boost::mysql::format_sql(handle.format_opts().value(), boost::mysql::runtime(("{0}" + str).c_str()), empty_arg(), make_stmt_arg(args)...).c_str() otherwise
            boost::mysql::format_sql(handle.format_opts().value(), boost::mysql::runtime(         str .c_str()),              make_stmt_arg(args)...).c_str();
    }
    catch ( const boost::system::system_error& )
    {
        return "[[cannot format string \"{}\" with args {}]]"s.format(str, tuple(args...));
    }
}

auto mysql_stream::make_stmt_arg ( const auto& val )
{
    using type = decay<decltype(val)>;

    if constexpr ( same_as<type,std::nullptr_t> or same_as<type,bool> or char_type<type> or number_type<type> )
        return val;
    else if constexpr ( same_as<type,const char*> )
        return val;
    else if constexpr ( string_type<type> )
        return std::string_view(string_view(val).begin(), string_view(val).size());
    else if constexpr ( same_as<type,time_point> )
        return boost::mysql::datetime(std::chrono::system_clock::time_point(val));
    else if constexpr ( same_as<type,duration> )
        return boost::mysql::time(std::chrono::microseconds(val));
    else 
        static_assert(false, "unsuppored statement arg");
}








} // Out of namespace ap

namespace boost::mysql
{
    template < >
    struct formatter<ap::mysql_stream::empty_arg>
    {
        constexpr const char* parse  ( const char* begin, const char* ) { return begin; }
        constexpr void        format ( const ap::mysql_stream::empty_arg&, format_context_base& ) { }
    };
    
} // namespace boost::mysql

namespace ap { // Back into namespace ap



