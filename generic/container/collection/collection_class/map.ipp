#pragma once

/// Class basic_map

// Core

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::basic_map ( std::initializer_list<pair<type1,type2>>&& init )
{
    for ( const pair<type1,type2>& p in init )
    {
        let it = cont.locate(p.key());

        if ( empty() or it->key() != p.key() )
            cont.push ( std::move ( const_cast<pair<type1,type2>&>(p) ), it );

        #if debug
            else if constexpr ( equalable<type2> ) // it->key() == p.key().
                if ( not empty() and it->value() != p.value() )
                    throw key_error("key {} with conflicing values {} and {}", p.key(), p.value(), it->value());
        #endif
    }
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::basic_map ( std::from_range_t, std::ranges::input_range auto&& r )
    requires requires { std::declval<basic_map>()[get<0>(*std::ranges::begin(r))] = get<1>(*std::ranges::begin(r)); }
{
    for ( auto&& p in r )
        self[std::forward<decltype(get<0>(p))>(get<0>(p))] = std::forward<decltype(get<1>(p))>(get<1>(p));
}

// Interface

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::size ( ) const
{
    return cont.size();
}

template < class type1, class type2, class key_less, class container >
constexpr bool basic_map<type1,type2,key_less,container>::empty ( ) const
{
    return size() == 0;
}

template < class type1, class type2, class key_less, class container >
constexpr auto& basic_map<type1,type2,key_less,container>::data ( )
{
    if constexpr ( requires { typename container::collection_type_recursive_data; } )
        return cont.data();
    else
        return cont;
}

template < class type1, class type2, class key_less, class container >
constexpr const auto& basic_map<type1,type2,key_less,container>::data ( ) const
{
    if constexpr ( requires { typename container::collection_type_recursive_data; } )
        return cont.data();
    else
        return cont;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::begin ( )
{
    return iterator ( cont.begin() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::begin ( ) const
{
    return const_iterator ( cont.begin() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::end ( )
{
    return iterator ( cont.end() );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::end ( ) const
{
    return const_iterator ( cont.end() );
}

template < class type1, class type2, class key_less, class container >
constexpr type2& basic_map<type1,type2,key_less,container>::operator [] ( type1&& k )
{
    let it = cont.locate(k);

    if ( empty() or it->key() != k )
        it = cont.push ( pair<type1&&,type2&&> ( std::move(k), type2() ), it );

    return const_cast<type2&> ( it->value() );
}

template < class type1, class type2, class key_less, class container >
constexpr type2& basic_map<type1,type2,key_less,container>::operator [] ( const type1& k )
{
    let it = cont.locate(k);

    if ( empty() or it->key() != k )
        it = cont.push ( pair<const type1&,type2&&> ( k, type2() ), it );

    return const_cast<type2&> ( it->value() );
}

template < class type1, class type2, class key_less, class container >
constexpr const type2& basic_map<type1,type2,key_less,container>::operator [] ( const type1& k ) const
{
    let it = cont.locate(k);

    if ( empty() or it->key() != k )
        #if debug
            throw index_error("key {} does not exist", k);
        #else
            return end()->value(); // Undefined behaviour, which matches the behaviour of index_error.
        #endif                     // Imaging you are operating an std::vector with invalid index, the result
                                   // might be segfault, invalid_but_no_segfault(e.x. out of size but in capacity), ...
    return it->value();            // No matter which case happens, it must satisfy the following 2 predicts:
}                                  // 1.Nobody can predict what happens. 2.It acts in same way as *end().

template < class type1, class type2, class key_less, class container >
constexpr const auto basic_map<type1,type2,key_less,container>::keys ( ) const
{
    return collection_keys_view ( const_cast<basic_map&>(self) );
}

template < class type1, class type2, class key_less, class container >
constexpr auto basic_map<type1,type2,key_less,container>::values ( )
{
    return collection_values_view ( self );
}

template < class type1, class type2, class key_less, class container >
constexpr const auto basic_map<type1,type2,key_less,container>::values ( ) const
{
    return collection_values_view ( const_cast<basic_map&>(self) );
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::clear ( )
{
    cont.clear();
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr bool basic_map<type1,type2,key_less,container>::contains ( const type1& k ) const
{
    return not empty() and cont.locate(k)->key() == k;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::pop ( const type1& k )
{
    let it = cont.locate(k);

    #if debug
        if ( empty() or it->key() != k )
            throw key_error("key {} does not exist", k);
    #endif

    cont.pop ( k, it );

    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>& basic_map<type1,type2,key_less,container>::update ( const map_type<type1,type2> auto& upd )
{
    for ( const auto& [k,v] in upd )
        self[k] = upd[k];

    return self;
}



/// Class basic_map::iterator

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator::iterator ( const container::const_iterator& init )
    extends it ( init )
{

}

template < class type1, class type2, class key_less, class container >
constexpr pair<const type1,type2>& basic_map<type1,type2,key_less,container>::iterator::operator * ( ) const
{
    return const_cast<pair<const type1,type2>&> ( static_cast<const pair<const type1,type2>&> ( *it ) );
}

template < class type1, class type2, class key_less, class container >
constexpr pair<const type1,type2>* basic_map<type1,type2,key_less,container>::iterator::operator -> ( ) const
{
    return &operator*();
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator& basic_map<type1,type2,key_less,container>::iterator::operator ++ ( )
{
    ++it;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator ++ ( int )
{
    let it2 = self;
    ++self;
    return it2;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator& basic_map<type1,type2,key_less,container>::iterator::operator -- ( )
{
    --it;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator -- ( int )
{
    let it2 = self;
    --self;
    return it2;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator + ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it + offset;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::iterator basic_map<type1,type2,key_less,container>::iterator::operator - ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it - offset;
}

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::iterator::operator - ( const iterator& right ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it - right.it;
}

/// Class basic_map::const_iterator

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator::const_iterator ( const container::const_iterator& init )
    extends it ( init )
{

}

template < class type1, class type2, class key_less, class container >
constexpr const pair<const type1,type2>& basic_map<type1,type2,key_less,container>::const_iterator::operator * ( ) const
{
    return static_cast<const pair<const type1,type2>&> ( *it );
}

template < class type1, class type2, class key_less, class container >
constexpr const pair<const type1,type2>* basic_map<type1,type2,key_less,container>::const_iterator::operator -> ( ) const
{
    return &operator*();
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator& basic_map<type1,type2,key_less,container>::const_iterator::operator ++ ( )
{
    ++it;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator ++ ( int )
{
    let it2 = self;
    ++self;
    return it2;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator& basic_map<type1,type2,key_less,container>::const_iterator::operator -- ( )
{
    --it;
    return self;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator -- ( int )
{
    let it2 = self;
    --self;
    return it2;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator + ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it + offset;
}

template < class type1, class type2, class key_less, class container >
constexpr basic_map<type1,type2,key_less,container>::const_iterator basic_map<type1,type2,key_less,container>::const_iterator::operator - ( int offset ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it - offset;
}

template < class type1, class type2, class key_less, class container >
constexpr int basic_map<type1,type2,key_less,container>::const_iterator::operator - ( const const_iterator& right ) const
    requires std::random_access_iterator<typename container::const_iterator>
{
    return it - right.it;
}