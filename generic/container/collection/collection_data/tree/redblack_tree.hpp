#pragma once

template < class type, class compares, class node >
class redblack_tree
    extends public binary_search_tree<type,compares,node>
{
    public: // Typedef
        using value_type     = type;
        using const_iterator = binary_search_tree<type,compares,node>::const_iterator;

    public: // Interface
        using binary_search_tree<type,compares,node>::size,
              binary_search_tree<type,compares,node>::empty,
              binary_search_tree<type,compares,node>::begin,
              binary_search_tree<type,compares,node>::end,
              binary_search_tree<type,compares,node>::min,
              binary_search_tree<type,compares,node>::mid,
              binary_search_tree<type,compares,node>::max,
              binary_search_tree<type,compares,node>::clear,
              binary_search_tree<type,compares,node>::locate;

        constexpr const_iterator push   (       auto&& val, const_iterator = const_iterator() ) requires std::convertible_to<decltype(val),type>;
        constexpr const_iterator pop    ( const auto&  val, const_iterator = const_iterator() ) requires requires { compares::equal_to(val,std::declval<type>()); };

    private: // Auxiliary
        constexpr void push_balance                ( const_iterator ); // Note: input node must be red.
        constexpr void push_balance_combine_red    ( const_iterator );
        constexpr void push_balance_same_direction ( const_iterator );
        constexpr void push_balance_diff_direction ( const_iterator );
        constexpr void pop_balance                 ( const_iterator );
        constexpr void left_rotate                 ( const_iterator );
        constexpr void right_rotate                ( const_iterator );
};



template < class type >
class redblack_tree_node
    extends public binary_node_interface<type,redblack_tree_node<type>>
{
    public: // Data
        enum { red = 1, black = 0 };
        bool flag = red;

    public: // Core
        using binary_node_interface<type,redblack_tree_node<type>>::binary_node_interface;
        constexpr redblack_tree_node ( tuple<type,bool> )       requires std::copyable<type>;
        constexpr auto copy ( )                           const requires std::copyable<type>;

    public: // Interface
        constexpr       bool& color ( );
        constexpr const bool& color ( ) const;
};

template < class type >
constexpr std::ostream& operator << ( std::ostream&, const redblack_tree_node<type>& );

#include "redblack_tree.ipp"