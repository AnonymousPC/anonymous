#pragma once

namespace detail
{
    struct io_initializer_t
    {
        io_initializer_t ( );
    };

    #if dll
        io_initializer_t::io_initializer_t ( )
        {
            try
            {
                ssl_client_context.set_default_verify_paths();

                ssl_server_context.set_options(boost::asio::ssl::context_base::default_workarounds
                                              |boost::asio::ssl::context_base::no_sslv2
                                              |boost::asio::ssl::context_base::single_dh_use);
                if ( is_directory("C:/Server") )
                {
                    ssl_server_context.use_certificate_chain_file("C:/Server/cert.pem");
                    ssl_server_context.use_private_key_file      ("C:/Server/key.pem", boost::asio::ssl::context::file_format::pem);
                    ssl_server_context.use_tmp_dh_file           ("C:/Server/dh.pem");
                }
                else if ( is_directory("~/Server") )
                {
                    ssl_server_context.use_certificate_chain_file("~/Server/cert.pem");
                    ssl_server_context.use_private_key_file      ("~/Server/key.pem", boost::asio::ssl::context::file_format::pem);
                    ssl_server_context.use_tmp_dh_file           ("~/Server/dh.pem");
                }
                else
                    throw network_error("failed to create ssl_server_context: certification file not found");
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("failed to create ssl_server_context").from(detail::system_error(e));
            }
        }
    #endif

    io_initializer_t io_initializer;
}