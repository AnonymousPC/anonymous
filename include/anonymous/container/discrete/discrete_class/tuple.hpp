template < class... types >
class tuple
    extends public std::tuple<types...>
{
    public: // Typedef
        template < int index > requires ( ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) ) ) using value_type      =       index_type_of<index,types...>;
        template < int index > requires ( ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) ) ) using reference       =       index_type_of<index,types...>&;
        template < int index > requires ( ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) ) ) using const_reference = const index_type_of<index,types...>&;
        struct tuple_tag { };
    
    public: // Core
        constexpr tuple ( ) = default;
        constexpr tuple ( types... ) requires ( sizeof...(types) >= 1 );

    public: // Conversion
        constexpr tuple ( const tuple_type auto& cvt ) requires ( sizeof...(types) >= 1 ) and detail::tuplewise_convertible_to<cvt_type,tuple>;

    public: // Member
        template < int index > constexpr reference<index>       value ( )       requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) );
        template < int index > constexpr const_reference<index> value ( ) const requires ( index >= -int(sizeof...(types)) and index <= -1 ) or ( index >= 1 and index <= int(sizeof...(types)) );
};

#include "tuple.cpp"
#include "detail/tuple_deduction.hpp"