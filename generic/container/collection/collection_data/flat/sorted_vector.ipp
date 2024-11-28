#pragma once

/// Class sorted_vector

// Interface

template < class type, class compares >
constexpr int sorted_vector<type,compares>::size ( ) const
{
    return vector<type>::size();
}

template < class type, class compares >
constexpr bool sorted_vector<type,compares>::empty ( ) const
{
    return vector<type>::empty();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::begin ( ) const
{
    return vector<type>::begin();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::end ( ) const
{
    return vector<type>::end();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::min ( ) const
{
    return not empty() ? begin() otherwise end();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::max ( ) const
{
    return not empty() ? end() - 1 otherwise end();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::locate ( const auto& val ) const
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    if ( empty() )
        return end();

    let it = std::lower_bound ( begin(), end(), val, compares::less );

    return it == end() ? --it otherwise it;
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::clear ( )
{
    vector<type>::clear();
    return end();
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::push ( auto&& val, const_iterator it )
    requires std::convertible_to<decltype(val),type>
{
    if ( size() == 0 )
    {
        vector<type>::push ( std::move ( val ) );
        return begin();
    }

    else // size() >= 1
    {
        if ( it == const_iterator() )
            it = locate ( val );

        if ( it == max() and not compares::less ( val, *max() ) )
            ++it; // Now it == end().

        int len = it - begin();

        #if debug
            if ( it != end() and compares::equal_to ( val, *it ) ) // In this case it == end(), and points to a zero-initialized space.
                throw key_error("key {} already exists", val);
        #endif

        vector<type>::insert ( it - begin() + 1, std::move ( val ) );

        return begin() + len;
    }
}

template < class type, class compares >
constexpr sorted_vector<type,compares>::const_iterator sorted_vector<type,compares>::pop ( const auto& val, const_iterator it )
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    #if debug
        if ( size() == 0 )
            error ( self, val, it );
    #endif

    if ( it == const_iterator() )
        it = locate ( val );

    int len = it - begin();

    #if debug
        if ( not compares::equal_to ( val, *it ) )
            throw key_error("key {} does not exist", val);
    #endif

    vector<type>::pop ( it - begin() + 1 );

    return begin() + len + 1;
}



template < class type, class compares >
constexpr vector<type>& sorted_vector<type,compares>::data ( )
{
    return static_cast<vector<type>&>(self);
}

template < class type, class compares >
constexpr const vector<type>& sorted_vector<type,compares>::data ( ) const
{
    return static_cast<const vector<type>&>(self);
}