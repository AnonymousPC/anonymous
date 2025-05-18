detail::mysql_error_with_diagnostics::mysql_error_with_diagnostics ( const boost::mysql::error_with_diagnostics& e )
    extends boost::mysql::error_with_diagnostics ( e )
{
    auto diag = e.get_diagnostics().server_message() != "" and e.get_diagnostics().client_message() != "" ? 
                   " (with server_message = {}, client_message = {})"s.format(std::string(e.get_diagnostics().server_message()), std::string(e.get_diagnostics().client_message())) :
               e.get_diagnostics().server_message() != "" ? 
                   " (with server_message = {})"s.format(std::string(e.get_diagnostics().server_message())) :
               e.get_diagnostics().client_message() != "" ? 
                   " (with client_message = {})"s.format(std::string(e.get_diagnostics().client_message())) :
             /*both == ""*/
                   "";

    error_what = string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()) + diag;
}

const char* detail::mysql_error_with_diagnostics::what ( ) const noexcept
{
    return error_what.c_str();
}