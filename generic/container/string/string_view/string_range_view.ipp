#pragma once

/// Class basic_string_range_view

// Core

template < class char_type >
constexpr basic_string_range_view<char_type>& basic_string_range_view<char_type>::operator = ( const basic_string_range_view& right )
{
    if ( ptr != nullptr ) [[likely]] // Assign
    {
        #if debug
            if ( self.size() != right.size() )
                throw value_error("cannot copy string of size {} into string_view of size {}", right.size(), self.size());
        #endif

        if ( self.ptr != right.ptr or self.idx.min() < right.idx.min() ) // From different hosts, or same host but first is before second.
            std::copy ( right.begin(), right.end(), self.begin() );
        else
            std::copy_backward ( right.begin(), right.end(), self.end() );
    }

    else // Delayed initialization
    {
        ptr = right.ptr;
        idx = right.idx;
    }

    return self;
}

template < class char_type >
constexpr basic_string_range_view<char_type>& basic_string_range_view<char_type>::operator = ( const basic_string<char_type>& right )
{
    #if debug
        if ( self.size() != right.size() )
            throw value_error("cannot copy string of size {} into string_view of size {}", right.size(), self.size());
    #endif

    if ( self.ptr != &right ) // From different hosts
        std::copy ( right.begin(), right.end(), self.begin() );

    // Else: from same host, which must be view == str[1,n].

    return self;
}

template < class char_type >
constexpr basic_string_range_view<char_type>& basic_string_range_view<char_type>::operator = ( basic_string<char_type>&& right )
{
    #if debug
        if ( self.size() != right.size() )
            throw value_error("cannot move string of size {} into string_view of size {}", right.size(), self.size());

        if ( self.ptr == &right ) // From same host, in which the view will be dangling.
            throw value_error("cannot move string into an string_view on itself");
    #endif

    std::move ( right.begin(), right.end(), self.begin() );

    return self;
}

// Constructor

template < class char_type >
constexpr basic_string_range_view<char_type>::basic_string_range_view ( basic_string<char_type>& str, int from, int to )
    extends ptr ( &str )
{
    idx = range ( from >  0 ? from otherwise from + str.size() + 1,
                  to   >= 0 ? to   otherwise to   + str.size() + 1 );

    #if debug
        if ( ( ( idx.min() < 1 or idx.min() > str.size() ) or
               ( idx.max() < 1 or idx.max() > str.size() ) )
        and not // Except for below:
             ( idx.min() == idx.max() + 1 and ( idx.min() == 1 or idx.max() == str.size() ) ) )
            throw index_error("idx [{},{}] is out of range with size {}", from, to, str.size());
    #endif
}

// Conversion

template < class char_type >
template < class char_type2 >
constexpr basic_string_range_view<char_type>::operator basic_string<char_type2> ( ) const
{
    return basic_string_view(self).operator basic_string<char_type2>();
}

template < class char_type >
template < class bool_type >
constexpr basic_string_range_view<char_type>::operator bool_type ( ) const
    requires std::same_as<char_type,char> and
             std::same_as<bool_type,bool>
{
    return basic_string_view(self).operator bool_type();
}

template < class char_type >
template < class number_type >
constexpr basic_string_range_view<char_type>::operator number_type ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string_range_view,number_type>::value ) and
             ( not general_string_type<number_type> ) and
             ( not std::same_as<number_type,bool> ) and
             ( std::integral<number_type> or std::floating_point<number_type> )
{
    return basic_string_view(self).operator number_type();
}

template < class char_type >
template < class inputable >
constexpr basic_string_range_view<char_type>::operator inputable ( ) const
    requires std::same_as<char_type,char> and
             ( not std::is_convertible<basic_string_range_view,inputable>::value ) and
             ( not general_string_type<inputable> ) and
             ( not std::same_as<inputable,bool> ) and
             ( not ( std::integral<inputable> or std::floating_point<inputable> ) ) and
             ap::inputable<inputable>
{
    return basic_string_view(self).operator inputable();
}

template < class char_type >
constexpr basic_string_range_view<char_type>::operator std::basic_string<char_type> ( ) const
{
    return basic_string_view(self).operator std::basic_string<char_type>();
}

template < class char_type >
constexpr basic_string_range_view<char_type>::operator std::basic_string_view<char_type> ( ) const
{
    return basic_string_view(self).operator std::basic_string_view<char_type>();
}

// Interface

template < class char_type >
constexpr int basic_string_range_view<char_type>::size ( ) const
{
    return idx.size();
}

template < class char_type >
constexpr bool basic_string_range_view<char_type>::empty ( ) const
{
    return size() == 0;
}

template < class char_type >
constexpr basic_string_range_view<char_type>::iterator basic_string_range_view<char_type>::begin ( )
{
    return ptr->begin() + *idx.begin() - 1;
}

template < class char_type >
constexpr basic_string_range_view<char_type>::const_iterator basic_string_range_view<char_type>::begin ( ) const
{
    return ptr->begin() + *idx.begin() - 1;;
}

template < class char_type >
constexpr basic_string_range_view<char_type>::iterator basic_string_range_view<char_type>::end ( )
{
    return ptr->begin() + *idx.end() - 1;
}

template < class char_type >
constexpr basic_string_range_view<char_type>::const_iterator basic_string_range_view<char_type>::end ( ) const
{
    return ptr->begin() + *idx.end() - 1;
}

template < class char_type >
constexpr char_type& basic_string_range_view<char_type>::operator [] ( int pos )
{
    return (*ptr)[idx[pos]];
}

template < class char_type >
constexpr const char_type& basic_string_range_view<char_type>::operator [] ( int pos ) const
{
    return (*ptr)[idx[pos]];
}

template < class char_type >
constexpr auto basic_string_range_view<char_type>::operator [] ( int from, int to )
{
    // Notice str[1,3][1,0] causes index_error in "idx[to]"
    return basic_string_range_view ( *ptr,
                                     from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                     to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to );
}

template < class char_type >
constexpr const auto basic_string_range_view<char_type>::operator [] ( int from, int to ) const
{
    // Notice str[1,3][1,0] causes index_error in "idx[to]"
    return basic_string_range_view ( const_cast<basic_string<char_type>&>(*ptr),
                                     from >  0 ? *idx.begin() + from - 1 otherwise *idx.end() + from,
                                     to   >= 0 ? *idx.begin() + to   - 1 otherwise *idx.end() + to );
}