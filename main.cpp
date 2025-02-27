#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

void client ( )
{
    sleep(1s);
    print("client.start");
    let stream = udp_stream();
    stream.connect("udp://127.0.0.1:12345");
    print("client: connect ok");
    stream << "hello, world" << std::endl;
    stream << "nice, Alex" << std::endl;
    print("client.quit");
    stream.close();
    
}

void server ( )
{
    let stream = udp_stream();
    stream.listen("udp://127.0.0.1:12345");
    print("server: listen ok");
    views::binary_istream<char>(stream)
        | std::views::take_while([] (const auto& ch) { return ch != '\n'; })
        | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
    sleep(10s);
}

void print_error ( std::exception_ptr ptr )
{
    try { std::rethrow_exception(ptr); } catch ( const std::exception& e ) { print(e.what()); }
}

int main ( )
{
    let client_task = std::execution::schedule(cpu::execution_context.get_scheduler())
                    | std::execution::then(client)
                    | std::execution::upon_error(print_error);
    let server_task = std::execution::schedule(cpu::execution_context.get_scheduler())
                    | std::execution::then(server)
                    | std::execution::upon_error(print_error);
    std::execution::sync_wait(std::execution::when_all(server_task, client_task));

}