#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

void server ( )
{
    ssl_stream stream;
    stream.listen("ssl://localhost:8888");
    int i = 100;
    views::binary_istream<char>(stream) 
        | std::views::take_while([] (const auto& ch) { return ch != '!'; })
        | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
}

void client ( )
{
    ssl_stream stream;
    stream.connect("ssl://localhost:8888");
    stream << "Hello, world!" << std::flush;
}

int main ( )
{
    let task1 = std::execution::schedule(cpu::execution_context.get_scheduler())
              | std::execution::then(server)
              | std::execution::upon_error([] (std::exception_ptr ptr) { try { std::rethrow_exception(ptr); } catch (std::exception& e) { print(e.what()); } });
    let task2 = std::execution::schedule(cpu::execution_context.get_scheduler())
              | std::execution::then(client)
              | std::execution::upon_error([] (std::exception_ptr ptr) { try { std::rethrow_exception(ptr); } catch (std::exception& e) { print(e.what()); } });
    std::execution::sync_wait(std::execution::when_all(task1, task2));       
}