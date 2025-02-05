#pragma once

template < class ret_type, class... arg_types >
constexpr function<ret_type(arg_types...)>::function ( function_type<ret_type(arg_types...)> auto f )
    extends base ( std::move(f) )
{
    
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

template < class ret_type, class... arg_types >
constexpr ret_type function<ret_type(arg_types...)>::operator() ( arg_types&&... args ) const
{
    if ( not empty() ) [[likely]]
        return base::operator()(std::forward<decltype(args)>(args)...);
    else
        throw type_error("bad function call: cannot call {} (whose type = {}, empty = {})", typeid(self), type(), empty());       
}
