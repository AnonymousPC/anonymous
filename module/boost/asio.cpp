module;
#undef in
#undef self
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

export module boost.asio;
import std;
import openssl;

export namespace boost::asio
{
    using boost::asio::buffer;
    using boost::asio::io_context;
    
    namespace ip
    {
        using boost::asio::ip::tcp;
        using boost::asio::ip::udp;
    }
}