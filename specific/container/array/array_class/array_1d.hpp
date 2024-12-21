#pragma once

template < class type, class device >
class array<type,1,device>
    extends public device::template vector<type>,   
            public std::mdspan<type,std::dextents<int,1>,std::layout_stride>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    public: // Typedef
        using  value_type     = type;
        using  device_type    = device;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
        struct array_tag { };

    private: // Typedef
        using vector = device::template vector<type>;
        using mdspan = std::mdspan<type,std::dextents<int,1>,std::layout_stride>;

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )                                                   requires std::copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  )                                       requires std::copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int );
        constexpr          array ( int,  const type& )                                               requires std::copyable<type>;
        constexpr          array ( int,  function_type<type()   > auto );
        constexpr          array ( int,  function_type<type(int)> auto );
        constexpr          array ( const std::initializer_list<type>& )                              requires std::copyable<type>;
        constexpr          array ( const range<type>& )                                              requires std::copyable<type>;
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r )            requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>;
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r, int )       requires std::convertible_to<std::ranges::range_value_t<decltype(r)>,type>;

    public: // Conversion (type)
                                 constexpr          array ( const array_type<type, 1,device> auto& ) requires std::copyable<type>;
        template < class type2 > constexpr          array ( const array_type<type2,1,device> auto& ) requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2>        );
        template < class type2 > constexpr explicit array ( const array_type<type2,1,device> auto& ) requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

    public: // Memebr
        constexpr       int    row         ( )      const = delete;
        constexpr       int    column      ( )      const = delete;
        constexpr       int    size        ( )      const;
        constexpr       int    capacity    ( )      const;
        constexpr       bool   empty       ( )      const;
        constexpr       type*  data        ( );
        constexpr const type*  data        ( )      const;
        constexpr       type*  begin       ( );
        constexpr const type*  begin       ( )      const;
        constexpr       type*  end         ( );
        constexpr const type*  end         ( )      const;
        constexpr       type&  operator [] ( int );
        constexpr const type&  operator [] ( int )  const;

    public: // Member
        constexpr array& clear  ( );
        constexpr array& resize ( int );
        constexpr array& push   ( type );
        constexpr array& pop    ( int );
        constexpr array& insert ( int, type );
        constexpr array& erase  ( int, int );

    public: // Views
        // using array_algo::operator[],
        //       array_algo::reshape,
        //       array_algo::flatten;
};

#include "array_1d.ipp"