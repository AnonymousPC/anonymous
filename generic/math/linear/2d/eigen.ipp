#pragma once

/// Declaration

constexpr pair_type auto eigen ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return eigen ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
    {
        #if debug
            if ( matrix.row() != matrix.column() )
                throw value_error("cannot calculate eigen of matrix of shape {}: matrix must be square", matrix.shape());
        #endif

        try
        {
            using solver_type = conditional<number_type<matrix_value_type>,
                                            Eigen::EigenSolver<decltype(aux::to_eigen(matrix))>,
                                            Eigen::ComplexEigenSolver<decltype(aux::to_eigen(matrix))>>;
            let solver = solver_type(aux::to_eigen(matrix));
            return pair ( aux::from_eigen(solver.eigenvalues()), aux::from_eigen(solver.eigenvectors().transpose()) );
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate eigen of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}

constexpr array_type auto eigen_value ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return eigen_value ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
    {
        #if debug
            if ( matrix.row() != matrix.column() )
                throw value_error("cannot calculate eigen_value of matrix of shape {}: matrix must be square", matrix.shape());
        #endif

        try
        {
            using solver_type = conditional<number_type<matrix_value_type>,
                                            Eigen::EigenSolver<decltype(aux::to_eigen(matrix))>,
                                            Eigen::ComplexEigenSolver<decltype(aux::to_eigen(matrix))>>;
            return aux::from_eigen(solver_type(aux::to_eigen(matrix)).eigenvalues());
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate eigen_value of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}

constexpr array_type auto eigen_vector ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> )
        return eigen_vector ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
    {
        #if debug
            if ( matrix.row() != matrix.column() )
                throw value_error("cannot calculate eigen_vector of matrix of shape {}: matrix must be square", matrix.shape());
        #endif

        try
        {
            using solver_type = conditional<number_type<matrix_value_type>,
                                            Eigen::EigenSolver<decltype(aux::to_eigen(matrix))>,
                                            Eigen::ComplexEigenSolver<decltype(aux::to_eigen(matrix))>>;
            let solver = solver_type(aux::to_eigen(matrix));
            return aux::from_eigen(solver.eigenvectors().transpose());
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate eigen_vector of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}