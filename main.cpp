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
    let outputs = pipe_process("g++-14",
                               pipe_process::param("-std=c++23", "-O3", "test.cpp", "test",
                                                   "-Wall", "-fdiagnostics-color=always"));

    let rgx = "([^:]*):([0-9]*):([0-9]*):(.*)"rgx;


}
