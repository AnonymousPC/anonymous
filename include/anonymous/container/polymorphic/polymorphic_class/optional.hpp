using std::nullopt;
using std::nullopt_t;

template < class types >
class optional
    extends public std::optional<types>
{
    private: // Precondition
        static_assert ( not is_void<types> and not is_reference<types> );

    private: // Base
        using base = std::optional<types>;

    public: // Typedef
        using value_type      =       types;
        using reference       =       types&;
        using const_reference = const types&;

    public: // Core
        constexpr optional ( )                                                       = default;
        constexpr optional ( const optional&  )             requires copyable<types> = default;
        constexpr optional (       optional&& )             requires movable <types> = default;
        constexpr optional& operator = ( const optional&  ) requires copyable<types> = default;
        constexpr optional& operator = (       optional&& ) requires movable <types> = default;
        
    public: // Constructor
        constexpr optional ( types );
        constexpr optional ( nullopt_t );

    public: // Member
        constexpr       reference       value ( );
        constexpr       const_reference value ( ) const;
        constexpr       bool            empty ( ) const;
        constexpr const std::type_info& type  ( ) const;
};

#include "optional.cpp"