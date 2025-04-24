constexpr any::any ( auto init )
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
    auto ptr = std::any_cast<value_type>(static_cast<base*>(&self));
    if ( ptr != nullptr )
        return *ptr;
    else
        throw type_error("bad any cast (with type() = {}, cast = {})", type(), typeid(value_type));
}

template < class value_type >
constexpr const value_type& any::value ( ) const
{
    auto ptr = std::any_cast<value_type>(static_cast<const base*>(&self));
    if ( ptr != nullptr ) [[likely]]
        return *ptr;
    else
        throw type_error("bad any cast (with type() = {}, cast = {})", type(), typeid(value_type));
}