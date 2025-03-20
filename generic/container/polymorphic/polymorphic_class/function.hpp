#pragma once

/// Declaration

template < class type >
class function; // No implemention.

template < class ret_type, class... arg_types >
class function<ret_type(arg_types...)>
    extends public std::function<ret_type(arg_types...)>
{
    private: // Typedef
        using base = std::function<ret_type(arg_types...)>;

    public: // Core
        constexpr function ( )                              = default;
        constexpr function ( const function&  )             = default;
        constexpr function (       function&& )             = default;
        constexpr function& operator = ( const function&  ) = default;
        constexpr function& operator = (       function&& ) = default;

    public: // Constructor
        constexpr function ( function_type<ret_type(arg_types...)> auto );

    public: // Member
        constexpr       bool            empty      ( )              const;
        constexpr const std::type_info& type       ( )              const;
        constexpr       ret_type        operator() ( arg_types... ) const;
};




/// Template deduction

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


#include "function.ipp"