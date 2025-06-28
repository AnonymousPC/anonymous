namespace detail
{
    template < class type >
    concept opencl_kernel_inputable = 
        is_class<type> and requires ( boost::compute::detail::meta_kernel& k, type t ) { k << t; };
    
} // namespace detail

OPENCL_DEFINE_BINARY_OPERATOR(+,  plus         )
OPENCL_DEFINE_BINARY_OPERATOR(-,  minus        )
OPENCL_DEFINE_BINARY_OPERATOR(*,  multiplies   )
OPENCL_DEFINE_BINARY_OPERATOR(/,  divides      )
OPENCL_DEFINE_UNARY_OPERATOR (-,  negate       )
OPENCL_DEFINE_BINARY_OPERATOR(==, equal_to     )
OPENCL_DEFINE_BINARY_OPERATOR(!=, not_equal_to )
OPENCL_DEFINE_BINARY_OPERATOR(<,  less         )
OPENCL_DEFINE_BINARY_OPERATOR(<=, less_equal   )
OPENCL_DEFINE_BINARY_OPERATOR(>,  greater      )
OPENCL_DEFINE_BINARY_OPERATOR(>=, greater_equal)
OPENCL_DEFINE_BINARY_OPERATOR(&&, logical_and  )
OPENCL_DEFINE_BINARY_OPERATOR(||, logical_or   )
OPENCL_DEFINE_UNARY_OPERATOR (!,  logical_not  )
OPENCL_DEFINE_BINARY_OPERATOR(&,  bit_and      )
OPENCL_DEFINE_BINARY_OPERATOR(|,  bit_or       )
OPENCL_DEFINE_BINARY_OPERATOR(^,  bit_xor      )
OPENCL_DEFINE_UNARY_OPERATOR (~,  bit_not      )



