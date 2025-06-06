template < class type, class compare, class device >
class priority_queue
    extends public device::template priority_queue<type,compare>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( relation_between<compare,type,type> );

    private: // Base
        using base = device::template priority_queue<type,compare>;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using compare_type    = compare;
        using device_type     = device;

    public: // Core
        constexpr priority_queue ( )                                                            = default;
        constexpr priority_queue ( const priority_queue&  )             requires copyable<type> = default;
        constexpr priority_queue (       priority_queue&& )                                     = default;
        constexpr priority_queue& operator = ( const priority_queue&  ) requires copyable<type> = default;
        constexpr priority_queue& operator = (       priority_queue&& )                         = default;

    public: // Member
        constexpr int             size  ( )      const;
        constexpr bool            empty ( )      const;

        constexpr const_reference top   ( )      const;

        constexpr void            push  ( type );
        constexpr value_type      pop   ( );
};



#include "priority_queue.cpp"