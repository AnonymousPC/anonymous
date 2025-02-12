#pragma once

template < class type, int len, class device >
class static_array
    extends public device::template array<type,len>,
            public array_algo<static_array<type,len,device>,type,1,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> ); // Does not requires movable.
        static_assert ( len >= 1 );

    private: // Typedef
        using base = device::template array<type,len>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = pointer;
        using  const_iterator  = const_pointer;
        using  device_type     = device;
        struct array_tag { };

    public: // Core
        constexpr static_array ( );
        constexpr static_array ( const static_array&  )             requires copyable<type> = default;
        constexpr static_array (       static_array&& )             requires movable <type> = default;
        constexpr static_array& operator = ( const static_array&  ) requires copyable<type> = default;
        constexpr static_array& operator = (       static_array&& ) requires movable <type> = default;

    public: // Constructor
        constexpr static_array ( std::initializer_list<type> ) requires copyable<type>;
        constexpr static_array ( range<type> )                 requires copyable<type>;

    public: // Conversion
        template < class type2,           class device2 > constexpr static_array ( const array        <type2,1,   device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> );
        template < class type2, int len2, class device2 > constexpr static_array ( const inplace_array<type2,len2,device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> ) and ( len2 >= len );
        template < class type2, int len2, class device2 > constexpr static_array ( const static_array <type2,len2,device2>& ) requires ( same_as<type,type2> or same_as<device,device2> ) and convertible_to<type2,type> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> ) and ( len2 == len );

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr static int                  size          ( );
        constexpr static int                  capacity      ( );
        constexpr static static_array<int,1>  shape         ( );
        constexpr        int                  row           ( )     const = delete;
        constexpr        int                  column        ( )     const = delete;
        constexpr static bool                 empty         ( );
        constexpr        pointer              data          ( );
        constexpr        const_pointer        data          ( )     const;
        constexpr        iterator             begin         ( );
        constexpr        const_iterator       begin         ( )     const;
        constexpr        iterator             end           ( );
        constexpr        const_iterator       end           ( )     const;
        constexpr        reference            operator []   ( int );
        constexpr        const_reference      operator []   ( int ) const;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );

    public: // ADL
        template < class type2, int dim2, class device2 = cpu > using array = array<type2,dim2,device2>;
};