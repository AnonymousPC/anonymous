/// Declaration

constexpr array_type auto inverse ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( numeric<matrix_value_type> or complex_type<matrix_value_type> )
{
    if constexpr ( integral<matrix_value_type> or complex_int_type<matrix_value_type> )
        return inverse ( matrix.template as_type<int_to_float_type<matrix_value_type>>() );
    else
    {
        #ifdef debug
            if ( matrix.row() != matrix.column() )
                throw value_error("cannot inverse matrix of shape {}: matrix must be square", matrix.shape());
        #endif

        try
        {
            return aux::from_eigen(aux::to_eigen(matrix).inverse());
        }
        catch ( const std::runtime_error& e )
        {
            throw math_error("cannot inverse matrix [[caused by {}: {}]]", "Eigen", e.what());
        }
    }
}