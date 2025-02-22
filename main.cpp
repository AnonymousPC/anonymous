#include <unistd.h>
#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

int main ( )
{
    let avoid_kill = set<int>{getpid()};

    for ( int i in range(7) )
        avoid_kill.push(int(input("vscode pid: ")));

    for ( int i in range(10000) )
    {
        if ( not avoid_kill.contains(i) )
            tryc
            {
                print("terminate process {} with exit code {}"s.format(i, terminate_process(i)));
            }
            catch ( const std::exception& e )
            {
                if ( not string(e.what()).contains("No such process") )
                    print("failed due to {}: {}"s.format(typeid(e), e.what()));
            }
    }       
}