#pragma once

template < class type, int len, class device >
class static_array
    extends public device::template array<type,len>
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
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
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
};

/* .ipp files are explicit extern included, which instantiates
 * array.shape(), array.inplace_shape() and array.static_shape()
 * in a correct order
 */