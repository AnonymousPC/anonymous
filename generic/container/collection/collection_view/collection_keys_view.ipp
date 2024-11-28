#pragma once

/// Class collection_keys_view

// Host

template < class container_type >
constexpr const container_type& collection_keys_view<container_type>::host ( ) const
{
    return col;
}

// Constructor

template < class container_type >
constexpr collection_keys_view<container_type>::collection_keys_view ( container_type& init )
    extends col ( init )
{

}

// Core

template < class container_type >
constexpr collection_keys_view<container_type>& collection_keys_view<container_type>::operator = ( const collection_keys_view& right )
{
    #if debug
        if ( self.size() != right.size() )
        throw value_error("cannot copy collection_view of size {} into collection_view of size {}", right.size(), self.size());
    #endif

    std::copy ( right.begin(), right.end(), begin() );
    return self;
}

// Interface

template < class container_type >
constexpr int collection_keys_view<container_type>::size ( ) const
{
    return col.size();
}

template < class container_type >
constexpr bool collection_keys_view<container_type>::empty ( ) const
{
    return col.empty();
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator collection_keys_view<container_type>::begin ( ) const
{
    return const_iterator(const_cast<const container_type&>(col).begin());
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator collection_keys_view<container_type>::end ( ) const
{
    return const_iterator(const_cast<const container_type&>(col).end());
}

template < class container_type >
constexpr bool collection_keys_view<container_type>::contains ( const value_type& k ) const
{
    return col.contains(k);
}





/// Class collection_keys_view::const_iterator

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator::const_iterator ( const container_type::const_iterator& init )
    extends container_type::const_iterator ( init )
{

}

template < class container_type >
constexpr const auto& collection_keys_view<container_type>::const_iterator::operator * ( ) const
{
    return container_type::const_iterator::operator*().key();
}

template < class container_type >
constexpr const auto* collection_keys_view<container_type>::const_iterator::operator -> ( ) const
{
    return &container_type::const_iterator::operator*().key();
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator& collection_keys_view<container_type>::const_iterator::operator ++ ( )
{
    container_type::const_iterator::operator++();
    return self;
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator collection_keys_view<container_type>::const_iterator::operator ++ ( int )
{
    return const_iterator(container_type::const_iterator::operator++(int()));
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator& collection_keys_view<container_type>::const_iterator::operator -- ( )
{
    container_type::const_iterator::operator--();
    return self;
}

template < class container_type >
constexpr collection_keys_view<container_type>::const_iterator collection_keys_view<container_type>::const_iterator::operator -- ( int )
{
    return const_iterator(container_type::const_iterator::operator--(int()));
}