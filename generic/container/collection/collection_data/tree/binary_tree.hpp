#pragma once

/* Note:
 * Binary_tree ( with trees based on binary_tree ) provides and only provides interfaces below:
 *
 * constructor, destructor, copy, move.
 * begin(), end(), min(), mid(), max(), locate(). [[ locate()      is always shortest  ]].
 * clear(), erase(), push(), pop().               [[ push(), pop() is always rightmost ]].
 *
 * In default compare mode, no repeated items are allowed.
 */


template < class type, class node >
class binary_tree
{
    private: // Data
        int         m       = 0;
        node        root    = node(); // root always not has_right() and link its left to data.
        const node* ptr_min = nullptr;
        const node* ptr_max = nullptr;

    public: // Typedef
        using value_type = type;
        class const_iterator;

    public: // Core
        constexpr  binary_tree ( ) = default;
        constexpr  binary_tree ( const binary_tree&  );
        constexpr  binary_tree (       binary_tree&& );
        constexpr  binary_tree& operator = ( binary_tree );

    public: // Interface
        constexpr  int            size    ( )     const;
        constexpr  bool           empty   ( )     const;

        constexpr  const_iterator begin   ( )     const;
        constexpr  const_iterator end     ( )     const;
        constexpr  const_iterator min     ( )     const;
        constexpr  const_iterator mid     ( )     const;
        constexpr  const_iterator max     ( )     const;
        constexpr  const_iterator clear   ( );

    public: // Print
        std::ostream& print_tree ( std::ostream& ) const;

    protected: // Auxiliary
        constexpr int&         get_size    ( );
        constexpr const node*& get_min     ( );
        constexpr const node*& get_max     ( );
};




template < class type >
class binary_tree_node
    extends public binary_node_interface<type,binary_tree_node<type>>
{
    using binary_node_interface<type,binary_tree_node<type>>::binary_node_interface;
};





template < class type, class node >
class binary_tree<type,node>::const_iterator
{
    private: // Data
        const node* ptr = nullptr;

    public: // Typedef
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const type*;
        using reference         = const type&;

    public: // Core
        constexpr const_iterator ( ) = default;

    public: // Conversion
        constexpr const_iterator ( const node* );
        constexpr operator         const node* ( ) const;

    public: // Interface
        constexpr const type&     operator  * ( )                       const;
        constexpr const type*     operator -> ( )                       const;
        constexpr bool            operator == ( const const_iterator& ) const = default;
        constexpr bool            operator != ( const const_iterator& ) const = default;
        constexpr const_iterator& operator ++ ( );
        constexpr const_iterator  operator ++ ( int );
        constexpr const_iterator& operator -- ( );
        constexpr const_iterator  operator -- ( int );
};



template < class type > std::ostream& operator << ( std::ostream&, const binary_tree<type>& ) requires printable<type>;


#include "binary_tree.ipp"