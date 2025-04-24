using std::nullopt;
using std::nullopt_t;

template < class types >
class optional
    extends public std::optional<types>
{
    private: // Precondition
        static_assert ( not is_const<types> and not is_volatile<types> and not is_reference<types> );

    private: // Typedef
        using base = std::optional<types>;

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
        constexpr       bool            empty ( ) const;
        constexpr const std::type_info& type  ( ) const;
        constexpr       types&          value ( );
        constexpr const types&          value ( ) const;
};

#include "optional.cpp"