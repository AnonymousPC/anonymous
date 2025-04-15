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

#define device_linalg_1_1($function, $input, $output)                                                                                                                                                                        \
    let input_mdspan  = $input .mdspan();                                                                                                                                                                                    \
    let output_mdspan = $output.mdspan();                                                                                                                                                                                    \
    switch ( input_mdspan.index() )                                                                                                                                                                                          \
    {                                                                                                                                                                                                                        \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                       \
    }

#define device_linalg_c1_1($function, $constant, $input, $output)                                                                                                                                                                       \
    let input_mdspan  = $input .mdspan();                                                                                                                                                                                               \
    let output_mdspan = $output.mdspan();                                                                                                                                                                                               \
    switch ( input_mdspan.index() )                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                   \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function($constant, input_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function($constant, input_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function($constant, input_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                  \
    }
    
#define device_linalg_1c_1($function, $input, $constant, $output)                                                                                                                                                                       \
    let input_mdspan  = $input .mdspan();                                                                                                                                                                                               \
    let output_mdspan = $output.mdspan();                                                                                                                                                                                               \
    switch ( input_mdspan.index() )                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                   \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                  \
    }

#define device_linalg_1_c($function, $input, $output)                                                                                                                                              \
    let input_mdspan = $input.mdspan();                                                                                                                                                            \
    switch ( input_mdspan.index() )                                                                                                                                                                \
    {                                                                                                                                                                                              \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), $output); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), $output); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), $output); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                             \
    }

#define device_linalg_2_1($function, $input1, $input2, $output)                                                                                                                                                                                                                                      \
    let input1_mdspan = $input1.mdspan();                                                                                                                                                                                                                                                            \
    let input2_mdspan = $input2.mdspan();                                                                                                                                                                                                                                                            \
    let output_mdspan = $output.mdspan();                                                                                                                                                                                                                                                            \
    switch ( 3 * input1_mdspan.index() + input2_mdspan.index() - 3 )                                                                                                                                                                                                                                 \
    {                                                                                                                                                                                                                                                                                                \
        case 1: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 4: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 5: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 6: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 7: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 8: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 9: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                                                                               \
    }

#define device_linalg_2_c($function, $input1, $input2, $constant)                                                                                                                                                                                                            \
    let input1_mdspan = $input1.mdspan();                                                                                                                                                                                                                                    \
    let input2_mdspan = $input2.mdspan();                                                                                                                                                                                                                                    \
    switch ( 3 * input1_mdspan.index() + input2_mdspan.index() - 3 )                                                                                                                                                                                                         \
    {                                                                                                                                                                                                                                                                        \
        case 1: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<1>(), $constant); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<2>(), $constant); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input1_mdspan.template value<1>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<1>(), input2_mdspan.template value<3>(), $constant); else throw linalg_error("internal error"); break; \
        case 4: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<1>(), $constant); else throw linalg_error("internal error"); break; \
        case 5: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<2>(), $constant); else throw linalg_error("internal error"); break; \
        case 6: if constexpr (requires{input1_mdspan.template value<2>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<2>(), input2_mdspan.template value<3>(), $constant); else throw linalg_error("internal error"); break; \
        case 7: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<1>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<1>(), $constant); else throw linalg_error("internal error"); break; \
        case 8: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<2>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<2>(), $constant); else throw linalg_error("internal error"); break; \
        case 9: if constexpr (requires{input1_mdspan.template value<3>(); input2_mdspan.template value<3>();}) device::linalg::$function(input1_mdspan.template value<3>(), input2_mdspan.template value<3>(), $constant); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                                                       \
    }

#include "operator.ipp"
#include "1d.ipp"
#include "2d.ipp"
#include "nd.ipp"

#undef device_linalg_1_1
#undef device_linalg_c1_1
#undef device_linalg_1c_1
#undef device_linalg_2_1
#undef device_linalg_2_c

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