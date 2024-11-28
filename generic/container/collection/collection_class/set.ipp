#pragma once

/// Class basic_set

// Core

template < class type, class less, class container >
constexpr basic_set<type,less,container>::basic_set ( std::initializer_list<type>&& init )
{
    for ( const type& v in init )
        self.push ( std::move ( const_cast<type&> ( v ) ) );
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::basic_set ( std::from_range_t, std::ranges::input_range auto&& r )
    requires requires { std::declval<basic_set>().push(*std::ranges::begin(r)); }
{
    for ( auto&& v in r )
        self.push ( std::forward<decltype(v)>(v) );
}

// Interface

template < class type, class less, class container >
constexpr int basic_set<type,less,container>::size ( ) const
{
    return cont.size();
}

template < class type, class less, class container >
constexpr bool basic_set<type,less,container>::empty ( ) const
{
    return size() == 0;
}

template < class type, class less, class container >
constexpr auto& basic_set<type,less,container>::data ( )
{
    if constexpr ( requires { typename container::collection_type_recursive_data; } )
        return cont.data();
    else
        return cont;
}

template < class type, class less, class container >
constexpr const auto& basic_set<type,less,container>::data ( ) const
{
    if constexpr ( requires { typename container::collection_type_recursive_data; } )
        return cont.data();
    else
        return cont;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::const_iterator basic_set<type,less,container>::begin ( ) const
{
    return cont.begin();
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>::const_iterator basic_set<type,less,container>::end ( ) const
{
    return cont.end();
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::clear ( )
{
    cont.clear();
    return self;
}

template < class type, class less, class container >
constexpr bool basic_set<type,less,container>::contains ( const type& val ) const
{
    return not empty() and *cont.locate(val) == val;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::push ( type val )
{
    auto it = cont.locate(val);
    if ( empty() or *it != val ) // Not contains.
        cont.push ( std::move ( val ), it );

    return self;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::pop ( const type& val )
{
    auto it = cont.locate(val);
    #if debug
        if ( empty() or *it != val )
            throw key_error("key {} does not exist", val);
    #endif
    cont.pop ( val, it );

    return val;
}

template < class type, class less, class container >
constexpr basic_set<type,less,container>& basic_set<type,less,container>::update ( const set_type<type> auto& upd )
{
    // TODO: Optimizable if less is same.

    for ( const auto& val in upd )
    {
        let it = cont.locate(val);

        if ( empty() or *it != val ) // Update if not contains.
            cont.push ( val, it );
    }
}