#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"
#include "specific/vscode/interface.hpp"
using namespace ap;

int main ( )
{
    pipe_stream stream;
    stream.open("ipconfig",
                pipe_stream::start_directory);
    stream.output() = stream.std_out;
    stream2.input() = stream1.output();

    setvbuf
}
