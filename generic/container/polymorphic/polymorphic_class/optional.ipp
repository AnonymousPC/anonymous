#pragma once

template < class types >
constexpr optional<types>::optional ( types init )
    extends base ( std::move(init) )
{
    
}

template < class types >
constexpr optional<types>::optional ( nullopt_t )
    extends base ( nullopt )
{
    
}

template < class types > 
constexpr bool optional<types>::empty ( ) const
{
    return not base::has_value();
}

template < class types >
constexpr const std::type_info& optional<types>::type ( ) const
{
    return not empty() ? typeid(types) otherwise typeid(void);
}

template < class types >
constexpr types& optional<types>::value ( )
{
    if ( not empty() )
        return base::value();
    else
        throw type_error("bad optional access: cannot access {} in {} (whose type = {}, empty = {})", typeid(types), typeid(self), typeid(void), true);
}

template < class types >
constexpr const types& optional<types>::value ( ) const
{
    if ( not empty() )
        return base::value();
    else
        throw type_error("bad optional access: cannot access {} in {} (whose type = {}, empty = {})", typeid(types), typeid(self), typeid(void), true);
}