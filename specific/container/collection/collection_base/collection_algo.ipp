#pragma once
#define derive_of_self       static_cast<      collection_type&>(self)
#define const_derive_of_self static_cast<const collection_type&>(self)

template < class collection_type, class type, class device > 
constexpr bool collection_algo<collection_type,type,device>::all ( predicate<type> auto pred ) const
{
    return device::all_of ( const_derive_of_self.begin(), const_derive_of_self.end(), pred );
}

template < class collection_type, class type, class device > 
constexpr int collection_algo<collection_type,type,device>::count ( predicate<type> auto pred ) const
{
    return device::count_if ( const_derive_of_self.begin(), const_derive_of_self.end(), pred );
}

template < class collection_type, class type, class device > 
constexpr bool collection_algo<collection_type,type,device>::exist ( predicate<type> auto pred ) const
{
    return device::any_of ( const_derive_of_self.begin(), const_derive_of_self.end(), pred );
}

template < class collection_type, class type, class device > 
constexpr bool collection_algo<collection_type,type,device>::none ( predicate<type> auto pred ) const
{
    return device::none_of ( const_derive_of_self.begin(), const_derive_of_self.end(), pred );
}

template < class collection_type, class type, class device > 
constexpr collection_type& collection_algo<collection_type,type,device>::each ( invocable<type&> auto op )
{
    device::for_each ( derive_of_self.begin(), derive_of_self.end(), op );
    return derive_of_self;
}

template < class collection_type, class type, class device > 
constexpr const collection_type& collection_algo<collection_type,type,device>::each ( invocable<const type&> auto op ) const
{
    device::for_each ( const_derive_of_self.begin(), const_derive_of_self.end(), op );
    return const_derive_of_self;
}

template < class collection_type, class type, class device > 
constexpr auto collection_algo<collection_type,type,device>::sum ( ) const
    requires default_initializable<type> and plusable<type>
{
    return device::accumulate ( const_derive_of_self.begin(), const_derive_of_self.end(), type() );
}

template < class collection_type, class type, class device > 
constexpr auto collection_algo<collection_type,type,device>::sum ( invocable<type> auto op ) const
    requires default_initializable<invoke_result<decltype(op),type>> and plusable<invoke_result<decltype(op),type>>
{
    return device::accumulate ( const_derive_of_self.begin(), const_derive_of_self.end(), invoke_result<decltype(op),type>(), [&] ( const auto& a, const auto& b ) { return a + op(b); } );
}

template < class collection_type, class type, class device > 
constexpr auto collection_algo<collection_type,type,device>::product ( ) const
    requires convertible_to<int,type> and multipliable<type>
{
    return device::accumulate ( const_derive_of_self.begin(), const_derive_of_self.end(), type(1), [] ( const auto& a, const auto& b ) { return a * b; } );
}

template < class collection_type, class type, class device > 
constexpr auto collection_algo<collection_type,type,device>::product ( invocable<type> auto op ) const
    requires convertible_to<int,invoke_result<decltype(op),type>> and multipliable<invoke_result<decltype(op),type>>
{
    return device::accumulate ( const_derive_of_self.begin(), const_derive_of_self.end(), invoke_result<decltype(op),type>(1), [&] ( const auto& a, const auto& b ) { return a * op(b); } );
}

#undef derive_of_self
#undef const_derive_of_self