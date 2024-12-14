#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"

using namespace ap;

int main ( )
{
    pipe_command("g++ --no-exist").each(print);
}