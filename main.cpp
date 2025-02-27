#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

void client ( )
{
    print("client.start");
    let stream = udp_stream();
    stream.connect("udp://127.0.0.1:12345");
    print("client: connect ok");
    sleep(5s);
    stream << string(65500, 'a') << std::flush;
    print("client.quit");
    stream.close();
    
}

void server ( )
{
    let stream = udp_stream();
    print("server hello");
    stream.listen("udp://127.0.0.1:12345");
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout)); print();
    stream.clear();
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout)); print();
    print("server.quit");
}

void print_error ( std::exception_ptr ptr )
{
    try { std::rethrow_exception(ptr); } catch ( const std::exception& e ) { print("ERROR", e.what()); }
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