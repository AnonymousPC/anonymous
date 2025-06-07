template < class type1, class type2, class compare, class device >
constexpr map<type1,type2,compare,device>::map ( std::initializer_list<pair<const type1,type2>> init )
    requires copyable<type1> and copyable<type2>
{
    for ( const auto& [k, v] in init )
        self[k] = v;
}

template < class type1, class type2, class compare, class device >
constexpr int map<type1,type2,compare,device>::size ( ) const
{
    return base::size();
}

template < class type1, class type2, class compare, class device >
constexpr bool map<type1,type2,compare,device>::empty ( ) const
{
    return base::empty();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::iterator map<type1,type2,compare,device>::begin ( )
{
    return base::begin();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_iterator map<type1,type2,compare,device>::begin ( ) const
{
    return base::begin();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::iterator map<type1,type2,compare,device>::end ( )
{
    return base::end();
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_iterator map<type1,type2,compare,device>::end ( ) const
{
    return base::end();
}

template < class type1, class type2, class compare, class device > 
constexpr bool map<type1,type2,compare,device>::contains ( const type1& k ) const
{
    return base::contains(k);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::value_reference map<type1,type2,compare,device>::operator[] ( const type1& k )
{
    return base::operator[](k);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>::const_value_reference map<type1,type2,compare,device>::operator[] ( const type1& k ) const
{
    auto it = base::find(k);
    if ( it != base::end() )
        return get<1>(*it);
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type1, class type2, class compare, class device > 
constexpr map<type1,type2,compare,device>& map<type1,type2,compare,device>::pop ( const type1& k )
{
    auto result = base::erase(k);
    if ( result >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type1, class type2, class compare, class device >
constexpr bool map<type1,type2,compare,device>::all ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    return empty() or (size() == 1 and *begin() == val);
}

template < class type1, class type2, class compare, class device >
constexpr int map<type1,type2,compare,device>::count ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it != base::end() and it->second == val.value() ? 1 : 0;
}

template < class type1, class type2, class compare, class device >
constexpr bool map<type1,type2,compare,device>::exist ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it != base::end() and it->second() == val.value();
}

template < class type1, class type2, class compare, class device >
constexpr bool map<type1,type2,compare,device>::none ( const equalable_to<pair<const type1,type2>> auto& val ) const
{
    auto it = base::find(val.key());
    return it == base::end() or it->second() != val.value();
}
