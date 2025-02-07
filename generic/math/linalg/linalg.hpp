#pragma once

#define left_type                         decay<decltype(left)>
#define left_value_type          typename decay<decltype(left)>::value_type
#define left_dimension                    decay<decltype(left)>::dimension()
#define left_device_type         typename decay<decltype(left)>::device_type
#define right_type                        decay<decltype(right)>
#define right_value_type         typename decay<decltype(right)>::value_type
#define right_dimension                   decay<decltype(right)>::dimension()
#define right_device_type        typename decay<decltype(right)>::device_type
#define vector_type                       decay<decltype(vector)>
#define vector_value_type        typename decay<decltype(vector)>::value_type
#define vector_dimension                  decay<decltype(vector)>::dimension()
#define vector_device_type       typename decay<decltype(vector)>::device_type
#define matrix_type                       decay<decltype(matrix)>
#define matrix_value_type        typename decay<decltype(matrix)>::value_type
#define matrix_dimension                  decay<decltype(matrix)>::dimension()
#define matrix_device_type       typename decay<decltype(matrix)>::device_type
#define ndarray_type                      decay<decltype(ndarray)>
#define ndarray_value_type       typename decay<decltype(ndarray)>::value_type
#define ndarray_dimension                 decay<decltype(ndarray)>::dimension()
#define ndarray_device_type      typename decay<decltype(ndarray)>::device_type

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( ( number_type<left_value_type> or complex_type<left_value_type> ) and ( number_type<right_value_type> or complex_type<right_value_type> ) ) and
             ( left_dimension == 2 and right_dimension == 2 ) and
             same_as<left_device_type,right_device_type>
{
    #if debug
    if ( left.column() != right.row() )
        throw linalg_error("multiply matrix with inconsistent row and column (with left_shape = {}, right_shape = {})", left.shape(), right.shape());
    #endif
    
    using device = left_device_type;
    let output = array<multiply_result<left_value_type,right_value_type>,2,device>().resize(left.row(), right.column());

    let left_mdspan   = left  .mdspan();
    let right_mdspan  = right .mdspan();
    let output_mdspan = output.mdspan();

    switch ( 3 * (left_mdspan.index() - 1) + 1 * (right_mdspan.index() - 1) + 1 )
    {
        case 1: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 2: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 3: device::linalg::multiply(left_mdspan.template value<1>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 4: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 5: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 6: device::linalg::multiply(left_mdspan.template value<2>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        case 7: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<1>(), output_mdspan.template value<1>()); break;
        case 8: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<2>(), output_mdspan.template value<1>()); break;
        case 9: device::linalg::multiply(left_mdspan.template value<3>(), right_mdspan.template value<3>(), output_mdspan.template value<1>()); break;
        default: throw linalg_error("invalid input");
    }

    return output;
}

#undef left_type
#undef left_value_type
#undef left_dimension
#undef left_device_type
#undef right_type
#undef right_value_type
#undef right_dimension
#undef right_device_type
#undef vector_type
#undef vector_value_type
#undef vector_dimension
#undef vector_device_type
#undef matrix_type
#undef matrix_value_type
#undef matrix_dimension
#undef matrix_device_type
#undef ndarray_type
#undef ndarray_value_type
#undef ndarray_dimension
#undef ndarray_device_type