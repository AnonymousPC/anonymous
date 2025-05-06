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

#define DEVICE_STRIDE_POINTER_IMPLEMENTION($device, $compare_result)                                                                                                                \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::stride_pointer ( pointer init_ptr, difference_type init_step )                                                                         \
        extends ptr ( init_ptr ), strd ( init_step )                                                                                                                                \
    {                                                                                                                                                                               \
                                                                                                                                                                                    \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::stride_pointer ( const_stride_pointer<type> cvt )                                                                                      \
        extends ptr ( cvt.get_pointer() ), strd ( cvt.get_stride() )                                                                                                                \
    {                                                                                                                                                                               \
                                                                                                                                                                                    \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::reference $device::stride_pointer<type>::operator * ( ) const                                                                          \
    {                                                                                                                                                                               \
        return *ptr;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::pointer $device::stride_pointer<type>::operator -> ( ) const                                                                           \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::reference $device::stride_pointer<type>::operator [] ( difference_type offset ) const                                                  \
    {                                                                                                                                                                               \
        return ptr[offset * strd];                                                                                                                                                  \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::pointer& $device::stride_pointer<type>::get_pointer ( )                                                                                \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr const $device::stride_pointer<type>::pointer& $device::stride_pointer<type>::get_pointer ( ) const                                                                    \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::stride_pointer<type>::difference_type& $device::stride_pointer<type>::get_stride ( )                                                                         \
    {                                                                                                                                                                               \
        return strd;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr const $device::stride_pointer<type>::difference_type& $device::stride_pointer<type>::get_stride ( ) const                                                             \
    {                                                                                                                                                                               \
        return strd;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::const_stride_pointer ( pointer init_ptr, difference_type init_step )                                                             \
        extends ptr ( init_ptr ), strd ( init_step )                                                                                                                                \
    {                                                                                                                                                                               \
                                                                                                                                                                                    \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::const_stride_pointer ( stride_pointer<type> cvt )                                                                                \
        extends ptr ( cvt.get_pointer() ), strd ( cvt.get_stride() )                                                                                                                \
    {                                                                                                                                                                               \
                                                                                                                                                                                    \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::reference $device::const_stride_pointer<type>::operator * ( ) const                                                              \
    {                                                                                                                                                                               \
        return *ptr;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::pointer $device::const_stride_pointer<type>::operator -> ( ) const                                                               \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::reference $device::const_stride_pointer<type>::operator [] ( difference_type offset ) const                                      \
    {                                                                                                                                                                               \
        return ptr[offset * strd];                                                                                                                                                  \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::pointer& $device::const_stride_pointer<type>::get_pointer ( )                                                                    \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr const $device::const_stride_pointer<type>::pointer& $device::const_stride_pointer<type>::get_pointer ( ) const                                                        \
    {                                                                                                                                                                               \
        return ptr;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::const_stride_pointer<type>::difference_type& $device::const_stride_pointer<type>::get_stride ( )                                                             \
    {                                                                                                                                                                               \
        return strd;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr const $device::const_stride_pointer<type>::difference_type& $device::const_stride_pointer<type>::get_stride ( ) const                                                 \
    {                                                                                                                                                                               \
        return strd;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr bool operator == ( $device::template stride_pointer<type> left, $device::template stride_pointer<type> right )                                                        \
    {                                                                                                                                                                               \
        return left.get_pointer() == right.get_pointer();                                                                                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr bool operator == ( $device::template stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                                  \
    {                                                                                                                                                                               \
        return left.get_pointer() == right.get_pointer();                                                                                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr bool operator == ( $device::template const_stride_pointer<type> left, $device::template stride_pointer<type> right )                                                  \
    {                                                                                                                                                                               \
        return left.get_pointer() == right.get_pointer();                                                                                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr bool operator == ( $device::template const_stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                            \
    {                                                                                                                                                                               \
        return left.get_pointer() == right.get_pointer();                                                                                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $compare_result operator <=> ( $device::template stride_pointer<type> left, $device::template stride_pointer<type> right )                                            \
    {                                                                                                                                                                               \
        return left.get_pointer() <=> right.get_pointer();                                                                                                                          \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $compare_result operator <=> ( $device::template stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                      \
    {                                                                                                                                                                               \
        return left.get_pointer() <=> right.get_pointer();                                                                                                                          \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $compare_result operator <=> ( $device::template const_stride_pointer<type> left, $device::template stride_pointer<type> right )                                      \
    {                                                                                                                                                                               \
        return left.get_pointer() <=> right.get_pointer();                                                                                                                          \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $compare_result operator <=> ( $device::template const_stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                \
    {                                                                                                                                                                               \
        return left.get_pointer() <=> right.get_pointer();                                                                                                                          \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type> operator + ( $device::template stride_pointer<type> left, std::ptrdiff_t right )                                               \
    {                                                                                                                                                                               \
        return $device::template stride_pointer<type>(left.get_pointer() + left.get_stride() * right, left.get_stride());                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type> operator + ( $device::template const_stride_pointer<type> left, std::ptrdiff_t right )                                   \
    {                                                                                                                                                                               \
        return $device::template const_stride_pointer<type>(left.get_pointer() + left.get_stride() * right, left.get_stride());                                                     \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type> operator + ( std::ptrdiff_t left, $device::template stride_pointer<type> right )                                               \
    {                                                                                                                                                                               \
        return $device::template stride_pointer<type>(left * right.get_stride() + right.get_pointer(), right.get_stride());                                                         \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type> operator + ( std::ptrdiff_t left, $device::template const_stride_pointer<type> right )                                   \
    {                                                                                                                                                                               \
        return $device::template const_stride_pointer<type>(left * right.get_stride() + right.get_pointer(), right.get_stride());                                                   \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type> operator - ( $device::template stride_pointer<type> left, std::ptrdiff_t right )                                               \
    {                                                                                                                                                                               \
        return $device::template stride_pointer<type>(left.get_pointer() - left.get_stride() * right, left.get_stride());                                                           \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type> operator - ( $device::template const_stride_pointer<type> left, std::ptrdiff_t right )                                   \
    {                                                                                                                                                                               \
        return $device::template const_stride_pointer<type>(left.get_pointer() - left.get_stride() * right, left.get_stride());                                                     \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr std::ptrdiff_t operator - ( $device::template stride_pointer<type> left, $device::template stride_pointer<type> right )                                               \
    {                                                                                                                                                                               \
        if constexpr ( debug )                                                                                                                                                      \
            if constexpr ( left.get_stride() != right.get_stride() )                                                                                                                \
                throw logic_error("cannot minus stride_pointer (with left.get_stride() = {}, right.get_stride() = {}): stride mismatches", left.get_stride(), right.get_stride());  \
        return (left.get_pointer() - right.get_pointer()) / left.get_stride();                                                                                                      \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr std::ptrdiff_t operator - ( $device::template stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                         \
    {                                                                                                                                                                               \
        if constexpr ( debug )                                                                                                                                                      \
            if constexpr ( left.get_stride() != right.get_stride() )                                                                                                                \
                throw logic_error("cannot minus stride_pointer (with left.get_stride() = {}, right.get_stride() = {}): stride mismatches", left.get_stride(), right.get_stride());  \
        return (left.get_pointer() - right.get_pointer()) / left.get_stride();                                                                                                      \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr std::ptrdiff_t operator - ( $device::template const_stride_pointer<type> left, $device::template stride_pointer<type> right )                                         \
    {                                                                                                                                                                               \
        if constexpr ( debug )                                                                                                                                                      \
            if constexpr ( left.get_stride() != right.get_stride() )                                                                                                                \
                throw logic_error("cannot minus stride_pointer (with left.get_stride() = {}, right.get_stride() = {}): stride mismatches", left.get_stride(), right.get_stride());  \
        return (left.get_pointer() - right.get_pointer()) / left.get_stride();                                                                                                      \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr std::ptrdiff_t operator - ( $device::template const_stride_pointer<type> left, $device::template const_stride_pointer<type> right )                                   \
    {                                                                                                                                                                               \
        if constexpr ( debug )                                                                                                                                                      \
            if constexpr ( left.get_stride() != right.get_stride() )                                                                                                                \
                throw logic_error("cannot minus stride_pointer (with left.get_stride() = {}, right.get_stride() = {}): stride mismatches", left.get_stride(), right.get_stride());  \
        return (left.get_pointer() - right.get_pointer()) / left.get_stride();                                                                                                      \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type>& operator += ( $device::template stride_pointer<type>& left, std::ptrdiff_t right )                                            \
    {                                                                                                                                                                               \
        left.get_pointer() += left.get_stride() * right;                                                                                                                            \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type>& operator += ( $device::template const_stride_pointer<type>& left, std::ptrdiff_t right )                                \
    {                                                                                                                                                                               \
        left.get_pointer() += left.get_stride() * right;                                                                                                                            \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type>& operator -= ( $device::template stride_pointer<type>& left, std::ptrdiff_t right )                                            \
    {                                                                                                                                                                               \
        left.get_pointer() -= left.get_stride() * right;                                                                                                                            \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type>& operator -= ( $device::template const_stride_pointer<type>& left, std::ptrdiff_t right )                                \
    {                                                                                                                                                                               \
        left.get_pointer() -= left.get_stride() * right;                                                                                                                            \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type>& operator ++ ( $device::template stride_pointer<type>& left )                                                                  \
    {                                                                                                                                                                               \
        left.get_pointer() += left.get_stride();                                                                                                                                    \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type>& operator ++ ( $device::template const_stride_pointer<type>& left )                                                      \
    {                                                                                                                                                                               \
        left.get_pointer() += left.get_stride();                                                                                                                                    \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type> operator ++ ( $device::template stride_pointer<type>& left, int )                                                              \
    {                                                                                                                                                                               \
        auto tmp = left;                                                                                                                                                            \
        ++left;                                                                                                                                                                     \
        return tmp;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type> operator ++ ( $device::template const_stride_pointer<type>& left, int )                                                  \
    {                                                                                                                                                                               \
        auto tmp = left;                                                                                                                                                            \
        ++left;                                                                                                                                                                     \
        return tmp;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type>& operator -- ( $device::template stride_pointer<type>& left )                                                                  \
    {                                                                                                                                                                               \
        left.get_pointer() -= left.get_stride();                                                                                                                                    \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type>& operator -- ( $device::template const_stride_pointer<type>& left )                                                      \
    {                                                                                                                                                                               \
        left.get_pointer() -= left.get_stride();                                                                                                                                    \
        return left;                                                                                                                                                                \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template stride_pointer<type> operator -- ( $device::template stride_pointer<type>& left, int )                                                              \
    {                                                                                                                                                                               \
        auto tmp = left;                                                                                                                                                            \
        --left;                                                                                                                                                                     \
        return tmp;                                                                                                                                                                 \
    }                                                                                                                                                                               \
                                                                                                                                                                                    \
    template < class type >                                                                                                                                                         \
    constexpr $device::template const_stride_pointer<type> operator -- ( $device::template const_stride_pointer<type>& left, int )                                                  \
    {                                                                                                                                                                               \
        auto tmp = left;                                                                                                                                                            \
        --left;                                                                                                                                                                     \
        return tmp;                                                                                                                                                                 \
    }

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