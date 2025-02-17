#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

void server()
{
    let stream = ssl_stream();
    stream.listen("ssl://127.0.0.1:8888");
    print("server listen ok!");
    views::binary_istream<char>(stream) | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
    stream.close();
}

void client()
{
    sleep(1s);
    let stream = ssl_stream();
    stream.connect("ssl://127.0.0.1:8888");
    print("client connect ok!");
    stream << "Hello,world!" << std::flush;
    stream.close();
}

int main ( )
{
    let task1 = std::execution::schedule(cpu::execution_context.get_scheduler())
              | std::execution::then(server);
    let task2 = std::execution::schedule(cpu::execution_context.get_scheduler())
              | std::execution::then(client);
    std::execution::sync_wait(std::execution::when_all(task1, task2));
    


    // for ( int i in range(1) )
    //     email_send(email_send::server  ("ssl://smtp.126.com:465"),
    //                email_send::username("shyeyian@126.com"),
    //                email_send::password("JWvhwefeXmFmgpzu"),
    //                email_send::from    ("shyeyian@126.com"),
    //                email_send::to      ("shyeyian@petalmail.com"),
    //                email_send::title   ("Your title"),
    //                email_send::data    ("This is a test message. id = {}. [[This is an email generated from C++]]"s.format(1))
    //             );
}