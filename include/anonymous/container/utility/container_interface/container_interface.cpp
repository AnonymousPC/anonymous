template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::begin ( )
{
    return static_cast<container&>(self).begin();
}

template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::begin ( ) const
{
    return static_cast<const container&>(self).begin();
}

template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::end ( )
{
    return static_cast<container&>(self).end();
}

template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::end ( ) const
{
    return static_cast<const container&>(self).end();
}

template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::size ( ) const
{
    return static_cast<const container&>(self).size();
}

template < class container, class type, class device >
constexpr auto container_interface<container,type,device>::empty ( ) const
{
    return static_cast<const container&>(self).empty();
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::adjacent_find ( ) const
    requires random_access_range<container> and equalable<type>
{
    auto pos = device::adjacent_find(begin(), end()) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::adjacent_find ( relation_between<type,type> auto rel ) const
    requires random_access_range<container>
{
    auto pos = device::adjacent_find(begin(), end(), rel) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr array<int> container_interface<container,type,device>::adjacent_where ( ) const
    requires random_access_range<container> and equalable<type>
{
    auto pos = array<int>();
    for ( auto it = begin(); (it = device::adjacent_find(it, end())) != end(); ++it )
        pos.push(it - begin() + 1);
    return pos;
}

template < class container, class type, class device >
constexpr array<int> container_interface<container,type,device>::adjacent_where ( relation_between<type,type> auto rel ) const
    requires random_access_range<container>
{
    auto pos = array<int>();
    for ( auto it = begin(); (it = device::adjacent_find(it, end(), rel)) != end(); ++it )
        pos.push(it - begin() + 1);
    return pos;
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::all ( const equalable_to<type> auto& val ) const
    requires forward_range<container>
{
    return device::all_of(begin(), end(), device::equal_to());
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::all ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::all_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::contains ( const equalable_to<type> auto& val ) const
    requires forward_range<container>
{
    return device::any_of(begin(), end(), device::equal_to());
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::contains ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::any_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::count ( const equalable_to<type> auto& val ) const
    requires forward_range<container>
{
    return device::count(begin(), end(), val);
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::count ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::count(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::exist ( const equalable_to<type> auto& val ) const
    requires forward_range<container>
{
    return device::any_of(begin(), end(), device::equal_to());
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::exist ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::any_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::find ( const equalable_to<type> auto& val ) const
    requires random_access_range<container>
{
    auto pos = device::find(begin(), end(), val) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr int container_interface<container,type,device>::find ( predicate_for<type> auto pred ) const
    requires random_access_range<container>
{
    auto pos = device::find_if(begin(), end(), pred) - begin() + 1;
    return pos <= size() ? pos : 0;
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::is_partitioned ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::is_partitioned(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::is_sorted ( ) const
    requires forward_range<container> and comparable<type>
{
    return device::is_sorted(begin(), end());
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::is_sorted ( relation_between<type,type> auto rel ) const
    requires forward_range<container>
{
    return device::is_sorted(begin(), end(), rel);
}

template < class container, class type, class device >
constexpr container_interface<container,type,device>::reference container_interface<container,type,device>::max ( )
    requires forward_range<container> and comparable<type>
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get max element (with empty() = true): container is empty");

    return *device::max_element(begin(), end());
}

template < class container, class type, class device >
constexpr container_interface<container,type,device>::const_reference container_interface<container,type,device>::max ( relation_between<type,type> auto rel ) const
    requires forward_range<container>
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get max element (with empty() = true): container is empty");

    return *device::max_element(begin(), end(), rel);
}

template < class container, class type, class device >
constexpr container_interface<container,type,device>::reference container_interface<container,type,device>::min ( )
    requires forward_range<container> and comparable<type>
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get min element (with empty() = true): container is empty");

    return *device::min_element(begin(), end());
}

template < class container, class type, class device >
constexpr container_interface<container,type,device>::const_reference container_interface<container,type,device>::min ( relation_between<type,type> auto rel ) const
    requires forward_range<container>
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot get min element (with empty() = true): container is empty");

    return *device::min_element(begin(), end(), rel);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::next_permutation ( )
    requires bidirectional_range<container> and comparable<type>
{
    device::next_permutation(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::next_permutation ( relation_between<type,type> auto rel )
    requires bidirectional_range<container>
{
    device::next_permutation(begin(), end(), rel);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::none ( const equalable_to<type> auto& val ) const
    requires forward_range<container>
{
    return device::none_of(begin(), end(), device::equal_to());
}

template < class container, class type, class device >
constexpr bool container_interface<container,type,device>::none ( predicate_for<type> auto pred ) const
    requires forward_range<container>
{
    return device::none_of(begin(), end(), pred);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::partial_sort ( int n )
    requires random_access_range<container> and comparable<type>
{
    if constexpr ( debug )
        if ( n < 0 or n > size() )
            throw value_error("cannot partial_sort container (with count = {}, size() = {}): count out of range", n, size());

    device::partial_sort(begin(), begin() + n, end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::partial_sort ( int n, relation_between<type,type> auto rel )
    requires random_access_range<container>
{
    if constexpr ( debug )
        if ( n < 0 or n > size() )
            throw value_error("cannot partial_sort container (with count = {}, size() = {}): count out of range", n, size());

    device::partial_sort(begin(), begin() + n, end(), rel);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::partition ( predicate_for<type> auto pred )
    requires forward_range<container>
{
    device::partition(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::prev_permutation ( )
    requires bidirectional_range<container> and comparable<type>
{
    device::prev_permutation(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::prev_permutation ( relation_between<type,type> auto rel )
    requires bidirectional_range<container>
{
    device::prev_permutation(begin(), end(), rel);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::remove ( const equalable_to<type> auto& val )
    requires forward_range<container>
{
    return static_cast<container&>(self).resize(device::remove(begin(), end(), val) - begin());
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::remove ( predicate_for<type> auto pred )
    requires forward_range<container>
{
    return static_cast<container&>(self).resize(device::remove_if(begin(), end(), pred) - begin());
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::reverse ( )
    requires bidirectional_range<container>
{
    device::reverse(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::rotate ( int n )
    requires forward_range<container>
{
    if constexpr ( debug )
        if ( n <= -size() or n >= size() )
            throw value_error("cannot rotate container (with step = {}, size() = {}): step out of range", n, size());

    n > 0 ? device::rotate(begin(), end  () - n, end()) :
            device::rotate(begin(), begin() - n, end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::stable_partition ( predicate_for<type> auto pred )
    requires bidirectional_range<container>
{
    device::stable_partition(begin(), end(), pred);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::stable_sort ( )
    requires random_access_range<container> and comparable<type>
{
    device::stable_sort(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::stable_sort ( relation_between<type,type> auto rel )
    requires random_access_range<container>
{
    device::stable_sort(begin(), end(), rel);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::sort ( )
    requires random_access_range<container> and comparable<type>
{
    device::sort(begin(), end());
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::sort ( relation_between<type,type> auto rel )
    requires random_access_range<container>
{    
    device::sort(begin(), end(), rel);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::unique ( )
    requires forward_range<container> and equalable<type>
{
    return static_cast<container&>(self).resize(device::unique(begin(), end()) - begin());
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::unique ( relation_between<type,type> auto rel )
    requires forward_range<container>
{
    return static_cast<container&>(self).resize(device::unique(begin(), end()) - begin(), rel);
}

template < class container, class type, class device >
constexpr array<int> container_interface<container,type,device>::where ( const equalable_to<type> auto& val ) const
    requires random_access_range<container>
{
    auto pos = array<int>();
    for ( auto it = begin(); (it = device::find(it, end(), val)) != end(); ++it )
        pos.push(it - begin() + 1);
    return pos;
}

template < class container, class type, class device >
constexpr array<int> container_interface<container,type,device>::where ( predicate_for<type> auto pred ) const
    requires random_access_range<container>
{
    auto pos = array<int>();
    for ( auto it = begin(); (it = device::find_if(it, end(), pred)) != end(); ++it )
        pos.push(it - begin() + 1);
    return pos;
}

template < class container, class type, class device >
constexpr type container_interface<container,type,device>::average ( ) const
    requires input_range<container> and default_initializable<type> and plusable<type> and dividable_to<type,int>
{
    if constexpr ( debug )
        if ( empty() )
            throw value_error("cannot calculate average (with empty() = true): container is empty");

    return sum() / size();
}

template < class container, class type, class device >
constexpr type container_interface<container,type,device>::sum ( ) const
    requires input_range<container> and default_initializable<type> and plusable<type>
{
    return device::accumulate(begin(), end(), type());
}

template < class container, class type, class device >
constexpr type container_interface<container,type,device>::product ( ) const
    requires input_range<container> and convertible_to<int,type> and multipliable<type>
{ 
    return device::accumulate(begin(), end(), type(1), device::multiplies());
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::fill ( const convertible_to<type> auto& val )
    requires forward_range<container>
{
    device::fill(begin(), end(), val);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::generate ( invocable_r<type> auto op )
    requires forward_range<container>
{
    device::generate(begin(), end(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::transform ( invocable_r<type,type> auto op )
    requires forward_range<container>
{
    device::transform(begin(), end(), begin(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::for_each ( invocable<reference> auto op )
    requires forward_range<container>
{
    device::for_each(begin(), end(), op);
    return static_cast<container&>(self);
}

template < class container, class type, class device >
constexpr const container& container_interface<container,type,device>::for_each ( invocable<value_type> auto op ) const
    requires forward_range<container>
{
    device::for_each(begin(), end(), op);
    return static_cast<const container&>(self);
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::replace ( const equalable_to<type> auto& old_val, const convertible_to<type> auto& new_val )
    requires forward_range<container>
{
    device::replace(begin(), end(), old_val, new_val);
    return static_cast<container&>(self);            
}

template < class container, class type, class device >
constexpr container& container_interface<container,type,device>::replace ( predicate_for<type> auto old_pred, const convertible_to<type> auto& new_val )
    requires forward_range<container>
{
    device::replace_if(begin(), end(), old_pred, new_val);
    return static_cast<container&>(self);  
}