template < class type, class device >
class stack
    extends public device::template stack<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );

    private: // Base
        using base = device::template stack<type>;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using device_type     = device;

    public: // Core
        constexpr stack ( )                                                   = default;
        constexpr stack ( const stack&  )             requires copyable<type> = default;
        constexpr stack (       stack&& )                                     = default;
        constexpr stack& operator = ( const stack&  ) requires copyable<type> = default;
        constexpr stack& operator = (       stack&& )                         = default;

    public: // Member
        constexpr int             size  ( )      const;
        constexpr bool            empty ( )      const;

        constexpr reference       top   ( );
        constexpr const_reference top   ( )      const;

        constexpr reference       push  ( type );
        constexpr value_type      pop   ( );
};

#include "stack.cpp"