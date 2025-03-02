#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

void client ( )
{
    let stream = ssl_stream();
    stream.connect("ssl://127.0.0.1:12345");
    print("client: connect ok");
    stream << "hello, world" << std::endl;
    stream << "hello, lyx"   << std::endl;
    print("client: send ok");
    sleep(1s);
    stream.close();
}

void server ( )
{
    let stream = ssl_stream();
    stream.listen("ssl://127.0.0.1:12345");
    print("server: listen ok");
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
    print("=====");
}

void print_error ( std::exception_ptr ptr )
{
    try
    {
        std::rethrow_exception(ptr);
    }
    catch ( const std::exception& e )
    {
        print(e.what());
    }
}

int main ( )
{
    let task1 = std::execution::schedule(cpu::execution_context.get_scheduler()) 
              | std::execution::then(client);
    let task2 = std::execution::schedule(cpu::execution_context.get_scheduler()) 
              | std::execution::then(server);
    let task  = std::execution::when_all(task1, task2)
              | std::execution::upon_error(print_error);
    std::execution::sync_wait(task);


}