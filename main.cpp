#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
#include "specific/audio/interface.hpp"
#include "specific/neural/interface.hpp"
#include "specific/spirit/interface.hpp"
#include "specific/stock/interface.hpp"
#include <vector>

using namespace ap;

int main ( )
{
    array a = { {1,2}, {3,4} };
    a[1];       // array&;
    a[1,2], // array&;
}