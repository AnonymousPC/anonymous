#pragma once

/// Class array_span_view

// Host

template < class container_type >
constexpr container_type& array_span_view<container_type>::host ( )
{
    return arr;
}

template < class container_type >
constexpr const container_type& array_span_view<container_type>::host ( ) const
{
    return arr;
}

// Core

template < class container_type >
constexpr array_span_view<container_type>::array_span_view ( container_type& init_arr, auto... init_idx )
    requires ( std::convertible_to<decltype(init_idx),pair<int>> and ... and ( sizeof...(init_idx) == container_type::dimension() ) )
    extends arr ( init_arr )
{
    let idx_abs = [&] ( auto&& func, const auto& shp, auto& p, auto&... args ) -> void
    {
        let row = shp.template get<1>();

        if ( p.key() < 0 )
            p.key() += ( row + 1 );
        if ( p.value() < 0 )
            p.value() += ( row + 1 );

        #if debug
            if ( ( ( p.key  () < 1 or p.key  () > row ) or
                   ( p.value() < 1 or p.value() > row ) )
            and not // Except for below:
                ( p.key() == p.value() + 1 and ( p.key() == 1 or p.value() == row ) ) )
                throw index_error("index {} is out of range with shape {}", array{init_idx...}, host().shape());
        #endif

        if constexpr ( sizeof...(args) >= 1 )
            return func ( func, shp.template get<2,-1>(), args... );
    };


    idx_abs ( idx_abs, host().tuple_shape(), init_idx... ); // Will throw idx_error in debug mode.

    let make_range = [] ( const pair<int>& p ) { return range ( p.key(), p.value() ); };
    idx = coor_type ( make_range ( init_idx )... );
}

template < class container_type >
constexpr array_span_view<container_type>::array_span_view ( container_type& init_arr, coor_type init_idx )
    extends arr ( init_arr ),
            idx ( std::move ( init_idx ) )
{

}

// Core

template < class container_type >
constexpr array_span_view<container_type>& array_span_view<container_type>::operator = ( const array_span_view& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right.host() or self.idx.template get<1>().min() < right.idx.template get<1>().min() ) // From different hosts, or from same host and first is before second.
        std::copy ( right.begin(), right.end(), self.begin() );
    else
        std::copy_backward ( right.begin(), right.end(), self.end() );

    return self;
}

template < class container_type >
constexpr array_span_view<container_type>& array_span_view<container_type>::operator = ( const container_type& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right ) // From different hosts.
        std::copy ( right.begin(), right.end(), begin() );

    // Else: from same host, which must be view == host()[{1,1,...,1},{-1,-1,...,-1}].

    return self;
}

template < class container_type >
constexpr array_span_view<container_type>& array_span_view<container_type>::operator = ( container_type&& right )
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot move array of shape {} into array_view of shape {}", right.shape(), self.shape());

        if ( &self.host() == &right ) // From same host, in which the view will be dangling.
            throw value_error("cannot move array into an array_view on itself");
    #endif

    std::move ( right.begin(), right.end(), begin() );
    if constexpr ( requires { right.clear(); } ) // As right might be array_fix_len or some other kind of view.
        right.clear();

    return self;
}

// Member

template < class container_type >
constexpr int array_span_view<container_type>::row ( ) const
    requires ( container_type::dimension() >= 2 )
{
    return idx.template get<1>().size();
}

template < class container_type >
constexpr int array_span_view<container_type>::column ( ) const
    requires ( container_type::dimension() == 2 )
{
    return idx.template get<2>().size();
}

template < class container_type >
constexpr int array_span_view<container_type>::size ( ) const
{
    if constexpr ( self.dimension() == 1 )
        return idx.template get<1>().size();
    else
        return idx.product ( [] ( const auto& a ) { return a.size(); } );
}

template < class container_type >
constexpr bool array_span_view<container_type>::empty ( ) const
{
    if constexpr ( self.dimension() == 1 )
        return idx.template get<1>().empty();
    else
        return idx.exist ( [] ( const auto& a ) { return a.empty(); } );
}

template < class container_type >
constexpr array_span_view<container_type>::iterator array_span_view<container_type>::begin ( )
{
    return iterator ( self, 1 );
}

template < class container_type >
constexpr array_span_view<container_type>::const_iterator array_span_view<container_type>::begin ( ) const
{
    return const_iterator ( self, 1 );
}

template < class container_type >
constexpr array_span_view<container_type>::iterator array_span_view<container_type>::end ( )
{
    if constexpr ( self.dimension() == 1 )
        return iterator ( self, size() + 1 );
    else
        return iterator ( self, row() + 1 );
}

template < class container_type >
constexpr array_span_view<container_type>::const_iterator array_span_view<container_type>::end ( ) const
{
    if constexpr ( self.dimension() == 1 )
        return const_iterator ( self, size() + 1 );
    else
        return const_iterator ( self, row() + 1 );
}

template < class container_type >
constexpr decltype(auto) array_span_view<container_type>::operator [] ( int pos )
    requires ( container_type::dimension() == 1 )
{
    return host()[idx.template get<1>()[pos]];
}

template < class container_type >
constexpr decltype(auto) array_span_view<container_type>::operator [] ( int pos ) const
    requires ( container_type::dimension() == 1 )
{
    return host()[idx.template get<1>()[pos]];
}

template < class container_type >
constexpr auto array_span_view<container_type>::operator [] ( int pos )
    requires ( container_type::dimension() >= 2 )
{
    return iterate_type ( host()[idx.template get<1>()[pos]], idx.template get<2,-1>() );
}

template < class container_type >
constexpr const auto array_span_view<container_type>::operator [] ( int pos ) const
    requires ( container_type::dimension() >= 2 )
{
    return iterate_type ( const_cast<container_type&>(host())[idx.template get<1>()[pos]], idx.template get<2,-1>() );
}



// Views

template < class container_type >
constexpr auto array_span_view<container_type>::operator [] ( pair<int> span1, pair<int> span2 )
    requires ( container_type::dimension() == 2 )
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]". Currently it is unsolved.
    return array_span_view ( host(), { idx.template get<1>()[span1.key()], idx.template get<1>()[span1.value()] },
                                     { idx.template get<2>()[span2.key()], idx.template get<2>()[span2.value()] } );
}

template < class container_type >
constexpr const auto array_span_view<container_type>::operator [] ( pair<int> span1, pair<int> span2 ) const
    requires ( container_type::dimension() == 2 )
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]". Currently it is unsolved.
    return array_span_view ( const_cast<container_type&>(host()), { idx.template get<1>()[span1.key()], idx.template get<1>()[span1.value()] },
                                                                  { idx.template get<2>()[span2.key()], idx.template get<2>()[span2.value()] } );
}