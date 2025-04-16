#pragma once

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::data ( )
{
    return static_cast<container&>(self).data();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::data ( ) const
{
    return static_cast<const container&>(self).data();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::empty ( ) const
{
    return static_cast<const container&>(self).empty();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::ownership ( ) const
{
    return static_cast<const container&>(self).ownership();
}

template < class container, class type, class device >
constexpr decltype(auto) array_algo<container,type,1,device>::contiguous ( ) const
{
    return static_cast<const container&>(self).contiguous();
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::adjacent_find ( ) const
    requires equalable<type>
{
    auto pos = contiguous() ? device::adjacent_find(data(), data() + size()) - data() + 1 :
                             device::adjacent_find(begin(), end()) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::adjacent_find ( relation<type,type> auto pred ) const
{
    auto pos = contiguous() ? device::adjacent_find(data(), data() + size(), pred) - data() + 1 :
                             device::adjacent_find(begin(), end(), pred) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr array<int> array_algo<container,type,1,device>::adjacent_where ( ) const
    requires equalable<type>
{
    auto pos = array<int>();
    if ( contiguous() )
        for ( auto it = data(); ; )
            if ( (it = device::adjacent_find(it, data() + size())) != data() + size() )
                pos.push((it++) - data() + 1);
            else   
                break;
    else
        for ( auto it = begin(); ; )
            if ( (it = device::adjacent_find(it, end())) != end() )
                pos.push((it++) - begin() + 1);
            else   
                break;
    return pos;
}

template < class container, class type, class device >
constexpr array<int> array_algo<container,type,1,device>::adjacent_where ( relation<type,type> auto pred ) const
{
    auto pos = array<int>();
    if ( contiguous() )
        for ( auto it = data(); ; )
            if ( (it = device::adjacent_find(it, data() + size(), pred)) != data() + size() )
                pos.push((it++) - data() + 1);
            else   
                break;
    else
        for ( auto it = begin(); ; )
            if ( (it = device::adjacent_find(it, end(), pred)) != end() )
                pos.push((it++) - begin() + 1);
            else   
                break;
    return pos;
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::all ( const equalable_to<type> auto& val ) const
{
    return contiguous() ? device::all_of(data(), data() + size(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); }) :
                             device::all_of(begin(), end(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); });
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::all ( predicate<type> auto pred ) const
{
    return contiguous() ? device::all_of(data(), data() + size(), pred) :
                          device::all_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::contains ( const equalable_to<type> auto& val ) const
{
    return contiguous() ? device::any_of(data(), data() + size(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); }) :
                          device::any_of(begin(), end(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); });
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::contains ( predicate<type> auto pred ) const
{
    return contiguous() ? device::any_of(data(), data() + size(), pred) :
                          device::any_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::count ( const equalable_to<type> auto& val ) const
{
    return contiguous() ? device::count(data(), data() + size(), val) :
                          device::count(begin(), end(), val);
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::count ( predicate<type> auto pred ) const
{
    return contiguous() ? device::count(data(), data() + size(), pred) :
                          device::count(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::exist ( const equalable_to<type> auto& val ) const
{
    return contiguous() ? device::any_of(data(), data() + size(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); }) :
                          device::any_of(begin(), end(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); });
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::exist ( predicate<type> auto pred ) const
{
    return contiguous() ? device::any_of(data(), data() + size(), pred) :
                          device::any_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::find ( const equalable_to<type> auto& val ) const
{
    auto pos = contiguous() ? device::find(data(), data() + size(), val) - data() + 1 :
                             device::find(begin(), end(), val) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::find ( predicate<type> auto pred ) const
{
    auto pos = contiguous() ? device::find_if(data(), data() + size(), pred) - data() + 1 :
                             device::find_if(begin(), end(), pred) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::is_partitioned ( predicate<type> auto pred ) const
{
    return contiguous() ? device::is_partitioned(data(), data() + size(), pred) :
                          device::is_partitioned(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::is_sorted ( ) const
    requires comparable<type>
{
    return is_sorted() ? device::is_sorted(data(), data() + size()) :
                         device::is_sorted(begin(), end());
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::is_sorted ( relation<type,type> auto pred ) const
{
    return is_sorted() ? device::is_sorted(data(), data() + size(), pred) :
                         device::is_sorted(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr array_algo<container,type,1,device>::reference array_algo<container,type,1,device>::max ( )
    requires comparable<type>
{
    #ifdef debug
        if ( empty() )
            throw value_error("get max element from an empty array");
    #endif
    return contiguous() ? *device::max_element(data(), data() + size()) :
                          *device::max_element(begin(), end());
}

template < class container, class type, class device >
constexpr array_algo<container,type,1,device>::const_reference array_algo<container,type,1,device>::max ( relation<type,type> auto pred ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("get max element from an empty array");
    #endif
    return contiguous() ? *device::max_element(data(), data() + size(), pred) :
                          *device::max_element(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr array_algo<container,type,1,device>::reference array_algo<container,type,1,device>::min ( )
    requires comparable<type>
{
    #ifdef debug
        if ( empty() )
            throw value_error("get min element from an empty array");
    #endif
    return contiguous() ? *device::min_element(data(), data() + size()) :
                          *device::min_element(begin(), end());
}

template < class container, class type, class device >
constexpr array_algo<container,type,1,device>::const_reference array_algo<container,type,1,device>::min ( relation<type,type> auto pred ) const
{
    #ifdef debug
        if ( empty() )
            throw value_error("get min element from an empty array");
    #endif
    return contiguous() ? *device::min_element(data(), data() + size(), pred) :
                          *device::min_element(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::next_permutation ( )
    requires comparable<type>
{
    contiguous() ? device::next_permutation(data(), data() + size()) :
                   device::next_permutation(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::next_permutation ( relation<type,type> auto pred )
{
    contiguous() ? device::next_permutation(data(), data() + size(), pred) :
                   device::next_permutation(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::none ( const equalable_to<type> auto& val ) const
{
    return contiguous() ? device::none_of(data(), data() + size(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); }) :
                          device::none_of(begin(), end(), [&] (const auto& item) { return device::template equal_to<type>()(item, val); });
}

template < class container, class type, class device >
constexpr bool array_algo<container,type,1,device>::none ( predicate<type> auto pred ) const
{
    return contiguous() ? device::none_of(data(), data() + size(), pred) :
                          device::none_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::partial_sort ( int n )
    requires comparable<type>
{
    #ifdef debug
        if ( n < 0 )
            throw value_error("partial_sort array with middle {} out of range with size {}", n, size());
    #endif
    contiguous() ? (void) device::partial_sort(data(), data() + n, data() + size()) :
                   (void) device::partial_sort(begin(), begin() + n, end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::partial_sort ( int n, relation<type,type> auto pred )
{
    #ifdef debug
        if ( n < 0 )
            throw value_error("partial_sort array with middle {} out of range with size {}", n, size());
    #endif
    contiguous() ? (void) device::partial_sort(data(), data() + n, data() + size(), pred) :
                   (void) device::partial_sort(begin(), begin() + n, end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::partition ( predicate<type> auto pred )
{
    contiguous() ? (void) device::partition(data(), data() + size(), pred) :
                   (void) device::partition(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::prev_permutation ( )
    requires comparable<type>
{
    contiguous() ? device::prev_permutation(data(), data() + size()) :
                   device::prev_permutation(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::prev_permutation ( relation<type,type> auto pred )
{
    contiguous() ? device::prev_permutation(data(), data() + size(), pred) :
                   device::prev_permutation(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::remove ( const equalable_to<type> auto& val )
{
    return static_cast<container&>(self).resize(contiguous() ? device::remove(data(), data() + size(), val) - data() :
                                                                device::remove(begin(), end(), val) - begin());
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::remove ( predicate<type> auto pred )
{
    return static_cast<container&>(self).resize(contiguous() ? device::remove_if(data(), data() + size(), pred) - data() :
                                                                device::remove_if(begin(), end(), pred) - begin());
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::reverse ( )
{
    contiguous() ? device::reverse(data(), data() + size()) :
                   device::reverse(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::right_adjacent_find ( ) const
    requires equalable<type>
{
    if ( contiguous() )
    {
        for ( auto it = data() + size() - 1; it != data(); it-- )
            if ( device::template equal_to<type>()(*(it-1), *it) )
                return it - data();
    }
    else
    {
        for ( auto it = end() - 1; it != begin(); it-- )
            if ( device::template equal_to<type>()(*(it-1), *it) )
                return it - begin();
    }
    return 0;
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::right_adjacent_find ( relation<type,type> auto pred ) const
{
    if ( contiguous() )
    {
        for ( auto it = data() + size() - 1; it != data(); it-- )
            if ( pred(*(it-1), *it) )
                return it - data();
    }
    else
    {
        for ( auto it = end() - 1; it != begin(); it-- )
            if ( pred(*(it-1), *it) )
                return it - begin();
    }
    return 0;
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::right_find ( const equalable_to<type> auto& val ) const
{
    if ( contiguous() )
    {
        for ( auto it = data() + size() - 1; it != data(); it-- )
            if ( device::template equal_to<type>()(*it, val) )
                return it - data() + 1;
    }
    else
    {
        for ( auto it = end() - 1; it != begin(); it-- )
            if ( device::template equal_to<type>()(*it, val) )
                return it - begin() + 1;
    }
    return 0;
}

template < class container, class type, class device >
constexpr int array_algo<container,type,1,device>::right_find ( predicate<type> auto pred ) const
{
    if ( contiguous() )
    {
        for ( auto it = data() + size() - 1; it != data(); it-- )
            if ( pred(*it) )
                return it - data() + 1;
    }
    else
    {
        for ( auto it = end() - 1; it != begin(); it-- )
            if ( pred(*it) )
                return it - begin() + 1;
    }
    return 0;
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::rotate ( int n )
{
    #ifdef debug
        if ( n <= -size() or n >= size() )
            throw value_error("rotate array with step {} out of range with size {}", n, size());
    #endif
    contiguous() ? n > 0 ? (void) device::rotate(data(), data() + size() - n, data() + size()) :
                              (void) device::rotate(data(), data() - n, data() + size())          :
                      n > 0 ? (void) device::rotate(begin(), end() - n, end())                    :
                              (void) device::rotate(begin(), begin() - n, end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::stable_partition ( predicate<type> auto pred )
{
    contiguous() ? (void) device::stable_partition(data(), data() + size(), pred) :
                   (void) device::stable_partition(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::stable_sort ( )
    requires comparable<type>
{
    contiguous() ? device::stable_sort(data(), data() + size()) : 
                   device::stable_sort(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::stable_sort ( relation<type,type> auto pred )
{
    contiguous() ? device::stable_sort(data(), data() + size(), pred) : 
                   device::stable_sort(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::sort ( )
    requires comparable<type>
{
    contiguous() ? device::sort(data(), data() + size()) : 
                   device::sort(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::sort ( relation<type,type> auto pred )
{    
    contiguous() ? device::sort(data(), data() + size(), pred) : 
                   device::sort(begin(), end(), pred);
    return static_cast<container&>(self);

}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::unique ( )
    requires equalable<type>
{
    return static_cast<container&>(self).resize(contiguous())? device::unique(data(), data() + size()) - data() : 
                                                               device::unique(begin(), end()) - begin();
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::unique ( relation<type,type> auto pred )
{
    return static_cast<container&>(self).resize(contiguous() ? device::unique(data(), data() + size(), pred) - data() : 
                                                               device::unique(begin(), end()) - begin(), pred);
}

template < class container, class type, class device >
constexpr array<int> array_algo<container,type,1,device>::where ( const equalable_to<type> auto& val ) const
{
    auto pos = array<int>();
    if ( contiguous() )
        for ( auto it = data(); ; )
            if ( (it = device::find(it, data() + size(), val)) != data() + size() )
                pos.push((it++) - data() + 1);
            else   
                break;
    else
        for ( auto it = begin(); ; )
            if ( (it = device::find(it, end(), val)) != end() )
                pos.push((it++) - begin() + 1);
            else   
                break;
    return pos;
}

template < class container, class type, class device >
constexpr array<int> array_algo<container,type,1,device>::where ( predicate<type> auto pred ) const
{
    auto pos = array<int>();
    if ( contiguous() )
        for ( auto it = data(); ; )
            if ( (it = device::find_if(it, data() + size(), pred)) != data() + size() )
                pos.push((it++) - data() + 1);
            else   
                break;
    else
        for ( auto it = begin(); ; )
            if ( (it = device::find_if(it, end(), pred)) != end() )
                pos.push((it++) - begin() + 1);
            else   
                break;
    return pos;
}

template < class container, class type, class device >
constexpr type array_algo<container,type,1,device>::average ( ) const
    requires default_initializable<type> and plusable<type> and dividable_to<type,int>
{
    #ifdef debug
        if ( empty() )
            throw value_error("get average from an empty array");
    #endif
    return sum() / size();
}

template < class container, class type, class device >
constexpr type array_algo<container,type,1,device>::sum ( ) const
    requires default_initializable<type> and plusable<type>
{
    if constexpr ( number_type<type> )
        return contiguous() ? device::reduce(data(), data() + size(), type()) :
                              device::reduce(begin(), end(), type());
    else    
        return contiguous() ? device::accumulate(data(), data() + size(), type()) :
                              device::accumulate(begin(), end(), type());
}

template < class container, class type, class device >
constexpr type array_algo<container,type,1,device>::product ( ) const
    requires convertible_to<int,type> and multipliable<type>
{
    if constexpr ( number_type<type> )
        return contiguous() ? device::reduce(data(), data() + size(), type(1), typename device::template multiplies<type>()) :
                              device::reduce(begin(), end(), type(1), typename device::template multiplies<type>());
    else    
        return contiguous() ? device::accumulate(data(), data() + size(), type(1), typename device::template multiplies<type>()) :
                              device::accumulate(begin(), end(), type(1), typename device::template multiplies<type>());
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::for_each ( invocable<reference> auto op )
{
    contiguous() ? (void) device::for_each(data(), data() + size(), op) :
                   (void) device::for_each(begin(), end(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr const container& array_algo<container,type,1,device>::for_each ( invocable<type> auto op ) const
{
    contiguous() ? (void) device::for_each(data(), data() + size(), op) :
                   (void) device::for_each(begin(), end(), op);
    return static_cast<const container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::fill ( const convertible_to<type> auto& val )
{
    contiguous() ? device::fill(data(), data() + size(), val) :
                   device::fill(begin(), end(), val);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::generate ( invocable_r<type> auto op )
{
    contiguous() ? device::generate(data(), data() + size(), op) :
                   device::generate(begin(), end(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::transform ( invocable_r<type,type> auto op )
{
    contiguous() ? (void) device::transform(data(), data() + size(), data(), op) :
                   (void) device::transform(begin(), end(), begin(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::replace ( const equalable_to<type> auto& old_val, const convertible_to<type> auto& new_val )
{
    contiguous() ? device::replace(data(), data() + size(), old_val, new_val) :
                   device::replace(begin(), end(), old_val, new_val);
    return static_cast<container&>(self);            
}

template < class container, class type, class device >
constexpr container& array_algo<container,type,1,device>::replace ( predicate<type> auto pred, const convertible_to<type> auto& new_val )
{
    contiguous() ? device::replace_if(data(), data() + size(), pred, new_val) :
                   device::replace_if(begin(), end(), pred, new_val);
    return static_cast<container&>(self);  
}