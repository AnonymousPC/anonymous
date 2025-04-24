template < anonymous::array_type type >
    requires formattable<typename type::value_type,char>
class formatter<type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Data
        anonymous::string pattern = "";
};

template < anonymous::string_type type >
class formatter<type,typename type::value_type>
    extends public formatter<std::basic_string_view<typename type::value_type>,typename type::value_type>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const type&, format_context& ) const;

    private: // Data
        formatter<basic_string_view<typename type::value_type>,typename type::value_type> base = {};
};

#include "std.cpp"