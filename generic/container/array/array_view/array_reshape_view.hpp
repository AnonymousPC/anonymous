#pragma once

template < class container_type, int dim, int dim_to_fill >
class array_reshape_view
    extends public array_algo<array_reshape_view<container_type,dim,dim_to_fill>,
                              typename container_type::value_type,
                              typename std::conditional<dim_to_fill<dim,array_reshape_view<container_type,dim,dim_to_fill+1>,typename container_type::value_type>::type,
                              dim-dim_to_fill+1>
{
    private: // Data
        using coor_type = array_coordinate<dim>;

        container_type& arr;
        coor_type       new_shape = coor_type();
        coor_type       new_index = coor_type();

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = std::conditional<dim_to_fill<dim,array_reshape_view<container_type,dim,dim_to_fill+1>,value_type>::type; // dim_to_fill [[less than]] dim.
        using  iterator       = array_view_iterator      <array_reshape_view>;
        using  const_iterator = array_view_const_iterator<array_reshape_view>;
        using  array_algo     = array_algo<array_reshape_view<container_type,dim,dim_to_fill>,typename container_type::value_type,typename std::conditional<dim_to_fill<dim,array_reshape_view<container_type,dim,dim_to_fill+1>,typename container_type::value_type>::type,dim-dim_to_fill+1>;
        struct array_tag { };

    public: // Friend
        template < class type2, int type3, int type4 >
        friend class ap::array_reshape_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    public: // Constructor
        constexpr array_reshape_view ( container_type&, const coor_type&, const coor_type& = coor_type() );

    public: // N-dimension
        constexpr static int            dimension   ( );
        constexpr        array<int>     shape       ( ) const;
        constexpr        coor_type      tuple_shape ( ) const;
        constexpr        auto           reshape     ( int_type auto... args )       requires ( ( dim == 1 and sizeof...(args) >= 2 ) or ( dim >= 2 and sizeof...(args) >= 1 ) );
        constexpr const  auto           reshape     ( int_type auto... args ) const requires ( ( dim == 1 and sizeof...(args) >= 2 ) or ( dim >= 2 and sizeof...(args) >= 1 ) );

    public: // Interface
        constexpr       int            row         ( )     const requires ( dimension() >= 2 );
        constexpr       int            size        ( )     const;
        constexpr       bool           empty       ( )     const;
        constexpr       void           resize      ( ) = delete;
        constexpr       iterator       begin       ( );
        constexpr       const_iterator begin       ( )     const;
        constexpr       iterator       end         ( );
        constexpr       const_iterator end         ( )     const;
        constexpr       decltype(auto) operator [] ( int )       requires ( dimension() == 1 );
        constexpr       decltype(auto) operator [] ( int ) const requires ( dimension() == 1 );
        constexpr       auto           operator [] ( int )       requires ( dimension() >= 2 );
        constexpr const auto           operator [] ( int ) const requires ( dimension() >= 2 );

    public: // Views
        using array_algo::operator[],
              array_algo::flatten;

    private: // Auxiliary
                               constexpr decltype(auto) at            ( const auto& );
                               constexpr decltype(auto) at            ( const auto& ) const;
                               constexpr static auto    compose       ( const auto&,  const auto& );
                               constexpr static auto    decompose     (               const auto&, int );
        template < int index > constexpr static auto    compose_aux   ( const auto&,  const auto&, int, int );
        template < int index > constexpr static auto    decompose_aux (       auto&&, const auto&, int, int );
};

#include "array_reshape_view.ipp"