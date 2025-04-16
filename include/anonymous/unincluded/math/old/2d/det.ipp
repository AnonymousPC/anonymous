#pragma once

/// Declaration

constexpr /*value_type*/ auto det ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( int_type<matrix_value_type> or complex_int_type<matrix_value_type> )
        return matrix_value_type ( round ( det ( matrix.template as_type<int_to_float_type<matrix_value_type>>() ) ) );
    else
    {
        #ifdef debug
            if ( matrix.row() != matrix.column() )
                throw value_error("cannot calculate determinant of matrx of shape {}: matrix must be square", matrix.shape());
        #endif

        try
        {
            if constexpr ( number_type<matrix_value_type> )
                return aux::to_eigen(matrix).determinant();
            else if constexpr ( complex_type<matrix_value_type> )
            {
                auto d = aux::to_eigen(matrix).determinant();
                return complex ( d.real(), d.imag() );
            }
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot calculate determinant of matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}