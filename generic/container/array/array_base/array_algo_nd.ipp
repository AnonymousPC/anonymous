#pragma once

#define templates             template < class container, class value_type, class iterate_type, int dim > requires ( dim >= 2 )
#define template_int_axis     template < int axis > requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
#define array_algo            array_algo<container,value_type,iterate_type,dim>
#define derive_of_self        static_cast<container&>(self)
#define const_derive_of_self  static_cast<const container&>(self)
#define result_type           typename std::invoke_result<decltype(op),iterate_type>::type

// Abbreviation

templates
constexpr int array_algo::row ( ) const
{
    return const_derive_of_self.row();
}

templates
constexpr int array_algo::size ( ) const
{
    return const_derive_of_self.size();
}

templates
constexpr bool array_algo::empty ( ) const
{
    return const_derive_of_self.empty();
}

templates
constexpr decltype(auto) array_algo::begin ( )
{
    return derive_of_self.begin();
}

templates
constexpr decltype(auto) array_algo::begin ( ) const
{
    return const_derive_of_self.begin();
}

templates
constexpr decltype(auto) array_algo::end ( )
{
    return derive_of_self.end();
}

templates
constexpr decltype(auto) array_algo::end ( ) const
{
    return const_derive_of_self.end();
}

// N-dimension

templates
constexpr int array_algo::dimension ( )
{
    return dim;
}

templates
[[nodiscard]]
constexpr array<int> array_algo::shape ( ) const
{
    if ( not empty() )
        return array<int> { const_derive_of_self.row() } .push ( self[1].shape() );
    else
        return array<int> { const_derive_of_self.row() } .push ( array<int> ( dim - 1 ) );
}

templates
constexpr auto array_algo::tuple_shape ( ) const
{
    let shp = array_coordinate<dimension()>();
    tuple_shape_aux ( shp, self );
    return shp;
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
constexpr auto array_algo::operator [] ( pair<int> span1, pair<int> span2 )
    requires ( dimension() == 2 )
{
    return array_span_view ( derive_of_self, span1, span2 );
}

templates
constexpr const auto array_algo::operator [] ( pair<int> span1, pair<int> span2 ) const
    requires ( dimension() == 2 )
{
    return array_span_view ( const_cast<container&>(const_derive_of_self), span1, span2 );
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
    requires ( sizeof...(args) >= 1 )
{
    #if debug
        if ( size() != ( ... * args ) )
            throw index_error("cannot reshape array of shape {} into shape {}", shape(), array{args...});
    #endif

    return array_reshape_view<container,sizeof...(args)> ( derive_of_self, { args... } );
}

templates
constexpr const auto array_algo::reshape ( int_type auto... args ) const
    requires ( sizeof...(args) >= 1 )
{
    #if debug
        if ( size() != ( ... * args ) )
            throw index_error("cannot reshape array of shape {} into shape {}", shape(), array{args...});
    #endif

    return array_reshape_view<container,sizeof...(args)> ( const_cast<container&>(const_derive_of_self), { args... } );
}

templates
constexpr auto array_algo::flatten ( )
{
    return array_flatten_view ( derive_of_self );
}

templates
constexpr const auto array_algo::flatten ( ) const
{
    return array_flatten_view ( const_cast<container&>(const_derive_of_self) ) ;
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

// Views (axis)

templates
template_int_axis
constexpr decltype(auto) array_algo::view_by_axis ( )
    requires ( axis == 1 or axis == -dimension() )
{
    return static_cast<container::base&> ( derive_of_self );
}

templates
template_int_axis
constexpr decltype(auto) array_algo::view_by_axis ( ) const
    requires ( axis == 1 or axis == -dimension() )
{
    return static_cast<const container::base&> ( const_cast<container&>(const_derive_of_self) );
}

templates
template_int_axis
constexpr auto array_algo::view_by_axis ( )
    requires ( axis != 1 and axis != -dimension() )
{
    if constexpr ( axis > 0 )
        return array_axis_view<container,axis>               ( derive_of_self );
    else
        return array_axis_view<container,axis+dimension()+1> ( derive_of_self );
}

templates
template_int_axis
constexpr const auto array_algo::view_by_axis ( ) const
    requires ( axis != 1 and axis != -dimension() )
{
    if constexpr ( axis > 0 )
        return array_axis_view<container,axis>               ( const_cast<container&>(const_derive_of_self) );
    else
        return array_axis_view<container,axis+dimension()+1> ( const_cast<container&>(const_derive_of_self) );
}


// Memory Operation

templates
template_int_axis
constexpr container& array_algo::clear ( )
    requires ( not is_view )
{
    derive_of_self.base::clear();
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::erase ( int from, int to )
    requires ( not is_view )
{
    // TODO: throw index_error while pos is_container.

    if constexpr ( axis == 1 or axis == -dim )
        derive_of_self.base::erase ( from, to );

    else
        for ( int i in range ( row() ) )
            if constexpr ( derive_of_self.dimension() == 2 )
                derive_of_self.base::operator[](i).erase ( from, to );
            else
                if constexpr ( axis > 0 )
                    derive_of_self.base::operator[](i).template erase<axis-1> ( from, to );
                else
                    derive_of_self.base::operator[](i).template erase<axis>   ( from, to );

    if ( size() == 0 )
        clear();

    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::insert ( aux::container_dim_range<int,0,1> auto pos, aux::container_dim_range<value_type,dim-1,dim> auto arr, aux::container_dim_range<value_type,dim-1,dim> auto... args )
    requires ( not is_view )
{
    if constexpr ( not std::convertible_to<decltype(pos),int> )
        pos.each ( [&] ( int& p ) { if ( p < 0 ) p += ( size() + 1 ); } )
           .sort ();

    #if debug
        if constexpr ( std::convertible_to<decltype(pos),int> )
        {
            if ( pos < -shape()[axis] or pos == 0 or pos > shape()[axis] + 1 )
                throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), axis);
        }
        else
        {
            if ( pos.exist( [&] ( int p ) { return p < 1 or p > shape()[axis] + 1; } ) )
                throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), axis);
            if ( pos.adjacent_find() != 0 )
                throw index_error("index {} is not unique", pos);
        }

        if constexpr ( arr.dimension() == dim - 1 )
        {
            if ( not empty() and shape().pop(axis) != arr.shape() )
                throw value_error("cannot insert array of shape {} into array of shape {} axis {}", arr.shape(), shape(), axis);
        }
        else
            if ( not empty() and shape().pop(axis) != arr.shape().pop(axis) )
                throw value_error("cannot insert array of shape {} into array of shape {} axis {}", arr.shape(), shape(), axis);
    #endif

    [[maybe_unused]] int step = [&] { if constexpr ( arr.dimension() == dim - 1 ) return 1; else return arr.shape()[axis]; } ();
    [[maybe_unused]] let base = []  ( auto& a )        -> decltype(auto) { if constexpr ( a.dimension() == dim - 1 ) return a; else return static_cast<typename std::decay<decltype(a)>::type::base&>(a); };
    [[maybe_unused]] let get  = []  ( auto& a, int i ) -> decltype(auto) { return a[i]; };

    if constexpr ( axis == 1 or axis == -dim )
        derive_of_self.base::insert ( pos, std::move(base(arr)), std::forward<decltype(base(args))>(base(args))... );

    else
    {
        if ( empty() )
        {
            if constexpr ( arr.dimension() == 1 )
                derive_of_self.base::resize ( arr.size() );
            else
                derive_of_self.base::resize ( arr.row() );
        }

        for ( int i in range ( row() ) )
            if constexpr ( derive_of_self.dimension() == 2 )
                derive_of_self.base::operator[](i).insert ( pos, std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
            else
                if constexpr ( axis > 0 )
                    derive_of_self.base::operator[](i).template insert<axis-1> ( pos, std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
                else
                    derive_of_self.base::operator[](i).template insert<axis>   ( pos, std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
    }

    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::push ( aux::container_dim_range<value_type,dim-1,dim> auto arr, aux::container_dim_range<value_type,dim-1,dim> auto... args )
    requires ( not is_view )
{
    #if debug
        if constexpr ( arr.dimension() == dim - 1 )
        {
            if ( not empty() and shape().pop(axis) != arr.shape() )
                throw value_error("cannot push array of shape {} into array of shape {} axis {}", arr.shape(), shape(), axis);
        }
        else
            if ( not empty() and shape().pop(axis) != arr.shape().pop(axis) )
                throw value_error("cannot push array of shape {} into array of shape {} axis {}", arr.shape(), shape(), axis);
    #endif

    [[maybe_unused]] let base = [] ( auto& a )        -> decltype(auto) { if constexpr ( a.dimension() == dim - 1 ) return a; else return static_cast<typename std::decay<decltype(a)>::type::base&>(a); };
    [[maybe_unused]] let get  = [] ( auto& a, int i ) -> decltype(auto) { return a[i]; };

    if constexpr ( axis == 1 or axis == -dim )
        derive_of_self.base::push ( std::move(base(arr)), std::forward<decltype(base(args))>(base(args))... );

    else
    {
        if ( empty() )
        {
            if constexpr ( arr.dimension() == 1 )
                derive_of_self.base::resize ( arr.size() );
            else
                derive_of_self.base::resize ( arr.row() );
        }

        for ( int i in range ( row() ) )
            if constexpr ( derive_of_self.dimension() == 2 )
                derive_of_self.base::operator[](i).push ( std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
            else
                if constexpr ( axis > 0 )
                    derive_of_self.base::operator[](i).template push<axis-1> ( std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
                else
                    derive_of_self.base::operator[](i).template push<axis>   ( std::move(arr[i]), std::forward<decltype(get(args,i))>(get(args,i))... );
    }

    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::pop ( )
    requires ( not is_view )
{
    return pop<axis>(-1);
}

templates
template_int_axis
constexpr container& array_algo::pop ( aux::container_dim_range<int,0,1> auto pos, aux::container_dim_range<int,0,1> auto... args )
    requires ( not is_view )
{
    if constexpr ( not std::convertible_to<decltype(pos),int> )
        pos.each ( [&] ( int& p ) { if ( p < 0 ) p += ( size() + 1 ); } )
           .sort ();

    #if debug
        if constexpr ( std::convertible_to<decltype(pos),int> )
        {
            if ( pos < -shape()[axis] or pos == 0 or pos > shape()[axis] )
                throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), axis);
        }
        else
        {
            if ( pos.exist( [&] ( int p ) { return p < 1 or p > shape()[axis] + 1; } ) )
                throw index_error("index {} is out of range with shape {} axis {}", pos, shape(), axis);
            if ( pos.adjacent_find() != 0 )
                throw index_error("index {} is not unique", pos);
        }
    #endif

    if constexpr ( axis == 1 or axis == -dim )
        derive_of_self.base::pop ( pos );

    else
        for ( int i in range ( row() ) )
            if constexpr ( derive_of_self.dimension() == 2 )
                derive_of_self.base::operator[](i).pop ( pos, args... );
            else
                if constexpr ( axis > 0 )
                    derive_of_self.base::operator[](i).template pop<axis-1> ( pos, args... );
                else
                    derive_of_self.base::operator[](i).template pop<axis>   ( pos, args... );

    if ( size() == 0 )
        clear();

    return derive_of_self;
}

// Linear algorithm

templates
template_int_axis
constexpr int array_algo::adjacent_find ( ) const
    requires equalable<value_type>
{
    return self.view_by_axis<axis>().adjacent_find();
}

templates
template_int_axis
constexpr int array_algo::adjacent_find ( binary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().adjacent_find(pred);
}

templates
template_int_axis
constexpr array<int> array_algo::adjacent_where ( ) const
    requires equalable<value_type>
{
    return self.view_by_axis<axis>().adjacent_where();
}

templates
template_int_axis
constexpr array<int> array_algo::adjacent_where ( binary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().adjacent_where(pred);
}

templates
template_int_axis
constexpr bool array_algo::all ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().all(val);
}

templates
template_int_axis
constexpr bool array_algo::all ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().all(pred);
}

templates
template_int_axis
constexpr bool array_algo::contains ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().contains(val);
}

templates
template_int_axis
constexpr bool array_algo::contains ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().contains(pred);
}

templates
template_int_axis
constexpr int array_algo::count ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().count(val);
}

templates
template_int_axis
constexpr int array_algo::count ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().count(pred);
}

templates
template_int_axis
constexpr bool array_algo::exist ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().exist(val);
}

templates
template_int_axis
constexpr bool array_algo::exist ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().exist(pred);
}

templates
template_int_axis
constexpr int array_algo::find ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().find(val);
}

templates
template_int_axis
constexpr int array_algo::find ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().find(pred);
}

templates
template_int_axis
constexpr bool array_algo::is_partitioned ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().is_partitioned(pred);
}

templates
template_int_axis
constexpr bool array_algo::is_sorted ( ) const
    requires comparable<value_type>
{
    return self.view_by_axis<axis>().is_sorted();
}

templates
template_int_axis
constexpr bool array_algo::is_sorted ( binary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().is_sorted(pred);
}

templates
template_int_axis
constexpr decltype(auto) array_algo::max ( ) const
    requires comparable<value_type>
{
    if constexpr ( axis == 1 or axis == -dimension() )
        return self.view_by_axis<axis>().max();
    else
    {
        let view = self.view_by_axis<axis>();
        return *std::max_element ( view.begin(), view.end() );
    }
}

templates
template_int_axis
constexpr decltype(auto) array_algo::max ( binary_pred<iterate_type> auto pred ) const
{
    if constexpr ( axis == 1 or axis == -dimension() )
        return self.view_by_axis<axis>().max(pred);
    else
    {
        let view = self.view_by_axis<axis>();
        return *std::max_element ( view.begin(), view.end(), pred );
    }
}

templates
template_int_axis
constexpr decltype(auto) array_algo::min ( ) const
    requires comparable<value_type>
{
    if constexpr ( axis == 1 or axis == -dimension() )
        return self.view_by_axis<axis>().min();
    else
    {
        let view = self.view_by_axis<axis>();
        return *std::min_element ( view.begin(), view.end() );
    }
}

templates
template_int_axis
constexpr decltype(auto) array_algo::min ( binary_pred<iterate_type> auto pred ) const
{
    if constexpr ( axis == 1 or axis == -dimension() )
        return self.view_by_axis<axis>().min(pred);
    else
    {
        let view = self.view_by_axis<axis>();
        return *std::min_element ( view.begin(), view.end(), pred );
    }
}

templates
template_int_axis
constexpr container& array_algo::next_permutation ( )
    requires comparable<value_type>
{
    self.view_by_axis<axis>().next_permutation();
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::next_permutation ( binary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().next_permutation(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr bool array_algo::none ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().none(val);
}

templates
template_int_axis
constexpr bool array_algo::none ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().none(pred);
}

templates
template_int_axis
constexpr container& array_algo::partial_sort ( int len )
    requires comparable<value_type>
{
    self.view_by_axis<axis>().partial_sort(len);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::partial_sort ( int len, binary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().partial_sort(len,pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::partition ( unary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().partition(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::prev_permutation ( )
    requires comparable<value_type>
{
    self.view_by_axis<axis>().prev_permutation();
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::prev_permutation ( binary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().prev_permutation(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::remove ( const equalable_to<iterate_type> auto& val )
    requires ( not is_view )
{
    let view = self.view_by_axis<axis>();
    self.erase<axis> ( std::remove ( view.begin(), view.end(), val ) - view.begin() + 1, -1 );

    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::remove ( unary_pred<iterate_type> auto pred )
    requires ( not is_view )
{
    let view = self.view_by_axis<axis>();
    self.erase<axis> ( std::remove_if ( view.begin(), view.end(), pred ) - view.begin() + 1, -1 );

    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::reverse ( )
{
    self.view_by_axis<axis>().reverse();
    return derive_of_self;
}

templates
template_int_axis
constexpr int array_algo::right_adjacent_find ( ) const
    requires equalable<value_type>
{
    return self.view_by_axis<axis>().right_adjacent_find();
}

templates
template_int_axis
constexpr int array_algo::right_adjacent_find ( binary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().right_adjacent_find(pred);
}

templates
template_int_axis
constexpr int array_algo::right_find ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().right_find(val);
}

templates
template_int_axis
constexpr int array_algo::right_find ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().right_find(pred);
}

templates
template_int_axis
constexpr container& array_algo::rotate ( int step )
{
    self.view_by_axis<axis>().rotate(step);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::stable_partition ( const equalable_to<iterate_type> auto& val )
    requires comparable<value_type>
{
    self.view_by_axis<axis>().stable_partition(val);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::stable_partition ( unary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().stable_partition(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::stable_sort ( )
    requires comparable<value_type>
{
    self.view_by_axis<axis>().stable_sort();
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::stable_sort ( binary_pred<iterate_type> auto pred )
{
    self.view_by_axis<axis>().stable_sort(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::sort ( )
    requires comparable<value_type>
{
    if ( self.view_by_axis<axis>().is_sorted() )
        return derive_of_self; // For unknown reason its essential.

    self.view_by_axis<axis>().sort();
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::sort ( binary_pred<iterate_type> auto pred )
{
    if ( self.view_by_axis<axis>().is_sorted(pred) )
        return derive_of_self; // For unknown reason its essential.

    self.view_by_axis<axis>().sort(pred);
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::unique ( )
    requires ( not is_view ) and equalable<value_type>
{
    let view = self.view_by_axis<axis>();
    self.erase<axis> ( std::unique ( view.begin(), view.end() ) - view.begin() + 1, -1 );
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::unique ( binary_pred<iterate_type> auto pred )
    requires ( not is_view )
{
    let view = self.view_by_axis<axis>();
    self.erase<axis> ( std::unique ( view.begin(), view.end(), pred ) - view.begin() + 1, -1 );
    return derive_of_self;
}

templates
template_int_axis
constexpr array<int> array_algo::where ( const equalable_to<iterate_type> auto& val ) const
{
    return self.view_by_axis<axis>().where(val);
}

templates
template_int_axis
constexpr array<int> array_algo::where ( unary_pred<iterate_type> auto pred ) const
{
    return self.view_by_axis<axis>().where(pred);
}

templates
template_int_axis
constexpr auto array_algo::average ( ) const
    requires std::default_initializable<value_type> and addable<value_type> and dividable_to<value_type,int>
{
    return self.template sum<axis>() / self.tuple_shape().template get<axis>();
}

templates
template_int_axis
constexpr auto array_algo::average ( std::invocable<iterate_type> auto op ) const
    requires std::default_initializable<result_type> and addable<result_type> and dividable_to<result_type,int>
{
    return self.template sum<axis>(op) / self.tuple_shape().template get<axis>();
}

templates
template_int_axis
constexpr auto array_algo::sum ( ) const
    requires std::default_initializable<value_type> and addable<value_type>
{
    let view = self.view_by_axis<axis>();

    if constexpr ( dimension() == 2 )
        if constexpr ( axis == 1 or axis == -2 )
            return std::accumulate ( view.begin(), view.end(), array<value_type,dim-1>().resize(const_derive_of_self.column()) );
        else
            return std::accumulate ( view.begin(), view.end(), array<value_type,dim-1>().resize(const_derive_of_self.row   ()) );
    else
        return std::accumulate ( view.begin(), view.end(), array<value_type,dim-1>().resize(shape().pop(axis)) );
}

templates
template_int_axis
constexpr auto array_algo::sum ( std::invocable<iterate_type> auto op ) const
    requires std::default_initializable<result_type> and addable<result_type>
{
    let view = self.view_by_axis<axis>();
    return std::accumulate ( view.begin(), view.end(), result_type(), [&] ( const auto& a, const auto& b ) { return a + op(b); } );
}

templates
template_int_axis
constexpr auto array_algo::product ( std::invocable<iterate_type> auto op ) const
    requires std::convertible_to<int,result_type> and multipliable<result_type>
{
    let view = self.view_by_axis<axis>();
    return std::accumulate ( view.begin(), view.end(), result_type(1), [&] ( const auto& a, const auto& b ) { return a * op(b); } );
}

templates
template_int_axis
constexpr container& array_algo::each ( std::invocable<iterate_type&> auto op )
{
    self.view_by_axis<axis>().each ( op );
    return derive_of_self;
}

templates
template_int_axis
constexpr const container& array_algo::each ( std::invocable<iterate_type> auto op ) const
{
    self.view_by_axis<axis>().each ( op );
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::fill ( const std::convertible_to<iterate_type> auto& val )
{
    self.view_by_axis<axis>().fill ( val );
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::generate ( function_type<iterate_type()> auto gen )
{
    self.view_by_axis<axis>().generate ( gen );
    #if debug // generate() in axis 1 can change it's shape, which will cause potential inalignment.
        if constexpr ( axis == 1 )
            if ( not empty() )
                for ( int i in range ( row() - 1 ) )
                    if ( self[i].shape() != self[i+1].shape() )
                        throw value_error("generate array with lines (by axis {}) not aligned", axis);
    #endif
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::transform ( unary_op<iterate_type> auto op )
{
    self.view_by_axis<axis>().transform ( op );
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::replace ( const equalable_to<iterate_type> auto& val1, const std::convertible_to<iterate_type> auto& val2 )
{
    self.view_by_axis<axis>().replace ( val1, val2 );
    return derive_of_self;
}

templates
template_int_axis
constexpr container& array_algo::replace ( unary_pred<iterate_type> auto pred, const std::convertible_to<iterate_type> auto& val )
{
    self.view_by_axis<axis>().replace ( pred, val );
    return derive_of_self;
}


// Auxiliary

templates
constexpr void array_algo::tuple_shape_aux ( auto& shp, const auto& arr )
{
    if constexpr ( arr.dimension() == 1 )
        shp.template get<1>() = arr.size();
    else
        shp.template get<1>() = arr.row();

    if constexpr ( arr.dimension() >= 2 )
        if ( not arr.empty() )
            tuple_shape_aux ( shp.template get<2,-1>(), arr[1] );
}


#undef templates
#undef template_int_axis
#undef array_algo
#undef derive_of_self
#undef const_derive_of_self
#undef result_type