template < class type, class device >
class forward_list
    extends public device::template forward_list<type>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> );

    private: // Typedef
        using base = device::template forward_list<type>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  iterator        = base::iterator;
        using  const_iterator  = base::const_iterator;
        using  device_type     = device;

    public: // Core
        constexpr forward_list ( )                                                          = default;
        constexpr forward_list ( const forward_list&  )             requires copyable<type> = default;
        constexpr forward_list (       forward_list&& )             requires movable <type> = default;
        constexpr forward_list& operator = ( const forward_list&  ) requires copyable<type> = default;
        constexpr forward_list& operator = (       forward_list&& ) requires movable <type> = default;

    public: // Member
        constexpr int             size          ( )      const;
        constexpr bool            empty         ( )      const;
        constexpr iterator        begin         ( );
        constexpr const_iterator  begin         ( )      const;
        constexpr iterator        end           ( );
        constexpr const_iterator  end           ( )      const;
        constexpr reference       front         ( );
        constexpr const_reference front         ( )      const;
        constexpr void            push_front    ( type )       requires movable<type>;
        constexpr type            pop_front     ( )            requires movable<type>;
};





#include "forward_list.cpp"