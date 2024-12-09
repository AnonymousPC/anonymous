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
    std::ios_base::sync_with_stdio(false);

    let outputs = pipe_process("g++",
                               pipe_process::param("-std=c++23", "-O3", "test.cpp", "-o", "test.exe",
                                                   "-Wall", "-fdiagnostics-color=always"));

    let gcc_regex   = "([^:]*|[A-Z]:[^:]*):([0-9]*):([0-9]*):(.*)"rgx;
    let seriousness = 0;

    outputs | std::views::transform([&] (const auto& line)
                {
                    try
                    {
                        let component = line.split(gcc_regex);
                        return "[{}] [{}] [{}] [{}]: {}"s.format(component[1], component[2], component[3], ++seriousness, component[4]);
                    }
                    catch ( const regex_error& )
                    {
                        return line;
                    }
                })
            | std::views::join_with('\n')
            | std::ranges::to<views::binary_ostream<char>>(std::ref(std::cout));


}
