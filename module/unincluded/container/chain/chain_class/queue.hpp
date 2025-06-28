template < class type, class device >
class queue
    extends public device::template queue<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );

    private: // Base
        using base = device::template queue<type>;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using device_type     = device;

    public: // Core
        constexpr queue ( )                                                   = default;
        constexpr queue ( const queue&  )             requires copyable<type> = default;
        constexpr queue (       queue&& )                                     = default;
        constexpr queue& operator = ( const queue&  ) requires copyable<type> = default;
        constexpr queue& operator = (       queue&& )                         = default;

    public: // Member
        constexpr int             size  ( )      const;
        constexpr bool            empty ( )      const;

        constexpr reference       front ( );
        constexpr const_reference front ( )      const;
        constexpr reference       back  ( );
        constexpr const_reference back  ( )      const;

        constexpr reference       push  ( type );
        constexpr value_type      pop   ( );
};

#include "queue.cpp"