#pragma once

#define template_int_axis template < int axis = 1 > requires ( ( axis >= 1 and axis <= dim ) or ( axis >= -dim and axis <= -1 ) )
#define result_type       invoke_result<decltype(op),iterate_type>

template < class array_type,
           class value_type,
           class iterate_type,
           int   dim >
    requires ( dim >= 2 )
class array_algo<array_type,value_type,iterate_type,dim>
{
    private: // Traits
        constexpr static const bool is_view = not requires { &array_type::resize; } and not requires { &array_type::template resize<1>; };

    private: // Abbreviation
        constexpr int            row   ( ) const;
        constexpr int            size  ( ) const;
        constexpr bool           empty ( ) const;
        constexpr decltype(auto) begin ( );
        constexpr decltype(auto) begin ( ) const;
        constexpr decltype(auto) end   ( );
        constexpr decltype(auto) end   ( ) const;

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
                                 constexpr       auto     operator [] ( pair<int>, pair<int> )              requires ( dimension() == 2 );
                                 constexpr const auto     operator [] ( pair<int>, pair<int> )        const requires ( dimension() == 2 );
                                 constexpr       auto     operator [] ( unary_pred<value_type> auto );
                                 constexpr const auto     operator [] ( unary_pred<value_type> auto ) const;
                                 constexpr       auto     reshape     ( int_type auto... args )             requires ( sizeof...(args) >= 1 );
                                 constexpr const auto     reshape     ( int_type auto... args )       const requires ( sizeof...(args) >= 1 );
                                 constexpr       auto     flatten     ( );
                                 constexpr const auto     flatten     ( )                             const;
        template < class type2 > constexpr const auto&    as_type     ( )                             const requires std::same_as<value_type,type2>;
        template < class type2 > constexpr const auto     as_type     ( )                             const requires ( not std::same_as<value_type,type2> ) but std::convertible_to<value_type,type2>;

    protected: // Views (axis)
        template_int_axis constexpr decltype(auto) view_by_axis ( )       requires ( axis == 1 or  axis == -dimension() );
        template_int_axis constexpr decltype(auto) view_by_axis ( ) const requires ( axis == 1 or  axis == -dimension() );
        template_int_axis constexpr       auto     view_by_axis ( )       requires ( axis != 1 and axis != -dimension() );
        template_int_axis constexpr const auto     view_by_axis ( ) const requires ( axis != 1 and axis != -dimension() );

    public: // Memory Operation
        template_int_axis constexpr array_type& clear  ( )                                                                                                                                                        requires ( not is_view );
        template_int_axis constexpr array_type& erase  ( int, int )                                                                                                                                               requires ( not is_view );
        template_int_axis constexpr array_type& insert ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<value_type,dim-1,dim> auto, aux::array_type_dim_range<value_type,dim-1,dim> auto... ) requires ( not is_view );
        template_int_axis constexpr array_type& push   (                                          aux::array_type_dim_range<value_type,dim-1,dim> auto, aux::array_type_dim_range<value_type,dim-1,dim> auto... ) requires ( not is_view );
        template_int_axis constexpr array_type& pop    ( )                                                                                                                                                        requires ( not is_view );
        template_int_axis constexpr array_type& pop    ( aux::array_type_dim_range<int,0,1> auto, aux::array_type_dim_range<int,0,1> auto... )                                                                    requires ( not is_view );

    public: // Linear Algorithm
        template_int_axis constexpr       int            adjacent_find       (                                        ) const requires equalable<value_type>;
        template_int_axis constexpr       int            adjacent_find       ( const binary_pred <iterate_type> auto  ) const;
        template_int_axis constexpr       array<int>     adjacent_where      (                                        ) const requires equalable<value_type>;
        template_int_axis constexpr       array<int>     adjacent_where      (       binary_pred <iterate_type> auto  ) const;
        template_int_axis constexpr       bool           all                 ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       bool           all                 (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       bool           contains            ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       bool           contains            (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       int            count               ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       int            count               (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       bool           exist               ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       bool           exist               (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       int            find                ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       int            find                (       unary_pred  <iterate_type> auto  ) const;
     // template_int_axis constexpr       bool           is_partitioned      (                                        ) const;
        template_int_axis constexpr       bool           is_partitioned      (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       bool           is_sorted           (                                        ) const requires comparable<value_type>;
        template_int_axis constexpr       bool           is_sorted           (       binary_pred <iterate_type> auto  ) const;
        template_int_axis constexpr       decltype(auto) max                 (                                        ) const requires comparable<value_type>; // If axis == 1 return const auto&; otherwise return auto&&.
        template_int_axis constexpr       decltype(auto) max                 (       binary_pred <iterate_type> auto  ) const;                                 // If axis == 1 return const auto&; otherwise return auto&&.
        template_int_axis constexpr       decltype(auto) min                 (                                        ) const requires comparable<value_type>; // If axis == 1 return const auto&; otherwise return auto&&.
        template_int_axis constexpr       decltype(auto) min                 (       binary_pred <iterate_type> auto  ) const;                                 // If axis == 1 return const auto&; otherwise return auto&&.
        template_int_axis constexpr       array_type&    next_permutation    (                                        )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    next_permutation    (       binary_pred <iterate_type> auto  );
        template_int_axis constexpr       bool           none                ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       bool           none                (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       array_type&    partial_sort        ( int                                    )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    partial_sort        ( int,  binary_pred <iterate_type> auto  );
     // template_int_axis constexpr       array_type&    partition           (                                        );
        template_int_axis constexpr       array_type&    partition           (       unary_pred  <iterate_type> auto  );
        template_int_axis constexpr       array_type&    prev_permutation    (                                        )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    prev_permutation    (       binary_pred <iterate_type> auto  );
        template_int_axis constexpr       array_type&    remove              ( const equalable_to<iterate_type> auto& )       requires ( not is_view );
        template_int_axis constexpr       array_type&    remove              (       unary_pred  <iterate_type> auto  )       requires ( not is_view );
        template_int_axis constexpr       array_type&    reverse             (                                        );
        template_int_axis constexpr       int            right_adjacent_find (                                        ) const requires equalable<value_type>;
        template_int_axis constexpr       int            right_adjacent_find (       binary_pred <iterate_type> auto  ) const;
        template_int_axis constexpr       int            right_find          ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       int            right_find          (       unary_pred  <iterate_type> auto  ) const;
        template_int_axis constexpr       array_type&    rotate              (       int                              );
        template_int_axis constexpr       array_type&    stable_partition    ( const equalable_to<iterate_type> auto& )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    stable_partition    (       unary_pred  <iterate_type> auto  );
        template_int_axis constexpr       array_type&    stable_sort         (                                        )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    stable_sort         (       binary_pred <iterate_type> auto  );
        template_int_axis constexpr       array_type&    sort                (                                        )       requires comparable<value_type>;
        template_int_axis constexpr       array_type&    sort                (       binary_pred <iterate_type> auto  );
        template_int_axis constexpr       array_type&    unique              (                                        )       requires ( not is_view ) and equalable<value_type>;
        template_int_axis constexpr       array_type&    unique              (       binary_pred <iterate_type> auto  )       requires ( not is_view );
        template_int_axis constexpr       array<int>     where               ( const equalable_to<iterate_type> auto& ) const;
        template_int_axis constexpr       array<int>     where               (       unary_pred  <iterate_type> auto  ) const;

        template_int_axis constexpr       auto           average             (                                            ) const requires std::default_initializable<value_type>  and addable<value_type>  and dividable_to<value_type, int>;
        template_int_axis constexpr       auto           average             (       std::invocable<iterate_type> auto op ) const requires std::default_initializable<result_type> and addable<result_type> and dividable_to<result_type,int>;
        template_int_axis constexpr       auto           sum                 (                                            ) const requires std::default_initializable<value_type>  and addable<value_type>;
        template_int_axis constexpr       auto           sum                 (       std::invocable<iterate_type> auto op ) const requires std::default_initializable<result_type> and addable<result_type>;
        template_int_axis constexpr       auto           product             (                                            ) const = delete;
        template_int_axis constexpr       auto           product             (       std::invocable<iterate_type> auto op ) const requires std::convertible_to<int,result_type>    and multipliable<result_type>;

        template_int_axis constexpr       array_type&    each                (       std::invocable     <iterate_type&> auto  );
        template_int_axis constexpr const array_type&    each                (       std::invocable     <iterate_type>  auto  ) const;
        template_int_axis constexpr       array_type&    fill                ( const std::convertible_to<iterate_type>  auto& );
        template_int_axis constexpr       array_type&    generate            (       function_type      <iterate_type()>auto  );
        template_int_axis constexpr       array_type&    transform           (       unary_op           <iterate_type>  auto  );
        template_int_axis constexpr       array_type&    replace             ( const equalable_to       <iterate_type>  auto&, const std::convertible_to<iterate_type> auto& );
        template_int_axis constexpr       array_type&    replace             (       unary_pred         <iterate_type>  auto,  const std::convertible_to<iterate_type> auto& );

        // Implemented in "root/math/random/container/array.cpp"
        template_int_axis constexpr       array_type&    sample              ( int )                                             requires ( not is_view ) and std::copyable<value_type>;
        template_int_axis constexpr       array_type&    shuffle             ( );

    private: // Auxiliary
        constexpr static void tuple_shape_aux ( auto&, const auto& );
};


#undef template_int_axis // Redefine it in .hpp
#undef result_type       // Redefine it in .hpp
#include "array_algo_nd.ipp"