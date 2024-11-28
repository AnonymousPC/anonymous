#pragma once

template < class type >
class deque
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );

    private: // Settings
        constexpr static const int chunk = 8;

    private: // Data
        vector<vector<type>> arr         = vector<vector<type>>();
        int                  index_first = 1;
        int                  index_last  = chunk; // As initialization it's equal to chunk, and after first push() it becomes 1.

    public: // Typedef
        using  value_type = type;
        struct deque_tag { };

    public: // Core
        constexpr deque ( )                                                        = default;
        constexpr deque ( const deque&  )             requires std::copyable<type> = default;
        constexpr deque (       deque&& );
        constexpr deque& operator = ( const deque&  ) requires std::copyable<type> = default;
        constexpr deque& operator = (       deque&& );

    public: // Interface
        constexpr       int   size       ( ) const;
        constexpr       bool  empty      ( ) const;

        constexpr       type& front      ( );
        constexpr const type& front      ( ) const;
        constexpr       type& back       ( );
        constexpr const type& back       ( ) const;

        constexpr       void  push_front ( type );
        constexpr       void  push_back  ( type );
        constexpr       type  pop_front  ( );
        constexpr       type  pop_back   ( );
};





#include "deque.ipp"