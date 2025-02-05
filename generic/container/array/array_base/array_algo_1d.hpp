#pragma once

template < class container,
           class type,
           int   dim,
           class device
         >
class array_algo;

template < class container,
           class type,
           class device
         >
class array_algo<container,type,1,device>
{
    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr decltype(auto) begin      ( );
        constexpr decltype(auto) begin      ( ) const;
        constexpr decltype(auto) end        ( );
        constexpr decltype(auto) end        ( ) const;
        constexpr decltype(auto) data       ( );
        constexpr decltype(auto) data       ( ) const;
        constexpr decltype(auto) size       ( ) const;
        constexpr decltype(auto) empty      ( ) const;
        constexpr decltype(auto) ownership  ( ) const;
        constexpr decltype(auto) contiguous ( ) const;

    public: // Member
        constexpr       int             adjacent_find       (                                       ) const requires equalable<type>;
        constexpr       int             adjacent_find       (       relation      <type,type> auto  ) const;
        constexpr       array<int>      adjacent_where      (                                       ) const requires equalable<type>;
        constexpr       array<int>      adjacent_where      (       relation      <type,type> auto  ) const;
        constexpr       bool            all                 ( const equalable_to  <type>      auto& ) const;
        constexpr       bool            all                 (       predicate     <type>      auto  ) const;
        constexpr       bool            contains            ( const equalable_to  <type>      auto& ) const;
        constexpr       bool            contains            (       predicate     <type>      auto  ) const;
        constexpr       int             count               ( const equalable_to  <type>      auto& ) const;
        constexpr       int             count               (       predicate     <type>      auto  ) const;
        constexpr       bool            exist               ( const equalable_to  <type>      auto& ) const;
        constexpr       bool            exist               (       predicate     <type>      auto  ) const;
        constexpr       int             find                ( const equalable_to  <type>      auto& ) const;
        constexpr       int             find                (       predicate     <type>      auto  ) const;
        constexpr       bool            is_partitioned      (       predicate     <type>      auto  ) const;
        constexpr       bool            is_sorted           (                                       ) const requires comparable<type>;
        constexpr       bool            is_sorted           (       relation      <type,type> auto  ) const;
        constexpr       reference       max                 (                                       )       requires comparable<type>;
        constexpr       const_reference max                 (       relation      <type,type> auto  ) const;
        constexpr       reference       min                 (                                       )       requires comparable<type>;
        constexpr       const_reference min                 (       relation      <type,type> auto  ) const;
        constexpr       container&      next_permutation    (                                       )       requires comparable<type>;
        constexpr       container&      next_permutation    (       relation      <type,type> auto  );
        constexpr       bool            none                ( const equalable_to  <type>      auto& ) const;
        constexpr       bool            none                (       predicate     <type>      auto  ) const;
        constexpr       container&      partial_sort        ( int                                   )       requires comparable<type>;
        constexpr       container&      partial_sort        ( int,  relation      <type,type> auto  );
        constexpr       container&      partition           (       predicate     <type>      auto  );
        constexpr       container&      prev_permutation    (                                       )       requires comparable<type>;
        constexpr       container&      prev_permutation    (       relation      <type,type> auto  );
        constexpr       container&      remove              ( const equalable_to  <type>      auto& );
        constexpr       container&      remove              (       predicate     <type>      auto  );
        constexpr       container&      reverse             (                                       );
        constexpr       int             right_adjacent_find (                                       ) const requires equalable<type>;
        constexpr       int             right_adjacent_find (       relation      <type,type> auto  ) const;
        constexpr       int             right_find          ( const equalable_to  <type>      auto& ) const;
        constexpr       int             right_find          (       predicate     <type>      auto  ) const;
        constexpr       container&      rotate              ( int                                   );
        constexpr       container&      stable_partition    (       predicate     <type>      auto  );
        constexpr       container&      stable_sort         (                                       )       requires comparable<type>;
        constexpr       container&      stable_sort         (       relation      <type,type> auto  );      
        constexpr       container&      sort                (                                       )       requires comparable<type>;
        constexpr       container&      sort                (       relation      <type,type> auto  );
        constexpr       container&      unique              (                                       )       requires equalable<type>;
        constexpr       container&      unique              (       relation      <type,type> auto  );
        constexpr       array<int>      where               ( const equalable_to  <type>      auto& ) const;
        constexpr       array<int>      where               (       predicate     <type>      auto  ) const;

        constexpr       type            average             (                                       ) const requires default_initializable<type> and plusable<type> and dividable_to<type,int>;
        constexpr       type            sum                 (                                       ) const requires default_initializable<type> and plusable<type>;
        constexpr       type            product             (                                       ) const requires convertible_to   <int,type> and multipliable<type>;

        constexpr       container&      for_each            (       invocable     <reference> auto  );
        constexpr const container&      for_each            (       invocable     <type>      auto  ) const;
        constexpr       container&      fill                ( const convertible_to<type>      auto& );
        constexpr       container&      generate            (       invocable_r   <type>      auto  );
        constexpr       container&      transform           (       invocable_r   <type,type> auto  );
        constexpr       container&      replace             ( const equalable_to  <type>      auto&, const convertible_to<type> auto& );
        constexpr       container&      replace             (       predicate     <type>      auto,  const convertible_to<type> auto& );
};

// This .ipp file is explicitly delay included in array.hpp
// #include "array_algo_1d.ipp"