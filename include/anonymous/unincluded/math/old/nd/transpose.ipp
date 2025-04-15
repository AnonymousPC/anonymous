#pragma once

constexpr array_type auto transpose ( const array_type auto& ndarray )
    requires std::copyable<ndarray_value_type>
{
    if constexpr ( ndarray.dimension() == -1 )
        return array<ndarray_value_type, 1> ( ndarray );

    else if constexpr ( ndarray.dimension() == 1 )
        return array<ndarray_value_type,-1> ( ndarray );

    else if constexpr ( ndarray.dimension() == 2 )
        return matrix ( ndarray.column(), ndarray.row(), [&] ( int i, int j ) { return ndarray[j][i]; } );

    else // ndarray.dimension() >= 3
        return array<ndarray_value_type,ndarray.dimension()> ( ndarray.shape()[-1],
                                                               [&] ( int i ) { return transpose ( array_axis_view<ndarray_type,ndarray.dimension()>(const_cast<ndarray_type&>(ndarray))[i] ); } );
}

constexpr array_type auto hermitian ( const array_type auto& ndarray )
    requires complex_type<ndarray_value_type>
{
    if constexpr ( ndarray.dimension() == -1 )
        return array<ndarray_value_type, 1> ( [&] ( int i ) { return conj(ndarray[i]); } );

    else if constexpr ( ndarray.dimension() == 1 )
        return array<ndarray_value_type,-1> ( [&] ( int i ) { return conj(ndarray[i]); } );

    else if constexpr ( ndarray.dimension() == 2 )
        return matrix ( ndarray.column(), ndarray.row(), [&] ( int i, int j ) { return conj(ndarray[j][i]); } );

    else // ndarray.dimension() >= 3
        return array<ndarray_value_type,ndarray.dimension()> ( ndarray.shape()[-1],
                                                               [&] ( int i ) { return hermitian ( array_axis_view<ndarray_type,ndarray.dimension()>(const_cast<ndarray_type&>(ndarray))[i] ); } );
}