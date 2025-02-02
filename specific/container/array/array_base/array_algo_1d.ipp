#pragma once

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::begin ( )
{
    return static_cast<array_type&>(self).begin();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::begin ( ) const
{
    return static_cast<const array_type&>(self).begin();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::end ( )
{
    return static_cast<array_type&>(self).end();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::end ( ) const
{
    return static_cast<const array_type&>(self).end();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::data ( )
{
    return static_cast<array_type&>(self).data();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::data ( ) const
{
    return static_cast<const array_type&>(self).data();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::size ( ) const
{
    return static_cast<const array_type&>(self).size();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::ownership ( ) const
{
    return static_cast<const array_type&>(self).ownership();
}

template < class array_type, class type, class device >
constexpr auto array_algo<array_type,type,1,device>::contiguous ( ) const
{
    return static_cast<const array_type&>(self).contiguous();
}

template < class array_type, class type, class device >
constexpr int array_algo<array_type,type,1,device>::adjacent_find ( ) const
    requires equalable<type>
{
    let pos = 0;
    if ( contiguous() )
        pos = device::adjacent_find(data(), data() + size()) - data() + 1;
    else
        pos = device::adjacent_find(begin(), end()) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

template < class array_type, class type, class device >
constexpr int array_algo<array_type,type,1,device>::adjacent_find ( const relation<type,type> auto pred ) const
{
    let pos = 0;
    if ( contiguous() )
        pos = device::adjacent_find(data(), data() + size(), pred) - data() + 1;
    else
        pos = device::adjacent_find(begin(), end(), pred) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

template < class array_type, class type, class device >
constexpr array<int> array_algo<array_type,type,1,device>::adjacent_where ( ) const
    requires equalable<type>
{
    let pos = array<int>();
    if ( contiguous() )
        for ( let it = data(); it != data() + size() + 1; it++ )
            pos.push((it = device::adjacent_find(it, data() + size())) - data() + 1);
    else
        for ( let it = begin(); it != end() + 1; it++ )
            pos.push((it = device::adjacent_find(it, end())) - begin() + 1);
    return pos;
}

template < class array_type, class type, class device >
constexpr array<int> array_algo<array_type,type,1,device>::adjacent_where ( const relation<type,type> auto pred ) const
{
    let pos = array<int>();
    if ( contiguous() )
        for ( let it = data(); it != data() + size() + 1; it++ )
            pos.push((it = device::adjacent_find(it, data() + size(), pred)) - data() + 1);
    else
        for ( let it = begin(); it != end() + 1; it++ )
            pos.push((it = device::adjacent_find(it, end(), pred)) - begin() + 1);
    return pos;
}

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::all ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::all ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::contains ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::contains ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::count ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::count ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::exist ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::exist ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::find ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::find ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::is_partitioned ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::is_sorted ( ) const
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::is_sorted ( const relation<type,type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr const array_algo<array_type,type,1,device>::reference array_algo<array_type,type,1,device>::max ( ) const
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr const array_algo<array_type,type,1,device>::reference array_algo<array_type,type,1,device>::max ( const relation<type,type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr const array_algo<array_type,type,1,device>::reference array_algo<array_type,type,1,device>::min ( ) const
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr const array_algo<array_type,type,1,device>::reference array_algo<array_type,type,1,device>::min ( const relation<type,type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::next_permutation ( )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::next_permutation ( const relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::none ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr bool array_algo<array_type,type,1,device>::none ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::partial_sort ( int n )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::partial_sort ( int n, relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::partition ( const predicate<type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::prev_permutation ( )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::prev_permutation ( const relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::remove ( const equalable_to<type> auto& value )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::remove ( const predicate<type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::reverse ( )
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::right_adjacent_find ( ) const
//     requires equalable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::right_adjacent_find ( const relation<type,type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::right_find ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr int array_algo<array_type,type,1,device>::right_find ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::rotate ( int n )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::stable_partition ( const equalable_to<type> auto& value )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::stable_partition ( const predicate<type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::stable_sort ( )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::stable_sort ( const relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::sort ( )
//     requires comparable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::sort ( const relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::unique ( )
//     requires equalable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::unique ( const relation<type,type> auto pred )
// {

// }

// template < class array_type, class type, class device >
// constexpr array<int> array_algo<array_type,type,1,device>::where ( const equalable_to<type> auto& value ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr array<int> array_algo<array_type,type,1,device>::where ( const predicate<type> auto pred ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr type array_algo<array_type,type,1,device>::average ( ) const
//     requires default_initializable<type> and plusable<type> and dividable_to<type,int>
// {

// }

// template < class array_type, class type, class device >
// constexpr type array_algo<array_type,type,1,device>::sum ( ) const
//     requires default_initializable<type> and plusable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr type array_algo<array_type,type,1,device>::product ( ) const
//     requires convertible_to<int,type> and multipliable<type>
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::each ( invocable<reference> auto func )
// {

// }

// template < class array_type, class type, class device >
// constexpr const array_type& array_algo<array_type,type,1,device>::each ( invocable<type> auto func ) const
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::fill ( const convertible_to<type> auto& value )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::generate ( invocable_r<type> auto gen )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::transform ( invocable_r<type,type> auto op )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::replace ( const equalable_to<type> auto& old_value, const convertible_to<type> auto& new_value )
// {

// }

// template < class array_type, class type, class device >
// constexpr array_type& array_algo<array_type,type,1,device>::replace ( predicate<type> auto pred, const convertible_to<type> auto& new_value )
// {

// }