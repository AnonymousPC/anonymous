constexpr /*value_type*/ auto tr ( const array_type auto& matrix )
    requires ( matrix.dimension() == 2 ) and ( number_type<matrix_value_type> or complex_type<matrix_value_type> )
{
    #ifdef debug
        if ( matrix.row() != matrix.column() )
            throw value_error("cannot calculate tr of matrix of shape {}: matrix must be square", matrix.shape());
    #endif

    matrix_value_type t = 0;
    for ( int i in range(matrix.row()) )
        t += matrix[i][i];
    return t;
}