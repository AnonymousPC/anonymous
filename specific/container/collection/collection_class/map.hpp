#pragma once

template < class type1, class type2, class compare, class device >
class map
    extends public device::template map<type1,type2,compare>,
            public collection_algo<map<type1,type2,compare,device>,pair<const type1,type2>,compare,device>
{
    private: // Precondition
        static_assert ( not is_const<type1> and not is_volatile<type1> and not is_reference<type1> );
        static_assert ( default_initializable<type1> and movable<type1> );
        static_assert ( not is_const<type2> and not is_volatile<type2> and not is_reference<type2> );
        static_assert ( default_initializable<type2> and movable<type2> );
        static_assert ( [] { if constexpr ( same_as<device,cpu> ) return relation<compare,type1,type1>; else return true; } () );

    private: // Typedef
        using base = device::template map<type1,type2,compare>;
        class keys_view;
        class values_view;

    private: // Data
        keys_view   k_view;
        values_view v_view;

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
        struct map_tag { };

    public: // Core
        constexpr map ( );
        constexpr map ( const map&  )             requires copyable<type1> and copyable<type2>;
        constexpr map (       map&& );
        constexpr map& operator = ( const map&  ) requires copyable<type1> and copyable<type2>;
        constexpr map& operator = (       map&& );

    public: // Constructor
        constexpr map ( std::initializer_list<pair<const type1,type2>> ) requires copyable<type1> and copyable<type2>;
\
    public: // Conversion 
        template < class type3, class type4, class compare2 > constexpr          map ( const map<type3,type4,compare2,device>& ) requires convertible_to    <type3,type1> and convertible_to    <type4,type2> but ( not same_as       <type1,type3> or not same_as       <type2,type4> );
        template < class type3, class type4, class compare2 > constexpr explicit map ( const map<type3,type4,compare2,device>& ) requires constructible_from<type1,type3> and constructible_from<type2,type4> but ( not convertible_to<type3,type1> or not convertible_to<type4,type2> );

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

        constexpr const  auto                  keys        ( )               const;
        constexpr        auto                  values      ( );
        constexpr const  auto                  values      ( )               const;
        
        constexpr        map&                  clear       ( );
        constexpr        map&                  pop         ( const type1&  );
        constexpr        map&                  update      ( const map&    );
};

#include "map.ipp"