#pragma once

struct sql_stream::username extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct sql_mode_tag { }; };
struct sql_stream::password extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct sql_mode_tag { }; };
struct sql_stream::database extends public detail::io_mode<string> { using detail::io_mode<string>::io_mode; struct sql_mode_tag { }; };

sql_stream::sql_stream ( url sql_server, sql_mode auto... args )
{
    connect(sql_server, std::forward<decltype(args)>(args)...);
}

sql_stream& sql_stream::connect ( url sql_server, sql_mode auto... args )
{
    // Params
    static_assert ( ( same_as<username,decltype(args)> or ... ) and
                    ( same_as<password,decltype(args)> or ... ),
                    "you should provide both username and password" );
    let params = boost::mysql::connect_params();
    params.server_address.emplace_host_and_port(sql_server.host().c_str(), int(sql_server.port()));
    params.username = detail::value_of_same_type<username>(args...).value.c_str();
    params.password = detail::value_of_same_type<password>(args...).value.c_str();
    params.database = [&] { if constexpr ( ( same_as<database,decltype(args)> or ... ) ) return detail::value_of_same_type<database>(args...).value.c_str(); else return ""; } ();

    // Connect
    try
    {
        sql_handle.connect(params);
    }
    catch ( const boost::mysql::error_with_diagnostics& e )
    {
        throw sql_error("failed to connect to the server (with server_url = {}, server_message = {}, client_message = {})",
                        sql_server,
                        e.get_diagnostics().server_message() != "" ? std::string(e.get_diagnostics().server_message()) otherwise "[[empty]]",
                        e.get_diagnostics().client_message() != "" ? std::string(e.get_diagnostics().client_message()) otherwise "[[empty]]"
                       ).from(detail::system_error(e));
    }
    
    return self;
}

matrix<typename sql_stream::value_type> sql_stream::execute ( string command, auto... args )
{
    try
    {
        let result = boost::mysql::results();
        sql_handle.execute(boost::mysql::with_params(boost::mysql::runtime(command.c_str()), args...), result);
        return {};
    }
    catch ( const boost::mysql::error_with_diagnostics& e )
    {
        throw sql_error("failed to execute sql command (with command (trivial replace) = {}, server_message = {}, client_message = {})",
                        command,
                        e.get_diagnostics().server_message() != "" ? std::string(e.get_diagnostics().server_message()) otherwise "[[empty]]",
                        e.get_diagnostics().client_message() != "" ? std::string(e.get_diagnostics().client_message()) otherwise "[[empty]]"
                       ).from(detail::system_error(e));
    }
    catch ( const boost::system::system_error& e )
    {
        throw sql_error("failed to execute sql command (with command (trivial replace) = {})", command).from(detail::system_error(e));
    }
}

