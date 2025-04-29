namespace detail
{
    // find_same_type
    template < class input_type, class... types >
    constexpr int find_same_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int find_same_type<input_type,type> = same_as<input_type,type> ? 1 : 0;

    template < class input_type, class type, class... types >
    constexpr int find_same_type<input_type,type,types...> = same_as<input_type,type>                 ? 1 :
                                                             find_same_type<input_type,types...> == 0 ? 0 :
                                                                                                        1 + find_same_type<input_type,types...>;
    // find_convertible_type
    template < class input_type, class... types >
    constexpr int find_convertible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int find_convertible_type<input_type,type> = convertible_to<input_type,type> ? 1 : 0;

    template < class input_type, class type, class... types >
    constexpr int find_convertible_type<input_type,type,types...> = convertible_to<input_type,type>                 ? 1 :
                                                                    find_convertible_type<input_type,types...> == 0 ? 0 :
                                                                                                                      1 + find_convertible_type<input_type,types...>;
    // find_constructible_type
    template < class input_type, class... types >
    constexpr int find_constructible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    
    template < class input_type, class type >
    constexpr int find_constructible_type<input_type,type> = constructible_from<type,input_type> ? 1 : 0;

    template < class input_type, class type, class... types >
    constexpr int find_constructible_type<input_type,type,types...> = constructible_from<type,input_type>               ? 1 :
                                                                      find_constructible_type<input_type,types...> == 0 ? 0 :
                                                                                                                          1 + find_constructible_type<input_type,types...>;
} // namespace detail





template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( convertible_to<decltype(v),types> or ... )
    extends std::variant<types...> ( std::in_place_index<(same_as<decltype(v),types> or ...) ? detail::find_same_type       <decltype(v),types...>-1 : 
                                                                                               detail::find_convertible_type<decltype(v),types...>-1>, 
                                     std::move(v) )
{

}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( constructible_to<decltype(v),types> or ... )
    extends std::variant<types...> ( std::in_place_index<detail::find_constructible_type<decltype(v),types...>-1>, 
                                     std::move(v) )
{

}

template < class... types >
template < class type >
constexpr type& variant<types...>::value ( )
    requires ( same_as<types,type> or ... )
{
    if ( self.index() == detail::find_same_type<type,types...> ) [[likely]]
        return std::get<type>(static_cast<std::variant<types...>&>(self));
    else
        throw type_error("bad variant access (with type() = {}, access = {})", self.type(), typeid(type));
}

template < class... types >
template < class type >
constexpr const type& variant<types...>::value ( ) const
    requires ( same_as<types,type> or ... )
{
    if ( self.index() == detail::find_same_type<type,types...> ) [[likely]]
        return std::get<type>(static_cast<const std::variant<types...>&>(self));
    else
        throw type_error("bad variant access (with type() = {}, access = {})", self.type(), typeid(type));
}

template < class... types >
template < int index >
constexpr variant<types...>::template reference<index> variant<types...>::value ( )
    requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) )
{
    if ( self.index() == index ) [[likely]]
        return std::get<index-1>(static_cast<std::variant<types...>&>(self));
    else
        throw type_error("bad variant access (with index() = {}, access = {})", self.index(), index);
}

template < class... types >
template < int index >
constexpr variant<types...>::template const_reference<index> variant<types...>::value ( ) const
    requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) )
{
    if ( self.index() == index ) [[likely]]
        return std::get<index-1>(static_cast<const std::variant<types...>&>(self));
    else
        throw type_error("bad variant access (with index() = {}, access = {})", self.index(), index);
}

template < class... types >
constexpr int variant<types...>::index ( ) const
{
    if ( not std::variant<types...>::valueless_by_exception() ) [[likely]]
        return std::variant<types...>::index() + 1;
    else
        return 0;
}

template < class... types >
constexpr const std::type_info& variant<types...>::type ( ) const
{
    if ( not std::variant<types...>::valueless_by_exception() ) [[likely]]
        return *(std::array<const std::type_info*,sizeof...(types)>{&typeid(types)...}[index()-1]);
    else
        return typeid(void);
}


template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& visitor )
{
    return std::variant<types...>::visit(std::forward<decltype(visitor)>(visitor));
}

template < class... types >
constexpr decltype(auto) variant<types...>::visit ( auto&& visitor ) const
{
    return std::variant<types...>::visit(std::forward<decltype(visitor)>(visitor));
}