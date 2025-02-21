#pragma once

namespace detail
{
    struct io_initializer_t
    {
        io_initializer_t ( );
    };

    //#if dll
        io_initializer_t::io_initializer_t ( )
        {
            let current_path = string(__FILE__).replace('\\', '/');
            let config_path  = "{}/config"s.format(current_path[1,current_path.right_find('/')-1]);

            try
            {
                ssl_context.set_default_verify_paths();
                ssl_context.set_options(boost::asio::ssl::context_base::default_workarounds
                                       |boost::asio::ssl::context_base::no_sslv2
                                       |boost::asio::ssl::context_base::single_dh_use);
                ssl_context.use_certificate_chain_file("{}/cert.pem"s.format(config_path));
                ssl_context.use_private_key_file      ("{}/key.pem"s .format(config_path), boost::asio::ssl::context::pem);
                ssl_context.use_tmp_dh_file           ("{}/dh.pem"s  .format(config_path));
            }
            catch ( const boost::system::system_error& e )
            {
                throw network_error("failed to create ssl_server_context").from(detail::system_error(e));
            }
        }
    //#endif

    io_initializer_t io_initializer;
}