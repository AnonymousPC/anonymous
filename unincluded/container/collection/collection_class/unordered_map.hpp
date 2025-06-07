template < class type1, class type2, class hash, class device >
class unordered_map
    extends public device::template unordered_map<type1,type2,hash>,
            public container_interface   <unordered_map<type1,type2,hash,device>,pair<const type1,type2>,device>
{
    private: // Precondition
        static_assert ( not is_const<type1> and not is_volatile<type1> and not is_reference<type1> );
        static_assert ( default_initializable<type1> and movable<type1> );
        static_assert ( not is_const<type2> and not is_volatile<type2> and not is_reference<type2> );
        static_assert ( default_initializable<type2> and movable<type2> );
        static_assert ( invocable<hash,type1> );

    private: // Base
        using base = device::template unordered_map<type1,type2,hash>;

    public: // Typedef
        using key_type              = device::template value_type        <type1>;
        using value_type            = device::template value_type        <type2>;
        using key_reference         = device::template reference         <type1>;
        using const_key_reference   = device::template const_reference   <type1>;
        using value_reference       = device::template reference         <type2>;
        using const_value_reference = device::template const_reference   <type2>;
        using key_pointer           = device::template pointer           <type1>;
        using const_key_pointer     = device::template const_pointer     <type1>;
        using value_pointer         = device::template pointer           <type2>;
        using const_value_pointer   = device::template const_pointer     <type2>;
        using iterator              = device::template transform_iterator<typename base::iterator,      detail::transform_to_pair<type1,type2,device>>; 
        using const_iterator        = device::template transform_iterator<typename base::const_iterator,detail::transform_to_pair<type1,type2,device>>;
        using hash_type             = hash;
        using device_type           = device;

    public: // Core
        constexpr unordered_map ( )                                                                                = default;
        constexpr unordered_map ( const unordered_map&  )             requires copyable<type1> and copyable<type2> = default;
        constexpr unordered_map (       unordered_map&& )                                                          = default;
        constexpr unordered_map& operator = ( const unordered_map&  ) requires copyable<type1> and copyable<type2> = default;
        constexpr unordered_map& operator = (       unordered_map&& )                                              = default;

    public: // Constructor
        constexpr unordered_map ( std::initializer_list<pair<const type1,type2>> ) requires copyable<type1> and copyable<type2>;

    public: // Member
        constexpr int                   size        ( )                      const;
        constexpr bool                  empty       ( )                      const;
        constexpr iterator              begin       ( );
        constexpr const_iterator        begin       ( )                      const;
        constexpr iterator              end         ( );
        constexpr const_iterator        end         ( )                      const;
        constexpr value_reference       operator [] ( const type1& );
        constexpr const_value_reference operator [] ( const type1& )         const;
        constexpr bool                  contains    ( const type1& )         const;
        
        constexpr unordered_map&        clear       ( );
        constexpr unordered_map&        pop         ( const type1&  );
        constexpr unordered_map&        update      ( const unordered_map& );

    public: // Algorithm
        constexpr bool all   ( const equalable_to<pair<const type1,type2>> auto& ) const;
        constexpr int  count ( const equalable_to<pair<const type1,type2>> auto& ) const;
        constexpr bool exist ( const equalable_to<pair<const type1,type2>> auto& ) const;
        constexpr bool none  ( const equalable_to<pair<const type1,type2>> auto& ) const;
};

#include "unordered_map.cpp"