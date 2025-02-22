#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

int main ( )
{
    int p = int(input("which local port to make connection?"));
    
    tcp::socket sock(io_context);
    sock.open   (boost::asio::ip::tcp::v4());
    sock.bind   (boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"),         p));
    sock.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("115.120.204.162"), 80  ));
    
    // let addr = input("listen which address: ");

    // while ( true )
    //     try
    //     {
    //         let stream = http_stream();
    //         print("listening...");
    //         stream.listen(addr);
    //         let info = "connected: local_endpoint = {}, remote_endpoint = {}"s.format(stream.local_endpoint(), stream.remote_endpoint());
    //         print(info);
    //         stream << info << std::flush;
    //     }
    //     catch ( const std::exception& e )
    //     {
    //         print("error:", e.what());
    //     }
}