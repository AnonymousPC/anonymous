#define left_value_type      typename remove_cvref<decltype(left  )>::value_type
#define left_layout_type     typename remove_cvref<decltype(left  )>::layout_type
#define left_accessor_type   typename remove_cvref<decltype(left  )>::accessor_type
#define right_value_type     typename remove_cvref<decltype(right )>::value_type
#define right_layout_type    typename remove_cvref<decltype(right )>::layout_type
#define right_accessor_type  typename remove_cvref<decltype(right )>::accessor_type
#define output_value_type    typename remove_cvref<decltype(output)>::value_type
#define output_layout_type   typename remove_cvref<decltype(output)>::layout_type
#define output_accessor_type typename remove_cvref<decltype(output)>::accessor_type
#define vector_value_type    typename remove_cvref<decltype(vector)>::value_type
#define vector_layout_type   typename remove_cvref<decltype(vector)>::layout_type
#define mdspan_value_type    typename remove_cvref<decltype(mdspan)>::value_type
#define mdspan_layout_type   typename remove_cvref<decltype(mdspan)>::layout_type
#define mdspan_accessor_type typename remove_cvref<decltype(mdspan)>::accessor_type







#define OPENCL_SOURCE(...) #__VA_ARGS__

#define OPENCL_DEFINE_UNARY_OPERATOR($operator, $functor)                                                       \
    template < class type >                                                                                     \
    class opencl::$functor                                                                                      \
        extends public std::$functor<type>                                                                      \
    {                                                                                                           \
        public:                                                                                                 \
            using result_type = type;                                                                           \
                                                                                                                \
            constexpr decltype(auto) operator() ( const type& a ) const                                         \
                requires ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> )                     \
            {                                                                                                   \
                return std::$functor<type>::operator()(a);                                                      \
            }                                                                                                   \
                                                                                                                \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const         \
            {                                                                                                   \
                return boost::compute::detail::invoked_function<                                                \
                           type,                                                                                \
                           boost::tuple<remove_cvref<decltype(a)>>                                              \
                       >(#$operator, std::string(), boost::make_tuple(a));                                      \
            }                                                                                                   \
    };                                                                                                          \
                                                                                                                \
    template < >                                                                                                \
    class opencl::$functor<void>                                                                                \
        extends public std::$functor<void>                                                                      \
    {                                                                                                           \
        public:                                                                                                 \
            constexpr decltype(auto) operator() ( const auto& a ) const                                         \
                requires requires { $operator a; } and                                                          \
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> )                      \
            {                                                                                                   \
                return std::$functor<void>::operator()(a);                                                      \
            }                                                                                                   \
                                                                                                                \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const         \
            {                                                                                                   \
                return boost::compute::detail::invoked_function<                                                \
                           decltype($operator std::declval<typename remove_cvref<decltype(a)>::result_type>()), \
                           boost::tuple<remove_cvref<decltype(a)>>                                              \
                       >(#$operator, std::string(), boost::make_tuple(a));                                      \
            }                                                                                                   \
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
                requires ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> ) and                                                        \
                         ( not detail::opencl_kernel_inputable<remove_cvref<decltype(b)>> )                                                            \
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
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(a)>> ) and                                                         \
                        ( not detail::opencl_kernel_inputable<remove_cvref<decltype(b)>> )                                                             \
            {                                                                                                                                          \
                return std::$functor<void>::operator()(a, b);                                                                                          \
            }                                                                                                                                          \
                                                                                                                                                       \
            constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const \
            {                                                                                                                                          \
                return boost::compute::detail::invoked_binary_operator<                                                                                \
                           remove_cvref<decltype(a)>,                                                                                                  \
                           remove_cvref<decltype(b)>,                                                                                                  \
                           decltype(std::declval<typename remove_cvref<decltype(a)>::result_type>() $operator                                          \
                                    std::declval<typename remove_cvref<decltype(b)>::result_type>())                                                   \
                       >(#$operator, a, b);                                                                                                            \
            }                                                                                                                                          \
    };

#define OPENCL_DEFINE_RESULT_OF_UNARY_OPERATOR($operator, $functor)                   \
    template < class type1 >                                                          \
    struct result_of<anonymous::opencl::$functor<void>(type1)>                        \
    {                                                                                 \
        using type = decltype($operator std::declval<type1>());                       \
    };

#define OPENCL_DEFINE_RESULT_OF_BINARY_OPERATOR($operator, $functor)                  \
    template < class type1, class type2 >                                             \
    struct result_of<anonymous::opencl::$functor<void>(type1,type2)>                  \
    {                                                                                 \
        using type = decltype(std::declval<type1>() $operator std::declval<type2>()); \
    };