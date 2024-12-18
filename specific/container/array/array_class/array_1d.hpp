#pragma once

template < class type, class device >
class array<type,1,device>
    extends public device::template vector<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> or requires { type(); } );                    // Sometimes default-constructor are only friend to array.
        static_assert ( std::movable<type> or requires { type(std::move(std::declval<type&&>())); } ); // Sometimes move-assignor       are only friend to array.

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
     // using  array_algo     = array_algo<array<type>,type>;
        using  device_type    = device;
        struct array_tag { };

    public: // Core
        constexpr          array ( ) = default;
        constexpr explicit array ( int );
        constexpr          array ( int,  const type& )                                         requires std::copyable<type>;
        constexpr          array ( int,  function_type<type()   > auto );
        constexpr          array ( int,  function_type<type(int)> auto );
        constexpr          array (       std::initializer_list<type>&& );
        constexpr          array ( const array_type<type,1> auto& )                            requires std::copyable<type>;
        constexpr          array ( const range_type<type>   auto& )                            requires std::copyable<type>;
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r )      requires requires { std::declval<array>().push(*std::ranges::begin(r)); };
        constexpr          array ( std::from_range_t, std::ranges::input_range auto&& r, int ) requires requires { std::declval<array>().push(*std::ranges::begin(r)); };
        constexpr         ~array ( );

    public: // Conversion
        template < class type2 > constexpr          array ( const array<type2>& )              requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2> );
        template < class type2 > constexpr explicit array ( const array<type2>& )              requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

   public: // Interface
        constexpr       void   row         ( )    = delete;
        constexpr       int    size        ( )      const;
        constexpr       bool   empty       ( )      const;
        constexpr       array& resize      ( int );
        constexpr       type*  data        ( );
        constexpr const type*  data        ( )      const;
        constexpr       type*  begin       ( );
        constexpr const type*  begin       ( )      const;
        constexpr       type*  end         ( );
        constexpr const type*  end         ( )      const;
        constexpr       type&  operator [] ( int );
        constexpr const type&  operator [] ( int )  const;

    public: // Views
        // using array_algo::operator[],
        //       array_algo::reshape,
        //       array_algo::flatten;
};