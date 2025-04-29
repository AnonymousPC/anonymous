template < class ret_type, class... arg_types, class device >
constexpr function<ret_type(arg_types...),device>::function ( invocable_r<ret_type,arg_types...> auto f )
    extends device::template function<ret_type(arg_types...)> ( std::move(f) )
{
    
}

template < class ret_type, class... arg_types, class device >
constexpr ret_type function<ret_type(arg_types...),device>::operator() ( arg_types... args ) const
{
    if ( not empty() ) [[likely]]
        return device::template function<ret_type(arg_types...)>::operator()(std::forward<decltype(args)>(args)...);
    else
        throw type_error("bad function call (with empty() = true)");       
}

template < class ret_type, class... arg_types, class device >
constexpr bool function<ret_type(arg_types...),device>::empty ( ) const
{
    return not device::template function<ret_type(arg_types...)>::operator bool();    
}

template < class ret_type, class... arg_types, class device >
constexpr const std::type_info& function<ret_type(arg_types...),device>::type ( ) const
{
    return device::template function<ret_type(arg_types...)>::target_type();  
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



