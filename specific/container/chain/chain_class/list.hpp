#pragma once

template < class type, class device >
class list
    extends public device::template list<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> );

    private: // Typedef
        using base = device::template list<type>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
        using  device_type     = device;
        struct list_tag { };

    public: // Core
        constexpr list ( )                                                  = default;
        constexpr list ( const list&  )             requires copyable<type> = default;
        constexpr list (       list&& )             requires movable <type> = default;
        constexpr list& operator = ( const list&  ) requires copyable<type> = default;
        constexpr list& operator = (       list&& ) requires movable <type> = default;

    public: // Member
        constexpr int             size          ( )      const;
        constexpr bool            empty         ( )      const;
        constexpr iterator        begin         ( );
        constexpr const_iterator  begin         ( )      const;
        constexpr iterator        end           ( );
        constexpr const_iterator  end           ( )      const;
        constexpr reference       front         ( );
        constexpr const_reference front         ( )      const;
        constexpr reference       back          ( );
        constexpr const_reference back          ( )      const;
        constexpr void            push_front    ( type )       requires movable<type>;
        constexpr void            push_back     ( type )       requires movable<type>;
        constexpr type            pop_front     ( )            requires movable<type>;
        constexpr type            pop_back      ( )            requires movable<type>;
};





#include "list.ipp"