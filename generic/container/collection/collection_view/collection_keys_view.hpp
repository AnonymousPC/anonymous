#pragma once

template < class container_type >
class collection_keys_view
    extends public collection_algo<collection_keys_view<container_type>,typename container_type::key_type>
{
    private: // Data
        container_type& col;

    public: // Typedef
        using  key_type     = container_type::key_type;
        using  value_type   = container_type::key_type;
        using  iterate_type = container_type::key_type;
        using  compare_type = container_type::key_compare_type;
        class  const_iterator;
        struct set_tag { };

    public: // Friend
        template < class type2 >
        friend class ap::collection_keys_view;
        friend container_type;

    private: // Host
        constexpr const container_type& host ( ) const;

    private: // Constructor
        constexpr collection_keys_view ( container_type& );

    public: // Core
        constexpr collection_keys_view ( const collection_keys_view& ) = default;
        constexpr collection_keys_view& operator = ( const collection_keys_view& );

    public: // Interface
        constexpr int            size     ( )                   const;
        constexpr bool           empty    ( )                   const;
        constexpr const_iterator begin    ( )                   const;
        constexpr const_iterator end      ( )                   const;
        constexpr bool           contains ( const value_type& ) const;
};



template < class container_type >
class collection_keys_view<container_type>::const_iterator
    extends public container_type::const_iterator
{
    public: // Typedef
        using value_type   = container_type::const_iterator::value_type::key_type;
        using pointer      = const value_type*;
        using reference    = const value_type&;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( const container_type::const_iterator& );

        constexpr const auto&     operator *  ( ) const;
        constexpr const auto*     operator -> ( ) const;

        constexpr const_iterator& operator ++ ( );
        constexpr const_iterator  operator ++ ( int );
        constexpr const_iterator& operator -- ( );
        constexpr const_iterator  operator -- ( int );
};

#include "collection_keys_view.ipp"