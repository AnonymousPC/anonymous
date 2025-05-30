#define decay<decltype(left)>                         decay<decltype(left)>
#define typename decay<decltype(left )>::value_type          typename decay<decltype(left)>::value_type
#define left_dimension                    decay<decltype(left)>::dimension()
#define typename decay<decltype(left )>::device_type         typename decay<decltype(left)>::device_type
#define decay<decltype(right)>                        decay<decltype(right)>
#define typename decay<decltype(right)>::value_type         typename decay<decltype(right)>::value_type
#define right_dimension                   decay<decltype(right)>::dimension()
#define typename decay<decltype(right)>::device_type        typename decay<decltype(right)>::device_type
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
    auto input_mdspan  = $input .mdspan();                                                                                                                                                                                    \
    auto output_mdspan = $output.mdspan();                                                                                                                                                                                    \
    switch ( input_mdspan.index() )                                                                                                                                                                                          \
    {                                                                                                                                                                                                                        \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                       \
    }

#define device_linalg_c1_1($function, $constant, $input, $output)                                                                                                                                                                       \
    auto input_mdspan  = $input .mdspan();                                                                                                                                                                                               \
    auto output_mdspan = $output.mdspan();                                                                                                                                                                                               \
    switch ( input_mdspan.index() )                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                   \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function($constant, input_mdspan.template value<1>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function($constant, input_mdspan.template value<2>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function($constant, input_mdspan.template value<3>(), output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                  \
    }
    
#define device_linalg_1c_1($function, $input, $constant, $output)                                                                                                                                                                       \
    auto input_mdspan  = $input .mdspan();                                                                                                                                                                                               \
    auto output_mdspan = $output.mdspan();                                                                                                                                                                                               \
    switch ( input_mdspan.index() )                                                                                                                                                                                                     \
    {                                                                                                                                                                                                                                   \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), $constant, output_mdspan.template value<1>()); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                                                                  \
    }

#define device_linalg_1_c($function, $input, $output)                                                                                                                                              \
    auto input_mdspan = $input.mdspan();                                                                                                                                                            \
    switch ( input_mdspan.index() )                                                                                                                                                                \
    {                                                                                                                                                                                              \
        case 1: if constexpr (requires{input_mdspan.template value<1>();}) device::linalg::$function(input_mdspan.template value<1>(), $output); else throw linalg_error("internal error"); break; \
        case 2: if constexpr (requires{input_mdspan.template value<2>();}) device::linalg::$function(input_mdspan.template value<2>(), $output); else throw linalg_error("internal error"); break; \
        case 3: if constexpr (requires{input_mdspan.template value<3>();}) device::linalg::$function(input_mdspan.template value<3>(), $output); else throw linalg_error("internal error"); break; \
        default: throw linalg_error("internal error");                                                                                                                                             \
    }

#define device_linalg_2_1($function, $input1, $input2, $output)                                                                                                                                                                                                                                      \
    auto input1_mdspan = $input1.mdspan();                                                                                                                                                                                                                                                            \
    auto input2_mdspan = $input2.mdspan();                                                                                                                                                                                                                                                            \
    auto output_mdspan = $output.mdspan();                                                                                                                                                                                                                                                            \
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
    auto input1_mdspan = $input1.mdspan();                                                                                                                                                                                                                                    \
    auto input2_mdspan = $input2.mdspan();                                                                                                                                                                                                                                    \
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

#include "operator.cpp"
#include "1d.cpp"
#include "2d.cpp"
#include "nd.cpp"

#undef device_linalg_1_1
#undef device_linalg_c1_1
#undef device_linalg_1c_1
#undef device_linalg_2_1
#undef device_linalg_2_c

#undef decay<decltype(left)>
#undef typename decay<decltype(left )>::value_type
#undef left_dimension
#undef typename decay<decltype(left )>::device_type
#undef decay<decltype(right)>
#undef typename decay<decltype(right)>::value_type
#undef right_dimension
#undef typename decay<decltype(right)>::device_type
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