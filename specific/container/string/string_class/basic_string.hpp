#pragma once

template < class type, class device >
class basic_string
    extends public device::template basic_string<type>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Base
        using base = device::template basic_string<type>;
        using view = basic_string_view<type,device>; 

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
        constexpr basic_string ( )                                  = default;
        constexpr basic_string ( const basic_string&  )             = default;
        constexpr basic_string (       basic_string&& )             = default;
        constexpr basic_string& operator = ( const basic_string&  ) = default;
        constexpr basic_string& operator = (       basic_string&& ) = default;

    public: // Constructor
        constexpr basic_string (      const type& );
        constexpr basic_string ( int, const type& );
        constexpr basic_string (      const type* );

    public: // Conversion (view)
        constexpr basic_string ( const view& );
        constexpr operator             view ( ) const;

    public: // Conversion (type)
        template < char_type type2 > constexpr explicit basic_string ( const basic_string     <type2,device>& );
        template < char_type type2 > constexpr explicit basic_string ( const basic_string_view<type2,device>& );

    public: // Conversion (device)
        template < class device2 > constexpr explicit basic_string ( const basic_string     <type,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;
        template < class device2 > constexpr explicit basic_string ( const basic_string_view<type,device2>& ) requires same_as<device,cpu> or same_as<device2,cpu>;

    public: // Conversion (other)
                                       constexpr explicit basic_string ( const bool& )                 requires same_as<type,char>;
                                       constexpr explicit operator             bool ( )          const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char>;
        template < printable   type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
        template < inputable   type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
                                       constexpr explicit basic_string ( const std::type_info& )       requires same_as<type,char>;

    public: // Member
        constexpr int             size        ( )                                    const;
        constexpr basic_string&   resize      ( int );
        constexpr bool            empty       ( )                                    const;
        constexpr iterator        begin       ( );
        constexpr const_iterator  begin       ( )                                    const;
        constexpr iterator        end         ( );
        constexpr const_iterator  end         ( )                                    const;
        constexpr pointer         data        ( );
        constexpr const_pointer   data        ( )                                    const;
        constexpr const_pointer   c_str       ( )                                    const;
        constexpr reference       operator [] ( int );
        constexpr const_reference operator [] ( int )                                const;
        constexpr view            operator [] ( int, int )                           const;

        constexpr basic_string&   clear       ( );
        constexpr basic_string&   erase       ( int, int );
        constexpr basic_string&   insert      ( int, view );
        constexpr basic_string&   push        (      view );
        constexpr basic_string&   pop         ( int );

    public: // Memory 
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );
};

template < char_type type >               basic_string ( type )                           -> basic_string<type>;
template < char_type type >               basic_string ( const type* )                    -> basic_string<type>;
template < char_type type, class device > basic_string ( basic_string_view<type,device> ) -> basic_string<type,device>;