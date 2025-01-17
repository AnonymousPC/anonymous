#pragma once

template < class type, class compare, class device >
class set
    extends public device::template set<type,compare>,
            public collection_algo<set<type,compare,device>,type,compare,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( [] { if constexpr ( same_as<device,cpu> ) return relation<compare,type,type>; else return true; } () );

    private: // Typedef
        using base = device::template set<type,compare>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  const_iterator  = base::const_iterator;
        using  compare_type    = compare;
        using  device_type     = device;
        struct set_tag { };

    public: // Core
        constexpr set ( )                                                 = default;
        constexpr set ( const set&  )             requires copyable<type> = default;
        constexpr set (       set&& )                                     = default;
        constexpr set& operator = ( const set&  ) requires copyable<type> = default;
        constexpr set& operator = (       set&& )                         = default;

    public: // Constructor
        constexpr          set ( std::initializer_list<type> )                          requires copyable<type>;
        constexpr explicit set ( std::from_range_t, std::ranges::input_range auto&& r ) requires requires { std::declval<set>().push(*std::ranges::begin(r)); };

    public: // Member
        constexpr int            size     ( )             const;
        constexpr bool           empty    ( )             const;
        constexpr const_iterator begin    ( )             const;
        constexpr const_iterator end      ( )             const;
        constexpr bool           contains ( const type& ) const;

        constexpr set&           clear    ( );
        constexpr set&           push     (       type  );
        constexpr set&           pop      ( const type& );
        constexpr set&           update   ( const set&  );
};

#include "set.ipp"