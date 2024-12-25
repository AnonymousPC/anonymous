#pragma once

template < class type, class device >
class array<type,1,device>
    extends public  device::template vector<type>,
            private aux::maybe_array_view<array<type,1,device>>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    private: // Typedef
        using base = device::template vector<type>;
        using span = aux::maybe_array_view<array<type,1,device>>;

    public: // Typedef
        using  value_type     = type;
        using  device_type    = device;
        using  iterate_type   = type;
        class  iterator;
        class  const_iterator;
        struct array_tag { };

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
        template < class type2 > constexpr          array ( const array<type2,1,device>& ) requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2>        );
        template < class type2 > constexpr explicit array ( const array<type2,1,device>& ) requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr        int                  size          ( )               const;
        constexpr        array<int>           shape         ( )               const;
        constexpr        static_array<int,1>  static_shape  ( )               const;
        constexpr        inplace_array<int,1> inplace_shape ( )               const;
        constexpr        int                  row           ( )               const = delete;
        constexpr        int                  column        ( )               const = delete;
        constexpr        bool                 empty         ( )               const;
        constexpr        type*                data          ( );
        constexpr const  type*                data          ( )               const;
        constexpr        iterator             begin         ( );
        constexpr        const_iterator       begin         ( )               const;
        constexpr        iterator             end           ( );
        constexpr        const_iterator       end           ( )               const;
        constexpr        type&                operator []   ( int_type auto );
        constexpr const  type&                operator []   ( int_type auto ) const;

    public: // Member
        constexpr array& clear  ( );
        constexpr array& resize ( int );
        constexpr array& push   ( type );
        constexpr array& pop    ( int );
        constexpr array& insert ( int, type );
        constexpr array& erase  ( int, int );

    public: // Views
        constexpr bool is_view ( ) const;

    public: // Views
        // using array_algo::operator[],
        //       array_algo::reshape,
        //       array_algo::flatten;
};

#include "array_1d.ipp"