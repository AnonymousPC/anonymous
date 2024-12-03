#pragma once

/// Declaration

class nullopt_t { };
constexpr nullopt_t nullopt = nullopt_t();




template < class types >
class optional
{
    private: // Precondition
        static_assert ( not is_const<types> and not is_volatile<types> and not is_reference<types> );

    private: // Base
        union union_obj;

    private: // Data
        union_obj storage;
        bool      flag = false;

    public: // Typedef
        using value_type = types;

    public: // Core
        constexpr  optional ( );
        constexpr  optional ( const optional&  )             requires std::copyable<types>;
        constexpr  optional (       optional&& )             requires std::movable <types>;
        constexpr  optional ( types )                        requires std::movable <types>;
        constexpr  optional ( nullopt_t );
        constexpr ~optional ( );
        constexpr  optional& operator = ( const optional&  ) requires std::copyable<types>;
        constexpr  optional& operator = (       optional&& ) requires std::movable <types>;
        constexpr  optional& operator = ( types )            requires std::movable <types>;
        constexpr  optional& operator = ( nullopt_t );

    public: // Member
        constexpr       bool            empty ( ) const;
        constexpr const std::type_info& type  ( ) const;
        constexpr       types&          value ( );
        constexpr const types&          value ( ) const;
};

#include "optional.ipp"