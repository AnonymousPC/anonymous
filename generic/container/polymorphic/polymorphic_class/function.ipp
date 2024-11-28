#pragma once

/// Class function

// Core

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>::function ( const function& init )
    extends ptr ( init.ptr != nullptr ? &init.ptr->copy() otherwise nullptr )
{

}

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>::function ( function&& init )
    extends ptr ( std::exchange ( init.ptr, nullptr ) )
{

}

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>::function ( ap::function_type<res_type(arg_types...)> auto init )
    extends ptr ( new dynamic_obj ( std::move ( init ) ) )
{

}

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>::~function ( )
{
    delete ptr;
}

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>& function<res_type(arg_types...)>::operator = ( const function& right )
{
    delete ptr;
    ptr = right.ptr != nullptr ? &right.ptr->copy() otherwise nullptr;
    return self;
}

template < class res_type, class... arg_types >
constexpr function<res_type(arg_types...)>& function<res_type(arg_types...)>::operator = ( function&& right )
{
    std::swap ( ptr, right.ptr );
    return self;
}

// Call

template < class res_type, class... arg_types >
constexpr res_type function<res_type(arg_types...)>::operator() ( arg_types... args ) const
{
    if ( empty() )
        throw type_error("cannot call empty function with args: {}", tuple(string(typeid(args))...));

    return ptr->operator() ( std::forward<decltype(args)>(args)... );
}

// Member

template < class res_type, class... arg_types >
constexpr bool function<res_type(arg_types...)>::empty ( ) const
{
    return ptr == nullptr;
}





/// Class function::dynamic_obj

// Declaration

template < class res_type, class... arg_types >
class function<res_type(arg_types...)>::static_obj
{
    public: // Core
        virtual constexpr ~static_obj             ( )                      = default;
        virtual constexpr  static_obj& copy       ( )                const = abstract;
        virtual constexpr  res_type    operator() ( arg_types&&... ) const = abstract;
};

template < class res_type, class... arg_types >
template < class type >
class function<res_type(arg_types...)>::dynamic_obj
    extends public static_obj
{
    public: // Data
        type data;

    public: // Core
        constexpr  dynamic_obj            ( type );
        constexpr ~dynamic_obj            ( )                      override = default;
        constexpr  static_obj& copy       ( )                const override;
        constexpr  res_type    operator() ( arg_types&&... ) const override;
};




// Implemention

template < class res_type, class... arg_types >
template < class type >
constexpr function<res_type(arg_types...)>::dynamic_obj<type>::dynamic_obj ( type init )
    extends data ( std::move ( init ) )
{

}

template < class res_type, class... arg_types >
template < class type >
constexpr function<res_type(arg_types...)>::static_obj& function<res_type(arg_types...)>::dynamic_obj<type>::copy ( ) const
{
    return *new dynamic_obj ( self );
}

template < class res_type, class... arg_types >
template < class type >
constexpr res_type function<res_type(arg_types...)>::dynamic_obj<type>::operator() ( arg_types&&... args ) const
{
    return data ( std::forward<decltype(args)>(args)... );
}