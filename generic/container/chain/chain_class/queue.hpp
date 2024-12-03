#pragma once

template < class type >
class queue
    extends private deque<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    public: // Typedef
        using  value_type = type;
        struct queue_tag { };

    public: // Core
        constexpr queue ( ) = default;

    public: // Interface
        constexpr       int   size  ( ) const;
        constexpr       bool  empty ( ) const;

        constexpr       type& front ( );
        constexpr const type& front ( ) const;
        constexpr       type& back  ( );
        constexpr const type& back  ( ) const;

        constexpr       void  push  ( type );
        constexpr       type  pop   ( );
};

#include "queue.ipp"