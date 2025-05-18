template < >
class formatter<type_info,char>
    extends public formatter<string,char>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  (                   parse_context&  );
        template < class format_context > constexpr format_context::iterator format ( const type_info&, format_context& ) const;
};

#include "formatter.cpp"