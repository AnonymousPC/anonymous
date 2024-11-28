#pragma once

/// Class binary_tree

// Core

template < class type, class node >
constexpr binary_tree<type,node>::binary_tree ( const binary_tree& init )
    extends m ( init.m )
{
    if ( not empty() )
    {
        let min_max = root.copy_tree ( init.root );
        ptr_min = &min_max.key();
        ptr_max = &min_max.value();
    }
}

template < class type, class node >
constexpr binary_tree<type,node>::binary_tree ( binary_tree&& init )
    extends m       ( std::exchange ( init.m,       0       ) ),
            ptr_min ( std::exchange ( init.ptr_min, nullptr ) ),
            ptr_max ( std::exchange ( init.ptr_max, nullptr ) )
{
    if ( init.root.has_left() )
        root.link_left  ( init.root.cut_left()  );

    if ( init.root.has_right() )
        root.link_right ( init.root.cut_right() );
}

template < class type, class node >
constexpr binary_tree<type,node>& binary_tree<type,node>::operator = ( binary_tree right )
{
    std::swap ( m,       right.m       );
    std::swap ( ptr_min, right.ptr_min );
    std::swap ( ptr_max, right.ptr_max );
    root.root_swap ( right.root );

    return self;
}

// Interface

template < class type, class node >
constexpr int binary_tree<type,node>::size ( ) const
{
    return m;
}

template < class type, class node >
constexpr bool binary_tree<type,node>::empty ( ) const
{
    return size() == 0;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::begin ( ) const
{
    return empty() ? &root otherwise ptr_min;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::end ( ) const
{
    return &root;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::max ( ) const
{
    return ptr_max != nullptr ? ptr_max otherwise &root;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::mid ( ) const
{
    return not empty() ? &root.left() otherwise &root;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::min ( ) const
{
    return ptr_min != nullptr ? ptr_min otherwise &root;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::clear ( )
{
    m = 0;
    if ( not empty() )
        root.left().delete_self();

    return const_iterator ( &root );
}


// Print

template < class type, class node >
std::ostream& binary_tree<type,node>::print_tree ( std::ostream& str ) const
{
    return not empty() ? static_cast<const node*>(mid())->print_tree(str) otherwise str;
}

// Auxiliary

template < class type, class node >
constexpr int& binary_tree<type,node>::get_size ( )
{
    return m;
}

template < class type, class node >
constexpr const node*& binary_tree<type,node>::get_min ( )
{
    return ptr_min;
}

template < class type, class node >
constexpr const node*& binary_tree<type,node>::get_max ( )
{
    return ptr_max;
}




/// Class binary_tree::const_iterator

// Conversion

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator::const_iterator ( const node* init )
    extends ptr ( init )
{

}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator::operator const node* ( ) const
{
    return ptr;
}

// Interface

template < class type, class node >
constexpr const type& binary_tree<type,node>::const_iterator::operator * ( ) const
{
    return ptr->value();
}

template < class type, class node >
constexpr const type* binary_tree<type,node>::const_iterator::operator -> ( ) const
{
    return &ptr->value();
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator& binary_tree<type,node>::const_iterator::operator ++ ( )
{
    if ( ptr->has_right() )
        ptr = &ptr->right().leftmost();
    else
        if ( ptr->is_left() )
            ptr = &ptr->up();
        else
        {
            while ( not ptr->is_left() )
                ptr = &ptr->up();
            ptr = &ptr->up();
        }

    return self;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::const_iterator::operator ++ ( int )
{
    let it = self;
    ++self;
    return it;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator& binary_tree<type,node>::const_iterator::operator -- ( )
{
    if ( ptr->has_left() )
        ptr = &ptr->left().rightmost();
    else
        if ( ptr->is_right() )
            ptr = &ptr->up();
        else
        {
            while ( not ptr->is_right() )
            {
                ptr = &ptr->up();

                if ( not ptr->has_up() ) // Pointing to root.
                    return self;
            }
            ptr = &ptr->up();
        }

    return self;
}

template < class type, class node >
constexpr binary_tree<type,node>::const_iterator binary_tree<type,node>::const_iterator::operator -- ( int )
{
    let it = self;
    --self;
    return it;
}



/// Global

template < class type, class node >
std::ostream& operator << ( std::ostream& left, const binary_tree<type,node>& right )
    requires printable<type>
{
    return right.print_tree(left);
}