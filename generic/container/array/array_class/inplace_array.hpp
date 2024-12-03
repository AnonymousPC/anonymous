#pragma once

/// Class inplace_array

template < class type, int len >
class inplace_array
    extends public array_algo<inplace_array<type,len>,type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> or requires { type(); } );                    // Sometimes default-constructor are only friend to array.
        static_assert ( std::movable<type> or requires { type(std::move(std::declval<type&&>())); } ); // Sometimes move-assignor       are only friend to array.
        static_assert ( len >= 0 );

    private: // Data
        int  m        = 0;
        type arr[len] = {};

    public: // Typedef
        using  value_type     = type;
        using  iterate_type   = type;
        using  iterator       = type*;
        using  const_iterator = const type*;
        using  array_algo     = array_algo<inplace_array,type>;
        struct array_tag { };

    public: // Core
        constexpr          inplace_array ( ) = default;
        constexpr          inplace_array ( const inplace_array&  )                                                requires std::copyable<type>;
        constexpr          inplace_array (       inplace_array&& );
        constexpr explicit inplace_array ( int );
        constexpr          inplace_array ( int,  const type& )                                                    requires std::copyable<type>;
        constexpr          inplace_array ( int,  function_type<type()   > auto );
        constexpr          inplace_array ( int,  function_type<type(int)> auto );
        constexpr          inplace_array (       std::initializer_list<type>&& );
        constexpr          inplace_array ( const array_type<type> auto& )                                         requires std::copyable<type>;
        constexpr          inplace_array ( const range_type<type> auto& )                                         requires std::copyable<type>;
        constexpr          inplace_array ( std::from_range_t, std::ranges::input_range auto&& r )                 requires requires { std::declval<inplace_array>().push(*std::ranges::begin(r)); };
        constexpr          inplace_array ( std::from_range_t, std::ranges::input_range auto&& r, int )            requires requires { std::declval<inplace_array>().push(*std::ranges::begin(r)); };
        constexpr          inplace_array& operator = ( const inplace_array&  )                                    requires std::copyable<type>;
        constexpr          inplace_array& operator = (       inplace_array&& );

    public: // Conversion
        template <              int len2 > constexpr          inplace_array ( const inplace_array<type, len2>&  ) requires ( len != len2 ) and std::copyable<type>;
        template <              int len2 > constexpr          inplace_array (       inplace_array<type, len2>&& ) requires ( len != len2 );
        template < class type2, int len2 > constexpr          inplace_array ( const inplace_array<type2,len2>&  ) requires std::convertible_to<type2,type>     but ( not std::same_as<type,type2> );
        template < class type2, int len2 > constexpr explicit inplace_array ( const inplace_array<type2,len2>&  ) requires std::constructible_from<type,type2> but ( not std::convertible_to<type2,type> );

    public: // Interface
        constexpr        int            size        ( )     const;
        constexpr static int            capacity    ( );
        constexpr        bool           empty       ( )     const;
        constexpr        inplace_array& resize      ( int );
        constexpr        type*          data        ( );
        constexpr const  type*          data        ( )     const;
        constexpr        type*          begin       ( );
        constexpr const  type*          begin       ( )     const;
        constexpr        type*          end         ( );
        constexpr const  type*          end         ( )     const;
        constexpr        type&          operator [] ( int );
        constexpr const  type&          operator [] ( int ) const;

    public: // Views
        using array_algo::operator[],
              array_algo::reshape,
              array_algo::flatten,
              array_algo::as_type;
};



template < class type >
inplace_array ( type, std::same_as<type> auto... args ) -> inplace_array<type,1+sizeof...(args)>;

#include "inplace_array.ipp"