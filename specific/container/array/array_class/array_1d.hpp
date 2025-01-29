#pragma once

template < class type, class device >
class array<type,1,device>
    extends public device::template vector<type>,
            public detail::array_upper<type,1,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( not same_as<type,bool> ); // std::vector<bool>

    public: // Base
        using base  = device::template vector<type>;
        using upper = detail::array_upper<type,1,device>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = detail::array_iterator          <type,1,device>;
        using  const_iterator  = detail::array_const_iterator    <type,1,device>;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr          array ( const array&  )             requires copyable<type>;
        constexpr          array (       array&& );
        constexpr          array& operator = ( const array&  ) requires copyable<type>;
        constexpr          array& operator = (       array&& );

    public: // Constructor
        constexpr explicit array ( int );
        constexpr          array ( int, const type& )                   requires copyable<type>;
        constexpr          array ( int, function_type<type()   > auto );
        constexpr          array ( int, function_type<type(int)> auto );
        constexpr          array ( std::initializer_list<type> )        requires copyable<type>;
        constexpr          array ( range<type> )                        requires copyable<type>;

    public: // Conversion (size)
        template < int len > constexpr array ( const inplace_array<type,len,device>& );
        template < int len > constexpr array ( const static_array <type,len,device>& );

    public: // Conversion (type)
        template < class type2 > constexpr          array ( const array<type2,1,device>& ) requires convertible_to<type2,type>     but ( not same_as<type,type2>        );
        template < class type2 > constexpr explicit array ( const array<type2,1,device>& ) requires constructible_from<type,type2> but ( not convertible_to<type2,type> );

    public: // Conversion (device)
        template < class device2 > constexpr array ( const array<type,1,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>; 

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr        int                  size          ( )     const;
        constexpr        int                  capacity      ( )     const;
        constexpr        array<int>           shape         ( )     const;
        constexpr        inplace_array<int,1> inplace_shape ( )     const;
        constexpr        static_array<int,1>  static_shape  ( )     const;
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
        constexpr array& pop    ( int = -1 );
        constexpr array& insert ( int, type );
        constexpr array& erase  ( int, int );

    public: // Memory
        constexpr bool ownership  ( ) const;
        constexpr bool contiguous ( ) const;
};

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */