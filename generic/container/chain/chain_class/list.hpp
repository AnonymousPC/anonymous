#pragma once


template < class type >
class list
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> );

    private: // Class node;
        class node;

    private: // Data
        int   m         = 0;
        node  root      = node();
        node* ptr_first = nullptr;
        node* ptr_last  = nullptr;

    public: // Typedef
        using  value_type = type;
        class  iterator;
        class  const_iterator;
        struct list_tag { };

    public: // Core
        constexpr list ( ) = default;
        constexpr list ( const list&  )             requires std::copyable<type>;
        constexpr list (       list&& );
        constexpr list& operator = ( const list&  ) requires std::copyable<type>;
        constexpr list& operator = (       list&& );

    public: // Interface
        constexpr       int            size       ( ) const;
        constexpr       bool           empty      ( ) const;
        constexpr       iterator       begin      ( );
        constexpr       const_iterator begin      ( ) const;
        constexpr       iterator       end        ( );
        constexpr       const_iterator end        ( ) const;

        constexpr       type&          front      ( );
        constexpr const type&          front      ( ) const;
        constexpr       type&          back       ( );
        constexpr const type&          back       ( ) const;

        constexpr       void           push_front ( type ) requires std::movable<type>;
        constexpr       void           push_back  ( type ) requires std::movable<type>;
        constexpr       type           pop_front  ( )      requires std::movable<type>;
        constexpr       type           pop_back   ( )      requires std::movable<type>;
};




template < class type >
class list<type>::node
{
    private: // Data
        type  data     = type();
        node* ptr_prev = nullptr;
        node* ptr_next = nullptr;

    public: // Core
        constexpr  node ( )             = default;
        constexpr  node ( type );
        constexpr  node ( const node& ) = delete;
        constexpr ~node ( );

    public: // Conversion
        constexpr operator       type& ( );
        constexpr operator const type& ( ) const;

    public: // Interface
        constexpr       node& prev ( );
        constexpr const node& prev ( ) const;
        constexpr       node& next ( );
        constexpr const node& next ( ) const;

        constexpr       bool  has_prev    ( ) const;
        constexpr       bool  has_next    ( ) const;
        constexpr       node& cut_prev    ( );
        constexpr       node& cut_next    ( );
        constexpr       node& link_prev   ( node& );
        constexpr       node& link_next   ( node& );
        constexpr       void  delete_self ( );

    public: // Friend
        friend list<type>::iterator;
        friend list<type>::const_iterator;

    public: // Auxiliary
        constexpr void  root_swap ( node& );
        constexpr node& copy_list ( const node& );
};





template < class type >
class list<type>::iterator
{
    private: // Data
        node* ptr;

    public: // Typedef
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = value_type*;
        using reference         = value_type&;

    public: // Core
        constexpr iterator ( ) = default;
        constexpr iterator ( node& );

    public: // Interface
        constexpr type&     operator *  ( )                 const;
        constexpr type*     operator -> ( )                 const;

        constexpr bool      operator == ( const iterator& ) const = default;
        constexpr bool      operator != ( const iterator& ) const = default;

        constexpr iterator& operator ++ ( );
        constexpr iterator  operator ++ ( int );
        constexpr iterator& operator -- ( );
        constexpr iterator  operator -- ( int );
};


template < class type >
class list<type>::const_iterator
{
    private: // Data
        const node* ptr;

    public: // Typedef
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = type;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const value_type*;
        using reference         = const value_type&;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( const node& );

    public: // Interface
        constexpr const type&     operator *  ( )                       const;
        constexpr const type*     operator -> ( )                       const;

        constexpr bool            operator == ( const const_iterator& ) const = default;
        constexpr bool            operator != ( const const_iterator& ) const = default;

        constexpr const_iterator& operator ++ ( );
        constexpr const_iterator  operator ++ ( int );
        constexpr const_iterator& operator -- ( );
        constexpr const_iterator  operator -- ( int );
};





#include "list.ipp"