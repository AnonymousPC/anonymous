#pragma once


template < class container_type >
class array_flatten_view
    extends public array_algo<array_flatten_view<container_type>,
                              typename container_type::value_type>
{
    private: // Data
        container_type& arr;

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = container_type::value_type;
        using  iterator       = array_view_iterator      <array_flatten_view>;
        using  const_iterator = array_view_const_iterator<array_flatten_view>;
        using  array_algo     = array_algo<array_flatten_view,typename container_type::value_type>;
        struct array_tag { };

    public: // Friend
        template < class type2 >
        friend class ap::array_flatten_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    public: // Constructor
        constexpr array_flatten_view ( container_type& );

    public: // Core
        constexpr array_flatten_view             ( const array_flatten_view& ) = default;
        constexpr array_flatten_view& operator = ( const array_flatten_view& )             requires std::copyable<value_type>; // Must be written, or the compiler will auto-summon a wrong one.
        constexpr array_flatten_view& operator = ( const array_type<value_type,1> auto&  ) requires std::copyable<value_type>;
        constexpr array_flatten_view& operator = (       array_type<value_type,1> auto&& );

    public: // Interface
        constexpr int            row         ( ) = delete;
        constexpr int            size        ( )     const;
        constexpr bool           empty       ( )     const;
        constexpr iterator       begin       ( );
        constexpr const_iterator begin       ( )     const;
        constexpr iterator       end         ( );
        constexpr const_iterator end         ( )     const;
        constexpr decltype(auto) operator [] ( int );
        constexpr decltype(auto) operator [] ( int ) const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;

    public: // Auxiliary
                               constexpr static decltype(auto) locate        (       auto&,  const auto& );
                               constexpr static decltype(auto) locate        ( const auto&,  const auto& );
                               constexpr static auto           decompose     (               const auto&, int );
        template < int index > constexpr static auto           decompose_aux (       auto&&, const auto&, int, int );
};



/// Template deduction

template < class container_type > array_flatten_view ( container_type ) -> array_flatten_view<container_type>;


#include "array_flatten_view.ipp"