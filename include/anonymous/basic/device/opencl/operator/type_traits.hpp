#pragma once

} // Out of namespace anonymous

#define OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR($operator, $functor)                       \
    namespace boost::compute                                                              \
    {                                                                                     \
        template < class type1 >                                                          \
        struct result_of<anonymous::opencl::$functor<void>(type1)>                               \
        {                                                                                 \
            using type = decltype($operator std::declval<type1>());                       \
        };                                                                                \
    }

#define OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR($operator, $functor)                      \
    namespace boost::compute                                                              \
    {                                                                                     \
        template < class type1, class type2 >                                             \
        struct result_of<anonymous::opencl::$functor<void>(type1,type2)>                         \
        {                                                                                 \
            using type = decltype(std::declval<type1>() $operator std::declval<type2>()); \
        };                                                                                \
    }

OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(+,  plus         )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(-,  minus        )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(*,  multiplies   )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(/,  divides      )
OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR (-,  negate       )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(==, equal_to     )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(!=, not_equal_to )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(<,  less         )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(<=, less_equal   )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(>,  greater      )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(>=, greater_equal)
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(&&, logical_and  )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(||, logical_or   )
OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR (!,  logical_not  )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(&,  bit_and      )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(|,  bit_or       )
OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR(^,  bit_xor      )
OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR (~,  bit_not      ) 
    
#undef OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR
#undef OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR

namespace anonymous { // Back into namespace anonymous