} // Out of namespace anonymous

template < >
class std::formatter<anonymous::color>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const anonymous::color&, format_context& ) const;

    private: // Auxiliary
        mutable anonymous::string parse_ctx = "";
};


template < >
class std::formatter<anonymous::time_point>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const anonymous::time_point&, format_context& ) const;

    private: // Auxiliary
        mutable anonymous::string parse_ctx = "";
};

template < >
class std::formatter<anonymous::duration>
{
    public: // Interface
        constexpr formatter ( ) = default;
        template < class parse_context  > constexpr parse_context ::iterator parse  ( parse_context& );
        template < class format_context > constexpr format_context::iterator format ( const anonymous::duration&, format_context& ) const;

    private: // Auxiliary
        mutable anonymous::string parse_ctx = "";
};

#include "format.cpp"

namespace anonymous { // Back into namespace anonymous