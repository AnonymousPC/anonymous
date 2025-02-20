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
                ssl_server_context.use_certificate_chain_file("./config/cert.pem");
                ssl_server_context.use_private_key_file      ("./config/key.pem", boost::asio::ssl::context::file_format::pem);
                ssl_server_context.use_tmp_dh_file           ("./config/dh.pem");
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("failed to create ssl_server_context").from(detail::system_error(e));
            }
        }
    #endif

    io_initializer_t io_initializer;
}