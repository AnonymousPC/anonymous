#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/asioexec/interface.hpp"
using namespace ap;

int main ( )
{
    let timer = boost::asio::system_timer(boost::asio::system_executor(), 3s);
    let task  = timer.async_wait(asioexec::use_sender);
    std::execution::sync_wait(task);
}