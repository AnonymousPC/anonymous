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

using my_array = std::pair<std::vector<float>,
                           std::mdspan<float,std::dextents<int,1>,std::layout_stride>
                          >;

int main ( )
{
    let scale = (10 * 60) * 44100;

    let x = int(std::sqrt(float(scale)))*512;
    let y = int(std::sqrt(float(scale)))/512;
    print(x, y);

    {
        let t = std::chrono::system_clock::now();
        std::vector<std::vector<float>> mat(x, std::vector<float>(y));
        print("traditional", std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count());
        
        char ch;
        std::cin >> ch;
    }

    {
        let t = std::chrono::system_clock::now();
        std::vector<float> vct(x * y);
        let t2 = std::chrono::system_clock::now();
        // std::vector<my_array> rows(x);
        // for ( int i in range(x) )
        //     rows[i-1].second = std::mdspan<float,std::dextents<int,1>,std::layout_stride>(const_cast<float*>(vct.data()) + (2*(i-1)), {std::array{y}, std::array{1}});
        // std::vector<my_array> columns(y);
        // for ( int i in range(y) )
        //     columns[i-1].second = std::mdspan<float,std::dextents<int,1>,std::layout_stride>(const_cast<float*>(vct.data()) + (1*(i-1)), {std::array{x}, std::array{y}});
        // print("new",   std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - t).count()); 
        print("crazy", std::chrono::duration_cast<std::chrono::microseconds>(t2                               - t).count());

        char ch;
        std::cin >> ch;
    }
}

// M*N + 4*M
// M*N + 12*(M+N);

// [1] transpose改变自身
// [2] flatten类似于行列 加一个副本
// [3] reshape加一个唯一副本。

// int main ( )
// {
//     print(sizeof(test1), sizeof(test2));

//     let vct = std::vector<int>(24);
//     for ( int i in range<int>(vct.size()) )
//         vct[i-1] = i;
    
//     let ptr = const_cast<int*>(vct.data());
//     let mds = std::mdspan<int,std::dextents<int,2>,std::layout_stride>(
//         ptr,
//         std::layout_stride::mapping<std::dextents<int,2>>(std::array{4, 6}, std::array{4, 1})
//     );
    
//     for ( int i in range<int>(mds.extent(0)) )
//     {
//         for ( int j in range<int>(mds.extent(1)) )
//             std::cout << mds[i-1, j-1] << ' ';
//         print();
//     }
// }



// row, column = optimize;
// range_view = delete;
// filter_view = delete;
// flatten_view = optimize;
// reshape_view = delete;
// type_view = optimize;

// .reshape(1, 2, 3) = delete;