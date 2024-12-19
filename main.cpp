#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"

using namespace ap;

int main ( ) 
{
    let mat = matrix(100, 200, [] { return random(1,100); });
    let r = mat[1];
    
    
}



// row, column = optimize;
// range_view = delete;
// filter_view = delete;
// flatten_view = optimize;
// reshape_view = delete;
// type_view = optimize;

// .reshape(1, 2, 3) = delete;