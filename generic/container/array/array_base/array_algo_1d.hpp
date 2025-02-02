#pragma once

#define result_type invoke_result<decltype(op),type>

template < class array_type,
           class type,
           class type,
           int   dim >
    requires ( dim == 1 )
class array_algo<array_type,type,type,dim>
{
    private: // Traits
        constexpr static const bool is_view = not requires { &array_type::resize; } and not requires { &array_type::template resize<int>; };

    private: // Abbreviation
        constexpr void           row         ( ) = delete;
        constexpr int            size        ( )     const;
        constexpr bool           empty       ( )     const;
        constexpr decltype(auto) begin       ( );
        constexpr decltype(auto) begin       ( )     const;
        constexpr decltype(auto) end         ( );
        constexpr decltype(auto) end         ( )     const;

    public: // N-dimension
        constexpr static int        dimension     ( );
        constexpr        array<int> shape         ( ) const;
        constexpr        auto       static_shape  ( ) const;
        constexpr        auto       inplace_shape ( ) const;
        constexpr        auto       tuple_shape   ( ) const;

    public: // Views
                                 constexpr decltype(auto) operator [] ( int );
                                 constexpr decltype(auto) operator [] ( int ) const;
                                 constexpr       auto     operator [] ( int, int );
                                 constexpr const auto     operator [] ( int, int )                    const;
                                 constexpr       auto     operator [] ( int, int, int );
                                 constexpr const auto     operator [] ( int, int, int )               const;
                                 constexpr       auto     operator [] ( unary_pred<type> auto );
                                 constexpr const auto     operator [] ( unary_pred<type> auto ) const;
                                 constexpr       auto     reshape     ( int_type auto... args )             requires ( sizeof...(args) >= 2 );
                                 constexpr const auto     reshape     ( int_type auto... args )       const requires ( sizeof...(args) >= 2 );
                                 constexpr       void     flatten     ( )                             const = delete;
        template < class type2 > constexpr const auto&    as_type     ( )                             const requires std::same_as<type,type2>;
        template < class type2 > constexpr const auto     as_type     ( )                             const requires ( not std::same_as<type,type2> ) and std::convertible_to<type,type2>;

    public: // Memory operation
        constexpr array_type& clear   ( )                                                                                                                                            requires ( not is_view );
        constexpr array_type& erase   ( int, int )                                                                                                                                   requires ( not is_view );
        constexpr array_type& insert  ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<type,0,1> auto, aux::array_type_dim_range<type,0,1> auto... ) requires ( not is_view );
        constexpr array_type& push    (                                          aux::array_type_dim_range<type,0,1> auto, aux::array_type_dim_range<type,0,1> auto... ) requires ( not is_view );
        constexpr array_type& pop     ( )                                                                                                                                            requires ( not is_view );
        constexpr array_type& pop     ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<int,0,1> auto... )                                                        requires ( not is_view );

    public: // Linear algorithm
        constexpr       int            adjacent_find       (                                        ) const requires equalable<type>;
        constexpr       int            adjacent_find       ( const relation    <type,type> auto  ) const;
        constexpr       array<int>     adjacent_where      (                                        ) const requires equalable<type>;
        constexpr       array<int>     adjacent_where      (       relation    <type,type> auto  ) const;
        constexpr       bool           all                 ( const equalable_to<type> auto& ) const;
        constexpr       bool           all                 (       predicate   <type>auto  ) const;
        constexpr       bool           contains            ( const equalable_to<type> auto& ) const;
        constexpr       bool           contains            (       predicate   <type>auto  ) const;
        constexpr       int            count               ( const equalable_to<type> auto& ) const;
        constexpr       int            count               (       predicate   <type>auto  ) const;
        constexpr       bool           exist               ( const equalable_to<type> auto& ) const;
        constexpr       bool           exist               (       predicate   <type>auto  ) const;
        constexpr       int            find                ( const equalable_to<type> auto& ) const;
        constexpr       int            find                (       predicate   <type>auto  ) const;
    //  constexpr       bool           is_partitioned      (                                        ) const;
        constexpr       bool           is_partitioned      (       predicate   <type>auto  ) const;
        constexpr       bool           is_sorted           (                                        ) const requires comparable<type>;
        constexpr       bool           is_sorted           (       relation    <type,type> auto  ) const;
        constexpr const type&  max                 (                                        ) const requires comparable<type>;
        constexpr const type&  max                 (       relation    <type,type> auto  ) const;
        constexpr const type&  min                 (                                        ) const requires comparable<type>;
        constexpr const type&  min                 (       relation    <type,type> auto  ) const;
        constexpr       array_type&    next_permutation    (                                        )       requires comparable<type>;
        constexpr       array_type&    next_permutation    (       relation    <type,type> auto  );
        constexpr       bool           none                ( const equalable_to<type> auto& ) const;
        constexpr       bool           none                (       predicate   <type>auto  ) const;
        constexpr       array_type&    partial_sort        ( int                                    )       requires comparable<type>;
        constexpr       array_type&    partial_sort        ( int,  relation    <type,type> auto  );
     // constexpr       array_type&    partition           (                                        );
        constexpr       array_type&    partition           (       predicate   <type>auto  );
        constexpr       array_type&    prev_permutation    (                                        )       requires comparable<type>;
        constexpr       array_type&    prev_permutation    (       relation    <type,type> auto  );
        constexpr       array_type&    remove              ( const equalable_to<type> auto& )       requires ( not is_view );
        constexpr       array_type&    remove              (       predicate   <type>auto  )       requires ( not is_view );
        constexpr       array_type&    reverse             (                                        );
        constexpr       int            right_adjacent_find (                                        ) const requires equalable<type>;
        constexpr       int            right_adjacent_find (       relation    <type,type> auto  ) const;
        constexpr       int            right_find          ( const equalable_to<type> auto& ) const;
        constexpr       int            right_find          (       predicate   <type>auto  ) const;
        constexpr       array_type&    rotate              (       int                              );
        constexpr       array_type&    stable_partition    ( const equalable_to<type> auto& )       requires comparable<type>;
        constexpr       array_type&    stable_partition    (       predicate   <type>auto  );
        constexpr       array_type&    stable_sort         (                                        )       requires comparable<type>;
        constexpr       array_type&    stable_sort         (       relation    <type,type> auto  );
        constexpr       array_type&    sort                (                                        )       requires comparable<type>;
        constexpr       array_type&    sort                (       relation    <type,type> auto  );
        constexpr       array_type&    unique              (                                        )       requires ( not is_view ) and equalable<type>;
        constexpr       array_type&    unique              (       relation    <type,type> auto  )       requires ( not is_view );
        constexpr       array<int>     where               ( const equalable_to<type> auto& ) const;
        constexpr       array<int>     where               (       predicate   <type>auto  ) const;

        constexpr       auto           average             (                                            ) const requires std::default_initializable<type>  and addable<type>  and dividable_to<type ,int>;
        constexpr       auto           average             (       std::invocable<type> auto op ) const requires std::default_initializable<result_type> and addable<result_type> and dividable_to<result_type,int>;
        constexpr       auto           sum                 (                                            ) const requires std::default_initializable<type>  and addable<type>;
        constexpr       auto           sum                 (       std::invocable<type> auto op ) const requires std::default_initializable<result_type> and addable<result_type>;
        constexpr       auto           product             (                                            ) const requires std::convertible_to<int,type>     and multipliable<type>;
        constexpr       auto           product             (       std::invocable<type> auto op ) const requires std::convertible_to<int,result_type>    and multipliable<result_type>;

        constexpr       array_type&    each                (       std::invocable     <type&> auto  );
        constexpr const array_type&    each                (       std::invocable     <type>  auto  ) const;
        constexpr       array_type&    fill                ( const std::convertible_to<type>  auto& );
        constexpr       array_type&    generate            (       function_type      <type()>auto  );
        constexpr       array_type&    transform           (       unary_op           <type>  auto  );
        constexpr       array_type&    replace             ( const equalable_to       <type>  auto&, const std::convertible_to<type> auto& );
        constexpr       array_type&    replace             (       unary_pred         <type>  auto,  const std::convertible_to<type> auto& );

        // Implemented in "root/math/random/container/array.cpp"
        constexpr       array_type&    sample              ( int )                                             requires ( not is_view ) and std::copyable<type>;
        constexpr       array_type&    shuffle             ( );

    private: // Auxiliary
        constexpr array_type& insert_aux ( int, int ); // Inputs pos and step. Notice that pos must be positive;
};

#undef result_type // Redefine it in .hpp
#include "array_algo_1d.ipp"