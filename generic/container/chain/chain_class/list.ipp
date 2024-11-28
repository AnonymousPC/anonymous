#pragma once


/// Class list

template < class type >
constexpr list<type>::list ( const list<type>& init )
    requires std::copyable<type>
    extends m ( init.m )
{
    if ( not empty() )
    {
        ptr_last  = &root.copy_list ( init.root );
        ptr_first = &root.next();
    }
}

template < class type >
constexpr list<type>::list ( list<type>&& init )
    extends m         ( std::exchange ( init.m,         0       ) ),
            ptr_first ( std::exchange ( init.ptr_first, nullptr ) ),
            ptr_last  ( std::exchange ( init.ptr_last,  nullptr ) )

{
    if ( not empty() )
        root.link_next ( init.root.cut_next() );
}

template < class type >
constexpr list<type>& list<type>::operator = ( const list<type>& right )
    requires std::copyable<type>
{
    m = right.m;

    if ( not empty() )
        root.cut_next().delete_self();

    if ( not right.empty() )
    {
        ptr_last  = &root.copy_list ( right.root );
        ptr_first = &root.next();
    }

    return self;
}

template < class type >
constexpr list<type>& list<type>::operator = ( list<type>&& right )
{
    std::swap ( m,         right.m         );
    std::swap ( ptr_first, right.ptr_first );
    std::swap ( ptr_last,  right.ptr_last  );
    root.root_swap ( right.root );

    return self;
}

// Interface

template < class type >
constexpr int list<type>::size ( ) const
{
    return m;
}

template < class type >
constexpr bool list<type>::empty ( ) const
{
    return size() == 0;
}

template < class type >
constexpr list<type>::iterator list<type>::begin ( )
{
    return empty() ? iterator() otherwise iterator(*ptr_first);
}

template < class type >
constexpr list<type>::const_iterator list<type>::begin ( ) const
{
    return empty() ? const_iterator() otherwise const_iterator(*ptr_first);
}

template < class type >
constexpr list<type>::iterator list<type>::end ( )
{
    return iterator();
}

template < class type >
constexpr list<type>::const_iterator list<type>::end ( ) const
{
    return const_iterator();
}

template < class type >
constexpr type& list<type>::front ( )
{
    #if debug
        if ( empty() )
            throw value_error("get front() from empty list");
    #endif

    return *ptr_first;
}

template < class type >
constexpr const type& list<type>::front ( ) const
{
    #if debug
        if ( empty() )
            throw value_error("get front() from empty list");
    #endif

    return *ptr_first;
}


template < class type >
constexpr type& list<type>::back ( )
{
    #if debug
        if ( empty() )
            throw value_error("get back() from empty list");
    #endif

    return *ptr_last;
}

template < class type >
constexpr const type& list<type>::back ( ) const
{
    #if debug
        if ( empty() )
            throw value_error("get back() from empty list");
    #endif

    return *ptr_last;
}

template < class type >
constexpr void list<type>::push_front ( type val )
    requires std::movable<type>
{
    auto& nd = *new node ( std::move ( val ) );

    if ( not empty() )
    {
        m++;
        ptr_first = &root.cut_next  ()
                         .link_prev ( nd )
                         .link_prev ( root )
                         .next      ();
    }

    else
    {
        m++;
        ptr_first = &root.link_next ( nd );
        ptr_last  = &root.next();
    }
}

template < class type >
constexpr void list<type>::push_back ( type val )
    requires std::movable<type>
{
    auto& nd = *new node ( std::move ( val ) );

    if ( not empty() )
    {
        m++;
        ptr_last = &( ptr_last -> link_next ( nd ) );
    }

    else
    {
        m++;
        ptr_first = &root.link_next ( nd );
        ptr_last  = &root.next();
    }
}

template < class type >
constexpr type list<type>::pop_front ( )
    requires std::movable<type>
{
    #if debug
        if ( empty() )
            throw value_error("pop_front() from empty list");
    #endif

    type out = std::move ( static_cast<type&> ( *ptr_first ) );

    if ( size() >= 2 )
    {
        m--;
        node& poped = *ptr_first;
        ptr_first = &root.cut_next()
                         .cut_next()
                         .link_prev ( root )
                         .next();
        poped.delete_self();
    }
    else
    {
        m--;
        root.cut_next().delete_self();
        ptr_first = nullptr;
        ptr_last  = nullptr;
    }

    return out;
}

template < class type >
constexpr type list<type>::pop_back ( )
    requires std::movable<type>
{
    #if debug
        if ( empty() )
            throw value_error("pop_back() from empty list");
    #endif

    type out = std::move ( static_cast<type&> ( *ptr_last ) );

    if ( size() >= 2 )
    {
        m--;
        node& poped = *ptr_last;
        ptr_last = &( ptr_last -> cut_prev() );
        poped.delete_self();
    }
    else
    {
        m--;
        root.cut_next().delete_self();
        ptr_first = nullptr;
        ptr_last  = nullptr;
    }

    return out;
}









/// Class list::node

// Core

template < class type >
constexpr list<type>::node::node ( type init_data )
    extends data ( std::move ( init_data ) )
{

}

template < class type >
constexpr list<type>::node::~node ( )
{
    delete ptr_next;
}

// Conversion

template < class type >
constexpr list<type>::node::operator type& ( )
{
    return data;
}

template < class type >
constexpr list<type>::node::operator const type& ( ) const
{
    return data;
}

// Interface

template < class type >
constexpr list<type>::node& list<type>::node::prev ( )
{
    #if debug
        if ( not has_prev() )
            throw nullptr_error();
    #endif

    return *ptr_prev;
}

template < class type >
constexpr const list<type>::node& list<type>::node::prev ( ) const
{
    #if debug
        if ( not has_prev() )
            throw nullptr_error();
    #endif

    return *ptr_prev;
}

template < class type >
constexpr list<type>::node& list<type>::node::next ( )
{
    #if debug
        if ( not has_next() )
            throw nullptr_error();
    #endif

    return *ptr_next;
}

template < class type >
constexpr const list<type>::node& list<type>::node::next ( ) const
{
    #if debug
        if ( not has_next() )
            throw nullptr_error();
    #endif

    return *ptr_next;
}

template < class type >
constexpr bool list<type>::node::has_prev ( ) const
{
    return ptr_prev != nullptr;
}

template < class type >
constexpr bool list<type>::node::has_next ( ) const
{
    return ptr_next != nullptr;
}

template < class type >
constexpr list<type>::node& list<type>::node::cut_prev ( )
{
    #if debug
        if ( not has_prev() )
            throw nullptr_error();
    #endif

    node& nd = prev();

    self.ptr_prev = nullptr;
    nd  .ptr_next = nullptr;

    return nd;
}

template < class type >
constexpr list<type>::node& list<type>::node::cut_next ( )
{
    #if debug
        if ( not has_next() )
            throw nullptr_error();
    #endif

    node& nd = next();

    self.ptr_next = nullptr;
    nd  .ptr_prev = nullptr;

    return nd;
}

template < class type >
constexpr list<type>::node& list<type>::node::link_prev ( node& link )
{
    #if debug
        if ( has_prev() or link.has_next() )
            throw nullptr_error();
    #endif

    self.ptr_prev = &link;
    link.ptr_next = &self;

    return prev();
}

template < class type >
constexpr list<type>::node& list<type>::node::link_next ( node& link )
{
    #if debug
        if ( has_next() or link.has_prev() )
            throw nullptr_error();
    #endif

    self.ptr_next = &link;
    link.ptr_prev = &self;

    return next();
}

template < class type >
constexpr void list<type>::node::delete_self ( )
{
    #if debug
        if ( self.has_prev() )
            throw nullptr_error(); // Not been cut before.
    #endif

    delete &self;
}



// Auxiliary

template < class type >
constexpr void list<type>::node::root_swap ( node& other )
{
    node* self_next  = self .has_next() ? &self .cut_next() otherwise nullptr;
    node* other_next = other.has_next() ? &other.cut_next() otherwise nullptr;

    if ( self_next != nullptr )
        other.link_next ( *self_next );

    if ( other_next != nullptr )
        self.link_next ( *other_next );
}

template < class type >
constexpr list<type>::node& list<type>::node::copy_list ( const node& from )
{
    #if debug
        if ( has_next() )
            throw value_error();
    #endif

    if ( from.has_next() )
        return self.link_next ( *new node ( from.next().data ) )
                   .copy_list ( from.next() );
    else
        return self;
}




// Class list::iterator

template < class type >
constexpr list<type>::iterator::iterator ( node& nd )
    extends ptr ( &nd )
{

}

template < class type >
constexpr type& list<type>::iterator::operator * ( ) const
{
    return *ptr;
}

template < class type >
constexpr type* list<type>::iterator::operator -> ( ) const
{
    return &static_cast<type&>(*ptr);
}

template < class type >
constexpr list<type>::iterator& list<type>::iterator::operator ++ ( )
{
    ptr = ptr->ptr_next;
    return self;
}

template < class type >
constexpr list<type>::iterator list<type>::iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type >
constexpr list<type>::iterator& list<type>::iterator::operator -- ( )
{
    ptr = ptr->ptr_prev;
    return self;
}

template < class type >
constexpr list<type>::iterator list<type>::iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}



// Class list::const_iterator

template < class type >
constexpr list<type>::const_iterator::const_iterator ( const node& nd )
    extends ptr ( &nd )
{

}

template < class type >
constexpr const type& list<type>::const_iterator::operator * ( ) const
{
    return *ptr;
}

template < class type >
constexpr const type* list<type>::const_iterator::operator -> ( ) const
{
    return &static_cast<const type&>(*ptr);
}

template < class type >
constexpr list<type>::const_iterator& list<type>::const_iterator::operator ++ ( )
{
    ptr = ptr->ptr_next;
    return self;
}

template < class type >
constexpr list<type>::const_iterator list<type>::const_iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type >
constexpr list<type>::const_iterator& list<type>::const_iterator::operator -- ( )
{
    ptr = ptr->ptr_prev;
    return self;
}

template < class type >
constexpr list<type>::const_iterator list<type>::const_iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}