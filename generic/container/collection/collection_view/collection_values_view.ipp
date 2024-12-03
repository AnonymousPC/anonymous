#pragma once

/// Class collection_values_view

// Host

template < class container_type >
constexpr const container_type& collection_values_view<container_type>::host ( ) const
{
    return col;
}

// Constructor

template < class container_type >
constexpr collection_values_view<container_type>::collection_values_view ( container_type& init )
    extends col ( init )
{

}

// Interface

template < class container_type >
constexpr int collection_values_view<container_type>::size ( ) const
{
    return col.size();
}

template < class container_type >
constexpr bool collection_values_view<container_type>::empty ( ) const
{
    return col.empty();
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator collection_values_view<container_type>::begin ( )
{
    return iterator(col.begin());
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator collection_values_view<container_type>::begin ( ) const
{
    return const_iterator(const_cast<const container_type&>(col).begin());
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator collection_values_view<container_type>::end ( )
{
    return iterator(col.end());
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator collection_values_view<container_type>::end ( ) const
{
    return const_iterator(const_cast<const container_type&>(col).end());
}



/// Class collection_values_view::iterator

template < class container_type >
constexpr auto& collection_values_view<container_type>::iterator::operator * ( ) const
{
    return container_type::iterator::operator*().value();
}

template < class container_type >
constexpr auto* collection_values_view<container_type>::iterator::operator -> ( ) const
{
    return &container_type::iterator::operator*().value();
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator& collection_values_view<container_type>::iterator::operator ++ ( )
{
    container_type::iterator::operator++();
    return self;
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator collection_values_view<container_type>::iterator::operator ++ ( int )
{
    return iterator(container_type::iterator::operator++(int()));
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator& collection_values_view<container_type>::iterator::operator -- ( )
{
    container_type::iterator::operator--();
    return self;
}

template < class container_type >
constexpr collection_values_view<container_type>::iterator collection_values_view<container_type>::iterator::operator -- ( int )
{
    return iterator(container_type::iterator::operator--(int()));
}



/// Class collection_values_view::const_iterator

template < class container_type >
constexpr const auto& collection_values_view<container_type>::const_iterator::operator * ( ) const
{
    return container_type::const_iterator::operator*().value();
}

template < class container_type >
constexpr const auto* collection_values_view<container_type>::const_iterator::operator -> ( ) const
{
    return &container_type::const_iterator::operator*().value();
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator& collection_values_view<container_type>::const_iterator::operator ++ ( )
{
    container_type::const_iterator::operator++();
    return self;
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator collection_values_view<container_type>::const_iterator::operator ++ ( int )
{
    return const_iterator(container_type::const_iterator::operator++(int()));
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator& collection_values_view<container_type>::const_iterator::operator -- ( )
{
    container_type::const_iterator::operator--();
    return self;
}

template < class container_type >
constexpr collection_values_view<container_type>::const_iterator collection_values_view<container_type>::const_iterator::operator -- ( int )
{
    return const_iterator(container_type::const_iterator::operator--(int()));
}