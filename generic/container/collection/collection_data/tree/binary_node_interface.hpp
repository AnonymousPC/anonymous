#pragma once

template < class type, class node >
class binary_node_interface
{
    private: // Data
        type  val       = type();
        node* ptr_up    = nullptr;
        node* ptr_left  = nullptr;
        node* ptr_right = nullptr;

    public: // Typedef
        using value_type = type;

    public: // Core
        constexpr  binary_node_interface ( )                               = default;
        constexpr  binary_node_interface ( const binary_node_interface&  ) = delete;
        constexpr  binary_node_interface (       binary_node_interface&& ) = delete;
        constexpr  binary_node_interface ( std::convertible_to<type> auto&& );
        constexpr ~binary_node_interface ( );
        constexpr  binary_node_interface ( tuple<type> )       requires std::copyable<type>;
        constexpr  auto copy ( )                         const requires std::copyable<type>;

    public: // Conversion
        constexpr       type& value ( );
        constexpr const type& value ( ) const;

    public: // Interface
        constexpr       node& up          ( );
        constexpr const node& up          ( ) const;
        constexpr       node& left        ( );
        constexpr const node& left        ( ) const;
        constexpr       node& right       ( );
        constexpr const node& right       ( ) const;
        constexpr       node& another     ( );
        constexpr const node& another     ( ) const;
        constexpr       node& leftmost    ( );
        constexpr const node& leftmost    ( ) const;
        constexpr       node& rightmost   ( );
        constexpr const node& rightmost   ( ) const;

        constexpr       node& cut_up      ( );
        constexpr       node& cut_left    ( );
        constexpr       node& cut_right   ( );
        constexpr       node& link_left   ( node& );
        constexpr       node& link_right  ( node& );
        constexpr       void  delete_self ( );
        constexpr       void  root_swap   ( node& );

        constexpr       bool  has_up      ( ) const;
        constexpr       bool  has_left    ( ) const;
        constexpr       bool  has_right   ( ) const;
        constexpr       bool  has_another ( ) const;
        constexpr       bool  is_left     ( ) const;
        constexpr       bool  is_right    ( ) const;
        constexpr       bool  is_leaf     ( ) const;

    public: // Tree
        constexpr pair<node&,node&> copy_tree  ( const node& ) requires std::copyable<type>;
        constexpr std::ostream&     print_tree ( std::ostream&, int = 0 ) const;
};


template < class type, class node >
constexpr std::ostream& operator << ( std::ostream&, const binary_node_interface<type,node>& );


#include "binary_node_interface.ipp"