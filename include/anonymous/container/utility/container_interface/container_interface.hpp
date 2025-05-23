template < class container, class type, class device >
class container_interface
{
    private: // Typedef
        using value_type      = device::template value_type     <type>;
        using reference       = device::template reference      <type>;
        using const_reference = device::template const_reference<type>;
        using pointer         = device::template pointer        <type>;
        using const_pointer   = device::template const_pointer  <type>;

    private: // Abbreviation
        constexpr auto begin ( );
        constexpr auto begin ( ) const;
        constexpr auto end   ( );
        constexpr auto end   ( ) const;
        constexpr auto size  ( ) const;
        constexpr auto empty ( ) const;

    public: // Member
        constexpr       int             adjacent_find       (                                         ) const requires random_access_range<container> and equalable<type>;
        constexpr       int             adjacent_find       (       relation_between<type,type> auto  ) const requires random_access_range<container>;
        constexpr       array<int>      adjacent_where      (                                         ) const requires random_access_range<container> and equalable<type>;
        constexpr       array<int>      adjacent_where      (       relation_between<type,type> auto  ) const requires random_access_range<container>;
        constexpr       bool            all                 ( const equalable_to    <type>      auto& ) const requires forward_range      <container>;
        constexpr       bool            all                 (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       bool            contains            ( const equalable_to    <type>      auto& ) const requires forward_range      <container>;
        constexpr       bool            contains            (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       int             count               ( const equalable_to    <type>      auto& ) const requires forward_range      <container>;
        constexpr       int             count               (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       bool            exist               ( const equalable_to    <type>      auto& ) const requires forward_range      <container>;
        constexpr       bool            exist               (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       int             find                ( const equalable_to    <type>      auto& ) const requires random_access_range<container>;
        constexpr       int             find                (       predicate_for   <type>      auto  ) const requires random_access_range<container>;
        constexpr       bool            is_partitioned      (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       bool            is_sorted           (                                         ) const requires forward_range      <container> and comparable<type>;
        constexpr       bool            is_sorted           (       relation_between<type,type> auto  ) const requires forward_range      <container>;
        constexpr       reference       max                 (                                         )       requires forward_range      <container> and comparable<type>;
        constexpr       const_reference max                 (       relation_between<type,type> auto  ) const requires forward_range      <container>;
        constexpr       reference       min                 (                                         )       requires forward_range      <container> and comparable<type>;
        constexpr       const_reference min                 (       relation_between<type,type> auto  ) const requires forward_range      <container>;
        constexpr       container&      next_permutation    (                                         )       requires bidirectional_range<container> and comparable<type>;
        constexpr       container&      next_permutation    (       relation_between<type,type> auto  )       requires bidirectional_range<container>;
        constexpr       bool            none                ( const equalable_to    <type>      auto& ) const requires forward_range      <container>;
        constexpr       bool            none                (       predicate_for   <type>      auto  ) const requires forward_range      <container>;
        constexpr       container&      partial_sort        ( int                                     )       requires random_access_range<container> and comparable<type>;
        constexpr       container&      partial_sort        ( int,  relation_between<type,type> auto  )       requires random_access_range<container>;
        constexpr       container&      partition           (       predicate_for   <type>      auto  )       requires forward_range      <container>;
        constexpr       container&      prev_permutation    (                                         )       requires bidirectional_range<container> and comparable<type>;
        constexpr       container&      prev_permutation    (       relation_between<type,type> auto  )       requires bidirectional_range<container>;
        constexpr       container&      remove              ( const equalable_to    <type>      auto& )       requires forward_range      <container>;
        constexpr       container&      remove              (       predicate_for   <type>      auto  )       requires forward_range      <container>;
        constexpr       container&      reverse             (                                         )       requires bidirectional_range<container>;
        constexpr       int             right_adjacent_find (                                         ) const requires random_access_range<container> and equalable<type>;
        constexpr       int             right_adjacent_find (       relation_between<type,type> auto  ) const requires random_access_range<container>;
        constexpr       int             right_find          ( const equalable_to    <type>      auto& ) const requires random_access_range<container>;
        constexpr       int             right_find          (       predicate_for   <type>      auto  ) const requires random_access_range<container>;
        constexpr       container&      rotate              ( int                                     )       requires forward_range      <container>;
        constexpr       container&      stable_partition    (       predicate_for   <type>      auto  )       requires bidirectional_range<container>;
        constexpr       container&      stable_sort         (                                         )       requires random_access_range<container> and comparable<type>;
        constexpr       container&      stable_sort         (       relation_between<type,type> auto  )       requires random_access_range<container>;      
        constexpr       container&      sort                (                                         )       requires random_access_range<container> and comparable<type>;
        constexpr       container&      sort                (       relation_between<type,type> auto  )       requires random_access_range<container>;
        constexpr       container&      unique              (                                         )       requires forward_range      <container> and equalable<type>;
        constexpr       container&      unique              (       relation_between<type,type> auto  )       requires forward_range      <container>;
        constexpr       array<int>      where               ( const equalable_to    <type>      auto& ) const requires random_access_range<container>;
        constexpr       array<int>      where               (       predicate_for   <type>      auto  ) const requires random_access_range<container>;

        constexpr       type            average             (                                         ) const requires input_range        <container> and default_initializable<type> and plusable    <type> and dividable_to<type,int>;
        constexpr       type            sum                 (                                         ) const requires input_range        <container> and default_initializable<type> and plusable    <type>;
        constexpr       type            product             (                                         ) const requires input_range        <container> and convertible_to   <int,type> and multipliable<type>;

        constexpr       container&      fill                ( const convertible_to  <type>      auto& )       requires forward_range      <container>;
        constexpr       container&      generate            (       invocable_r     <type>      auto  )       requires forward_range      <container>;
        constexpr       container&      transform           (       invocable_r     <type,type> auto  )       requires forward_range      <container>;
        constexpr       container&      for_each            (       invocable       <reference> auto  )       requires forward_range      <container>;
        constexpr const container&      for_each            (       invocable       <value_type>auto  ) const requires forward_range      <container>;

    public: // Member
        constexpr       container&      replace             ( const equalable_to    <type>      auto&,  const convertible_to<type> auto& ) requires forward_range<container>;
        constexpr       container&      replace             (       predicate_for   <type>      auto,   const convertible_to<type> auto& ) requires forward_range<container>;
};