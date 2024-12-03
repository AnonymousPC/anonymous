#pragma once

/// Class array_range_view

// Host

template < class container_type, bool continuous >
constexpr container_type& array_range_view<container_type,continuous>::host ( )
{
    return arr;
}

template < class container_type, bool continuous >
constexpr const container_type& array_range_view<container_type,continuous>::host ( ) const
{
    return arr;
}

// Constructor

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::array_range_view ( container_type& init_arr, int from, int to )
    requires ( continuous )
    extends arr ( init_arr )
{
    let row = [&] { if constexpr ( container_type::dimension() == 1 ) return host().size(); else return host().row(); } ();

    idx = range<int,true> ( from >  0 ? from otherwise from + row + 1,
                            to   >= 0 ? to   otherwise to   + row + 1 );

    #if debug
        if ( ( ( idx.min() < 1 or idx.min() > row ) or
               ( idx.max() < 1 or idx.max() > row ) )
        and not // Except for below:
             ( idx.min() == idx.max() + 1 and ( idx.min() == 1 or idx.max() == row ) ) )
            throw index_error("index [{},{}] is out of range with size {}", from, to, row);
    #endif
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::array_range_view ( container_type& init_arr, int from, int to, int step )
    requires ( not continuous )
    extends arr ( init_arr ),
            idx ()
{
    let row = [&] { if constexpr ( container_type::dimension() == 1 ) return host().size(); else return host().row(); } ();

    idx = range<int> ( from >  0 ? from otherwise from + row + 1,
                       to   >= 0 ? to   otherwise to   + row + 1,
                       step );

    #if debug
        let a = idx.min() >= 1 and idx.min() <= row;                            // Legal.
        let b = idx.max() >= 1 and idx.max() <= row;                            // Legal.
        let c = ( idx.sep() > 0 and idx.min() == idx.max() + idx.sep() ) or
                ( idx.sep() < 0 and idx.min() == idx.max() + idx.sep() );   // Legal, protects a b.
        if ( ( not a or not b ) and not ( ( a or b ) and c ) )
            throw index_error("index [{},{},{}] is out of range with size {}", from, to, step, row);
    #endif
}

// Core

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>& array_range_view<container_type,continuous>::operator = ( const array_range_view& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right.host() ) // From different hosts.
        std::copy ( right.begin(), right.end(), self.begin() );
    else
        if constexpr ( continuous ) // Optimizable.
            if ( self.idx.min() < right.idx.min() )
                std::copy ( right.begin(), right.end(), self.begin() );
            else
                std::copy_backward ( right.begin(), right.end(), self.end() );
        else // Too complex.
            self = container_type ( right );

    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>& array_range_view<container_type,continuous>::operator = ( const container_type& right )
    requires std::copyable<value_type>
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot copy array of shape {} into array_view of shape {}", right.shape(), self.shape());
    #endif

    if ( &self.host() != &right ) // From different hosts.
        std::copy ( right.begin(), right.end(), self.begin() );

    else // From same host, which must be view == host()[1,n] or view == host()[n,1,-1].
        if ( not idx.empty() and idx.min() == right.size() ) // view == host()[n,1,-1], which only needs to be reversed.
            std::reverse ( right.begin(), right.end() );

    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>& array_range_view<container_type,continuous>::operator = ( container_type&& right )
{
    #if debug
        if ( self.shape() != right.shape() )
            throw value_error("cannot move array of shape {} into array_view of shape {}", right.shape(), self.shape());

        if ( &self.host() == &right ) // From same host, in which the view will be dangling.
            throw value_error("cannot move array into an array_view on itself");
    #endif

    std::move ( right.begin(), right.end(), self.begin() );
    if constexpr ( requires { right.clear(); } ) // As right might be array_fix_len or other kind of view.
        right.clear();

    return self;
}

// Interface

template < class container_type, bool continuous >
constexpr int array_range_view<container_type,continuous>::row ( ) const
    requires ( container_type::dimension() >= 2 )
{
    return idx.size();
}

template < class container_type, bool continuous >
constexpr int array_range_view<container_type,continuous>::size ( ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return idx.size();
    else
        return host().size() / host().row() * row();
}

template < class container_type, bool continuous >
constexpr bool array_range_view<container_type,continuous>::empty ( ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return size() == 0;
    else
        return row() == 0;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator array_range_view<container_type,continuous>::begin ( )
{
    if constexpr ( continuous )
        return host().begin() + *idx.begin() - 1;
    else
        return iterator ( host().begin() + *idx.begin() - 1, idx.sep() );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator array_range_view<container_type,continuous>::begin ( ) const
{
    if constexpr ( continuous )
        return host().begin() + *idx.begin() - 1;
    else
        return const_iterator ( host().begin() + *idx.begin() - 1, idx.sep() );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator array_range_view<container_type,continuous>::end ( )
{
    if constexpr ( continuous )
        return host().begin() + *idx.end() - 1;
    else
        return iterator ( host().begin() + *idx.end() - 1, idx.sep() );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator array_range_view<container_type,continuous>::end ( ) const
{
    if constexpr ( continuous )
        return host().begin() + *idx.end() - 1;
    else
        return const_iterator ( host().begin() + *idx.end() - 1, idx.sep() );
}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::operator [] ( int pos )
{
    return host()[idx[pos]];
}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::operator [] ( int pos ) const
{
    return host()[idx[pos]];
}



// Views

template < class container_type, bool continuous >
constexpr auto array_range_view<container_type,continuous>::operator [] ( int from, int to )
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]"
    if constexpr ( continuous )
        return array_range_view<container_type,true> ( host(),
                                                       from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                                       to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to );
    else
        return array_range_view<container_type,false> ( host(),
                                                        from >  0 ? *idx.begin() + ( from - 1 ) * idx.sep() otherwise *idx.begin() + ( from + idx.size() ) * idx.sep(),
                                                        to   >= 0 ? *idx.begin() + ( to   - 1 ) * idx.sep() otherwise *idx.begin() + ( to   + idx.size() ) * idx.sep(),
                                                        idx.sep() );
}

template < class container_type, bool continuous >
constexpr const auto array_range_view<container_type,continuous>::operator [] ( int from, int to ) const
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]"
    if constexpr ( continuous )
        return array_range_view<container_type,true> ( const_cast<container_type&>(host()),
                                                       from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                                       to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to );
    else
        return array_range_view<container_type,false> ( const_cast<container_type&>(host()),
                                                        from >  0 ? *idx.begin() + ( from - 1 ) * idx.sep() otherwise *idx.begin() + ( from + idx.size() ) * idx.sep(),
                                                        to   >= 0 ? *idx.begin() + ( to   - 1 ) * idx.sep() otherwise *idx.begin() + ( to   + idx.size() ) * idx.sep(),
                                                        idx.sep() );
}

template < class container_type, bool continuous >
constexpr auto array_range_view<container_type,continuous>::operator [] ( int from, int to, int step )
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]"
    if constexpr ( continuous )
        return array_range_view<container_type,false> ( host(),
                                                        from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                                        to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to,
                                                        step );
    else
        return array_range_view<container_type,false> ( host(),
                                                        from >  0 ? *idx.begin() + ( from - 1 ) * idx.sep() otherwise *idx.begin() + ( from + idx.size() ) * idx.sep(),
                                                        to   >= 0 ? *idx.begin() + ( to   - 1 ) * idx.sep() otherwise *idx.begin() + ( to   + idx.size() ) * idx.sep(),
                                                        step * idx.sep() );
}

template < class container_type, bool continuous >
constexpr const auto array_range_view<container_type,continuous>::operator [] ( int from, int to, int step ) const
{
    // Notice arr[1,3][1,0] causes index_error in "idx[to]"
    if constexpr ( continuous )
        return array_range_view<container_type,false> ( const_cast<container_type&>(host()),
                                                        from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                                        to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to,
                                                        step );
    else
        return array_range_view<container_type,false> ( const_cast<container_type&>(host()),
                                                        from >  0 ? *idx.begin() + ( from - 1 ) * idx.sep() otherwise *idx.begin() + ( from + idx.size() ) * idx.sep(),
                                                        to   >= 0 ? *idx.begin() + ( to   - 1 ) * idx.sep() otherwise *idx.begin() + ( to   + idx.size() ) * idx.sep(),
                                                        step * idx.sep() );
}





/// Class array_range_view::iterator

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator::iterator ( )
{

}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator::iterator ( container_type::iterator init_ptr, int init_step )
    extends ptr  ( init_ptr  ),
            step ( init_step )
{

}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::iterator_base::iterator::operator * ( ) const
{
    return *ptr;
}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::iterator_base::iterator::operator -> ( ) const
{
    return ptr;
}

template < class container_type, bool continuous >
constexpr bool array_range_view<container_type,continuous>::iterator_base::iterator::operator == ( const iterator& right ) const
{
    return ptr == right.ptr;
}

template < class container_type, bool continuous >
constexpr std::strong_ordering array_range_view<container_type,continuous>::iterator_base::iterator::operator <=> ( const iterator& right ) const
{
    return ptr <=> right.ptr; // Here assumes that iterator all aligns in integral_times of step.
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator array_range_view<container_type,continuous>::iterator_base::iterator::operator + ( int offset ) const
{
    return iterator ( ptr + offset * step, step );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator array_range_view<container_type,continuous>::iterator_base::iterator::operator - ( int offset ) const
{
    return iterator ( ptr - offset * step, step );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator::difference_type array_range_view<container_type,continuous>::iterator_base::iterator::operator - ( const iterator& right ) const
{
    return ( self.ptr - right.ptr ) / step;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator& array_range_view<container_type,continuous>::iterator_base::iterator::operator ++ ( )
{
    ptr += step;
    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator array_range_view<container_type,continuous>::iterator_base::iterator::operator ++ ( int )
{
    auto it = self;
    ptr += step;
    return it;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator& array_range_view<container_type,continuous>::iterator_base::iterator::operator -- ( )
{
    ptr -= step;
    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::iterator_base::iterator array_range_view<container_type,continuous>::iterator_base::iterator::operator -- ( int )
{
    auto it = self;
    ptr -= step;
    return it;
}





/// Class array_range_view::const_iterator

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator::const_iterator ( )
{

}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator::const_iterator ( container_type::const_iterator init_ptr, int init_step )
    extends ptr  ( init_ptr  ),
            step ( init_step )
{

}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator * ( ) const
{
    return *ptr;
}

template < class container_type, bool continuous >
constexpr decltype(auto) array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator -> ( ) const
{
    return ptr;
}

template < class container_type, bool continuous >
constexpr bool array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator == ( const const_iterator& right ) const
{
    return ptr == right.ptr;
}

template < class container_type, bool continuous >
constexpr std::strong_ordering array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator <=> ( const const_iterator& right ) const
{
    return ptr <=> right.ptr; // Here assumes that const_iterator all aligns in integral_times of step.
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator + ( int offset ) const
{
    return const_iterator ( ptr + offset * step, step );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator - ( int offset ) const
{
    return const_iterator ( ptr - offset * step, step );
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator::difference_type array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator - ( const const_iterator& right ) const
{
    return ( self.ptr - right.ptr ) / step;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator& array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator ++ ( )
{
    ptr += step;
    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator ++ ( int )
{
    auto it = self;
    ptr += step;
    return it;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator& array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator -- ( )
{
    ptr -= step;
    return self;
}

template < class container_type, bool continuous >
constexpr array_range_view<container_type,continuous>::const_iterator_base::const_iterator array_range_view<container_type,continuous>::const_iterator_base::const_iterator::operator -- ( int )
{
    auto it = self;
    ptr -= step;
    return it;
}
