#pragma once

template < class type1, class type2, class key_less, class container >
class basic_map
    extends public collection_algo<basic_map<type1,type2,key_less,container>,pair<const type1,type2>>
{
    private: // Precondition
        static_assert ( not is_const<type1> and not is_volatile<type1> and not is_reference<type1> );
        static_assert ( std::default_initializable<type1> and std::movable<type1> );
        static_assert ( not is_const<type2> and not is_volatile<type2> and not is_reference<type2> );
        static_assert ( std::default_initializable<type2> and std::movable<type2> );
        static_assert ( function_type<key_less,bool(type1,type1)> );

    private: // Data
        container cont = container();

    public: // Typedef
        using  key_type         = type1;
        using  value_type       = type2;
        using  iterate_type     = pair<const type1,type2>;
        using  key_compare_type = key_less;
        using  container_type   = container;
        class  iterator;
        class  const_iterator;
        struct map_tag { };

    public: // Core
        constexpr basic_map ( ) = default;
        constexpr basic_map ( std::initializer_list<pair<type1,type2>>&& );
        constexpr basic_map ( std::from_range_t, std::ranges::input_range auto&& r ) requires requires { std::declval<basic_map>()[get<0>(*std::ranges::begin(r))] = get<1>(*std::ranges::begin(r)); };

    public: // Interface
        constexpr        int            size        ( )                                   const;
        constexpr        bool           empty       ( )                                   const;
        constexpr        auto&          data        ( );
        constexpr const  auto&          data        ( )                                   const;
        constexpr        iterator       begin       ( );
        constexpr        const_iterator begin       ( )                                   const;
        constexpr        iterator       end         ( );
        constexpr        const_iterator end         ( )                                   const;

        constexpr        type2&         operator [] ( const type1&  );
        constexpr        type2&         operator [] (       type1&& );
        constexpr const  type2&         operator [] ( const type1&  )                     const;

        constexpr const  auto           keys        ( )                                   const;
        constexpr        auto           values      ( );
        constexpr const  auto           values      ( )                                   const;

        constexpr        basic_map&     clear       ( );
        constexpr        bool           contains    ( const type1&  )                     const;
        constexpr        basic_map&     pop         ( const type1& );
        constexpr        basic_map&     update      ( const map_type<type1,type2> auto& );
};







template < class type1, class type2, class key_less, class container >
class basic_map<type1,type2,key_less,container>::iterator // container_type::const_iterator might be a trivial pointer in flat-map, thus extends is not available.
{
    public: // Tyepdef
        using iterator_category = std::iterator_traits<typename container::const_iterator>::iterator_category;
        using value_type        = pair<const type1,type2>;
        using difference_type   = std::iterator_traits<typename container::const_iterator>::difference_type;
        using pointer           = value_type*;
        using reference         = value_type&;

    private: // Data
        container::const_iterator it;

    public: // Bidirectional_iterator
        constexpr iterator ( ) = default;
        constexpr iterator ( const container::const_iterator& );
        constexpr pair<const type1,type2>& operator *  ( )                 const;
        constexpr pair<const type1,type2>* operator -> ( )                 const;
        constexpr bool                     operator == ( const iterator& ) const = default;
        constexpr bool                     operator != ( const iterator& ) const = default;
        constexpr iterator&                operator ++ ( );
        constexpr iterator                 operator ++ ( int );
        constexpr iterator&                operator -- ( );
        constexpr iterator                 operator -- ( int );

    public: // Random_access_iterator
        constexpr iterator                 operator +  ( int )             const requires std::random_access_iterator<typename container::const_iterator>;
        constexpr iterator                 operator -  ( int )             const requires std::random_access_iterator<typename container::const_iterator>;
        constexpr int                      operator -  ( const iterator& ) const requires std::random_access_iterator<typename container::const_iterator>;
};

template < class type1, class type2, class key_less, class container >
class basic_map<type1,type2,key_less,container>::const_iterator
{
    public: // Tyepdef
        using iterator_category = std::iterator_traits<typename container::const_iterator>::iterator_category;
        using value_type        = pair<const type1,type2>;
        using difference_type   = std::iterator_traits<typename container::const_iterator>::difference_type;
        using pointer           = const value_type*;
        using reference         = const value_type&;

    private: // Data
        container::const_iterator it;

    public: // Core
        constexpr const_iterator ( ) = default;
        constexpr const_iterator ( const container::const_iterator& );
        constexpr const pair<const type1,type2>& operator *  ( )                       const;
        constexpr const pair<const type1,type2>* operator -> ( )                       const;
        constexpr bool                           operator == ( const const_iterator& ) const = default;
        constexpr bool                           operator != ( const const_iterator& ) const = default;
        constexpr const_iterator&                operator ++ ( );
        constexpr const_iterator                 operator ++ ( int );
        constexpr const_iterator&                operator -- ( );
        constexpr const_iterator                 operator -- ( int );

    public: // Random_access_iterator
        constexpr const_iterator                 operator +  ( int )                   const requires std::random_access_iterator<typename container::const_iterator>;
        constexpr const_iterator                 operator -  ( int )                   const requires std::random_access_iterator<typename container::const_iterator>;
        constexpr int                            operator -  ( const const_iterator& ) const requires std::random_access_iterator<typename container::const_iterator>;
};







/// Template deduction

basic_map ( map_type auto m ) -> basic_map<typename decltype(m)::key_type,typename decltype(m)::value_type,typename decltype(m)::key_compare_type,typename decltype(m)::container_type>;

template < std::ranges::input_range type >
    requires ( pair_type<decay<decltype(*std::ranges::begin(std::declval<type>()))>> )
basic_map ( std::from_range_t, type ) -> map<typename decay<decltype(*std::ranges::begin(std::declval<type>()))>::key_type,
                                             typename decay<decltype(*std::ranges::begin(std::declval<type>()))>::value_type>;

#include "map.ipp"