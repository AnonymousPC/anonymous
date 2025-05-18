template < class... types >
class tuple
    extends public std::tuple<types...>,
            public structure_interface<tuple<types...>,types...>
{
    private: // Base
        using base = std::tuple<types...>;

    public: // Typedef
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using value_type      =       index_type_of<index,types...>;
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using reference       =       index_type_of<index,types...>&;
        template < int index > requires ( ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) ) ) using const_reference = const index_type_of<index,types...>&;
    
    public: // Core
        constexpr tuple ( ) = default;
        constexpr tuple ( types... ) requires ( sizeof...(types) >= 1 );

    public: // Conversion
        template < class... types2 >          constexpr tuple ( const tuple<types2...>& ) requires ( convertible_to  <types2,types> and ... );
        template < class... types2 > explicit constexpr tuple ( const tuple<types2...>& ) requires ( constructible_to<types2,types> and ... );

    public: // Member
        template < int index > constexpr reference      <index> value ( )       requires ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) );
        template < int index > constexpr const_reference<index> value ( ) const requires ( index >= -sizeof...(types) and index <= -1 ) or ( index >= 1 and index <= sizeof...(types) );
};

#include "tuple.cpp"