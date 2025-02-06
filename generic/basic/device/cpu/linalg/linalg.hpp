#pragma once

constexpr void cpu::linalg_matrix_product ( const auto& A, const auto& B, auto& C )
{
    using AV  = decay<decltype(A)>::value_type;
    using BV  = decay<decltype(B)>::value_type;
    using CV  = decay<decltype(C)>::value_type;
    using ABV = common_type<AV,BV>;

   // if ( not A.transposed() and not B.transposed() )
    {
        let AM = Eigen::Map<const Eigen::Matrix<AV,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(A.data(), A.shape()[1], A.shape()[2]);
        let BM = Eigen::Map<const Eigen::Matrix<BV,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(B.data(), B.shape()[1], B.shape()[2]);
        let CM = Eigen::Map<      Eigen::Matrix<CV,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>>(C.data(), C.shape()[1], C.shape()[2]);
        if constexpr ( same_as<AV,BV> )
            CM = AM * BM;
        else if constexpr ( same_as<AV,ABV> )
            CM = AM * BM.template cast<ABV>();
        else if constexpr ( same_as<BV,ABV> )   
            CM = AM.template cast<ABV>() * BM;
        else
            CM = AM.template cast<ABV>() * BM.template cast<ABV>();
    }

    
}



// 方法一 直接处理

auto operator * ( const auto& A, const auto& B )
    requires matrix...
{
    using device = ...;

    if constexpr ( not device::linalg::requires_same_value_type() )
        if ( ( A.memory_contiguous() or A.memory_transposed() ) and 
             ( B.memory_contiguous() or B.memory_transposed() ) )
            if constexpr ( same_as<AV,BV> )
            {
                let C = array<AV,2,device>(A.row(), A.column());
                device::linalg::matrix_product(A, B, C);
                return C;
            }
            else
            {
                let C = array<ABV,2,device>(A.row(), A.column());
                device::linalg::matrix_product(A, B, C);
                return C;
            }
        else if ( A.memory_contiguous() or A.memory_transposed() )
            return A * decay<decltype(B)>(B);
        else if ( B.memory_contiguous() or B.memory_transposed() )
            return decay<decltype(A)>(A) * B;
        else
            return decay<decltype(A)>(A) * decay<decltype(B)>(B);
    
    else
        if constexpr ( same_as<AV,ABV> )
            return A * array<ABV,2,device>(B);
        else if constexpr ( same_as<BV,ABV> )
            return array<ABV,2,device>(A) * B;
        else
            return array<ABV,2,device>(A) * array<ABV,2,device>(B);
}


// 方法二 mdspan 逐个 if constexpr ( requires { device::linalg::... } ) then use it, else to weaker...