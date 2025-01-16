#pragma once

using std::nullopt;
using std::nullopt_t;

template < class type >
class optional
    extends public std::optional<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );

    private: // Typedef
        using base = std::optional<type>;

    public: // Core
        constexpr optional ( )                                                      = default;
        constexpr optional ( const optional&  )             requires copyable<type> = default;
        constexpr optional (       optional&& )             requires movable <type> = default;
        constexpr optional& operator = ( const optional&  ) requires copyable<type> = default;
        constexpr optional& operator = (       optional&& ) requires movable <type> = default;
        
    public: // Constructor
        constexpr optional ( type )
        constexpr optional ( nullopt_t );

    public: // Member
        constexpr       bool            empty ( ) const;
        constexpr const std::type_info& type  ( ) const;
        constexpr       type&           value ( );
        constexpr const type&           value ( ) const;
};

#include "optional.ipp"