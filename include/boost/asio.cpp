module;
#undef in
#undef self
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

export module boost.asio;
import std;
import openssl;

namespace boost::asio
{
    export using boost::asio::buffer;
    export using boost::asio::io_context;
    
    namespace ip
    {
        export using boost::asio::ip::tcp;
        export using boost::asio::ip::udp;
    }
}