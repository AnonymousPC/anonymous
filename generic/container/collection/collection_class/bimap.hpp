#pragma once

template < class type1, class type2, class key_less, class value_less, class container1, class container2 >
class basic_bimap
    extends public collection_algo<basic_bimap<type1,type2,key_less,value_less,container1,container2>,pair<const type1,const type2>>
{
    private: // Precondition
        static_assert ( not std::is_const<type1>::value and not std::is_volatile<type1>::value and not std::is_reference<type1>::value );
        static_assert ( std::is_default_constructible<type1>::value and std::is_move_assignable<type1>::value );
        static_assert ( not std::is_const<type2>::value and not std::is_volatile<type2>::value and not std::is_reference<type2>::value );
        static_assert ( std::is_default_constructible<type2>::value and std::is_move_assignable<type2>::value );
        static_assert ( is_function_type<key_less,  bool(type1,type1)>::value );
        static_assert ( is_function_type<value_less,bool(type2,type2)>::value );

    private: // Data
        container1 forward_data = container1();
        container2 reverse_data = container2();

    public: // Typedef
        using  key_type           = type1;
        using  value_type         = type2;
        using  iterate_type       = pair<const type1,const type2>;
        using  key_compare_type   = key_less;
        using  value_compare_type = value_less;
        class  iterator;
        class  const_iterator;
        struct bimap_tag { };

    public: // Core
        constexpr  basic_bimap ( )                                                                                                                   = default;
        constexpr  basic_bimap ( const basic_bimap&  )                        requires std::is_copy_assignable<pair<type1,type2>>::value = default;
        constexpr  basic_bimap (       basic_bimap&& )                                                                                                 = default;
        constexpr  basic_bimap ( std::initializer_list<pair<type1,type2>>&& );
        constexpr  basic_bimap ( std::ranges::input_range auto&& r )          requires requires { std::declval<basic_bimap>()[get<0>(*r.begin())] = get<1>(*r.begin()); };
        constexpr ~basic_bimap ( )                                                                                                                   = default;
        constexpr  basic_bimap& operator = ( const basic_bimap&  )            requires std::is_copy_assignable<pair<type1,type2>>::value = default;
        constexpr  basic_bimap& operator = (       basic_bimap&& )                                                                                     = default;

    public: // Conversion
        constexpr       auto& native_handle ( );
        constexpr const auto& native_handle ( ) const;

    public: // Interface
        constexpr        int              size        ( )                                   const;
        constexpr        bool             empty       ( )                                   const;
        constexpr        iterator         begin       ( );
        constexpr        const_iterator   begin       ( )                                   const;
        constexpr        iterator         end         ( );
        constexpr        const_iterator   end         ( )                                   const;

        constexpr const  type2&           operator [] ( const type1& )                      const;
        constexpr const  type1&           operator [] ( const type2& )                      const;

        constexpr const  auto             keys        ( )                                   const;
        constexpr        auto             values      ( );
        constexpr const  auto             values      ( )                                   const;

        constexpr        basic_bimap&     clear       ( );
        constexpr        bool             contains    ( const type1& )                      const;
        constexpr        basic_bimap&     pop         ( const type1& );
        constexpr        basic_bimap&     update      ( const map_type<type1,type2> auto& );
};