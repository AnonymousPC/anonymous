using std::nullopt;
using std::nullopt_t;

template < class types, class device >
class optional
    extends public device::template optional<types>
{
    private: // Precondition
        static_assert ( not is_void<types> and not is_reference<types> );

    public: // Typedef
        using value_type      = device::template value_type     <types>;
        using reference       = device::template reference      <types>;
        using const_reference = device::template const_reference<types>;
        using device_type     = device;

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