#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/asio/interface.hpp"

using namespace ap;

int main ( )
{
    let devices = array<string>{"Bluetooth-Incoming-Port",
                                "HUAWEIFreeBudsPro3",
                                "HUAWEIFreeClip",
                                "debug-console"};
    let task = std::execution::schedule(cpu::execution_context.get_scheduler())
             | std::execution::bulk(4, [&] (int i)
                {
                    let stream = serial_port_stream("/dev/cu.{}"s.format(devices[i-1]));
                })
}
































// #include "stdexec/execution.hpp"
// #include "specific/asio/src.hpp"
// #include "boost/asio/steady_timer.hpp"
// #include <iostream>

// namespace ex = stdexec;
// using asio_timer = asio2exec::use_sender_t::as_default_on_t<boost::asio::steady_timer>;

// int main() {
//     asio2exec::asio_context ctx;

//     ctx.start();

//     ex::sender auto work = ex::starts_on(ctx.get_scheduler(), ex::just(boost::asio::steady_timer(ctx.get_executor(), std::chrono::seconds(3)))) 
//                          | ex::let_value([&] (auto&& timer)
//                             {
//                                 return timer.async_wait(asio2exec::use_sender);
//                             })
//                          | ex::then([](boost::system::error_code ec){
//                                 if(ec)
//                                     throw boost::system::system_error{ec};
//                                 std::cout << "Hello World\n";
//                             });
//     ex::sender auto work2= ex::starts_on(ctx.get_scheduler(), ex::just(boost::asio::steady_timer(ctx.get_executor(), std::chrono::seconds(3)))) 
//                          | ex::let_value([&] (auto&& timer)
//                             {
//                                 return timer.async_wait(asio2exec::use_sender);
//                             })
//                          | ex::then([](boost::system::error_code ec){
//                                 if(ec)
//                                     throw boost::system::system_error{ec};
//                                 std::cout << "Hello World\n";
//                             });
    
//     ex::sync_wait(ex::when_all(std::move(work), std::move(work2)));
// }