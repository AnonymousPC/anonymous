template < class... types >
class variant
    extends public std::variant<types...>
{    
    private: // Precondition
        static_assert ( sizeof...(types) >= 1 and detail::all_different<types...> );
        static_assert ( not ( is_const<types> or ... ) and not ( is_volatile<types> or ... ) and not ( is_reference<types> or ... ) );
        static_assert ( ( default_initializable<first_type_of<types...>> ) );

    private: // Typedef
        using base = std::variant<types...>;

    public: // Core
        constexpr variant ( )                                                                  = default;
        constexpr variant ( const variant&  )             requires ( copyable<types> and ... ) = default;
        constexpr variant (       variant&& )             requires ( movable <types> and ... ) = default;
        constexpr variant& operator = ( const variant&  ) requires ( copyable<types> and ... ) = default;
        constexpr variant& operator = (       variant&& ) requires ( movable <types> and ... ) = default;

    public: // Constructor 
        constexpr          variant ( auto v ) requires ( same_as           <types,decltype(v)> or ... );
        constexpr          variant ( auto v ) requires ( convertible_to    <decltype(v),types> or ... ) and ( not ( same_as       <types,decltype(v)> or ... ) );
        constexpr explicit variant ( auto v ) requires ( constructible_from<types,decltype(v)> or ... ) and ( not ( convertible_to<decltype(v),types> or ... ) );

    public: // Member
                                       constexpr       int                                  index ( )          const;
                                       constexpr const std::type_info&                      type  ( )          const;
        template < class value_type  > constexpr       value_type&                          value ( )                requires ( same_as<types,value_type> or ... );
        template < class value_type  > constexpr const value_type&                          value ( )          const requires ( same_as<types,value_type> or ... );
        template < int   value_index > constexpr       index_type_of<value_index,types...>& value ( )                requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) );
        template < int   value_index > constexpr const index_type_of<value_index,types...>& value ( )          const requires ( ( value_index >= -sizeof...(types) and value_index <= -1 ) or ( value_index >= 1 and value_index <= sizeof...(types) ) );
                                       constexpr       decltype(auto)                       visit ( auto&& v )       requires detail::all_invocable_and_returns_same_type<decltype(v),types...>;
                                       constexpr       decltype(auto)                       visit ( auto&& v ) const requires detail::all_invocable_and_returns_same_type<decltype(v),types...>;

    public: // Traits
        constexpr static int size ( );
};

template < class... types > std::ostream& operator << ( std::ostream&, const variant<types...>& ) requires ( printable<types> and ... ) and ( sizeof...(types) >= 1 );

#include "variant.cpp"