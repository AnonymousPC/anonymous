template < class type, class hash, class device >
class unordered_set
    extends public device::template unordered_set<type,hash>,
            public collection_algo<unordered_set<type,hash,device>,type,device>
{
    private: // Precondition
        static_assert ( not is_const<type> and not is_volatile<type> and not is_reference<type> );
        static_assert ( default_initializable<type> and movable<type> );
        static_assert ( [] { if constexpr ( same_as<device,cpu> ) return invocable<hash,type>; else return true; } () );

    private: // Typedef
        using base = device::template unordered_set<type,hash>;

    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;
        using  const_iterator  = base::const_iterator;
        using  hash_type       = hash;
        using  device_type     = device;
        struct set_concept { };

    public: // Core
        constexpr unordered_set ( )                                                           = default;
        constexpr unordered_set ( const unordered_set&  )             requires copyable<type> = default;
        constexpr unordered_set (       unordered_set&& )                                     = default;
        constexpr unordered_set& operator = ( const unordered_set&  ) requires copyable<type> = default;
        constexpr unordered_set& operator = (       unordered_set&& )                         = default;

    public: // Constructor
        constexpr unordered_set ( std::initializer_list<type> ) requires copyable<type>;

    public: // Member
        constexpr int            size     ( )                      const;
        constexpr bool           empty    ( )                      const;
        constexpr const_iterator begin    ( )                      const;
        constexpr const_iterator end      ( )                      const;
        constexpr bool           contains ( const type& )          const;

        constexpr unordered_set& clear    ( );
        constexpr unordered_set& push     (       type  );
        constexpr unordered_set& pop      ( const type& );
        constexpr unordered_set& update   ( const unordered_set& );

    public: // Override
        constexpr auto emplace ( auto&&... args ) requires constructible_from<typename base::value_type,decltype(args)...>;
};

#include "unordered_set.cpp"