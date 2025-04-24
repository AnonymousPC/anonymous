constexpr pair_type auto qr ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return qr ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
        try
        {
            auto solver = Eigen::HouseholderQR<decltype(aux::to_eigen(matrix))>(aux::to_eigen(matrix));
            return pair ( aux::from_eigen(Eigen::Matrix<typename decltype(aux::to_eigen(matrix))::Scalar,Eigen::Dynamic,Eigen::Dynamic>(solver.householderQ())),
                          aux::from_eigen(Eigen::Matrix<typename decltype(aux::to_eigen(matrix))::Scalar,Eigen::Dynamic,Eigen::Dynamic>(solver.matrixQR().template triangularView<Eigen::Upper>())) );
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot qr-decompose matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
}