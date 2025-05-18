template < class type, class device >
class list
    extends public device::template list<type>,
            public container_interface<list<type,device>,type,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );

    private: // Base
        using base = device::template list<type>;

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
        constexpr list ( )                                                  = default;
        constexpr list ( const list&  )             requires copyable<type> = default;
        constexpr list (       list&& )                                     = default;
        constexpr list& operator = ( const list&  ) requires copyable<type> = default;
        constexpr list& operator = (       list&& )                         = default;

    public: // Member
        constexpr int             size       ( )      const;
        constexpr bool            empty      ( )      const;
        constexpr iterator        begin      ( );
        constexpr const_iterator  begin      ( )      const;
        constexpr iterator        end        ( );
        constexpr const_iterator  end        ( )      const;

        constexpr reference       front      ( );
        constexpr const_reference front      ( )      const;
        constexpr reference       back       ( );
        constexpr const_reference back       ( )      const;

        constexpr reference       push_front ( type );
        constexpr reference       push_back  ( type );
        constexpr value_type      pop_front  ( );
        constexpr value_type      pop_back   ( );

    public: // Algorithm
        constexpr list& remove  ( const equalable_to<type>      auto& );
        constexpr list& remove  (       predicate   <type>      auto  );
        constexpr list& reverse (                                     );
        constexpr list& sort    (                                     ) requires comparable<type>;
        constexpr list& sort    (       relation    <type,type> auto  );
        constexpr list& unique  (                                     ) requires equalable <type>;
        constexpr list& unique  (       relation    <type,type> auto  );
};





#include "list.cpp"