template < class type1, class type2, class hash, class device >
constexpr unordered_map<type1,type2,hash,device>::unordered_map ( std::initializer_list<pair<const type1,type2>> init )
    requires copyable<type1> and copyable<type2>
{
    for ( const auto& [k, v] in init )
        self[k] = v;
}

template < class type1, class type2, class hash, class device >
constexpr int unordered_map<type1,type2,hash,device>::size ( ) const
{
    return base::size();
}

template < class type1, class type2, class hash, class device >
constexpr bool unordered_map<type1,type2,hash,device>::empty ( ) const
{
    return base::empty();
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::iterator unordered_map<type1,type2,hash,device>::begin ( )
{
    return base::begin();
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::const_iterator unordered_map<type1,type2,hash,device>::begin ( ) const
{
    return base::begin();
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::iterator unordered_map<type1,type2,hash,device>::end ( )
{
    return base::end();
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::const_iterator unordered_map<type1,type2,hash,device>::end ( ) const
{
    return base::end();
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::value_reference unordered_map<type1,type2,hash,device>::operator[] ( const type1& k )
{
    return base::operator[](k);
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>::const_value_reference unordered_map<type1,type2,hash,device>::operator[] ( const type1& k ) const
{
    auto it = base::find(k);
    if ( it != base::end() )
        return get<1>(*it);
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class hash, class device > 
constexpr bool unordered_map<type1,type2,hash,device>::contains ( const type1& k ) const
{
    return base::contains(k);
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>& unordered_map<type1,type2,hash,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type1, class type2, class hash, class device > 
constexpr unordered_map<type1,type2,hash,device>& unordered_map<type1,type2,hash,device>::pop ( const type1& k )
{
    auto result = base::erase(k);
    if ( result >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class hash, class device >
constexpr bool unordered_map<type1,type2,hash,device>::all ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    return empty() or (size() == 1 and *begin() == val);
}

template < class type1, class type2, class hash, class device >
constexpr int unordered_map<type1,type2,hash,device>::count ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it != base::end() and it->second == val.value() ? 1 : 0;
}

template < class type1, class type2, class hash, class device >
constexpr bool unordered_map<type1,type2,hash,device>::exist ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it != base::end() and it->second() == val.value();
}

template < class type1, class type2, class hash, class device >
constexpr bool unordered_map<type1,type2,hash,device>::none ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it == base::end() or it->second() != val.value();
}