template < class types, class device >
constexpr optional<types,device>::optional ( types init )
    extends device::template optional<types> ( std::move(init) )
{
    
}

template < class types, class device >
constexpr optional<types,device>::optional ( nullopt_t )
    extends device::template optional<types> ( nullopt )
{
    
}

template < class types, class device >
constexpr optional<types,device>::reference optional<types,device>::value ( )
{
    if ( not empty() ) [[likely]]
        return device::template optional<types>::value();
    else
        throw type_error("bad optional access (with empty() = true)");
}

template < class types, class device >
constexpr optional<types,device>::const_reference optional<types,device>::value ( ) const
{
    if ( not empty() ) [[likely]]
        return device::template optional<types>::value();
    else
        throw type_error("bad optional access (with empty() = true)");
}

template < class types, class device >
constexpr bool optional<types,device>::empty ( ) const
{
    return not device::template optional<types>::has_value();
}

template < class types, class device >
constexpr const std::type_info& optional<types,device>::type ( ) const
{
    return not empty() ? typeid(types) : typeid(void);
}

