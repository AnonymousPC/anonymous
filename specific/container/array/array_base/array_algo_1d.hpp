#pragma once

template < class array_type,
           class type,
           int   dim,
           class device
         >
class array_algo;

template < class array_type,
           class type,
           class device
         >
class array_algo<array_type,type,1,device>
{
    public: // Typedef
        using  value_type      = device::template value_type     <type>;
        using  reference       = device::template reference      <type>;
        using  const_reference = device::template const_reference<type>;
        using  pointer         = device::template pointer        <type>;
        using  const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr auto begin      ( );
        constexpr auto begin      ( ) const;
        constexpr auto end        ( );
        constexpr auto end        ( ) const;
        constexpr auto data       ( );
        constexpr auto data       ( ) const;
        constexpr auto size       ( ) const;
        constexpr auto ownership  ( ) const;
        constexpr auto contiguous ( ) const;

    public: // Member
        constexpr       int            adjacent_find       (                                       ) const requires equalable<type>;
        constexpr       int            adjacent_find       ( const relation      <type,type> auto  ) const;
        constexpr       array<int>     adjacent_where      (                                       ) const requires equalable<type>;
        constexpr       array<int>     adjacent_where      ( const relation      <type,type> auto  ) const;
        constexpr       bool           all                 ( const equalable_to  <type>      auto& ) const;
        constexpr       bool           all                 ( const predicate     <type>      auto  ) const;
        constexpr       bool           contains            ( const equalable_to  <type>      auto& ) const;
        constexpr       bool           contains            ( const predicate     <type>      auto  ) const;
        constexpr       int            count               ( const equalable_to  <type>      auto& ) const;
        constexpr       int            count               ( const predicate     <type>      auto  ) const;
        constexpr       bool           exist               ( const equalable_to  <type>      auto& ) const;
        constexpr       bool           exist               ( const predicate     <type>      auto  ) const;
        constexpr       int            find                ( const equalable_to  <type>      auto& ) const;
        constexpr       int            find                ( const predicate     <type>      auto  ) const;
        constexpr       bool           is_partitioned      ( const predicate     <type>      auto  ) const;
        constexpr       bool           is_sorted           (                                       ) const requires comparable<type>;
        constexpr       bool           is_sorted           ( const relation      <type,type> auto  ) const;
        constexpr const reference      max                 (                                       ) const requires comparable<type>;
        constexpr const reference      max                 ( const relation      <type,type> auto  ) const;
        constexpr const reference      min                 (                                       ) const requires comparable<type>;
        constexpr const reference      min                 ( const relation      <type,type> auto  ) const;
        constexpr       array_type&    next_permutation    (                                       )       requires comparable<type>;
        constexpr       array_type&    next_permutation    ( const relation      <type,type> auto  );
        constexpr       bool           none                ( const equalable_to  <type>      auto& ) const;
        constexpr       bool           none                ( const predicate     <type>      auto  ) const;
        constexpr       array_type&    partial_sort        ( int                                   )       requires comparable<type>;
        constexpr       array_type&    partial_sort        ( int, relation       <type,type> auto  );
        constexpr       array_type&    partition           ( const predicate     <type>      auto  );
        constexpr       array_type&    prev_permutation    (                                       )       requires comparable<type>;
        constexpr       array_type&    prev_permutation    ( const relation      <type,type> auto  );
        constexpr       array_type&    remove              ( const equalable_to  <type>      auto& );
        constexpr       array_type&    remove              ( const predicate     <type>      auto  );
        constexpr       array_type&    reverse             (                                       );
        constexpr       int            right_adjacent_find (                                       ) const requires equalable<type>;
        constexpr       int            right_adjacent_find ( const relation      <type,type> auto  ) const;
        constexpr       int            right_find          ( const equalable_to  <type>      auto& ) const;
        constexpr       int            right_find          ( const predicate     <type>      auto  ) const;
        constexpr       array_type&    rotate              ( int                                   );
        constexpr       array_type&    stable_partition    ( const equalable_to  <type>      auto& )       requires comparable<type>;
        constexpr       array_type&    stable_partition    ( const predicate     <type>      auto  );
        constexpr       array_type&    stable_sort         (                                       )       requires comparable<type>;
        constexpr       array_type&    stable_sort         ( const relation      <type,type> auto  );      
        constexpr       array_type&    sort                (                                       )       requires comparable<type>;
        constexpr       array_type&    sort                ( const relation      <type,type> auto  );
        constexpr       array_type&    unique              (                                       )       requires equalable<type>;
        constexpr       array_type&    unique              ( const relation      <type,type> auto  );
        constexpr       array<int>     where               ( const equalable_to  <type>      auto& ) const;
        constexpr       array<int>     where               ( const predicate     <type>      auto  ) const;

        constexpr       type           average             (                                       ) const requires default_initializable<type> and plusable<type> and dividable_to<type,int>;
        constexpr       type           sum                 (                                       ) const requires default_initializable<type> and plusable<type>;
        constexpr       type           product             (                                       ) const requires convertible_to   <int,type> and multipliable<type>;

        constexpr       array_type&    each                (       invocable     <reference> auto  );
        constexpr const array_type&    each                (       invocable     <type>      auto  ) const;
        constexpr       array_type&    fill                ( const convertible_to<type>      auto& );
        constexpr       array_type&    generate            (       invocable_r   <type>      auto  );
        constexpr       array_type&    transform           (       invocable_r   <type,type> auto  );
        constexpr       array_type&    replace             ( const equalable_to  <type>      auto&, const convertible_to<type> auto& );
        constexpr       array_type&    replace             (       predicate     <type>      auto,  const convertible_to<type> auto& );
};

// This .ipp file is explicitly delay included in array.hpp
// #include "array_algo_1d.ipp"