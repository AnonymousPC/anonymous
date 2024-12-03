#pragma once

/// Class array_filter_view

// Host

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr container_type& array_filter_view<container_type,filter>::host ( )
{
    return arr;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr const container_type& array_filter_view<container_type,filter>::host ( ) const
{
    return arr;
}

// Constuctor

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::array_filter_view ( container_type& init_arr, filter init_filt )
    extends arr  ( init_arr  ),
            filt ( init_filt )
{

}

// Core

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>& array_filter_view<container_type,filter>::operator = ( const array_filter_view& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right.host() ) // From different hosts.
        std::copy ( right.begin(), right.end(), begin() );
    else // Too complex.
        self = container_type ( right );

    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>& array_filter_view<container_type,filter>::operator = ( const container_type& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() or &self.host() == &right )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right ) // From different hosts.
        std::copy ( right.begin(), right.end(), begin() );

    // Else: from same host, which must be view == host()[all].

    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>& array_filter_view<container_type,filter>::operator = ( container_type&& right )
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot move array of shape {} into array_view of shape {}", right.shape(), self.shape());

        if ( &self.host() == &right ) // From same host, in which the view will be dangling.
            throw value_error("cannot move array into an array_view on itself");
    #endif

    std::move ( right.begin(), right.end(), begin() );
    if constexpr ( requires { right.clear(); } ) // As right might be array_fix_len or other kind of view.
        right.clear();

    return self;
}

// Interface

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr int array_filter_view<container_type,filter>::row ( ) const
    requires ( container_type::dimension() >= 2 )
{
    return std::count_if ( host().begin(), host().end(), filt );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr int array_filter_view<container_type,filter>::size ( ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return std::count_if ( host().begin(), host().end(), filt );
    else
        return host().size() / host().row() * row();
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr bool array_filter_view<container_type,filter>::empty ( ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return size() == 0;
    else
        return row() == 0;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::begin ( )
{
    int pos = host().find ( filt );
    return iterator ( host(), filt, ( pos != 0 ) ? pos otherwise host().size() + 1 );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::begin ( ) const
{
    int pos = host().find ( filt );
    return const_iterator ( host(), filt, ( pos != 0 ) ? pos otherwise host().size() + 1 );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::end ( )
{
    return iterator ( host(), filt, host().size() + 1 );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::end ( ) const
{
    return const_iterator ( host(), filt, host().size() + 1 );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::operator [] ( int pos )
{
    #if debug
        if ( pos == 0 or begin() == end() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    if ( pos > 0 )
    {
        auto it = begin();
        for ( int _ in range(pos-1) )
        {
            it++;
            if ( it == end() )
                throw index_error("index {} is out of range with size {}", pos, size());
        }
        return *it;
    }

    else
    {
        auto it = end();
        it--;

        for ( int _ in range(-pos-1) )
        {
            it--;
            if ( it < begin() )
                throw index_error("index {} is out of range with size {}", pos, size());
        }

        return *it;
    }
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::operator [] ( int pos ) const
{
    #if debug
        if ( pos == 0 or begin() == end() )
            throw index_error("index {} is out of range with size {}", pos, size());
    #endif

    if ( pos > 0 )
    {
        auto it = begin();
        for ( int _ in range ( pos - 1 ) )
        {
            it++;
            if ( it == end() )
                throw index_error("index {} is out of range with size {}", pos, size());
        }
        return *it;
    }

    else
    {
        auto it = end();
        it--;

        for ( int _ in range ( -pos - 1 ) )
        {
            it--;
            if ( it < begin() )
                throw index_error("index {} is out of range with size {}", pos, size());
        }

        return *it;
    }
}

// Views

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr auto array_filter_view<container_type,filter>::operator [] ( unary_pred<iterate_type> auto new_filt )
{
    let compose_filt = [&] ( const iterate_type& val ) { return filt(val) and new_filt(val); };
    return array_filter_view<container_type,decltype(compose_filt)> ( host(), compose_filt );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr const auto array_filter_view<container_type,filter>::operator [] ( unary_pred<iterate_type> auto new_filt ) const
{
    let compose_filt = [&] ( const iterate_type& val ) { return filt(val) and new_filt(val); };
    return array_filter_view<container_type,decltype(compose_filt)> ( const_cast<container_type&>(host()), compose_filt );
}









/// Class array_filter_view::iterator

// Host

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr container_type& array_filter_view<container_type,filter>::iterator::host ( ) const
{
    return *arr_ptr;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr const filter& array_filter_view<container_type,filter>::iterator::function ( ) const
{
    return *filt_ptr;
}

// Core

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator::iterator ( container_type& init_arr, const filter& init_filt, int init_pos )
    extends arr_ptr  ( &init_arr  ),
            filt_ptr ( &init_filt ),
            pos      ( init_pos  )
{

}

// Operator

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::iterator::operator * ( ) const
{
    #if debug
        if constexpr ( container_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error("index {} is out of range with size {}", pos, host().size());
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error("index {} is out of arnge with shape {} axis {}", pos, host().shape(), 1);
    #endif

    return host()[pos];
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::iterator::operator -> ( ) const
{
    #if debug
        if constexpr ( container_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error("index {} is out of range with size {}", pos, host().size());
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error("index {} is out of arnge with shape {} axis {}", pos, host().shape(), 1);
    #endif

    return &host()[pos];
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr bool array_filter_view<container_type,filter>::iterator::operator == ( const iterator& right ) const
{
    #if debug
        if ( &self.host() != &right.host() or &self.function() != &right.function() )
            throw value_error("cannot operate array_filter_view::iterator from different array or filter");
    #endif

    return pos == right.pos;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr std::strong_ordering array_filter_view<container_type,filter>::iterator::operator <=> ( const iterator& right ) const
{
    #if debug
        if ( &self.host() != &right.host() or &self.function() != &right.function() )
            throw value_error("cannot operate array_filter_view::iterator from different array or filter");
    #endif

    return pos <=> right.pos;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::iterator::operator + ( int offset ) const
{
    let it = self;

    if ( offset > 0 )
        for ( int _ in range(offset) )
            ++it;
    else if ( offset < 0 )
        for ( int _ in range(offset) )
            --it;

    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::iterator::operator - ( int offset ) const
{
    let it = self;

    if ( offset > 0 )
        for ( int _ in range(offset) )
            --it;
    else if ( offset < 0 )
        for ( int _ in range(offset) )
            ++it;

    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator::difference_type array_filter_view<container_type,filter>::iterator::operator - ( const iterator& right ) const
{
    if ( right < self )
        return std::count_if ( right, self, function() );
    else
        return - std::count_if ( self, right, function() );
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator& array_filter_view<container_type,filter>::iterator::operator ++ ( )
{
    int p = host()[pos+1,-1].find(function());
    self.pos = ( p != 0 ) ? p + pos otherwise host().size() + 1;
    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::iterator::operator ++ ( int )
{
    auto it = self;
    int p = host()[pos+1,-1].find(function());
    self.pos = ( p != 0 ) ? p + pos otherwise host().size() + 1;
    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator& array_filter_view<container_type,filter>::iterator::operator -- ( )
{
    int p = pos - 1;
    while ( p >= 1 and not function() ( host()[p] ) )
        p--;

    self.pos = ( p != 0 ) ? p otherwise 0;
    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::iterator array_filter_view<container_type,filter>::iterator::operator -- ( int )
{
    auto it = self;
    int p = pos - 1;
    while ( p >= 1 and not function() ( host()[p] ) )
        p--;

    self.pos = ( p != 0 ) ? p otherwise 0;
    return it;
}



/// Class array_filter_view::const_iterator

// Host

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr const container_type& array_filter_view<container_type,filter>::const_iterator::host ( ) const
{
    return *arr_ptr;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr const filter& array_filter_view<container_type,filter>::const_iterator::function ( ) const
{
    return *filt_ptr;
}

// Core

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator::const_iterator ( const container_type& init_arr, const filter& init_filt, int init_pos )
    extends arr_ptr  ( &init_arr  ),
            filt_ptr ( &init_filt ),
            pos      ( init_pos  )
{

}

// Operator

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::const_iterator::operator * ( ) const
{
    #if debug
        if constexpr ( container_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error("index {} is out of range with size {}", pos, host().size());
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error("index {} is out of arnge with shape {} axis {}", pos, host().shape(), 1);
    #endif

    return host()[pos];
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr decltype(auto) array_filter_view<container_type,filter>::const_iterator::operator -> ( ) const
{
    #if debug
        if constexpr ( container_type::dimension() == 1 )
        {
            if ( pos < 1 or pos > host().size() )
                throw index_error("index {} is out of range with size {}", pos, host().size());
        }

        else
            if ( pos < 1 or pos > host().row() )
                throw index_error("index {} is out of arnge with shape {} axis {}", pos, host().shape(), 1);
    #endif

    return &host()[pos];
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr bool array_filter_view<container_type,filter>::const_iterator::operator == ( const const_iterator& right ) const
{
    #if debug
        if ( &self.host() != &right.host() or &self.function() != &right.function() )
            throw value_error("cannot operate array_filter_view::const_iterator from different array or filter");
    #endif

    return pos == right.pos;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr std::strong_ordering array_filter_view<container_type,filter>::const_iterator::operator <=> ( const const_iterator& right ) const
{
    #if debug
        if ( &self.host() != &right.host() or &self.function() != &right.function() )
            throw value_error("cannot operate array_filter_view::const_iterator from different array or filter");
    #endif

    return pos <=> right.pos;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::const_iterator::operator + ( int offset ) const
{
    let it = self;

    if ( offset > 0 )
        for ( int _ in range(offset) )
            ++it;
    else if ( offset < 0 )
        for ( int _ in range(offset) )
            --it;

    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::const_iterator::operator - ( int offset ) const
{
    let it = self;

    if ( offset > 0 )
        for ( int _ in range ( offset ) )
            --it;
    else if ( offset < 0 )
        for ( int _ in range ( offset ) )
            ++it;

    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator::difference_type array_filter_view<container_type,filter>::const_iterator::operator - ( const const_iterator& right ) const
{
    if ( right < self )
        return std::count_if ( right, self, function() );
    else
        return - std::count_if ( self, right, function() );
}


template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator& array_filter_view<container_type,filter>::const_iterator::operator ++ ( )
{
    int p = host()[pos+1,-1].find(function());
    self.pos = ( p != 0 ) ? p + pos otherwise host().size() + 1;
    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::const_iterator::operator ++ ( int )
{
    auto it = self;
    int p = host()[pos+1,-1].find(function());
    self.pos = ( p != 0 ) ? p + pos otherwise host().size() + 1;
    return it;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator& array_filter_view<container_type,filter>::const_iterator::operator -- ( )
{
    int p = pos - 1;
    while ( p >= 1 and not function() ( host()[p] ) )
        p--;

    self.pos = ( p != 0 ) ? p otherwise 0;
    return self;
}

template < class container_type, unary_pred<typename container_type::iterate_type> filter >
constexpr array_filter_view<container_type,filter>::const_iterator array_filter_view<container_type,filter>::const_iterator::operator -- ( int )
{
    auto it = self;
    int p = pos - 1;
    while ( p >= 1 and not function() ( host()[p] ) )
        p--;

    self.pos = ( p != 0 ) ? p otherwise 0;
    return it;
}