#pragma once

/// Class binary_search_tree

// Member

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::locate ( const auto& val ) const
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    if ( size() == 0 )
        return const_iterator ( end() );

    else // size() >= 1
    {
        const node* ptr = mid();

        while ( true )
        {
            if ( compares::equal_to(val, ptr->value()) )    // ==
                return ptr;

            if ( compares::less(val, ptr->value()) )        // <
                if ( ptr->has_left() )
                    ptr = &ptr->left();
                else
                    return ptr;

            else                                                                 // >
                if ( ptr->has_right() )
                    ptr = &ptr->right();
                else
                    return ptr;
        }
    }
}

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::push ( auto&& val, const_iterator it )
    requires std::convertible_to<decltype(val),type>
{
    if ( size() == 0 )
    {
        node* ptr = &const_cast<node*>(static_cast<const node*>(end()))->link_left(*new node(std::move(val)));
        self.get_size() ++;
        self.get_min () = ptr;
        self.get_max () = ptr;
        return ptr;
    }

    else // size() >= 1
    {
        node* ptr = const_cast<node*>(static_cast<const node*>(it != const_iterator() ? it otherwise locate(val)));

        #if debug
            if ( compares::equal_to(val, ptr->value()) ) // ==
                throw key_error("key {} already exists", val);
        #endif

        if ( compares::less(val, ptr->value()) )         // <
        {
            ptr = &ptr->link_left(*new node(std::move(val)));
            self.get_size() ++;
            self.get_min () = const_iterator(&ptr->up()) == self.min() ? const_iterator(ptr) otherwise self.min();
            return ptr;
        }

        else                                                                   // >
        {
            ptr = &ptr->link_right(*new node(std::move(val)));
            self.get_size() ++;
            self.get_max () = const_iterator(&ptr->up()) == self.max() ? const_iterator(ptr) otherwise self.max();
            return ptr;
        }
    }
}

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::pop ( const auto& val, const_iterator it )
    requires requires { compares::equal_to(val,std::declval<type>()); }
{
    #if debug
        if ( size() == 0 )
            throw key_error("key {} does not exist", val);
    #endif

    if ( size() == 1 )
    {
        #if debug
            if ( not compares::equal_to(val, *mid()) )
                throw key_error("key {} does not exist", val);
        #endif

        const_cast<node*>(static_cast<const node*>(mid()))->up().cut_left().delete_self();
        self.get_size() --;
        self.get_min () = end();
        self.get_max () = end();
        return end();
    }

    else // size() >= 2
    {
        node* ptr = const_cast<node*>(static_cast<const node*>(it != const_iterator() ? it otherwise locate(val)));

        #if debug
            if ( not compares::equal_to(val, ptr->value()) )
                throw key_error("key {} does not eixst", val);
        #endif

        self.get_size() --;
        self.get_min() = self.min() != const_iterator(ptr) ? self.min() otherwise ++const_iterator(self.min());
        self.get_max() = self.max() != const_iterator(ptr) ? self.max() otherwise --const_iterator(self.max());
        return ptr->is_leaf()                      ? pop_leaf   ( ptr ) otherwise
               ptr->has_left() != ptr->has_right() ? pop_branch ( ptr ) otherwise
                                                     pop_crotch ( ptr );
    }
}

// Auxiliary

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::pop_leaf ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));
    node* high = &curr->up();
    curr->is_left() ? curr->up().cut_left ().delete_self() otherwise
                      curr->up().cut_right().delete_self();
    return high;
}

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::pop_branch ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));
    node* high = curr->is_left() ? &curr->cut_up().link_left (curr->has_left() ? curr->cut_left() otherwise curr->cut_right()) otherwise
                                   &curr->cut_up().link_right(curr->has_left() ? curr->cut_left() otherwise curr->cut_right());
    curr->delete_self();
    return high;
}

template < class type, class compares, class node >
constexpr binary_search_tree<type,compares,node>::const_iterator binary_search_tree<type,compares,node>::pop_crotch ( const_iterator it )
{
    node* curr = const_cast<node*>(static_cast<const node*>(it));
    node* next = &curr->right().leftmost();

    if ( &curr->right() != next ) // Not adjacent
    {
        bool  curr_is_left   = curr->is_left();
        node* curr_up        = &curr->cut_up();
        node* curr_left      = &curr->cut_left();
        node* curr_right     = &curr->cut_right();

        bool  next_is_left   = next->is_left();
        node* next_up        = &next->cut_up();
        node* next_right     = next->has_right() ? &next->cut_right() otherwise nullptr;

        curr_is_left ? curr_up->link_left (*next) otherwise
                       curr_up->link_right(*next);
        next->link_left (*curr_left );
        next->link_right(*curr_right);

        next_is_left ? next_up->link_left (*curr) otherwise
                       next_up->link_right(*curr);
        if ( next_right != nullptr )
            curr->link_right(*next_right);
    }

    else // Adjacent
    {
        curr->cut_right(); // == next.
        bool  curr_is_left   = curr->is_left();
        node* curr_up        = &curr->cut_up();
        node* curr_left      = &curr->cut_left();
        node* next_right     = next->has_right() ? &next->cut_right() otherwise nullptr;

        curr_is_left ? curr_up->link_left(*next) otherwise curr_up->link_right(*next);
        next->link_left (*curr_left);
        next->link_right(*curr);
        if ( next_right != nullptr )
            curr->link_right(*next_right);
    }

    return curr->is_leaf() ? pop_leaf(curr) otherwise pop_branch(curr); // As the remain size() >= 2.
}