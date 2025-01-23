#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
// #include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"*
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

template < int from, int to, int add, int index >
constexpr void for_constexpr_impl ( auto&& op )
{
    if constexpr ( ( add > 0 and index <= to ) or
                    ( add < 0 and index >= to ) )
    {
        op<index>;
        for_constexpr_impl<from,to,index+add>(std::forward<decltype(op)>(op));
    }
}

template < int from, int to, int add = 1 >
constexpr void for_constexpr ( auto&& op )
{
    static_assert(add != 0, "this for-clause is infinite");
    if constexpr ( ( add > 0 and from <= to ) or
                    ( add < 0 and from >= to ) )
        for_constexpr_impl<from,to,add,from>(op);
    else
        static_assert(false, "this for-clause does not do anything");
}

int main ( )
{
    let t = [] <int index> (const auto&) { return index; };

    for_constexpr<1,3>(t);
};


// /*

// (2, 3, 4)

// [[[ 1,  2,  3,  4],
//   [ 5,  6,  7,  8],
//   [ 9, 10, 11, 12]],

//  [[13, 14, 15, 16],
//   [17, 18, 19, 20],
//   [21, 22, 23, 24]]]

// [  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 ]
// columns<2>: offset=1, shape=(2, 3)
//  [[ 2,  6, 10],
//   [14, 18, 22]]
// columns<1>: offset=2, shape=(2)
//  [10, 22]



// [  1, 13,  5, 17,  9, 21,  2, 14,  6, 18, 10, 22,  3, 15,  7, 19, 11, 23,  4, 16,  8, 20, 12, 24 ]


// */