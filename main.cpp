#include "generic/basic/interface.hpp"
#include "generic/container/interface.hpp"
// #include "generic/io/interface.hpp"
#include "generic/math/interface.hpp"
// #include "specific/neural/interface.hpp"
// #include "specific/spirit/interface.hpp"
// #include "specific/stock/interface.hpp"
using namespace ap;
#include <ccomplex>
int main ( )
{
    Eigen::Matrix<complex<double>,Eigen::Dynamic,Eigen::Dynamic> A(2, 2);

    print((A * A).eval());


    // let A = array<int,2,opencl>(10, 10);
    // let B = array<int,2,opencl>(10, 10);
    // let C = array<int,2,opencl>(10, 10);

    // clblast::Gemm<int>(
    //     clblast::Layout::kColMajor, clblast::Transpose::kNo, clblast::Transpose::kNo,
    //     10, 10, 10,
    //     1,
    //     A.data().get_buffer().get(), A.data().get_index(), 10,
    //     B.data().get_buffer().get(), B.data().get_index(), 10,
    //     0,
    //     C.data().get_buffer().get(), C.data().get_index(), 10,
    //     &opencl::execution_context.command_queue().get()
    // );
}