#pragma once

template < class type, class device >
class basic_string_view
    extends public device::template basic_string_view<type>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Base
        using base   = device::template basic_string_view<type>;
        using string = basic_string<type,device>; 

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
        using  device_type     = device;  
        struct string_tag { };

    public: // Core
        constexpr basic_string_view ( const basic_string_view&  )             = default;
        constexpr basic_string_view (       basic_string_view&& )             = default;

    private: // Core
        constexpr basic_string_view ( )                                       = default;
        constexpr basic_string_view& operator = ( const basic_string_view&  ) = default;
        constexpr basic_string_view& operator = (       basic_string_view&& ) = default;

    public: // Constructor
        constexpr basic_string_view ( const_reference );
        constexpr basic_string_view ( const_pointer );
        constexpr basic_string_view ( const_pointer, int );

    public: // Conversion (other)
                                       constexpr explicit operator bool  ( ) const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator type2 ( ) const requires same_as<type,char>;
        template < inputable   type2 > constexpr explicit operator type2 ( ) const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );

    public: // Member
        constexpr int               size        ( )          const;
        constexpr bool              empty       ( )          const;
        constexpr const_iterator    begin       ( )          const;
        constexpr const_iterator    end         ( )          const;
        constexpr const_pointer     data        ( )          const;
        constexpr const_reference   operator [] ( int )      const;
        constexpr basic_string_view operator [] ( int, int ) const;

    public: // Memory
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );
};

template < char_type type >               basic_string_view ( type )                      -> basic_string_view<type>;
template < char_type type >               basic_string_view ( const type* )               -> basic_string_view<type>;
template < char_type type, class device > basic_string_view ( basic_string<type,device> ) -> basic_string_view<type,device>;