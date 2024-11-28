#pragma once

#define result_type invoke_result<decltype(op),iterate_type>

template < class array_type,
           class value_type,
           class iterate_type,
           int   dim >
    requires ( dim == 1 )
class array_algo<array_type,value_type,iterate_type,dim>
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
                                 constexpr       auto     operator [] ( unary_pred<value_type> auto );
                                 constexpr const auto     operator [] ( unary_pred<value_type> auto ) const;
                                 constexpr       auto     reshape     ( int_type auto... args )             requires ( sizeof...(args) >= 2 );
                                 constexpr const auto     reshape     ( int_type auto... args )       const requires ( sizeof...(args) >= 2 );
                                 constexpr       void     flatten     ( )                             const = delete;
        template < class type2 > constexpr const auto&    as_type     ( )                             const requires std::same_as<value_type,type2>;
        template < class type2 > constexpr const auto     as_type     ( )                             const requires ( not std::same_as<value_type,type2> ) and std::convertible_to<value_type,type2>;

    public: // Memory operation
        constexpr array_type& clear   ( )                                                                                                                                            requires ( not is_view );
        constexpr array_type& erase   ( int, int )                                                                                                                                   requires ( not is_view );
        constexpr array_type& insert  ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<value_type,0,1> auto, aux::array_type_dim_range<value_type,0,1> auto... ) requires ( not is_view );
        constexpr array_type& push    (                                          aux::array_type_dim_range<value_type,0,1> auto, aux::array_type_dim_range<value_type,0,1> auto... ) requires ( not is_view );
        constexpr array_type& pop     ( )                                                                                                                                            requires ( not is_view );
        constexpr array_type& pop     ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<int,0,1> auto... )                                                        requires ( not is_view );

    public: // Linear algorithm
        constexpr       int            adjacent_find       (                                        ) const requires equalable<value_type>;
        constexpr       int            adjacent_find       ( const binary_pred <iterate_type> auto  ) const;
        constexpr       array<int>     adjacent_where      (                                        ) const requires equalable<value_type>;
        constexpr       array<int>     adjacent_where      (       binary_pred <iterate_type> auto  ) const;
        constexpr       bool           all                 ( const equalable_to<iterate_type> auto& ) const;
        constexpr       bool           all                 (       unary_pred  <iterate_type> auto  ) const;
        constexpr       bool           contains            ( const equalable_to<iterate_type> auto& ) const;
        constexpr       bool           contains            (       unary_pred  <iterate_type> auto  ) const;
        constexpr       int            count               ( const equalable_to<iterate_type> auto& ) const;
        constexpr       int            count               (       unary_pred  <iterate_type> auto  ) const;
        constexpr       bool           exist               ( const equalable_to<iterate_type> auto& ) const;
        constexpr       bool           exist               (       unary_pred  <iterate_type> auto  ) const;
        constexpr       int            find                ( const equalable_to<iterate_type> auto& ) const;
        constexpr       int            find                (       unary_pred  <iterate_type> auto  ) const;
    //  constexpr       bool           is_partitioned      (                                        ) const;
        constexpr       bool           is_partitioned      (       unary_pred  <iterate_type> auto  ) const;
        constexpr       bool           is_sorted           (                                        ) const requires comparable<value_type>;
        constexpr       bool           is_sorted           (       binary_pred <iterate_type> auto  ) const;
        constexpr const iterate_type&  max                 (                                        ) const requires comparable<value_type>;
        constexpr const iterate_type&  max                 (       binary_pred <iterate_type> auto  ) const;
        constexpr const iterate_type&  min                 (                                        ) const requires comparable<value_type>;
        constexpr const iterate_type&  min                 (       binary_pred <iterate_type> auto  ) const;
        constexpr       array_type&    next_permutation    (                                        )       requires comparable<value_type>;
        constexpr       array_type&    next_permutation    (       binary_pred <iterate_type> auto  );
        constexpr       bool           none                ( const equalable_to<iterate_type> auto& ) const;
        constexpr       bool           none                (       unary_pred  <iterate_type> auto  ) const;
        constexpr       array_type&    partial_sort        ( int                                    )       requires comparable<value_type>;
        constexpr       array_type&    partial_sort        ( int,  binary_pred <iterate_type> auto  );
     // constexpr       array_type&    partition           (                                        );
        constexpr       array_type&    partition           (       unary_pred  <iterate_type> auto  );
        constexpr       array_type&    prev_permutation    (                                        )       requires comparable<value_type>;
        constexpr       array_type&    prev_permutation    (       binary_pred <iterate_type> auto  );
        constexpr       array_type&    remove              ( const equalable_to<iterate_type> auto& )       requires ( not is_view );
        constexpr       array_type&    remove              (       unary_pred  <iterate_type> auto  )       requires ( not is_view );
        constexpr       array_type&    reverse             (                                        );
        constexpr       int            right_adjacent_find (                                        ) const requires equalable<value_type>;
        constexpr       int            right_adjacent_find (       binary_pred <iterate_type> auto  ) const;
        constexpr       int            right_find          ( const equalable_to<iterate_type> auto& ) const;
        constexpr       int            right_find          (       unary_pred  <iterate_type> auto  ) const;
        constexpr       array_type&    rotate              (       int                              );
        constexpr       array_type&    stable_partition    ( const equalable_to<iterate_type> auto& )       requires comparable<value_type>;
        constexpr       array_type&    stable_partition    (       unary_pred  <iterate_type> auto  );
        constexpr       array_type&    stable_sort         (                                        )       requires comparable<value_type>;
        constexpr       array_type&    stable_sort         (       binary_pred <iterate_type> auto  );
        constexpr       array_type&    sort                (                                        )       requires comparable<value_type>;
        constexpr       array_type&    sort                (       binary_pred <iterate_type> auto  );
        constexpr       array_type&    unique              (                                        )       requires ( not is_view ) and equalable<value_type>;
        constexpr       array_type&    unique              (       binary_pred <iterate_type> auto  )       requires ( not is_view );
        constexpr       array<int>     where               ( const equalable_to<iterate_type> auto& ) const;
        constexpr       array<int>     where               (       unary_pred  <iterate_type> auto  ) const;

        constexpr       auto           average             (                                            ) const requires std::default_initializable<value_type>  and addable<value_type>  and dividable_to<value_type ,int>;
        constexpr       auto           average             (       std::invocable<iterate_type> auto op ) const requires std::default_initializable<result_type> and addable<result_type> and dividable_to<result_type,int>;
        constexpr       auto           sum                 (                                            ) const requires std::default_initializable<value_type>  and addable<value_type>;
        constexpr       auto           sum                 (       std::invocable<iterate_type> auto op ) const requires std::default_initializable<result_type> and addable<result_type>;
        constexpr       auto           product             (                                            ) const requires std::convertible_to<int,value_type>     and multipliable<value_type>;
        constexpr       auto           product             (       std::invocable<iterate_type> auto op ) const requires std::convertible_to<int,result_type>    and multipliable<result_type>;

        constexpr       array_type&    each                (       std::invocable     <iterate_type&> auto  );
        constexpr const array_type&    each                (       std::invocable     <iterate_type>  auto  ) const;
        constexpr       array_type&    fill                ( const std::convertible_to<iterate_type>  auto& );
        constexpr       array_type&    generate            (       function_type      <iterate_type()>auto  );
        constexpr       array_type&    transform           (       unary_op           <iterate_type>  auto  );
        constexpr       array_type&    replace             ( const equalable_to       <iterate_type>  auto&, const std::convertible_to<iterate_type> auto& );
        constexpr       array_type&    replace             (       unary_pred         <iterate_type>  auto,  const std::convertible_to<iterate_type> auto& );

        // Implemented in "root/math/random/container/array.cpp"
        constexpr       array_type&    sample              ( int )                                             requires ( not is_view ) and std::copyable<value_type>;
        constexpr       array_type&    shuffle             ( );

    private: // Auxiliary
        constexpr array_type& insert_aux ( int, int ); // Inputs pos and step. Notice that pos must be positive;
};

#undef result_type // Redefine it in .hpp
#include "array_algo_1d.ipp"