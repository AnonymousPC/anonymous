#pragma once

template < class type >
constexpr optional<type>::optional ( type init )
    extends base ( std::move(init) )
{
    
}

template < class type >
constexpr optional<type>::optional ( nullopt_t )
    extends base ( nullopt_t() )
{
    
}

template < class type > 
constexpr bool optional<type>::empty ( ) const
{
    return not base::has_value();
}

template < class type >
constexpr const std::type_info& optional<type>::type ( ) const
{
    return not empty() ? typeid(type) otherwise typeid(void);
}

template < class type >
constexpr type& optional<type>::value ( )
{
    if ( not empty() )
        return base::value();
    else
        throw type_error("bad optional access: cannot get {} from {} (whose type = {}, empty = {})", typeid(type), typeid(self), typeid(void), true);
}

template < class type >
constexpr const type& optional<type>::value ( ) const
{
    if ( not empty() )
        return base::value();
    else
        throw type_error("bad optional access: cannot get {} from {} (whose type = {}, empty = {})", typeid(type), typeid(self), typeid(void), true);
}