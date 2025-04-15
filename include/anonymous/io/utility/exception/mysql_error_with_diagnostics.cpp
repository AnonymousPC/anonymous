#pragma once

detail::mysql_error_with_diagnostics::mysql_error_with_diagnostics ( const boost::mysql::error_with_diagnostics& e )
    extends boost::mysql::error_with_diagnostics ( e )
{
    let diag = e.get_diagnostics().server_message() != "" and e.get_diagnostics().client_message() != "" ? 
                   " (with server_message = {}, client_message = {})"s.format(std::string(e.get_diagnostics().server_message()), std::string(e.get_diagnostics().client_message())) otherwise
               e.get_diagnostics().server_message() != "" ? 
                   " (with server_message = {})"s.format(std::string(e.get_diagnostics().server_message())) otherwise
               e.get_diagnostics().client_message() != "" ? 
                   " (with client_message = {})"s.format(std::string(e.get_diagnostics().client_message())) otherwise
             /*both == ""*/
                   "";

    error_what = string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()) + diag;
}

const char* detail::mysql_error_with_diagnostics::what ( ) const noexcept
{
    return error_what.c_str();
}