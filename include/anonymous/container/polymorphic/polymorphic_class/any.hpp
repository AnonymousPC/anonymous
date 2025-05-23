class any
    extends public std::any
{
    private: // Base
        using base = std::any;

    public: // Core
        constexpr any ( ) = default;
        constexpr any ( copyable auto );

    public: // Member
        template < class value_type > constexpr       value_type&     value ( );
        template < class value_type > constexpr const value_type&     value ( ) const;
                                      constexpr       bool            empty ( ) const;
                                      constexpr const std::type_info& type  ( ) const;
};

#include "any.cpp"