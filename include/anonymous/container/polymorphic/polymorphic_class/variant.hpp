template < class... types >
class variant
    extends public std::variant<types...>
{    
    private: // Precondition
        static_assert ( sizeof...(types) >= 1 );
        static_assert ( not ( is_void<types> or ... ) and not ( is_reference<types> or ... ) );
        static_assert ( ( default_initializable<first_type_of<types...>> ) );

    private: // Base
        using base = std::variant<types...>;

    public: // Typedef
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using value_type      =       index_type_of<index,types...>;
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using reference       =       index_type_of<index,types...>&;
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using const_reference = const index_type_of<index,types...>&;

    public: // Core
        constexpr variant ( )                                                                  = default;
        constexpr variant ( const variant&  )             requires ( copyable<types> and ... ) = default;
        constexpr variant (       variant&& )             requires ( movable <types> and ... ) = default;
        constexpr variant& operator = ( const variant&  ) requires ( copyable<types> and ... ) = default;
        constexpr variant& operator = (       variant&& ) requires ( movable <types> and ... ) = default;

    public: // Constructor 
        constexpr          variant ( auto v ) requires ( convertible_to  <decltype(v),types> or ... );
        constexpr explicit variant ( auto v ) requires ( constructible_to<decltype(v),types> or ... );

    public: // Member
        template < class type  > constexpr       type&                  value ( )              requires ( same_as<types,type> or ... );
        template < class type  > constexpr const type&                  value ( )        const requires ( same_as<types,type> or ... );
        template < int   index > constexpr       reference<index>       value ( )              requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) );
        template < int   index > constexpr       const_reference<index> value ( )        const requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) );
                                 constexpr       int                    index ( )        const;
                                 constexpr const std::type_info&        type  ( )        const;

    public: // Visit
        constexpr decltype(auto) visit ( auto&& );
        constexpr decltype(auto) visit ( auto&& ) const;
};

#include "variant.cpp"