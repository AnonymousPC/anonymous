template < class type, class compare, class device >
constexpr set<type,compare,device>::set ( std::initializer_list<type> init )
    requires copyable<type>
    extends base ( std::forward<decltype(init)>(init) )
{

}

template < class type, class compare, class device >
constexpr int set<type,compare,device>::size ( ) const
{
    return base::size();
}

template < class type, class compare, class device >
constexpr bool set<type,compare,device>::empty ( ) const
{
    return base::empty();
}

template < class type, class compare, class device >
constexpr set<type,compare,device>::const_iterator set<type,compare,device>::begin ( ) const
{
    return base::begin();
}

template < class type, class compare, class device >
constexpr set<type,compare,device>::const_iterator set<type,compare,device>::end ( ) const
{
    return base::end();
}

template < class type, class compare, class device >
constexpr bool set<type,compare,device>::contains ( const type& k ) const
{
    return base::contains(k);
}

template < class type, class compare, class device >
constexpr set<type,compare,device>& set<type,compare,device>::clear ( )
{
    base::clear();
    return self;
}

template < class type, class compare, class device >
constexpr set<type,compare,device>& set<type,compare,device>::push ( type k )
{
    auto result = base::insert(k);
    if ( result.second == true )
        return self;
    else
        throw key_error("key {} already found", k);
}

template < class type, class compare, class device >
constexpr set<type,compare,device>& set<type,compare,device>::pop ( const type& k )
{
    auto result = base::erase(k);
    if ( result >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type, class compare, class device >
constexpr bool set<type,compare,device>::all ( const equalable_to<type> auto& val ) const
{
    return empty() or (size() == 1 and *begin() == val);
}

template < class type, class compare, class device >
constexpr int set<type,compare,device>::count ( const equalable_to<type> auto& val ) const
{
    return contains(val) ? 1 : 0;
}

template < class type, class compare, class device >
constexpr bool set<type,compare,device>::exist ( const equalable_to<type> auto& val ) const
{
    return contains(val);
}

template < class type, class compare, class device >
constexpr bool set<type,compare,device>::none ( const equalable_to<type> auto& val ) const
{
    return not contains(val);
}