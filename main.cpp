#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
#include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;
int main ( )
{
    file_csv f;
    matrix<string> m = matrix<string>(10, 10, [] (int i, int j) { return string(i*10+j); });
    f = m;
    f.save_as("test.csv");

    file_csv f2 = "test.csv";
    f2.flatten().each([] (auto& val) { val = '[' + val + ']'; });
    f2.save();
}