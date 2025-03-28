#pragma once

template < class type, class device >
class basic_string
    extends public device::template basic_string<type>,
            public array_algo <basic_string<type,device>,type,1,device>,
            public string_algo<basic_string<type,device>,type,  device>
{
    private: // Precondition
        static_assert ( char_type<type> );

    private: // Base
        using base        = device::template basic_string<type>;
        using array_algo  = array_algo <basic_string<type,device>,type,1,device>;
        using string_algo = string_algo<basic_string<type,device>,type,  device>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = pointer;
        using  const_iterator  = const_pointer;
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
        constexpr basic_string (      const basic_string_view<type,device>& );

    public: // Conversion
        template < class type2, class device2 > constexpr basic_string ( const basic_string<type2,device2>& ) requires same_as<type,type2> and ( same_as<device,device2> or same_as<device,cpu> or same_as<device2,cpu> );

    public: // Conversion
                                       constexpr explicit basic_string ( const bool& )                 requires same_as<type,char>;
                                       constexpr explicit operator             bool ( )          const requires same_as<type,char>;
        template < number_type type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char>;
        template < number_type type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char>;
        template < printable   type2 > constexpr explicit basic_string ( const type2& )                requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
        template < inputable   type2 > constexpr explicit operator             type2 ( )         const requires same_as<type,char> and ( not number_type<type2> ) and ( not string_type<type2> );
                                       constexpr explicit basic_string ( const std::type_info& )       requires same_as<type,char>;

    public: // Member
        constexpr int                            size        ( )          const;
        constexpr basic_string&                  resize      ( int );
        constexpr bool                           empty       ( )          const;
        constexpr iterator                       begin       ( );
        constexpr const_iterator                 begin       ( )          const;
        constexpr iterator                       end         ( );
        constexpr const_iterator                 end         ( )          const;
        constexpr pointer                        data        ( );
        constexpr const_pointer                  data        ( )          const;
        constexpr const_pointer                  c_str       ( )          const;
        constexpr reference                      operator [] ( int );
        constexpr const_reference                operator [] ( int )      const;
        constexpr basic_string_view<type,device> operator [] ( int, int ) const;

        constexpr basic_string&                  clear       ( );
        constexpr basic_string&                  erase       ( int, int );
        constexpr basic_string&                  insert      ( int, basic_string_view<type,device> );
        constexpr basic_string&                  push        (      basic_string_view<type,device> );
        constexpr basic_string&                  pop         ( int = -1 );

    public: // Memory 
        constexpr static bool ownership  ( );
        constexpr static bool contiguous ( );

    public: // Algo (disambiguation)
        using string_algo::ends_with,
        
              string_algo::all,
              string_algo::contains,
              string_algo::count,
              string_algo::exist,
              string_algo::find,
              string_algo::none,
              string_algo::partition, 
              string_algo::remove,
              string_algo::replace,
              string_algo::right_find,
              string_algo::where;
};

template < char_type type >               basic_string ( type )                           -> basic_string<type>;
template < char_type type >               basic_string ( const type* )                    -> basic_string<type>;
template < char_type type, class device > basic_string ( basic_string_view<type,device> ) -> basic_string<type,device>;