#pragma once

/// Class array_type_view

// Host

template < class container_type, class type2 >
constexpr container_type& array_type_view<container_type,type2>::host ( )
{
    return arr;
}

template < class container_type, class type2 >
constexpr const container_type& array_type_view<container_type,type2>::host ( ) const
{
    return arr;
}

// Constructor

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::array_type_view ( container_type& init )
    extends arr ( init )
{

}

// Interface

template < class container_type, class type2 >
constexpr int array_type_view<container_type,type2>::row ( ) const
    requires ( container_type::dimension() >= 2 )
{
    return host().row();
}

template < class container_type, class type2 >
constexpr int array_type_view<container_type,type2>::column ( ) const
    requires ( container_type::dimension() == 2 )
{
    return host().column();
}

template < class container_type, class type2 >
constexpr int array_type_view<container_type,type2>::size ( ) const
{
    return host().size();
}

template < class container_type, class type2 >
constexpr bool array_type_view<container_type,type2>::empty ( ) const
{
    return host().empty();
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::begin ( )
{
    return iterator ( host().begin() );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::begin ( ) const
{
    return const_iterator ( host().begin() );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::end ( )
{
    return iterator ( host().end() );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::end ( ) const
{
    return const_iterator ( host().end() );
}

template < class container_type, class type2 >
constexpr auto array_type_view<container_type,type2>::operator [] ( int pos )
{
    if constexpr ( container_type::dimension() == 1 )
        return type2(host()[pos]);
    else
        return host()[pos].template as_type<type2>();
}

template < class container_type, class type2 >
constexpr const auto array_type_view<container_type,type2>::operator [] ( int pos ) const
{
    if constexpr ( container_type::dimension() == 1 )
        return type2(host()[pos]);
    else
        return host()[pos].template as_type<type2>();
}





/// Class array_type_view::iterator

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator::iterator ( container_type::iterator init )
    extends ptr ( init )
{

}

template < class container_type, class type2 >
constexpr auto array_type_view<container_type,type2>::iterator::operator * ( ) const
{
    return type2 ( *ptr );
}

template < class container_type, class type2 >
constexpr bool array_type_view<container_type,type2>::iterator::operator == ( const iterator& right ) const
{
    return ptr == right.ptr;
}

template < class container_type, class type2 >
constexpr std::strong_ordering array_type_view<container_type,type2>::iterator::operator <=> ( const iterator& right ) const
{
    return ptr <=> right.ptr;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::iterator::operator + ( int offset ) const
{
    return iterator ( ptr + offset );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::iterator::operator - ( int offset ) const
{
    return iterator ( ptr - offset );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator::difference_type array_type_view<container_type,type2>::iterator::operator - ( const iterator& right ) const
{
    return ptr - right.ptr;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator& array_type_view<container_type,type2>::iterator::operator ++ ( )
{
    ++ptr;
    return self;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::iterator::operator ++ ( int )
{
    let it = self;
    ++ptr;
    return it;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator& array_type_view<container_type,type2>::iterator::operator -- ( )
{
    --ptr;
    return self;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::iterator array_type_view<container_type,type2>::iterator::operator -- ( int )
{
    let it = self;
    --ptr;
    return it;
}




template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator::const_iterator ( container_type::const_iterator init )
    extends ptr ( init )
{

}

template < class container_type, class type2 >
constexpr const auto array_type_view<container_type,type2>::const_iterator::operator * ( ) const
{
    return type2 ( *ptr );
}

template < class container_type, class type2 >
constexpr bool array_type_view<container_type,type2>::const_iterator::operator == ( const const_iterator& right ) const
{
    return ptr == right.ptr;
}

template < class container_type, class type2 >
constexpr std::strong_ordering array_type_view<container_type,type2>::const_iterator::operator <=> ( const const_iterator& right ) const
{
    return ptr <=> right.ptr;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::const_iterator::operator + ( int offset ) const
{
    return const_iterator ( ptr + offset );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::const_iterator::operator - ( int offset ) const
{
    return const_iterator ( ptr - offset );
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator::difference_type array_type_view<container_type,type2>::const_iterator::operator - ( const const_iterator& right ) const
{
    return ptr - right.ptr;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator& array_type_view<container_type,type2>::const_iterator::operator ++ ( )
{
    ++ptr;
    return self;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::const_iterator::operator ++ ( int )
{
    let it = self;
    ++ptr;
    return it;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator& array_type_view<container_type,type2>::const_iterator::operator -- ( )
{
    --ptr;
    return self;
}

template < class container_type, class type2 >
constexpr array_type_view<container_type,type2>::const_iterator array_type_view<container_type,type2>::const_iterator::operator -- ( int )
{
    let it = self;
    --ptr;
    return it;
}











// Auxiliary

template < class >
struct aux::is_array_type_view
{
    constexpr static const bool value = false;
};

template < class type3, class type4 >
struct aux::is_array_type_view<array_type_view<type3,type4>>
{
    constexpr static const bool value = true;
};

template < class container_type, class type2 >
    requires ( container_type::dimension() == 1 )
struct aux::array_type_view_iterate_type<container_type,type2>
{
    using type = type2;
};

template < class container_type, class type2 >
    requires ( container_type::dimension() >= 2 )
struct aux::array_type_view_iterate_type<container_type,type2>
{
    using type = array_type_view<typename container_type::iterate_type,type2>;
};