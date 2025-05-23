template < class type, class compare, class device >
class set
    extends public device::template set<type,compare>,
            public container_interface<set<type,compare,device>,type,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( relation_between<compare,type,type> );

    private: // Base
        using base = device::template set<type,compare>;

    public: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;
        using const_iterator  = base::const_iterator;
        using compare_type    = compare;
        using device_type     = device;

    public: // Core
        constexpr set ( )                                                 = default;
        constexpr set ( const set&  )             requires copyable<type> = default;
        constexpr set (       set&& )                                     = default;
        constexpr set& operator = ( const set&  ) requires copyable<type> = default;
        constexpr set& operator = (       set&& )                         = default;

    public: // Constructor
        constexpr set ( std::initializer_list<type> ) requires copyable<type>;

    public: // Member
        constexpr int            size     ( )             const;
        constexpr bool           empty    ( )             const;
        constexpr const_iterator begin    ( )             const;
        constexpr const_iterator end      ( )             const;
        constexpr bool           contains ( const type& ) const;

        constexpr set&           clear    ( );
        constexpr set&           push     (       type  );
        constexpr set&           pop      ( const type& );

    public: // Algorithm
        constexpr bool all   ( const equalable_to<type> auto& ) const;
        constexpr int  count ( const equalable_to<type> auto& ) const;
        constexpr bool exist ( const equalable_to<type> auto& ) const;
        constexpr bool none  ( const equalable_to<type> auto& ) const;
};

#include "set.cpp"