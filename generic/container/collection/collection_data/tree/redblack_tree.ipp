#pragma once

#define top() (*const_cast<node*>(static_cast<const node*>(mid())))

/// Class redblack_tree

// Member

template < class type, class compares, class node >
constexpr redblack_tree<type,compares,node>::const_iterator redblack_tree<type,compares,node>::push ( auto&& val, const_iterator it )
    requires std::convertible_to<decltype(val),type>
{
    if ( size() == 0 )
        top().color() = node::black; // In default constructor it's red, we turn it into black the first time we push in new nodes.

    let unbalanced = binary_search_tree<type,compares,node>::push(std::move(val), it);
    push_balance(unbalanced);
    top().color() = node::black;
    return unbalanced;
}

template < class type, class compares, class node >
constexpr redblack_tree<type,compares,node>::const_iterator redblack_tree<type,compares,node>::pop ( const auto& val, const_iterator it )
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    let unbalanced = binary_search_tree<type,compares,node>::pop(val, it);
    top().color() = node::black;
    pop_balance(unbalanced);
    return unbalanced;
}

// Auxiliary

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::push_balance ( const_iterator it ) // Note: color must be red.
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));

    if ( curr->up().color() == node::black )
        return;

    // Now nd.color() == red and nd.up().color() == red, where conflicts happens.

    if ( curr != &top() )
    {
        if ( curr->up().has_another() and curr->up().another().color() == node::red )
            return push_balance_combine_red(curr);

        else if ( curr->is_left() == curr->up().is_left() )
            return push_balance_same_direction(curr);

        else
            return push_balance_diff_direction(curr);
    }
}

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::push_balance_combine_red ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));

    curr->up()           .color() = node::black;
    curr->up().another() .color() = node::black;
    curr->up().up()      .color() = node::red;

    return push_balance(&curr->up().up());
}

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::push_balance_same_direction ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));

    curr->is_left() ? right_rotate(&curr->up()) otherwise left_rotate(&curr->up());
    curr->up()     .color() = node::black;
    curr->another().color() = node::red;

    return;
}

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::push_balance_diff_direction ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));

    if ( curr->is_left() )
    {
        right_rotate(curr);
        return push_balance_same_direction(&curr->right());
    }

    else
    {
        left_rotate(curr);
        return push_balance_same_direction(&curr->left());
    }
}

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::pop_balance ( const_iterator )
{
    return;
}


template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::left_rotate ( const_iterator it )
{
    node* axis = const_cast<node*>(static_cast<const node*>(it));

    #if debug
        if ( axis->is_left() or not axis->up().has_up() )
            throw nullptr_error();
    #endif

    bool flag = axis->up().is_left();

    node* a = &axis->up().cut_up();
    node* b = &axis->cut_up();
    node* c = axis->has_left() ? &axis->cut_left() otherwise nullptr;

    flag ? a->link_left(*axis) otherwise a->link_right(*axis);
    axis->link_left(*b);

    if ( c != nullptr )
        b->link_right(*c);
}

template < class type, class compares, class node >
constexpr void redblack_tree<type,compares,node>::right_rotate ( const_iterator it )
{
    node* axis = const_cast<node*>(static_cast<const node*>(it));

    #if debug
        if ( axis->is_right() or not axis->up().has_up() )
            throw nullptr_error();
    #endif

    bool flag = axis->up().is_right();

    node* a = &axis->up().cut_up();
    node* b = &axis->cut_up();
    node* c = axis->has_right() ? &axis->cut_right() otherwise nullptr;

    flag ? a->link_right(*axis) otherwise a->link_left(*axis);
    axis->link_right(*b);

    if ( c != nullptr )
        b->link_left(*c);
}









/// Class redblack_tree_node

template < class type >
constexpr redblack_tree_node<type>::redblack_tree_node ( tuple<type,bool> init_data )
    requires std::copyable<type>
    extends binary_node_interface<type,redblack_tree_node<type>> ( std::move(init_data[constexpr_index<1>()]) ),
            flag                                                 ( std::move(init_data[constexpr_index<2>()]) )
{

}

template < class type >
constexpr auto redblack_tree_node<type>::copy ( ) const
    requires std::copyable<type>
{
    return tuple(self.value(), color());
}

template < class type >
constexpr bool& redblack_tree_node<type>::color ( )
{
    return flag;
}

template < class type >
constexpr const bool& redblack_tree_node<type>::color ( ) const
{
    return flag;
}

template < class type >
constexpr std::ostream& operator << ( std::ostream& left, const redblack_tree_node<type>& right )
{
    return left << right.value() << '[' << (right.color() == right.red ? "red" otherwise "black") << ']';
}

#undef color
#undef top