#include "generic/basic/interface.hpp"
// #include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
// #include "generic/math/interface.hpp"
// #include "specific/audio/interface.hpp"
#include "specific/container/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;

struct my_plus
    extends public boost::compute::plus<int>
{
    decltype(auto) operator() ( const auto& a, const auto& b )
    {
        print("my_plus::operator():", demangle(typeid(a)), demangle(typeid(b)));
        print(exception().what());
        return boost::compute::plus<int>::operator()(a, b);
    }  
};

int main ( )
{
    let arr = boost::compute::vector<int>(100000);
    let t = std::chrono::system_clock::now();
    for ( int i in range(3) )
    {
        let result = 0;
        boost::compute::reduce(arr.begin(), arr.end(), &result);
        print(result);
    }
    print(std::chrono::system_clock::now() - t);

    let arr2 = array<int,1,opencl>(range(100000));
    t = std::chrono::system_clock::now();
    for ( int i in range(3) )
        print(arr2.sum());
    print(std::chrono::system_clock::now() - t);

    let arr3 = array<int,1,cpu>(range(100000));
    t = std::chrono::system_clock::now();
    for ( int i in range(3) )
        print(arr3.sum());
    print(std::chrono::system_clock::now() - t);
}

//     print("begin");
//     let arr = array<float,2,opencl> { {1, 2}, {3, 4} }; 
//     let slice = arr[1];
//     print(array(slice));
//     slice = arr[2];
//     print(array(slice));
//     arr.template push<2>(array<float,1,opencl>(range<float>(10, 11)));
//     print(arr);
// }


// TODO:
// 1. 所有的pointer(3个stride, 1个opencl::pointer)都要typedef 5个性质, operator+(ptrdiff_t).
// 4. 先开启io, 然后适配线性代数。
// 5. boost::compute::plus改为, 双重继承std/boost::compute, 然后两个using operator(). 试试加上plus<void>