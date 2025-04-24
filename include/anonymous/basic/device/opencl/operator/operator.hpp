namespace detail
{
    template < class type >
    concept opencl_kernel_inputable = 
        is_class<type> and requires ( boost::compute::detail::meta_kernel& k, type t ) { k << t; };
    
} // namespace detail

#define OPENCL_DEFINE_UNARY_OPERATOR($operator, $functor)                                               \
    template < class type >                                                                             \
    class opencl::$functor                                                                              \
        extends public std::$functor<type>                                                              \
    {                                                                                                   \
        public:                                                                                         \
            using result_type = type;                                                                   \
                                                                                                        \
            constexpr decltype(auto) operator() ( const type& a ) const                                 \
                requires ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> )                    \
            {                                                                                           \
                return std::$functor<type>::operator()(a);                                              \
            }                                                                                           \
                                                                                                        \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const \
            {                                                                                           \
                return boost::compute::detail::invoked_function<                                        \
                        type,                                                                           \
                        boost::tuple<remove_cvref<decltype(a)>>                                                \
                    >(#$operator, std::string(), boost::make_tuple(a));                                 \
            }                                                                                           \
    };                                                                                                  \
                                                                                                        \
    template < >                                                                                        \
    class opencl::$functor<void>                                                                        \
        extends public std::$functor<void>                                                              \
      {                                                                                                 \
        public:                                                                                         \
            constexpr decltype(auto) operator() ( const auto& a ) const                                 \
                requires requires { $operator a; } and                                                  \
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> )                     \
            {                                                                                           \
                return std::$functor<void>::operator()(a);                                              \
            }                                                                                           \
                                                                                                        \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const \
            {                                                                                           \
                return boost::compute::detail::invoked_function<                                        \
                        decltype($operator std::declval<typename remove_cvref<decltype(a)>::result_type>()),   \
                        boost::tuple<remove_cvref<decltype(a)>>                                                \
                    >(#$operator, std::string(), boost::make_tuple(a));                                 \
            }                                                                                           \
    }; 

#define OPENCL_DEFINE_BINARY_OPERATOR($operator, $functor)                                                                                             \
    template < class type >                                                                                                                            \
    class opencl::$functor                                                                                                                             \
        extends public boost::compute::$functor<type>,                                                                                                 \
                public std::$functor<type>                                                                                                             \
    {                                                                                                                                                  \
        public:                                                                                                                                        \
            using boost::compute::$functor<type>::result_type;                                                                                         \
                                                                                                                                                       \
            constexpr decltype(auto) operator() ( const type& a, const type& b ) const                                                                 \
                requires ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> ) and                                                               \
                         ( not detail::opencl_kernel_inputable<remove_cvref<decltype(b)>> )                                                                   \
            {                                                                                                                                          \
                return std::$functor<type>::operator()(a, b);                                                                                          \
            }                                                                                                                                          \
                                                                                                                                                       \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const \
            {                                                                                                                                          \
                return boost::compute::$functor<type>::operator()(a, b);                                                                               \
            }                                                                                                                                          \
    };                                                                                                                                                 \
                                                                                                                                                       \
    template < >                                                                                                                                       \
    class opencl::$functor<void>                                                                                                                       \
        extends public std::$functor<void>                                                                                                             \
    {                                                                                                                                                  \
        public:                                                                                                                                        \
            constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const                                                                 \
                requires requires { a $operator b; } and                                                                                               \
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> ) and                                                                \
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(b)>> )                                                                    \
            {                                                                                                                                          \
                return std::$functor<void>::operator()(a, b);                                                                                          \
            }                                                                                                                                          \
                                                                                                                                                       \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const \
            {                                                                                                                                          \
                return boost::compute::detail::invoked_binary_operator<                                                                                \
                        remove_cvref<decltype(a)>,                                                                                                            \
                        remove_cvref<decltype(b)>,                                                                                                            \
                        decltype(std::declval<typename remove_cvref<decltype(a)>::result_type>() $operator                                                    \
                                 std::declval<typename remove_cvref<decltype(b)>::result_type>())                                                             \
                    >(#$operator, a, b);                                                                                                               \
            }                                                                                                                                          \
    };

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

#undef OPENCL_DEFINE_UNARY_OPERATOR
#undef OPENCL_DEFINE_BINARY_OPERATOR


