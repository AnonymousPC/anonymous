#pragma once

template < class type, class device >
class array<type,1,device>
    extends public device::template vector<type>,
            public detail::upper_array<type,1,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( not same_as<type,bool> );

    private: // Base
        using base  = device::template vector<type>;
        using upper = detail::upper_array<type,1,device>;

    public: // Typedef
        using  value_type      = base::value_type;
        using  reference       = base::reference;
        using  const_reference = base::const_reference;
        using  pointer         = base::pointer;
        using  const_pointer   = base::const_pointer;
        class  iterator;
        class  const_iterator;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )                                         requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  )                             requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int );
        constexpr          array ( int,  const type& )                                     requires copyable<type>;
        constexpr          array ( int,  function_type<type()   > auto );
        constexpr          array ( int,  function_type<type(int)> auto );
        constexpr          array ( const std::initializer_list<type>& )                    requires copyable<type>;
        constexpr          array ( const range<type>& )                                    requires copyable<type>;
        constexpr          array ( std::from_range_t, input_range auto&& r )               requires convertible_to<range_value<decltype(r)>,type>;
        constexpr          array ( std::from_range_t, input_range auto&& r, int )          requires convertible_to<range_value<decltype(r)>,type>;

    public: // Conversion (size)
        template < int len > constexpr array ( const inplace_array<type,len,device> auto& );
        template < int len > constexpr array ( const static_array <type,len,device> auto& );

    public: // Conversion (type)
        template < class type2 > constexpr          array ( const array<type2,1,device>& ) requires convertible_to<type2,type>     but ( not same_as<type,type2>        );
        template < class type2 > constexpr explicit array ( const array<type2,1,device>& ) requires constructible_from<type,type2> but ( not convertible_to<type2,type> );

    public: // Conversion (device)
        template < class device2 > constexpr array ( const array<type,1,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>; 

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr        int                  size          ( )     const;
        constexpr        array<int>           shape         ( )     const;
        constexpr        static_array<int,1>  static_shape  ( )     const;
        constexpr        inplace_array<int,1> inplace_shape ( )     const;
        constexpr        int                  row           ( )     const = delete;
        constexpr        int                  column        ( )     const = delete;
        constexpr        bool                 empty         ( )     const;
        constexpr        pointer              data          ( );
        constexpr        const_pointer        data          ( )     const;
        constexpr        iterator             begin         ( );
        constexpr        const_iterator       begin         ( )     const;
        constexpr        iterator             end           ( );
        constexpr        const_iterator       end           ( )     const;
        constexpr        reference            operator []   ( int );
        constexpr        const_reference      operator []   ( int ) const;

    public: // Member
        constexpr array& clear  ( );
        constexpr array& resize ( int );
        constexpr array& push   ( type );
        constexpr array& pop    ( int );
        constexpr array& insert ( int, type );
        constexpr array& erase  ( int, int );

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;
};

#include "array_1d.ipp"