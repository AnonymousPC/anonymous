#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

int main ( )
{
    let stream = tcp_stream();
    stream.connect("tcp://218.82.57.42:3306");
    print("OK");
}