#pragma once

/// Class binary_node_interface

// Core

template < class type, class node >
constexpr binary_node_interface<type,node>::binary_node_interface ( std::convertible_to<type> auto&& init_val )
    extends val ( std::move ( init_val ) )
{

}

template < class type, class node >
constexpr binary_node_interface<type,node>::~binary_node_interface ( )
{
    delete ptr_left;
    delete ptr_right;
}

template < class type, class node >
constexpr binary_node_interface<type,node>::binary_node_interface ( tuple<type> init_val )
    requires std::copyable<type>
    extends binary_node_interface ( std::move(init_val[constexpr_index<1>()]) )
{

}

template < class type, class node >
constexpr auto binary_node_interface<type,node>::copy ( ) const
    requires std::copyable<type>
{
    return tuple(val);
}

// Conversion

template < class type, class node >
constexpr type& binary_node_interface<type,node>::value ( )
{
    return val;
}


template < class type, class node >
constexpr const type& binary_node_interface<type,node>::value ( ) const
{
    return val;
}

// Interface

template < class type, class node >
constexpr node& binary_node_interface<type,node>::up ( )
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return *ptr_up;
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::up ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return *ptr_up;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::left ( )
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif
    return *ptr_left;
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::left ( ) const
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif
    return *ptr_left;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::right ( )
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif
    return *ptr_right;
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::right ( ) const
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif
    return *ptr_right;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::another ( )
{
    #if debug
        if ( not has_another() )
            throw nullptr_error();
    #endif
    return is_left() ? up().right() otherwise
                       up().left ();
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::another ( ) const
{
    #if debug
        if ( not has_another() )
            throw nullptr_error();
    #endif
    return is_left() ? up().right() otherwise
                       up().left ();
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::leftmost ( )
{
    node* ptr = &static_cast<node&>(self);
    while ( ptr->has_left() )
        ptr = ptr->ptr_left;

    return *ptr;
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::leftmost ( ) const
{
    const node* ptr = &static_cast<const node&>(self);
    while ( ptr->has_left() )
        ptr = ptr->ptr_left;

    return *ptr;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::rightmost ( )
{
    node* ptr = &static_cast<node&>(self);
    while ( ptr->has_right() )
        ptr = ptr->ptr_right;

    return *ptr;
}

template < class type, class node >
constexpr const node& binary_node_interface<type,node>::rightmost ( ) const
{
    const node* ptr = &static_cast<const node&>(self);
    while ( ptr->has_right() )
        ptr = ptr->ptr_right;

    return *ptr;
}



template < class type, class node >
constexpr node& binary_node_interface<type,node>::cut_up ( )
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif

    ( is_left() ? up().ptr_left otherwise up().ptr_right ) = nullptr;

    node* ptr = ptr_up;
    ptr_up = nullptr;

    return *ptr;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::cut_left ( )
{
    #if debug
        if ( not has_left() )
            throw nullptr_error();
    #endif

    left().ptr_up = nullptr;

    node* ptr = ptr_left;
    ptr_left = nullptr;

    return *ptr;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::cut_right ( )
{
    #if debug
        if ( not has_right() )
            throw nullptr_error();
    #endif

    right().ptr_up = nullptr;

    node* ptr = ptr_right;
    ptr_right = nullptr;

    return *ptr;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::link_left ( node& link )
{
    #if debug
        if ( has_left() or link.has_up() )
            throw nullptr_error();
    #endif

    self.ptr_left = &link;
    link.ptr_up   = &static_cast<node&>(self);

    return *ptr_left;
}

template < class type, class node >
constexpr node& binary_node_interface<type,node>::link_right ( node& link )
{
    #if debug
        if ( has_right() or link.has_up() )
            throw nullptr_error();
    #endif

    self.ptr_right = &link;
    link.ptr_up    = &static_cast<node&>(self);

    return *ptr_right;
}

template < class type, class node >
constexpr void binary_node_interface<type,node>::delete_self ( )
{
    #if debug
        if ( has_up() )
            throw nullptr_error(); // Not been cut before
    #endif

    delete &static_cast<node&>(self);
}

template < class type, class node >
constexpr void binary_node_interface<type,node>::root_swap ( node& other )
{
    node* self_left   = self .has_left () ? &self .cut_left () otherwise nullptr;
    node* self_right  = self .has_right() ? &self .cut_right() otherwise nullptr;
    node* other_left  = other.has_left () ? &other.cut_left () otherwise nullptr;
    node* other_right = other.has_right() ? &other.cut_right() otherwise nullptr;

    if ( self_left != nullptr )
        other.link_left ( *self_left );
    if ( self_right != nullptr )
        other.link_right ( *self_right );

    if ( other_left != nullptr )
        self.link_left ( *other_left );
    if ( other_right != nullptr )
        self.link_right ( *other_right );
}



template < class type, class node >
constexpr bool binary_node_interface<type,node>::has_up ( ) const
{
    return ptr_up != nullptr;
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::has_left ( ) const
{
    return ptr_left != nullptr;
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::has_right ( ) const
{
    return ptr_right != nullptr;
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::has_another ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return is_left() ? up().has_right() otherwise
                       up().has_left ();
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::is_left ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return up().ptr_left == &self;
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::is_right ( ) const
{
    #if debug
        if ( not has_up() )
            throw nullptr_error();
    #endif
    return up().ptr_right == &self;
}

template < class type, class node >
constexpr bool binary_node_interface<type,node>::is_leaf ( ) const
{
    return not has_left() and not has_right();
}

// Tree

template < class type, class node >
constexpr pair<node&,node&> binary_node_interface<type,node>::copy_tree ( const node& from )
    requires std::copyable<type>
{
    #if debug
        if ( not is_leaf() )
            throw value_error();
    #endif

    return pair<node&,node&> ( from.has_left()  ? static_cast<node&>(self).link_left (*new node(from.left().copy()))
                                                                          .copy_tree (from.left())
                                                                          .key() otherwise
                                                  static_cast<node&>(self),
                               from.has_right() ? static_cast<node&>(self).link_right(*new node(from.right().copy()))
                                                                          .copy_tree (from.right() )
                                                                          .value() otherwise
                                                  static_cast<node&>(self)
                             );
}

template < class type, class node >
constexpr std::ostream& binary_node_interface<type,node>::print_tree ( std::ostream& stream, int indent ) const
{
    for ( int _ in range ( indent ) )
        stream << "    ";
    stream << static_cast<const node&>(self) << '\n';

    if ( is_leaf() )
        return stream;

    if ( has_left() )
        self.left().print_tree ( stream, indent + 1 );
    else
    {
        for ( int _ in range ( indent + 1 ) )
            stream << "    ";
        stream << '_' << '\n';
    }

    if ( has_right() )
        self.right().print_tree ( stream, indent + 1 );
    else
    {
        for ( int _ in range ( indent + 1 ) )
            stream << "    ";
        stream << '_' << '\n';
    }

    return stream;
}





/// Global

template < class type, class node >
constexpr std::ostream& operator << ( std::ostream& left, const binary_node_interface<type,node>& right )
{
    return left << static_cast<const type&>(right);
}