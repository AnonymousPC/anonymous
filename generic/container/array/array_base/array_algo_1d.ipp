#pragma once

#include "../array_class/array_1d.hpp"
#include "../array_class/inplace_array.hpp"

#define templates            template < class container, class value_type, class iterate_type, int dim > requires ( dim == 1 )
#define array_algo           array_algo<container,value_type,iterate_type,dim>
#define derive_of_self       static_cast<container&>(self)
#define const_derive_of_self static_cast<const container&>(self)
#define result_type invoke_result<decltype(op),iterate_type>

// Abbreviation

templates
constexpr int array_algo::size ( ) const
{
    return size();
}

templates
constexpr bool array_algo::empty ( ) const
{
    return empty();
}

templates
constexpr decltype(auto) array_algo::begin ( )
{
    return derive_of_self.begin();
}

templates
constexpr decltype(auto) array_algo::begin ( ) const
{
    return begin();
}

templates
constexpr decltype(auto) array_algo::end ( )
{
    return derive_of_self.end();
}

templates
constexpr decltype(auto) array_algo::end ( ) const
{
    return end();
}

// N-dimension

templates
constexpr int array_algo::dimension ( )
{
    return 1;
}

templates
[[nodiscard]]
constexpr array<int> array_algo::shape ( ) const
{
    return array<int> { size() };
}

templates
constexpr auto array_algo::tuple_shape ( ) const
{
    return array_coordinate<1> ( size() );
}

// Views

templates
constexpr decltype(auto) array_algo::operator [] ( int pos )
{
    return derive_of_self [pos];
}

templates
constexpr decltype(auto) array_algo::operator [] ( int pos ) const
{
    return const_derive_of_self [pos];
}

templates
constexpr auto array_algo::operator [] ( int from, int to )
{
    return array_range_view ( derive_of_self, from, to );
}

templates
constexpr const auto array_algo::operator [] ( int from, int to ) const
{
    return array_range_view ( const_cast<container&>(const_derive_of_self), from, to );
}

templates
constexpr auto array_algo::operator [] ( int from, int to, int step )
{
    return array_range_view ( derive_of_self, from, to, step );
}

templates
constexpr const auto array_algo::operator [] ( int from, int to, int step ) const
{
    return array_range_view ( const_cast<container&>(const_derive_of_self), from, to, step );
}

templates
constexpr auto array_algo::operator [] ( unary_pred<value_type> auto pred )
{
    return array_filter_view ( derive_of_self, pred );
}

templates
constexpr const auto array_algo::operator [] ( unary_pred<value_type> auto pred ) const
{
    return array_filter_view ( const_cast<container&>(const_derive_of_self), pred );
}

templates
constexpr auto array_algo::reshape ( int_type auto... args )
    requires ( sizeof...(args) >= 2 )
{
    #if debug
        if ( size() != ( ... * args ) )
            throw value_error("cannot reshape array of size {} into shape {}", size(), array{args...});
    #endif

    return array_reshape_view<container,sizeof...(args)> ( derive_of_self, { args... } );
}


templates
constexpr const auto array_algo::reshape ( int_type auto... args ) const
    requires ( sizeof...(args) >= 2 )
{
    #if debug
        if ( size() != ( ... * args ) )
            throw value_error("cannot reshape array of size {} into shape {}", size(), array{args...});
    #endif

    return array_reshape_view<container,sizeof...(args)> ( const_cast<container&>(const_derive_of_self), { args... } );
}

templates
template < class type2 >
constexpr const auto& array_algo::as_type ( ) const
    requires std::same_as<value_type,type2>
{
    return const_derive_of_self;
}

templates
template < class type2 >
constexpr const auto array_algo::as_type ( ) const
    requires ( not std::same_as<value_type,type2> ) but std::convertible_to<value_type,type2>
{
    return container_view<container,type2> ( const_cast<container&>(const_derive_of_self) );
}




// Memory operation

templates
constexpr container& array_algo::clear ( )
    requires ( not is_view )
{
    return derive_of_self.resize(0);
}

templates
constexpr container& array_algo::erase ( int from, int to )
    requires ( not is_view )
{
    int pos_1 = from >  0 ? from otherwise from + size() + 1;
    int pos_2 = to   >= 0 ? to   otherwise to   + size() + 1;

    #if debug
        if ( ( ( pos_1 < 1 or pos_1 > size() ) or
               ( pos_2 < 1 or pos_2 > size() ) )
        and not // Except for below:
             ( pos_1 == pos_2 + 1 and ( pos_1 == size() + 1 or pos_2 == 0 ) ) )
            throw index_error("index [{},{}] is out of range with size {}", from, to, size());
    #endif

    int erase_len = pos_2 - pos_1 + 1;

    std::move_backward ( begin() + pos_2, end(), end() - erase_len );
    return derive_of_self.resize ( size() - erase_len );
}

templates
constexpr container& array_algo::insert ( aux::container_dim_range<int,0,1> auto pos, aux::container_dim_range<value_type,0,1> auto item, aux::container_dim_range<value_type,0,1> auto... args )
    requires ( not is_view )
{
    if constexpr ( std::convertible_to<decltype(pos),int> )
    {
        #if debug
            if ( pos < -size() or pos == 0 or pos > size() + 1 )
                throw index_error("index {} is out of range with size {}", pos, size());
        #endif

        int step = [&] { if constexpr ( std::convertible_to<decltype(item),value_type> ) return 1; else return item.size(); } ();

        if ( pos < 0 )
            pos += size() + 1;

        if constexpr ( std::convertible_to<decltype(item),value_type> )
        {
            insert_aux ( pos, 1 );
            self[pos] = std::move ( item );
        }
        else
        {
            insert_aux ( pos, item.size() );
            std::move ( item.begin(), item.end(), begin() + pos - 1 );
        }

        if constexpr ( sizeof...(args) >= 1 )
            return insert ( pos + step, std::forward<decltype(args)>(args)... );
        else
            return derive_of_self;
    }

    else
    {
        pos.each ( [&] ( int& p ) { if ( p < 0 ) p += ( size() + 1 ); } )
           .sort ();

        #if debug
            if ( pos.exist ( [&] ( int p ) { return p < 1 or p > size(); } ) )
                throw index_error("index {} is out of range with size {}", pos, size());
            if ( pos.adjacent_find() != 0 )
                throw index_error("index {} is not unique", pos);
        #endif

        auto items = container().push(std::move(item), std::forward<decltype(args)>(args)...);

        for ( int each_pos in pos )
        {
            insert ( each_pos, items );
            pos.each ( [&] ( int& p ) { p += items.size(); } );
        }

        return derive_of_self;
    }
}

templates
constexpr container& array_algo::push ( aux::container_dim_range<value_type,0,1> auto item, aux::container_dim_range<value_type,0,1> auto... args )
    requires ( not is_view )
{
    if constexpr ( std::convertible_to<decltype(item),value_type> )
    {
        derive_of_self.resize ( size() + 1 );
        self[-1] = std::move ( item );
    }
    else
    {
        derive_of_self.resize ( size() + item.size() );
        std::move ( item.begin(), item.end(), end() - item.size() );
    }

    if constexpr ( sizeof...(args) >= 1 )
        return push ( std::forward<decltype(args)>(args)... );
    else
        return derive_of_self;
}

templates
constexpr container& array_algo::pop ( )
    requires ( not is_view )
{
    return pop(-1);
}

templates
constexpr container& array_algo::pop ( aux::container_dim_range<int,0,1> auto pos, aux::container_dim_range<int,0,1> auto... args )
    requires ( not is_view )
{
    if constexpr ( sizeof...(args) == 0 )
        if constexpr ( std::convertible_to<decltype(pos),int> )
        {
            #if debug
                if ( pos < -size() or pos == 0 or pos > size() )
                    throw index_error("index {} is out of range with size {}", pos, size());
            #endif

            if ( pos < 0 )
                pos += ( size() + 1 );

            std::move ( begin() + pos, end(), begin() + pos - 1 ); // Cannot be paralelled.
            return derive_of_self.resize ( size() - 1 );
        }

        else
        {
            pos.each ( [&] ( int& p ) { if ( p < 0 ) p += ( size() + 1 ); } )
               .sort ();

            #if debug
                if ( pos.exist ( [&] ( int p ) { return p < 1 or p > size(); } ) )
                    throw index_error("index {} is out of range with size {}", pos, size());
                if ( pos.adjacent_find() != 0 )
                    throw index_error("index {} is not unique", pos);
            #endif

            auto pred = [&] ( const value_type& val ) { return pos.contains ( &val - &self[1] + 1 ); };
            return derive_of_self.resize ( std::remove_if ( begin(), end(), pred ) - begin() );
        }

    else
        return derive_of_self.pop ( array<int>().push(std::move(pos), std::forward<decltype(args)>(args)...) );
}


// Linear algorithm

templates
constexpr int array_algo::adjacent_find ( ) const
    requires equalable<value_type>
{
    int pos = std::adjacent_find ( begin(), end() ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr int array_algo::adjacent_find ( binary_pred<iterate_type> auto pred ) const
{
    int pos = std::adjacent_find ( begin(), end(), pred ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr array<int> array_algo::adjacent_where ( ) const
    requires equalable<value_type>
{
    array<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::adjacent_find ( it, end() );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}

templates
constexpr array<int> array_algo::adjacent_where ( binary_pred<iterate_type> auto pred ) const
{
    array<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::adjacent_find ( it, end(), pred );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}


templates
constexpr bool array_algo::all ( const equalable_to<iterate_type> auto& val ) const
{
    return std::all_of ( begin(), end(), [&] ( const auto& item ) { return item == val; } );
}


templates
constexpr bool array_algo::all ( unary_pred<iterate_type> auto pred ) const
{
    return std::all_of ( begin(), end(), pred );
}

templates
constexpr bool array_algo::contains ( const equalable_to<iterate_type> auto& val ) const
{
    return std::any_of ( begin(), end(), [&] ( const auto& item ) { return item == val; } );
}


templates
constexpr bool array_algo::contains ( unary_pred<iterate_type> auto pred ) const
{
    return std::any_of ( begin(), end(), pred );
}

templates
constexpr int array_algo::count ( const equalable_to<iterate_type> auto& val ) const
{
    return std::count ( begin(), end(), val );
}


templates
constexpr int array_algo::count ( unary_pred<iterate_type> auto pred ) const
{
    return std::count_if ( begin(), end(), pred );
}

templates
constexpr bool array_algo::exist ( const equalable_to<iterate_type> auto& val ) const
{
    return std::any_of ( begin(), end(), [&] ( const auto& item ) { return item == val; } );
}


templates
constexpr bool array_algo::exist ( unary_pred<iterate_type> auto pred ) const
{
    return std::any_of ( begin(), end(), pred );
}

templates
constexpr int array_algo::find ( const equalable_to<iterate_type> auto& val ) const
{
    int pos = std::find ( begin(), end(), val ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr int array_algo::find ( unary_pred<iterate_type> auto pred ) const
{
    int pos = std::find_if ( begin(), end(), pred ) - begin() + 1;
    return pos <= size() ? pos otherwise 0;
}

templates
constexpr bool array_algo::is_partitioned ( unary_pred<iterate_type> auto pred ) const
{
    return std::is_partitioned ( begin(), end(), pred );
}

templates
constexpr bool array_algo::is_sorted ( ) const
    requires comparable<value_type>
{
    return std::is_sorted ( begin(), end() );
}

templates
constexpr bool array_algo::is_sorted ( binary_pred<iterate_type> auto pred ) const
{
    return std::is_sorted ( begin(), end(), pred );
}

templates
constexpr const iterate_type& array_algo::max ( ) const
    requires comparable<value_type>
{
    #if debug
        if ( empty() )
            throw value_error("get max() from empty array");
    #endif

    return *std::max_element ( begin(), end() );
}

templates
constexpr const iterate_type& array_algo::max ( binary_pred<iterate_type> auto pred ) const
{
    #if debug
        if ( empty() )
            throw value_error("get max() from empty array");
    #endif

    return *std::max_element ( begin(), end(), pred );
}

templates
constexpr const iterate_type& array_algo::min ( ) const
    requires comparable<value_type>
{
    #if debug
        if ( empty() )
            throw value_error("get min() from empty array");
    #endif

    return *std::min_element ( begin(), end() );
}

templates
constexpr const iterate_type& array_algo::min ( binary_pred<iterate_type> auto pred ) const
{
    #if debug
        if ( empty() )
            throw value_error("get min() from empty array");
    #endif

    return *std::min_element ( begin(), end(), pred );
}

templates
constexpr container& array_algo::next_permutation ( )
    requires comparable<value_type>
{
    std::next_permutation ( begin(), end() );
    return derive_of_self;
}

templates
constexpr container& array_algo::next_permutation ( binary_pred<iterate_type> auto pred )
{
    std::next_permutation ( begin(), end(), pred );
    return derive_of_self;
}

templates
constexpr bool array_algo::none ( const equalable_to<iterate_type> auto& val ) const
{
    return std::none_of ( begin(), end(), [&] ( const value_type& item ) { return item == val; } );
}

templates
constexpr bool array_algo::none ( unary_pred<iterate_type> auto pred ) const
{
    return std::none_of ( begin(), end(), pred );
}

templates
constexpr container& array_algo::partial_sort ( int len )
    requires comparable<value_type>
{
    #if debug
        if ( len < 0 or len > size() )
            throw value_error("partial_sort {} elements is out of range with size {}", len, size());
    #endif
    std::partial_sort ( begin(), begin() + len, end() );
    return derive_of_self;
}

templates
constexpr container& array_algo::partial_sort ( int len, binary_pred<iterate_type> auto pred )
{
    #if debug
        if ( len < 0 or len > size() )
            throw value_error("partial_sort {} elements is out of range with size {}", len, size());
    #endif
    std::partial_sort ( begin(), begin() + len, end(), pred );
    return derive_of_self;
}

templates
constexpr container& array_algo::partition ( unary_pred<iterate_type> auto pred )
{
    std::partition ( begin(), end(), pred );
    return derive_of_self;
}

templates
constexpr container& array_algo::prev_permutation ( )
    requires comparable<value_type>
{
    std::prev_permutation ( begin(), end() );
    return derive_of_self;
}

templates
constexpr container& array_algo::prev_permutation ( binary_pred<iterate_type> auto pred )
{
    std::next_permutation ( begin(), end(), pred );
    return derive_of_self;
}

templates
constexpr container& array_algo::remove ( const equalable_to<iterate_type> auto& val )
    requires ( not is_view )
{
    return derive_of_self.resize ( std::remove ( begin(), end(), val ) - begin() );
}

templates
constexpr container& array_algo::remove ( unary_pred<iterate_type> auto pred )
    requires ( not is_view )
{
    return derive_of_self.resize ( std::remove_if ( begin(), end(), pred ) - begin() );
}

templates
constexpr container& array_algo::reverse ( )
{
    std::reverse ( begin(), end() );
    return derive_of_self;
}

templates
constexpr int array_algo::right_adjacent_find ( ) const
    requires equalable<value_type>
{
    for ( auto it = end() - 1; it != begin(); it-- )
        if ( *it == *(it-1) )
            return it - begin();
    return 0;
}

templates
constexpr int array_algo::right_adjacent_find ( binary_pred<iterate_type> auto pred ) const
{
    for ( auto it = end() - 1; it != begin(); it-- )
        if ( pred ( *it, *(it-1) ) )
            return it - begin();
    return 0;
}

templates
constexpr int array_algo::right_find ( const equalable_to<iterate_type> auto& val ) const
{
    for ( auto it = end() - 1; it != begin() - 1; it-- )
        if ( *it == val )
            return it - begin() + 1;
    return 0;
}

templates
constexpr int array_algo::right_find ( unary_pred<iterate_type> auto pred ) const
{
    for ( auto it = end() - 1; it != begin() - 1; it-- )
        if ( pred ( *it ) )
            return it - begin() + 1;
    return 0;
}

templates
constexpr container& array_algo::rotate ( int step )
{
    if ( step > 0 )
        std::rotate ( begin(), begin() + size() - step, end() );
    else if ( step < 0 )
        std::rotate ( begin(), begin()          - step, end() );

    return derive_of_self;
}

templates
constexpr container& array_algo::sort ( )
    requires comparable<value_type>
{
    std::sort ( begin(), end() );
    return derive_of_self;
}

templates
constexpr container& array_algo::sort ( binary_pred<iterate_type> auto pred )
{
    std::sort ( begin(), end(), pred );
    return derive_of_self;
}

templates
constexpr container& array_algo::unique ( )
    requires ( not is_view ) and equalable<value_type>
{
    return derive_of_self.resize ( std::unique ( begin(), end() ) - begin() );
}

templates
constexpr container& array_algo::unique ( binary_pred<iterate_type> auto pred )
    requires ( not is_view )
{
    return derive_of_self.resize ( std::unique ( begin(), end(), pred ) - begin() );
}

templates
constexpr array<int> array_algo::where ( const equalable_to<iterate_type> auto& val ) const
{
    array<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::find ( it, end(), val );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}

templates
constexpr array<int> array_algo::where ( unary_pred<iterate_type> auto pred ) const
{
    array<int> poses;
    for ( auto it = begin(); it != end() + 1; it++ )
    {
        it = std::find_if ( it, end(), pred );
        if ( it != end() )
            poses.push ( it - begin() + 1 );
    }

    return poses;
}

templates
constexpr auto array_algo::average ( ) const
    requires std::default_initializable<value_type> and addable<value_type> and dividable_to<value_type,int>
{
    return sum() / size();
}

templates
constexpr auto array_algo::average ( std::invocable<iterate_type> auto op ) const
    requires std::default_initializable<result_type> and addable<result_type> and dividable_to<result_type,int>
{
    return sum(op) / size();
}

templates
constexpr auto array_algo::sum ( ) const
    requires std::default_initializable<value_type> and addable<value_type>
{
    return std::accumulate ( begin(), end(), iterate_type() );
}

templates
constexpr auto array_algo::sum ( std::invocable<iterate_type> auto op ) const
    requires std::default_initializable<result_type> and addable<result_type>
{
    return std::accumulate ( begin(), end(), result_type(), [&] ( const auto& a, const auto& b ) { return a + op(b); } );
}

templates
constexpr auto array_algo::product ( ) const
    requires std::convertible_to<int,value_type> and multipliable<value_type>
{
    return std::accumulate ( begin(), end(), iterate_type(1), [] ( const auto& a, const auto& b ) { return a * b; } );
}

templates
constexpr auto array_algo::product ( std::invocable<iterate_type> auto op ) const
    requires std::convertible_to<int,result_type> and multipliable<result_type>
{
    return std::accumulate ( begin(), end(), result_type(1), [&] ( const auto& a, const auto& b ) { return a * op(b); } );
}

templates
constexpr container& array_algo::each ( std::invocable<iterate_type&> auto op )
{
    std::for_each ( begin(), end(), op );
    return derive_of_self;
}

templates
constexpr const container& array_algo::each ( std::invocable<iterate_type> auto op ) const
{
    std::for_each ( begin(), end(), op );
    return const_derive_of_self;
}

templates
constexpr container& array_algo::fill ( const std::convertible_to<iterate_type> auto& val )
{
    std::fill ( begin(), end(), val );
    return derive_of_self;
}

templates
constexpr container& array_algo::generate ( function_type<iterate_type()> auto gen )
{
    std::generate ( begin(), end(), gen );
    return derive_of_self;
}

templates
constexpr container& array_algo::transform ( unary_op<iterate_type> auto op )
{
    std::transform ( begin(), end(), begin(), op );
    return derive_of_self;
}

templates
constexpr container& array_algo::replace ( const equalable_to<iterate_type> auto& val1, const std::convertible_to<iterate_type> auto& val2 )
{
    std::replace ( begin(), end(), val1, val2 );
    return derive_of_self;
}

templates
constexpr container& array_algo::replace ( unary_pred<iterate_type> auto pred, const std::convertible_to<iterate_type> auto& val )
{
    std::replace_if ( begin(), end(), pred, val );
    return derive_of_self;
}


// Auxiliary

templates
constexpr container& array_algo::insert_aux ( int pos, int step )
{
    if ( pos < 0 )
        pos += ( size() + 1 );

    derive_of_self.resize ( size() + step );

    std::move_backward ( begin() + pos - 1, end() - step, end() ); // Cannot be paralelled.

    return derive_of_self;
}





#undef templates
#undef array_algo
#undef derive_of_self
#undef const_derive_of_self