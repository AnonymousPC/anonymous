#pragma once

namespace detail
{
    template < class type >
    constexpr bool is_dll_function = false;
    
    template < class ret_type, class... arg_types >
    constexpr bool is_dll_function<ret_type(arg_types...)> = true; // Strict function, does not accept lambda, struct with operator(), std::function...

    template < class type >
    constexpr bool is_dll_member_function = false;

    template < class ret_type, class class_type, class... arg_types >
    constexpr bool is_dll_member_function<ret_type(class_type::*)(arg_types...)> = true;
    
    template < class type >
    constexpr bool is_dll_variable = not is_dll_function<type> and 
                                     not is_dll_member_function<type>;

    template < class type >
    struct get_member_function_info;

    template < class ret_type, class class_type, class... arg_types >
    struct get_member_function_info<ret_type(class_type::*)(arg_types...)>
    {
        using classname = class_type;
        using funcname  = ret_type(arg_types...);
    };

    template < class type >
    using get_member_function_classname = get_member_function_info<type>::classname;

    template < class type >
    using get_member_function_funcname  = get_member_function_info<type>::funcname;
    
} // namespace detail

constexpr file_dll_any::file_dll_any ( boost::dll::shared_library& init_library, const std::string& init_symbol )
    extends library ( init_library ),
            symbol  ( init_symbol )
{
    
}

constexpr bool file_dll_any::empty ( ) const
{
    return false;
}

template < class value_type >
constexpr value_type& file_dll_any::value ( )
{
    try
    {
        if constexpr ( detail::is_dll_variable<value_type> )
            return library.get<value_type>(mangle<value_type>(symbol)); // No overload.

        else if constexpr ( detail::is_dll_function<value_type> )
            try
            {
                return library.get<value_type>()
            }


        else if constexpr ( detail::is_dll_member_function<value_type> )
            return lib_ptr->get_mem_fn<detail::get_member_function_classname<value_type>,detail::get_member_function_funcname<value_type>>(symbol);
        else
            static_assert(false, "not supported yet");
    }
    catch ( const boost::system::system_error& e )
    {
        throw file_error("failed to load dll symbol (with mangled = {}, demangled = {})", symbol, boost::core::demangle(symbol.c_str())).from(e);
    }
}