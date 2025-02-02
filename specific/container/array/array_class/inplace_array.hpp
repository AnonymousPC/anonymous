#pragma once

template < class type, int len, class device >
class inplace_array
    extends public device::template inplace_vector<type,len>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> ); // Does not requires movable.
        static_assert ( len >= 1 );

    private: // Typedef
        using base = device::template inplace_vector<type,len>;

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
        constexpr inplace_array ( )                                                           = default;
        constexpr inplace_array ( const inplace_array&  )             requires copyable<type> = default;
        constexpr inplace_array (       inplace_array&& )             requires movable <type> = default;
        constexpr inplace_array& operator = ( const inplace_array&  ) requires copyable<type> = default;
        constexpr inplace_array& operator = (       inplace_array&& ) requires movable <type> = default;

    public: // Constructor
        constexpr explicit inplace_array ( int );
        constexpr          inplace_array ( int, const type& )                   requires copyable<type>;
        constexpr          inplace_array ( int, function_type<type()   > auto ) requires movable <type>;
        constexpr          inplace_array ( int, function_type<type(int)> auto ) requires movable <type>;
        constexpr          inplace_array ( std::initializer_list<type> )        requires copyable<type>;
        constexpr          inplace_array ( range<type> )                        requires copyable<type>;

    public: // Memebr
        constexpr static int                  dimension     ( );
        constexpr        int                  size          ( )     const;
        constexpr static int                  capacity      ( );
        constexpr        static_array<int,1>  shape         ( )     const;
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
        constexpr inplace_array& clear  ( );
        constexpr inplace_array& resize ( int );
        constexpr inplace_array& push   ( type )      requires movable<type>;
        constexpr inplace_array& pop    ( int = -1 )  requires movable<type>;
        constexpr inplace_array& insert ( int, type ) requires movable<type>;
        constexpr inplace_array& erase  ( int, int )  requires movable<type>;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );
};

#include "inplace_array.ipp"