#pragma once


template < class type, class compare >
class priority_queue
    extends private vector<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( std::default_initializable<type> and std::movable<type> );
        static_assert ( function_type<compare,bool(type,type)> );

    public: // Typedef
        using  value_type = type;
        struct list_tag { };

    public: // Core
        constexpr priority_queue ( ) = default;

    public: // Interface
        constexpr       int   size  ( ) const;
        constexpr       bool  empty ( ) const;
        constexpr const type& top   ( ) const;
        constexpr       void  push  ( type );
        constexpr       type  pop   ( );

    private: // Auxiliary
        constexpr static const auto reverse = [] ( const type& left, const type& right ) { return not compare() ( left, right ); };
};



#include "priority_queue.ipp"