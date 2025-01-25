#pragma once

namespace detail
{
    template < int from, int to, int add, int index >
    constexpr void for_constexpr_impl ( auto&& op )
    {
        if constexpr ( ( add > 0 and index <= to ) or
                       ( add < 0 and index >= to ) )
        {
            op.template operator()<index>();
            for_constexpr_impl<from,to,add,index+add>(std::forward<decltype(op)>(op));
        }
    }

    template < int from, int to, int add = 1 >
    constexpr void for_constexpr ( auto&& op )
    {
        static_assert(add != 0, "this for-clause is infinite");
        if constexpr ( ( add > 0 and from <= to ) or
                       ( add < 0 and from >= to ) )
            for_constexpr_impl<from,to,add,from>(op);
        else
            static_assert(false, "this for-clause does not do anything");
    }
} // namespace detail


template < class... types >
constexpr int tuple<types...>::size ( )
{
    return sizeof...(types);
}

template < class... types >
constexpr tuple<types...>::tuple ( types... inits )
    extends std::tuple<types...>(std::move(inits)...)
{

}

template < class... types >
template < class... types2 >
constexpr tuple<types...>::tuple ( const tuple<types2...>& cvt )
    requires ( convertible_to<types2,types> and ... ) but ( not ( same_as<types,types2> and ... ) )
{
    detail::for_constexpr<1,size()>([&] <int index> { self.template value<index>() = index_type_of<index,types...>(cvt.template value<index>()); });
}

template < class... types >
template < class... types2 >
constexpr tuple<types...>::tuple ( const tuple<types2...>& cvt )
    requires ( constructible_from<types,types2> and ... ) but ( not ( convertible_to<types2,types> and ... ) )
{
    detail::for_constexpr<1,size()>([&] <int index> { self.template value<index>() = index_type_of<index,types...>(cvt.template value<index>()); });
}

template < class... types >
template < int index >
constexpr index_type_of<index,types...>& tuple<types...>::value ( )
    requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<std::tuple<types...>&>(self));
    else
        return std::get<index+size()>(static_cast<std::tuple<types...>&>(self));
}

template < class... types >
template < int index >
constexpr const index_type_of<index,types...>& tuple<types...>::value ( ) const
    requires ( index >= -size() and index <= -1 ) or ( index >= 1 and index <= size() )
{
    if constexpr ( index > 0 )
        return std::get<index-1>(static_cast<const std::tuple<types...>&>(self));
    else
        return std::get<index+size()>(static_cast<const std::tuple<types...>&>(self));
}