#pragma once

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>::unordered_set ( const std::initializer_list<type>& init )
    extends base ( /*initialized later*/ )
{
    for ( const auto& k in init )  
        self.push(k);
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>::unordered_set ( std::from_range_t, std::ranges::input_range auto&& r )
    requires requires { std::declval<unordered_set>().push(*std::ranges::begin(r)); }
{
    for ( auto&& k in r )
        self.push(std::forward<decltype(k)>(k));   
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
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::clear ( )
{
    base::clear();
    return self;
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
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::push ( type k )
{
    let result = base::insert(k);
    if ( result.second == true )
        return self;
    else
        throw key_error("key {} already exists", k);
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::pop ( const type& k )
{
    let pop_count = base::erase(k);
    if ( pop_count >= 1 )
        return self;
    else
        throw key_error("key {} not found", k);
}

template < class type, class hash, class device >
constexpr unordered_set<type,hash,device>& unordered_set<type,hash,device>::update ( const unordered_set& s )
{
    for ( const auto& k in s )
        self.push(k);

    return self;
}