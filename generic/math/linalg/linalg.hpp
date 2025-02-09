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

#include "nd/operator.hpp"

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