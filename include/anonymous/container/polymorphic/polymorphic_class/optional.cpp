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
constexpr optional<types>::reference optional<types>::value ( )
{
    if ( not empty() ) [[likely]]
        return base::value();
    else
        throw type_error("bad optional access (with empty() = true)");
}

template < class types >
constexpr optional<types>::const_reference optional<types>::value ( ) const
{
    if ( not empty() ) [[likely]]
        return base::value();
    else
        throw type_error("bad optional access (with empty() = true)");
}

template < class types >
constexpr bool optional<types>::empty ( ) const
{
    return not base::has_value();
}

template < class types >
constexpr const std::type_info& optional<types>::type ( ) const
{
    return not empty() ? typeid(types) : typeid(void);
}

