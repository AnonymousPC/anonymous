#pragma once

template < class type, class compares >
class sorted_vector
    extends public vector<type>
{
    public: // Typedef
        using value_type     = vector<type>::value_type;
        using const_iterator = vector<type>::const_iterator;

    public: // Core
        constexpr sorted_vector ( ) = default;

    public: // Interface
        constexpr int            size    ( )                                const;
        constexpr bool           empty   ( )                                const;

        constexpr const_iterator begin   ( )                                const;
        constexpr const_iterator min     ( )                                const;
        constexpr const_iterator max     ( )                                const;
        constexpr const_iterator end     ( )                                const;
        constexpr const_iterator locate  ( const auto&  val )               const                requires requires { compares::equal_to(val,std::declval<type>()); };
        constexpr const_iterator clear   ( );
        constexpr const_iterator push    (       auto&& val, const_iterator = const_iterator() ) requires std::convertible_to<decltype(val),type>;
        constexpr const_iterator pop     ( const auto&  val, const_iterator = const_iterator() ) requires requires { compares::equal_to(val,std::declval<type>()); };

        constexpr       vector<type>& data ( );
        constexpr const vector<type>& data ( ) const;
        struct collection_type_recursive_data { };
};

#include "sorted_vector.ipp"