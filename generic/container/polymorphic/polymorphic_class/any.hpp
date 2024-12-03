#pragma once

class any
{
    private: // Base
                                 class static_obj;
        template < class types > class dynamic_obj;

    private: // Data
        static_obj*           ptr  = nullptr;
        const std::type_info* rtti = nullptr;

    public: // Core
        constexpr  any ( )                    = default;
        constexpr  any ( const any&  );
        constexpr  any (       any&& );
        constexpr  any ( std::copyable auto );
        constexpr ~any ( );
        constexpr  any& operator = ( const any&  );
        constexpr  any& operator = (       any&& );

    public: // Member
                                       constexpr       bool            empty ( ) const;
                                       constexpr const std::type_info& type  ( ) const;
        template < class output_type > constexpr       output_type&    value ( );
        template < class output_type > constexpr const output_type&    value ( ) const;
};

#include "any.ipp"