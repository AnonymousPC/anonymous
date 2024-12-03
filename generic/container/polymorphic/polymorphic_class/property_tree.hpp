#pragma once
#include "variant.hpp"

namespace aux
{
    template < class type > class auto_ptr;
}

template < class... types >
class property_tree
{
    private: // Precondition
        static_assert ( sizeof...(types) >= 1 and aux::all_different<types...> );
        static_assert ( not ( is_const<types> or ... ) and not ( is_volatile<types> or ... ) and not ( is_reference<types> or ... ) );

    private: // Data
        /** DO NOT USE DATA **/
        variant<aux::auto_ptr<types>...> data = {};

    public: // Core
        constexpr          property_tree ( )                                                                                                                                 = default;
        constexpr          property_tree ( const property_tree&  )             requires ( std::copyable<types> and ... )                                                     = default;
        constexpr          property_tree (       property_tree&& )                                                                                                           = default;
        constexpr          property_tree (       auto  val )                   requires aux::same_as_only_one_of                             <decay<decltype(val)>,types...>;
        constexpr          property_tree ( const auto& val )                   requires aux::not_same_but_convertible_to_only_one_of         <decay<decltype(val)>,types...>;
        constexpr explicit property_tree ( const auto& val )                   requires aux::not_convertible_but_constructible_to_only_one_of<decay<decltype(val)>,types...>;
        constexpr          property_tree& operator = ( const property_tree&  ) requires ( std::copyable<types> and ... )                                                     = default;
        constexpr          property_tree& operator = (       property_tree&& )                                                                                               = default;
        constexpr          property_tree& operator = (       auto  val )       requires aux::same_as_only_one_of                             <decay<decltype(val)>,types...>;
        constexpr          property_tree& operator = ( const auto& val )       requires aux::not_same_but_assignable_to_only_one_of          <decay<decltype(val)>,types...>;
        constexpr          property_tree& operator = (       auto  val )       requires aux::not_assignable_to_any_of                        <decay<decltype(val)>,types...> = delete; // Explicitly deleted, e.x. char[5] to int (which is constructible but not assignable and is not expected).

    public: // Operator
        template < class result_type > constexpr operator       result_type& ( )       requires aux::same_as_only_one_of<result_type,types...>;
        template < class result_type > constexpr operator const result_type& ( ) const requires aux::same_as_only_one_of<result_type,types...>;

    public: // Member
        constexpr int type ( ) const;

    public: // Visit
        constexpr decltype(auto) visit ( auto&& visitor )       requires aux::all_invocable_and_returns_same_type<decltype(visitor),      types&...>;
        constexpr decltype(auto) visit ( auto&& visitor ) const requires aux::all_invocable_and_returns_same_type<decltype(visitor),const types&...>;
};


#include "property_tree.ipp"