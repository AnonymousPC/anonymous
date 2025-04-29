template < class type1, class type2, class compare, class device >
class map
    extends public  device::template map<type1,type2,compare>,
            private detail::map_keys  <map<type1,type2,compare,device>,type1,device>,
            private detail::map_values<map<type1,type2,compare,device>,type2,device>,
            public  collection_algo<map<type1,type2,compare,device>,pair<const type1,type2>,device>
{
    private: // Precondition
        static_assert ( not is_const<type1> and not is_volatile<type1> and not is_reference<type1> );
        static_assert ( default_initializable<type1> and movable<type1> );
        static_assert ( not is_const<type2> and not is_volatile<type2> and not is_reference<type2> );
        static_assert ( default_initializable<type2> and movable<type2> );
        static_assert ( [] { if constexpr ( same_as<device,cpu> ) return relation<compare,type1,type1>; else return true; } () );

    private: // Typedef
        using base = device::template map<type1,type2,compare>;
        friend detail::map_keys  <map,type1,device>;
        friend detail::map_values<map,type2,device>;
        
    public: // Typedef
        using  key_type              = device::template value_type     <type1>;
        using  value_type            = device::template value_type     <type2>;
        using  reference             = device::template reference      <pair<const type1,type2>>;
        using  const_reference       = device::template const_reference<pair<const type1,type2>>;
        using  key_reference         = device::template reference      <type1>;
        using  const_key_reference   = device::template const_reference<type1>;
        using  value_reference       = device::template reference      <type2>;
        using  const_value_reference = device::template const_reference<type2>;
        using  pointer               = device::template pointer        <pair<const type1,type2>>;
        using  const_pointer         = device::template const_pointer  <pair<const type1,type2>>;
        using  key_pointer           = device::template pointer        <type1>;
        using  const_key_pointer     = device::template const_pointer  <type1>;
        using  value_pointer         = device::template pointer        <type2>;
        using  const_value_pointer   = device::template const_pointer  <type2>;
        class  iterator;         
        class  const_iterator;      
        using  compare_type          = compare;
        using  device_type           = device;
        struct map_concept { };

    public: // Core
        constexpr map ( )                                                                      = default;
        constexpr map ( const map&  )             requires copyable<type1> and copyable<type2> = default;
        constexpr map (       map&& )                                                          = default;
        constexpr map& operator = ( const map&  ) requires copyable<type1> and copyable<type2> = default;
        constexpr map& operator = (       map&& )                                              = default;

    public: // Constructor
        constexpr map ( std::initializer_list<pair<const type1,type2>> ) requires copyable<type1> and copyable<type2>;

    public: // Member
        constexpr        int                   size        ( )               const;
        constexpr        bool                  empty       ( )               const;
        constexpr        iterator              begin       ( );
        constexpr        const_iterator        begin       ( )               const;
        constexpr        iterator              end         ( );
        constexpr        const_iterator        end         ( )               const;
        constexpr        value_reference       operator [] ( const type1&  );
        constexpr        value_reference       operator [] (       type1&& );
        constexpr        const_value_reference operator [] ( const type1&  ) const;
        constexpr        bool                  contains    ( const type1&  ) const;

        constexpr const  auto&                 keys        ( )               const;
        constexpr        auto&                 values      ( );
        constexpr const  auto&                 values      ( )               const;
        
        constexpr        map&                  clear       ( );
        constexpr        map&                  pop         ( const type1&  );
        constexpr        map&                  update      ( const map&    );

    public: // Override
        constexpr auto emplace ( auto&&... args ) requires constructible_from<typename base::value_type,decltype(args)...>;
};

#include "map.cpp"