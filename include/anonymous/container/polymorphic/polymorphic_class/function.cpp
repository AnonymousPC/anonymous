template < class ret_type, class... arg_types >
constexpr function<ret_type(arg_types...)>::function ( invocable_r<ret_type,arg_types...> auto f )
    extends base ( std::move(f) )
{
    
}

template < class ret_type, class... arg_types >
constexpr ret_type function<ret_type(arg_types...)>::operator() ( arg_types... args ) const
{
    if ( not empty() ) [[likely]]
        return base::operator()(std::forward<decltype(args)>(args)...);
    else
        throw type_error("bad function call (with empty() = true)");       
}

template < class ret_type, class... arg_types >
constexpr bool function<ret_type(arg_types...)>::empty ( ) const
{
    return not base::operator bool();    
}

template < class ret_type, class... arg_types >
constexpr const std::type_info& function<ret_type(arg_types...)>::type ( ) const
{
    return base::target_type();  
}






namespace detail
{
    template < class type >
    struct member_function_deduction_helper;

    template < class ret_type, bool exception, class... arg_types >
    struct member_function_deduction_helper<ret_type(*)(arg_types...) noexcept(exception)>
    {
        using type = ret_type(arg_types...);
    };

    template < class ret_type, class functor, bool exception, class... arg_types >
        requires ( not requires { std::declval<functor>().operator(); } )
    struct member_function_deduction_helper<ret_type(functor::*)(arg_types...) noexcept(exception)>
    {
        using type = ret_type(arg_types...);
    };

    template < class ret_type,  class functor, bool exception, class... arg_types >
        requires ( not requires { std::declval<functor>().operator(); } )
    struct member_function_deduction_helper<ret_type(functor::*)(arg_types...)& noexcept(exception)>
    {
        using type = ret_type(arg_types...);
    };

    template < class ret_type, class functor, bool exception, class... arg_types >
        requires ( not requires { std::declval<functor>().operator(); } )
    struct member_function_deduction_helper<ret_type(functor::*)(arg_types...)const noexcept(exception)>
    {
        using type = ret_type(arg_types...);
    };

    template < class ret_type, class functor, bool exception, class... arg_types >
        requires ( not requires { std::declval<functor>().operator(); } )
    struct member_function_deduction_helper<ret_type(functor::*)(arg_types...)const& noexcept(exception)>
    {
        using type = ret_type(arg_types...);
    };

    template < class type >
    using member_function_deduction = member_function_deduction_helper<type>::type;
    
} // namespace detail

template < class ret_type, bool exception, class... arg_types >
function ( ret_type(arg_types...) noexcept(exception) ) -> function<ret_type(arg_types...)>;

template < class functor >
function ( functor ) -> function<detail::member_function_deduction<decltype(&functor::operator())>>;



