#pragma once

namespace aux
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
                ssl_server_context.set_options(boost::asio::ssl::context::default_workarounds
                                              |boost::asio::ssl::context::no_sslv2
                                              |boost::asio::ssl::context::single_dh_use);
                #ifdef _WIN32
                    ssl_server_context.use_certificate_chain_file("C:/Server/cert.pem");
                    ssl_server_context.use_private_key_file      ("C:/Server/key.pem", boost::asio::ssl::context::file_format::pem);
                    ssl_server_context.use_tmp_dh_file           ("C:/Server/dh.pem");
                #endif
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("ssl server context failed to initialize [[caused by {}: {}]]",
                                    typeid(e), string(e.what()).encode(std::text_encoding::environment(), std::text_encoding::literal()));
            }
        }
    #endif

    io_initializer_t io_initializer;
}