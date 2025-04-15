#pragma once

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
    if constexpr ( requires { base::contains(k); } )
        return base::contains(k);
    else
        return base::find(k) != base::end();
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
    let result = base::insert(k);
    if ( result.second == true )
        return self;
    else
        throw key_error("key {} already exists", k);
}

template < class type, class compare, class device >
constexpr set<type,compare,device>& set<type,compare,device>::pop ( const type& k )
{
    let pop_count = base::erase(k);
    if ( pop_count >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type, class compare, class device >
constexpr set<type,compare,device>& set<type,compare,device>::update ( const set& s )
{
    for ( const auto& k in s )
        push(k);

    return self;
}

template < class type, class compare, class device >
constexpr auto set<type,compare,device>::emplace ( auto&&... args )
    requires constructible_from<typename base::value_type,decltype(args)...>
{
    return base::emplace(std::forward<decltype(args)>(args)...);
}