#pragma once

namespace detail
{
    template < class type >
    concept opencl_kernel_inputable = 
        is_class<type> and requires ( boost::compute::detail::meta_kernel& k, type t ) { k << t; };
    
} // namespace detail


template < class type >
class opencl::plus
    extends public boost::compute::plus<type>,
            public std::plus<type>
{
    public:
        using boost::compute::plus<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::plus<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::plus<type>::operator()(a, b);
        }
};

template < >
class opencl::plus<void>
    extends public std::plus<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a + b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::plus<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()+
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("+", a, b);
        }
};

template < class type >
class opencl::minus
    extends public boost::compute::minus<type>,
            public std::minus<type>
{
    public:
        using boost::compute::minus<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::minus<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::minus<type>::operator()(a, b);
        }
};

template < >
class opencl::minus<void>
    extends public std::minus<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a - b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::minus<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()-
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("-", a, b);
        }
};

template < class type >
class opencl::multiplies
    extends public boost::compute::multiplies<type>,
            public std::multiplies<type>
{
    public:
        using boost::compute::multiplies<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::multiplies<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::multiplies<type>::operator()(a, b);
        }
};

template < >
class opencl::multiplies<void>
    extends public std::multiplies<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a * b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::multiplies<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()*
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("*", a, b);
        }
};

template < class type >
class opencl::divides
    extends public boost::compute::divides<type>,
            public std::divides<type>
{
    public:
        using boost::compute::divides<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::divides<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::divides<type>::operator()(a, b);
        }
};

template < >
class opencl::divides<void>
    extends public std::divides<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a / b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::divides<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()/
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("/", a, b);
        }
};

template < class type >
class opencl::negate
    extends public std::negate<type> // boost::compute does not implements negate.
{
    public:
        using result_type = type;

        constexpr decltype(auto) operator() ( const type& a ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::negate<type>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::detail::invoked_function<
                       type,
                       boost::tuple<decay<decltype(a)>>
                   >("-", std::string(), boost::make_tuple(a));
        }
};

template < >
class opencl::negate<void>
    extends public std::negate<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a ) const
            requires requires { -a; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::negate<void>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::detail::invoked_function<
                       decltype(-std::declval<typename decay<decltype(a)>::result_type>()),
                       boost::tuple<decay<decltype(a)>>
                   >("-", std::string(), boost::make_tuple(a));
        }
};

template < class type >
class opencl::equal_to
    extends public boost::compute::equal_to<type>,
            public std::equal_to<type>
{
    public:
        using boost::compute::equal_to<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::equal_to<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::equal_to<type>::operator()(a, b);
        }
};

template < >
class opencl::equal_to<void>
    extends public std::equal_to<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a == b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::equal_to<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()==
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("==", a, b);
        }
};

template < class type >
class opencl::not_equal_to
    extends public boost::compute::not_equal_to<type>,
            public std::not_equal_to<type>
{
    public:
        using boost::compute::not_equal_to<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::not_equal_to<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::not_equal_to<type>::operator()(a, b);
        }
};

template < >
class opencl::not_equal_to<void>
    extends public std::not_equal_to<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a != b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::not_equal_to<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()!=
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("!=", a, b);
        }
};

template < class type >
class opencl::less
    extends public boost::compute::less<type>,
            public std::less<type>
{
    public:
        using boost::compute::less<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::less<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::less<type>::operator()(a, b);
        }
};

template < >
class opencl::less<void>
    extends public std::less<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a < b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::less<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()<
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("<", a, b);
        }
};

template < class type >
class opencl::less_equal
    extends public boost::compute::less_equal<type>,
            public std::less_equal<type>
{
    public:
        using boost::compute::less_equal<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::less_equal<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::less_equal<type>::operator()(a, b);
        }
};

template < >
class opencl::less_equal<void>
    extends public std::less_equal<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a <= b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::less_equal<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()<=
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("<=", a, b);
        }
};

template < class type >
class opencl::greater
    extends public boost::compute::greater<type>,
            public std::greater<type>
{
    public:
        using boost::compute::greater<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::greater<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::greater<type>::operator()(a, b);
        }
};

template < >
class opencl::greater<void>
    extends public std::greater<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a > b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::greater<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()>
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >(">", a, b);
        }
};

template < class type >
class opencl::greater_equal
    extends public boost::compute::greater_equal<type>,
            public std::greater_equal<type>
{
    public:
        using boost::compute::greater_equal<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::greater_equal<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::greater_equal<type>::operator()(a, b);
        }
};

template < >
class opencl::greater_equal<void>
    extends public std::greater_equal<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a >= b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::greater_equal<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()>=
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >(">=", a, b);
        }
};

template < class type >
class opencl::logical_and
    extends public boost::compute::logical_and<type>,
            public std::logical_and<type>
{
    public:
        using boost::compute::logical_and<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::logical_and<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::logical_and<type>::operator()(a, b);
        }
};

template < >
class opencl::logical_and<void>
    extends public std::logical_and<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a && b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::logical_and<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()&&
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("&&", a, b);
        }
};

template < class type >
class opencl::logical_or
    extends public boost::compute::logical_or<type>,
            public std::logical_or<type>
{
    public:
        using boost::compute::logical_or<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::logical_or<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::logical_or<type>::operator()(a, b);
        }
};

template < >
class opencl::logical_or<void>
    extends public std::logical_or<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a || b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::logical_or<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()||
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("||", a, b);
        }
};

template < class type >
class opencl::logical_not
    extends public boost::compute::logical_not<type>,
            public std::logical_not<type>
{
    public:
        using boost::compute::logical_not<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::logical_not<type>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::logical_not<type>::operator()(a);
        }
};

template < >
class opencl::logical_not<void>
    extends public std::logical_not<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a ) const
            requires requires { !a; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::logical_not<void>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::detail::invoked_function<
                       decltype(!std::declval<typename decay<decltype(a)>::result_type>()),
                       boost::tuple<decay<decltype(a)>>
                   >("!", std::string(), boost::make_tuple(a));
        }
};

template < class type >
class opencl::bit_and
    extends public boost::compute::bit_and<type>,
            public std::bit_and<type>
{
    public:
        using boost::compute::bit_and<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_and<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::bit_and<type>::operator()(a, b);
        }
};

template < >
class opencl::bit_and<void>
    extends public std::bit_and<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a & b; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_and<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()&
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("&", a, b);
        }
};

template < class type >
class opencl::bit_or
    extends public boost::compute::bit_or<type>,
            public std::bit_or<type>
{
    public:
        using boost::compute::bit_or<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_or<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::bit_or<type>::operator()(a, b);
        }
};

template < >
class opencl::bit_or<void>
    extends public std::bit_or<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a | b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_or<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()|
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("|", a, b);
        }
};

template < class type >
class opencl::bit_xor
    extends public boost::compute::bit_xor<type>,
            public std::bit_xor<type>
{
    public:
        using boost::compute::bit_xor<type>::result_type;

        constexpr decltype(auto) operator() ( const type& a, const type& b ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_xor<type>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::bit_xor<type>::operator()(a, b);
        }
};

template < >
class opencl::bit_xor<void>
    extends public std::bit_xor<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a, const auto& b ) const
            requires requires { a ^ b; } and 
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> ) and
                     ( not detail::opencl_kernel_inputable<decay<decltype(b)>> )
        {
            return std::bit_xor<void>::operator()(a, b);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a, const detail::opencl_kernel_inputable auto& b ) const
        {
            return boost::compute::detail::invoked_binary_operator<
                       decay<decltype(a)>,
                       decay<decltype(b)>,
                       decltype(std::declval<typename decay<decltype(a)>::result_type>()^
                                std::declval<typename decay<decltype(b)>::result_type>())
                   >("^", a, b);
        }
};

template < class type >
class opencl::bit_not
    extends public std::bit_not<type> // boost::compute does not implements bit_not.
{
    public:
        using result_type = type;

        constexpr decltype(auto) operator() ( const type& a ) const
            requires ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::bit_not<type>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::detail::invoked_function<
                       type,
                       boost::tuple<decay<decltype(a)>>
                   >("~", std::string(), boost::make_tuple(a));
        }
};

template < >
class opencl::bit_not<void>
    extends public std::bit_not<void>
{
    public:
        constexpr decltype(auto) operator() ( const auto& a ) const
            requires requires { -a; } and
                     ( not detail::opencl_kernel_inputable<decay<decltype(a)>> )
        {
            return std::bit_not<void>::operator()(a);
        }

        constexpr decltype(auto) operator() ( const detail::opencl_kernel_inputable auto& a ) const
        {
            return boost::compute::detail::invoked_function<
                       decltype(~std::declval<typename decay<decltype(a)>::result_type>()),
                       boost::tuple<decay<decltype(a)>>
                   >("~", std::string(), boost::make_tuple(a));
        }
};
