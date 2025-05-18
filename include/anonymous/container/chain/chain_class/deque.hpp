template < class type, class device >
class deque
    extends public device::template deque<type>,
            public container_interface<deque<type,device>,type,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );

    private: // Base
        using base = device::template deque<type>;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;
        using iterator        = base::iterator;
        using const_iterator  = base::const_iterator;
        using device_type     = device;

    public: // Core
        constexpr deque ( )                                                   = default;
        constexpr deque ( const deque&  )             requires copyable<type> = default;
        constexpr deque (       deque&& )                                     = default;
        constexpr deque& operator = ( const deque&  ) requires copyable<type> = default;
        constexpr deque& operator = (       deque&& )                         = default;

    public: // Member
        constexpr int             size        ( )      const;
        constexpr bool            empty       ( )      const;
        constexpr iterator        begin       ( );
        constexpr const_iterator  begin       ( )      const;
        constexpr iterator        end         ( );
        constexpr const_iterator  end         ( )      const;
        constexpr reference       operator [] ( int );
        constexpr const_reference operator [] ( int )  const;

        constexpr reference       front       ( );
        constexpr const_reference front       ( )      const;
        constexpr reference       back        ( );
        constexpr const_reference back        ( )      const;

        constexpr reference       push_front  ( type );
        constexpr reference       push_back   ( type );
        constexpr value_type      pop_front   ( );
        constexpr value_type      pop_back    ( );
        constexpr reference       insert      ( int, type );
        constexpr value_type      erase       ( int );
};





#include "deque.cpp"