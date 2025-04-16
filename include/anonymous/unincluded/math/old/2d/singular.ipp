#pragma once

/// Declaration

constexpr tuple_type auto singular ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return singular ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
        try
        {
            auto solver = Eigen::JacobiSVD<decltype(aux::to_eigen(matrix))>(aux::to_eigen(matrix), Eigen::ComputeFullU | Eigen::ComputeFullV);
            return tuple ( aux::from_eigen(solver.singularValues()),
                           aux::from_eigen(solver.matrixU().transpose()),
                           aux::from_eigen(solver.matrixV().transpose()) );
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate singular of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
}

constexpr array_type auto singular_value ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return singular_value ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
        try
        {
            return aux::from_eigen(Eigen::JacobiSVD<decltype(aux::to_eigen(matrix))>(aux::to_eigen(matrix)).singularValues());
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate singular_value of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
}

constexpr pair_type auto singular_vector ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return singular_vector ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
        try
        {
            auto solver = Eigen::JacobiSVD<decltype(aux::to_eigen(matrix))>(aux::to_eigen(matrix), Eigen::ComputeFullU | Eigen::ComputeFullV);
            return pair ( aux::from_eigen(solver.matrixU().transpose()),
                          aux::from_eigen(solver.matrixV().transpose()) );
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate singular_vector of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
}