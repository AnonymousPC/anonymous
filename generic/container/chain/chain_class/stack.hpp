#pragma once

template < class type >
class stack
    extends private deque<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    public: // Typedef
        using  value_type = type;
        struct stack_tag { };

    public: // Core
        constexpr stack ( ) = default;

    public: // Interface
        constexpr       int   size  ( ) const;
        constexpr       bool  empty ( ) const;

        constexpr       type& top   ( );
        constexpr const type& top   ( ) const;

        constexpr       void  push  ( type );
        constexpr       type  pop   ( );
};

#include "stack.ipp"