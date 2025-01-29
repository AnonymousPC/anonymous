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

struct accessor
{
    public: // Typedef
        using offset_policy    = accessor;
        using element_type     = int;
        using reference        = int&;
        using data_handle_type = std::vector<int>::iterator;

    public: // Member
        constexpr reference access ( data_handle_type p, std::size_t i ) const
        {
            return *(p + i);
        }

        constexpr data_handle_type offset ( data_handle_type p, std::size_t i ) const
        {
            return p + i;
        }
};


int main ( )
{
    let a = std::vector<int>(1000000);
    for ( int i in range(1000000) )
        a[i-1] = i;

    int v = 1;

    let t2 = std::chrono::system_clock::now();
    let s2 = std::mdspan<int,std::dextents<size_t,3>,std::layout_right,accessor>(a.begin(), std::array{100, 100, 100});
    for ( int _ in range(10) )
        for ( int i in range(100) )
            for ( int j in range(100) )
                for ( int k in range(100) )
                    v += s2[i, j, k];
    print(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - t2));



    let t1 = std::chrono::system_clock::now();
    let s1 = std::mdspan(a.data(), std::array{100, 100, 100});
    for ( int _ in range(10) )
        for ( int i in range(100) )
            for ( int j in range(100) )
                for ( int k in range(100) )
                    v += s1[i, j, k];
    print(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - t1));

    print(v);
}


// TODO:
// 1. 去掉opencl::pointer的iterator tag./
// 2. 重写opencl::[[container_base]], 可以不考虑map
// 3. array<nd>.resize().
// 4. 先开启io, 然后适配线性代数。
