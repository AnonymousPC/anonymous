#pragma once

template < class type, class compares, class node >
class binary_search_tree
    extends public binary_tree<type,node>
{
    public: // Typedef
        using value_type     = type;
        using const_iterator = binary_tree<type,node>::const_iterator;

    public: // Interface
        using binary_tree<type,node>::size,
              binary_tree<type,node>::empty,
              binary_tree<type,node>::begin,
              binary_tree<type,node>::end,
              binary_tree<type,node>::min,
              binary_tree<type,node>::mid,
              binary_tree<type,node>::max,
              binary_tree<type,node>::clear;

        constexpr const_iterator locate ( const auto&  val )                                    const requires requires { compares::equal_to(val,std::declval<type>()); };
        constexpr const_iterator push   (       auto&& val, const_iterator = const_iterator() )       requires std::convertible_to<decltype(val),type>;
        constexpr const_iterator pop    ( const auto&  val, const_iterator = const_iterator() )       requires requires { compares::equal_to(val,std::declval<type>()); };

    private: // Auxiliary
        constexpr const_iterator pop_leaf   ( const_iterator );
        constexpr const_iterator pop_branch ( const_iterator );
        constexpr const_iterator pop_crotch ( const_iterator );
};



template < class type >
class binary_search_tree_node
    extends public binary_node_interface<type,binary_search_tree_node<type>>
{
    using binary_node_interface<type,binary_search_tree_node<type>>::binary_node_interface;
};





#include "binary_search_tree.ipp"