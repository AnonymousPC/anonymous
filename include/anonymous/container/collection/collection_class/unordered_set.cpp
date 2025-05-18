template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>::unordered_set ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{

}

template < class type, class hash, class device >
constexpr int unordered_set<type,hash,device>::size ( ) const
{
    return base::size();
}

template < class type, class hash, class device >
constexpr bool unordered_set<type,hash,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>::const_iterator unordered_set<type,hash,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>::const_iterator unordered_set<type,hash,device>::end ( ) const
{
    return base::end();
}

template < class type, class hash, class device >
constexpr bool unordered_set<type,hash,device>::contains ( const type& k ) const
{
    if constexpr ( requires { base::contains(k); } )
        return base::contains(k);
    else
        return base::find(k) != base::end();
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::push ( type k )
{
    auto result = base::insert(k);
    if ( result.second == true )
        return self;
    else
        throw key_error("key {} already found", k);
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::pop ( const type& k )
{
    auto pop_count = base::erase(k);
    if ( pop_count >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type, class hash, class device >
constexpr bool unordered_set<type,hash,device>::all ( const equalable_to<type> auto& val ) const
{
    return empty() or (size() == 1 and *begin() == val);
}

template < class type, class hash, class device >
constexpr int unordered_set<type,hash,device>::count ( const equalable_to<type> auto& val ) const
{
    return contains(val) ? 1 : 0;
}

template < class type, class hash, class device >
constexpr bool unordered_set<type,hash,device>::exist ( const equalable_to<type> auto& val ) const
{
    return contains(val);
}

template < class type, class hash, class device >
constexpr bool unordered_set<type,hash,device>::none ( const equalable_to<type> auto& val ) const
{
    return not contains(val);
}