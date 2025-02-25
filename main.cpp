#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
using namespace ap;

int main ( )
{
    let stream = pipe_stream("zsh");
    stream << "ifconfig" << std::endl
           << "exit" << std::endl;

    views::binary_istream<char>(stream) 
        | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));
}