#pragma once

/// Declaration

template < class type >
class function; // No implemention.



/// Class function

/** As the sso-optimization here is quite ugly,
  * and spoils the attractive feature of it,
  * we ignore sso optimization temporarily.
  */

template < class res_type, class... arg_types >
class function<res_type(arg_types...)>
{
    private: // Base
                                class static_obj;
        template < class type > class dynamic_obj;

    private: // Data
        static_obj* ptr = nullptr;

    public: // Typedef
        using function_type = res_type(arg_types...);
        using result_type   = res_type;
        template < int index > requires ( ( index >= -sizeof...(arg_types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(arg_types) ) )
        using argument_type = index_type_of<index,arg_types...>;

    public: // Core
        constexpr  function ( ) = default;
        constexpr  function ( const function&  );
        constexpr  function (       function&& );
        constexpr  function ( ap::function_type<res_type(arg_types...)> auto );
        constexpr ~function ( );
        constexpr  function& operator = ( const function&  );
        constexpr  function& operator = (       function&& );

    public: // Call
        constexpr res_type operator() ( arg_types... ) const;

    public: // Member
        constexpr bool empty ( ) const;
};




/// Template deduction

// Global function

template < class res_type, class... arg_types >
function ( res_type (*) ( arg_types... ), auto... ) -> function<res_type(arg_types...)>;

// Member function

template < class function_type >
struct member_function_deduction
{

};

template < class res_type, class functor_type, bool exception, class... arg_types >
    requires ( not requires { std::declval<functor_type>().operator(); } ) // non-static
struct member_function_deduction<res_type(functor_type::*)(arg_types...) noexcept(exception)>
{
    using type = res_type(arg_types...);
};

template < class res_type,  class functor_type, bool exception, class... arg_types >
    requires ( not requires { std::declval<functor_type>().operator(); } ) // non-static
struct member_function_deduction<res_type(functor_type::*)(arg_types...)& noexcept(exception)>
{
    using type = res_type(arg_types...);
};

template < class res_type, class functor_type, bool exception, class... arg_types >
    requires ( not requires { std::declval<functor_type>().operator(); } ) // non-static
struct member_function_deduction<res_type(functor_type::*)(arg_types...)const noexcept(exception)>
{
    using type = res_type(arg_types...);
};

template < class res_type, class functor_type, bool exception, class... arg_types >
    requires ( not requires { std::declval<functor_type>().operator(); } ) // non-static
struct member_function_deduction<res_type(functor_type::*)(arg_types...)const& noexcept(exception)>
{
    using type = res_type(arg_types...);
};

template < class res_type, bool exception, class... arg_types >
struct member_function_deduction<res_type(*)(arg_types...) noexcept(exception)> // static or not-member
{
    using type = res_type(arg_types...);
};

template < class functor_type >
function ( functor_type, auto... ) -> function<typename member_function_deduction<decltype(&functor_type::operator())>::type>;


#include "function.ipp"