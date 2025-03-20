#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/ioexec/interface.hpp"
using namespace ap;

// void main1 ( ) 
// {
//     let task = std::execution::just        ()
//              | std::execution::let_value   ([] { print("main_context",   std::this_thread::get_id()); return std::execution::just(); })
//              | std::execution::continues_on(system::execution_context.get_scheduler())
//              | std::execution::then        ([] { print("system_context", std::this_thread::get_id()); })
//              | std::execution::continues_on(cpu::execution_context.get_scheduler())
//              | std::execution::then        ([] { print("cpu_context",    std::this_thread::get_id()); });
//     std::execution::sync_wait(task);
// }   

void main2 ( )
{
    let timer1 = boost::asio::system_timer(boost::asio::system_executor(), 3s);
    let timer2 = boost::asio::system_timer(boost::asio::system_executor(), 5s);
    let task1 = std::execution::schedule (system::execution_context.get_scheduler())
              | std::execution::then     ([ ]             { print("cpu_context",    std::this_thread::get_id()); })
              | std::execution::let_value([&]             { return timer1.async_wait(ioexec::use_sender); })
              | std::execution::then     ([ ] (auto&&...) { print("system_context", std::this_thread::get_id()); });
    let task2 = std::execution::schedule (system::execution_context.get_scheduler())
              | std::execution::then     ([ ]             { print("cpu_context",    std::this_thread::get_id()); })
              | std::execution::let_value([&]             { return timer2.async_wait(ioexec::use_sender); })
              | std::execution::then     ([ ] (auto&&...) { print("system_context", std::this_thread::get_id()); });
    std::execution::sync_wait(std::execution::when_all(task1, task2));
}

// void main3 ( )
// {
//     print(now());

//     let timer = boost::asio::system_timer(boost::asio::system_executor(), 3s);
//     let tasks = std::execution::schedule(system::execution_context.get_scheduler())
//               | std::execution::then([] { return "argument"s; })
//               | std::execution::bulk(3, [&] (int i, auto&&...)
//                   {
//                       sleep(3s); 
//                   })
//               | std::execution::then([] (auto&&... args)
//                   {
//                       print(sizeof...(args), demangle(typeid(args))...);
//                       print("finish");
//                   });
//     std::execution::sync_wait(tasks);

//     print(now());
// } 


int main ( )
{
    
}