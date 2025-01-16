#pragma once

constexpr any::any ( movable auto init )
    extends base ( std::move(init) )
{

}

constexpr bool any::empty ( ) const 
{
    return not base::has_value();
}

constexpr const std::type_info& any::type ( ) const
{
    return base::type();
} 

template < class value_type >
constexpr value_type& any::value ( )
{
    try
    {
        return std::any_cast<value_type&>(static_cast<base&>(self));   
    }
    catch ( const std::bad_any_cast& e )
    {
        throw type_error("bad any cast: cannot get {} from {} (whose type = {}, empty = {})", typeid(value_type), typeid(self), type(), empty()).from(e);
    }
}

template < class value_type >
constexpr const value_type& any::value ( ) const
{
    try
    {
        return std::any_cast<const value_type&>(static_cast<const base&>(self));   
    }
    catch ( const std::bad_any_cast& e )
    {
        throw type_error("bad any cast: cannot get {} from {} (whose type = {}, empty = {})", typeid(value_type), typeid(self), type(), empty()).from(e);
    }
}