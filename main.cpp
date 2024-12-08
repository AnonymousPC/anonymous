#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"
#include "specific/vscode/interface.hpp"

/// TODO: pipe_buf.underflow, actually 2 position will all setg().
/// TODO: pipe_buf.move moves the context handle, so that the pipe.depend_context should also be moved.

using namespace ap;

int main ( )
{
    pipe_command("dir").each(print);
    print("what");
    sleep(10s);
}
