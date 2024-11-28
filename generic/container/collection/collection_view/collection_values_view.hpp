#pragma once

template < class container_type >
class collection_values_view
    extends public collection_algo<collection_values_view<container_type>,typename container_type::value_type>
{
    private: // Data
        container_type& col;

    public: // Typedef
        using  value_type   = container_type::value_type;
        using  iterate_type = container_type::value_type;
        class  iterator;
        class  const_iterator;

    public: // Friend
        template < class type2 >
        friend class ap::collection_values_view;
        friend container_type;

    private: // Host
        constexpr const container_type& host ( ) const;

    private: // Constructor
        constexpr collection_values_view ( container_type& );

    public: // Core
        constexpr collection_values_view ( const collection_values_view& ) = default;
        constexpr collection_values_view& operator = ( const collection_values_view& ) = delete;

    public: // Interface
        constexpr int            size     ( ) const;
        constexpr bool           empty    ( ) const;
        constexpr iterator       begin    ( );
        constexpr const_iterator begin    ( ) const;
        constexpr iterator       end      ( );
        constexpr const_iterator end      ( ) const;
};



template < class container_type >
class collection_values_view<container_type>::iterator
    extends public container_type::iterator
{
    public: // Typedef
        using value_type   = container_type::const_iterator::value_type::value_type;
        using pointer_type = value_type*;
        using reference    = value_type&;

    public: // Core
        constexpr auto&     operator *  ( ) const;
        constexpr auto*     operator -> ( ) const;

        constexpr iterator& operator ++ ( );
        constexpr iterator  operator ++ ( int );
        constexpr iterator& operator -- ( );
        constexpr iterator  operator -- ( int );
};


template < class container_type >
class collection_values_view<container_type>::const_iterator
    extends public container_type::const_iterator
{
    public: // Typedef
        using value_type   = container_type::const_iterator::value_type::value_type;
        using pointer_type = const value_type*;
        using reference    = const value_type&;

    public: // Core
        constexpr const auto&     operator *  ( ) const;
        constexpr const auto*     operator -> ( ) const;

        constexpr const_iterator& operator ++ ( );
        constexpr const_iterator  operator ++ ( int );
        constexpr const_iterator& operator -- ( );
        constexpr const_iterator  operator -- ( int );
};

#include "collection_values_view.ipp"