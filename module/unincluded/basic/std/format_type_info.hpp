template < >
class formatter<type_info,char>
    extends public formatter<string,char>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  (                   parse_context&  );
        template < class format_context > constexpr format_context::iterator format ( const type_info&, format_context& ) const;
};

template < class parse_context >
constexpr parse_context::iterator formatter<type_info,char>::parse ( parse_context& ctx )
{
    return formatter<string,char>::parse(ctx);
}

template < class format_context >
constexpr format_context::iterator formatter<type_info,char>::format ( const type_info& val, format_context& ctx ) const
{
    return formatter<string,char>::format(boost::core::demangle(val.name()), ctx);
}