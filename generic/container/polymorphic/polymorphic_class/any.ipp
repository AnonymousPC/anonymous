#pragma once

/** As class any is not template, it requires a correct
  * declaration and depend sequence, which desires
  * class any::static_obj and class any::dynamic_obj to
  * be defined before class any is implemented.
  */

/// Class any::dynamic_obj

// Declaration

class any::static_obj
{
    public: // Core
        virtual constexpr ~static_obj       ( )       = default;
        virtual constexpr  static_obj& copy ( ) const = abstract;
};

template < class types >
class any::dynamic_obj
    extends public static_obj
{
    public: // Data
        types data;

    public: // Core
        constexpr  dynamic_obj      ( types );
        constexpr ~dynamic_obj      ( )       override = default;
        constexpr  static_obj& copy ( ) const override;
};


// Implemention

template < class types >
constexpr any::dynamic_obj<types>::dynamic_obj ( types init )
    extends data ( std::move ( init ) )
{

}

template < class types >
constexpr any::static_obj& any::dynamic_obj<types>::copy ( ) const
{
    if constexpr ( std::copyable<types> )
        return *new dynamic_obj ( self );
    else
        throw type_error("bad any access: cannot copy {} (whost type = {}, copyable = false)", 
                         typeid(any), typeid(types));
}






/// Class any

// Core

constexpr any::any ( const any& init )
    extends ptr  ( init.ptr != nullptr ? &init.ptr->copy() otherwise nullptr ),
            rtti ( init.rtti )
{

}

constexpr any::any ( any&& init )
    extends ptr  ( std::exchange ( init.ptr,  nullptr ) ),
            rtti ( std::exchange ( init.rtti, nullptr ) )
{

}

constexpr any::any ( std::movable auto init )
    extends ptr  ( new dynamic_obj ( std::move ( init ) ) ),
            rtti ( &typeid ( init ) )
{

}

constexpr any::~any ( )
{
    delete ptr;
}

constexpr any& any::operator = ( const any& right )
{
    delete ptr;

    ptr  = right.ptr != nullptr ? &right.ptr->copy() otherwise nullptr;
    rtti = right.rtti;

    return self;
}

constexpr any& any::operator = ( any&& right )
{
    std::swap ( ptr,  right.ptr  );
    std::swap ( rtti, right.rtti );

    return self;
}

// Member

constexpr bool any::empty ( ) const
{
    return ptr == nullptr;
}

constexpr const std::type_info& any::type ( ) const
{
    return rtti == nullptr ? typeid(void) otherwise *rtti;
}

template < class output_type >
constexpr output_type& any::value ( )
{
    let p = dynamic_cast<dynamic_obj<output_type>*> ( ptr );

    if ( p != nullptr )
        return p->data;
    else
        throw type_error("bad-any-access: cannot get {} from {} (whose type = {})",
                         typeid(output_type), typeid(any), self.type());
}

template < class output_type >
constexpr const output_type& any::value ( ) const
{
    let p = dynamic_cast<dynamic_obj<output_type>*> ( ptr );

    if ( p != nullptr )
        return p->data;
    else
        throw type_error("bad-any-access: cannot get {} from {} (whose type = {})",
                         typeid(output_type), typeid(any), self.type());
}