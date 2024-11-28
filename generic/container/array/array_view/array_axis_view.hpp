#pragma once

template < class container_type, int axis, int axis_to_fill >
class array_axis_view
    extends public array_algo<array_axis_view<container_type,axis,axis_to_fill>,
                              typename container_type::value_type,
                              typename std::conditional<axis_to_fill<container_type::dimension(),array_axis_view<container_type,axis,axis_to_fill+1>,typename container_type::value_type>::type,
                              1>
{
    private: // Data
        using coor_type = array_coordinate<container_type::dimension()>;
        using buff_type = array<typename container_type::value_type,container_type::dimension()-1>; // Note: buff_type.dimension() == arr.dimension() - 1.

        container_type& arr;
        coor_type       idx      = coor_type();
        buff_type*      buff_ptr = nullptr;
        bool            buff_own = false;

    public: // Typedef
        using  value_type     = container_type::value_type;
        using  iterate_type   = std::conditional<axis_to_fill<container_type::dimension(),array_axis_view<container_type,axis,axis_to_fill+1>,value_type>::type; // axis_to_fill [[less than]] container_type::dimension().
        using  iterator       = array_view_iterator      <array_axis_view>;
        using  const_iterator = array_view_const_iterator<array_axis_view>;
        using  array_algo     = array_algo               <array_axis_view,value_type,iterate_type,1>;
        struct array_tag { };

    public: // Friend
        template < class type2, int type3, int type4 >
        friend class ap::array_axis_view;
        template < class type2, class type3, class type4, int type5 >
        friend class ap::array_algo;
        friend container_type;

    private: // Host
        constexpr       container_type& host ( );
        constexpr const container_type& host ( ) const;

    public: // Constructor
        constexpr array_axis_view ( container_type&, const coor_type& = coor_type(), buff_type* = nullptr );

    public: // Core
        constexpr  array_axis_view             ( const array_axis_view&  ) requires ( axis_to_fill == 2 );
        constexpr  array_axis_view             ( const array_axis_view&  ) requires ( axis_to_fill != 2 ) = delete;
        constexpr  array_axis_view             (       array_axis_view&& ) requires ( axis_to_fill == 2 );
        constexpr  array_axis_view             (       array_axis_view&& ) requires ( axis_to_fill != 2 ) = delete;
        constexpr ~array_axis_view             ( );
        constexpr  array_axis_view& operator = ( const array_axis_view&  );
        constexpr  array_axis_view& operator = (       array_axis_view&& );

    public: // N-dimension
        constexpr static int            dimension   ( );
        constexpr        array<int>     shape       ( ) const;

    public: // Conversion: for fill() and replace().
        constexpr array_axis_view             ( const array_type<value_type,dimension()> auto& ) requires ( axis_to_fill >= 2 ); // No implemention.
        constexpr array_axis_view& operator = ( const array_type<value_type,dimension()> auto& ) requires ( axis_to_fill >= 2 );

    public: // Interface
        constexpr       int            row         ( )     const requires ( dimension() >= 2 );
        constexpr       int            column      ( )     const requires ( dimension() == 2 );
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

    private: // Auxiliary
        template < int count = 1 > constexpr static       auto& at_arr  (       auto&,  const auto& );
        template < int count = 1 > constexpr static       auto& at_arr  (       auto&&, const auto& );
        template < int count = 1 > constexpr static const auto& at_arr  ( const auto&,  const auto& );
        template < int count = 1 > constexpr static       auto& at_buff (       auto&,  const auto& );
        template < int count = 1 > constexpr static       auto& at_buff (       auto&&, const auto& );
        template < int count = 1 > constexpr static const auto& at_buff ( const auto&,  const auto& );
};



// Swap

template < class container_type, int axis, int axis_to_fill >
constexpr void swap ( array_axis_view<container_type,axis,axis_to_fill>&&, array_axis_view<container_type,axis,axis_to_fill>&& );



#include "array_axis_view.ipp"