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
    let stream = udp_stream();
    stream.connect("udp://localhost:10000");
    print("client: connect ok");
    stream << "hello from client" << std::flush;
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
}

void server ( )
{
    let stream = udp_stream();
    stream.listen("udp://localhost:10000");
    print("server: listen ok");
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
    stream << "hello from server" << std::flush;
    views::binary_istream<char>(std::cin) | std::ranges::to<views::binary_ostream<char>>(std::ref(stream));
}

int main ( )
{
    let client_task = std::execution::schedule(cpu::execution_context.get_scheduler())
                    | std::execution::then(client);
    let server_task = std::execution::schedule(cpu::execution_context.get_scheduler())
                    | std::execution::then(server);
    std::execution::sync_wait(std::execution::when_all(server_task, client_task));

}