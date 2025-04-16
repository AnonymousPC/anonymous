#pragma once
#include "concept.cpp" // This .ipp is included at the beinning instead of at the end.

/// Type traits

template < class type >                                    constexpr bool is_abstract                        = std::is_abstract                       <type>                 ::value;
template < class type >                                    constexpr bool is_aggregate                       = std::is_aggregate                      <type>                 ::value;
template < class type >                                    constexpr bool is_arithmetic                      = std::is_arithmetic                     <type>                 ::value;
template < class type >                                    constexpr bool is_array                           = std::is_array                          <type>                 ::value;
template < class type, class type2 >                       constexpr bool is_assignable                      = std::is_assignable                     <type,type2>           ::value;
template < class type >                                    constexpr bool is_bounded_array                   = std::is_bounded_array                  <type>                 ::value;
template < class type >                                    constexpr bool is_class                           = std::is_class                          <type>                 ::value;
template < class type >                                    constexpr bool is_compound                        = std::is_compound                       <type>                 ::value;
template < class type >                                    constexpr bool is_const                           = std::is_const                          <type>                 ::value;
template < class type >                                    constexpr bool is_empty                           = std::is_empty                          <type>                 ::value;
template < class type >                                    constexpr bool is_enum                            = std::is_enum                           <type>                 ::value;
template < class type >                                    constexpr bool is_final                           = std::is_final                          <type>                 ::value;
template < class type >                                    constexpr bool is_function                        = std::is_function                       <type>                 ::value;
template < class type >                                    constexpr bool is_fundamental                     = std::is_fundamental                    <type>                 ::value;
template < class type >                                    constexpr bool is_lvalue_reference                = std::is_lvalue_reference               <type>                 ::value;
template < class type >                                    constexpr bool is_member_object_pointer           = std::is_member_object_pointer          <type>                 ::value;
template < class type >                                    constexpr bool is_member_pointer                  = std::is_member_pointer                 <type>                 ::value;
template < class type >                                    constexpr bool is_member_function_pointer         = std::is_member_function_pointer        <type>                 ::value;
template < class type >                                    constexpr bool is_null_pointer                    = std::is_null_pointer                   <type>                 ::value;
template < class type >                                    constexpr bool is_object                          = std::is_object                         <type>                 ::value;
template < class type >                                    constexpr bool is_pointer                         = std::is_pointer                        <type>                 ::value;
template < class type >                                    constexpr bool is_polymorphic                     = std::is_polymorphic                    <type>                 ::value;
template < class type >                                    constexpr bool is_reference                       = std::is_reference                      <type>                 ::value;
template < class type >                                    constexpr bool is_rvalue_reference                = std::is_rvalue_reference               <type>                 ::value;
template < class type, class type2 >                       constexpr bool is_same                            = std::is_same                           <type,type2>           ::value;
template < class type >                                    constexpr bool is_scalar                          = std::is_scalar                         <type>                 ::value;
template < class type >                                    constexpr bool is_standard_layout                 = std::is_standard_layout                <type>                 ::value;
template < class type >                                    constexpr bool is_unbounded_array                 = std::is_unbounded_array                <type>                 ::value;
template < class type >                                    constexpr bool is_union                           = std::is_union                          <type>                 ::value;
template < class type >                                    constexpr bool is_void                            = std::is_void                           <type>                 ::value;
template < class type >                                    constexpr bool is_volatile                        = std::is_volatile                       <type>                 ::value;

template < class type >                                    using          add_const                          = std::add_const                         <type>                 ::type;
template < class type >                                    using          add_cv                             = std::add_cv                            <type>                 ::type;
template < class type >                                    using          add_lvalue_reference               = std::add_lvalue_reference              <type>                 ::type;
template < class type >                                    using          add_pointer                        = std::add_pointer                       <type>                 ::type;
template < class type >                                    using          add_rvalue_reference               = std::add_rvalue_reference              <type>                 ::type;
template < class type >                                    using          add_volatile                       = std::add_volatile                      <type>                 ::type;
template < class type, class... types >                    using          basic_common_reference             = std::basic_common_reference            <type,types...>        ::type;
template < class type, class... types >                    using          common_type                        = std::common_type                       <type,types...>        ::type;
template < class type, class... types >                    using          common_reference                   = std::common_reference                  <type,types...>        ::type;
template < bool condition, class type1, class type2 >      using          conditional                        = std::conditional                       <condition,type1,type2>::type;
template < class type >                                    using          decay                              = std::decay                             <type>                 ::type;
template < class type, class... types >                    using          invoke_result                      = std::invoke_result                     <type,types...>        ::type;
template < class type >                                    using          make_signed                        = std::make_signed                       <type>                 ::type;
template < class type >                                    using          make_unsigned                      = std::make_unsigned                     <type>                 ::type;
template < class type >                                    using          remove_all_extents                 = std::remove_all_extents                <type>                 ::type;
template < class type >                                    using          remove_const                       = std::remove_const                      <type>                 ::type;
template < class type >                                    using          remove_cv                          = std::remove_cv                         <type>                 ::type;
template < class type >                                    using          remove_cvref                       = std::remove_cvref                      <type>                 ::type;
template < class type >                                    using          remove_volatile                    = std::remove_volatile                   <type>                 ::type;
template < class type >                                    using          remove_extent                      = std::remove_extent                     <type>                 ::type;
template < class type >                                    using          remove_pointer                     = std::remove_pointer                    <type>                 ::type;
template < class type >                                    using          remove_reference                   = std::remove_reference                  <type>                 ::type;
template < class type >                                    using          type_identity                      = std::type_identity                     <type>                 ::type;

template < class type >                                    using          iter_value                         = std::iter_value_t                      <type>;
template < class type >                                    using          iter_reference                     = std::iter_reference_t                  <type>;
template < class type >                                    using          iter_const_reference               = std::iter_const_reference_t            <type>;
template < class type >                                    using          iter_rvalue_reference              = std::iter_rvalue_reference_t           <type>;
template < class type >                                    using          iter_common_reference              = std::iter_common_reference_t           <type>;
template < class type >                                    using          iter_difference                    = std::iter_difference_t                 <type>;
template < class type >                                    using          range_value                        = std::ranges::range_value_t             <type>;
template < class type >                                    using          range_reference                    = std::ranges::range_reference_t         <type>;
template < class type >                                    using          range_const_reference              = std::ranges::range_const_reference_t   <type>;
template < class type >                                    using          range_rvalue_reference             = std::ranges::range_rvalue_reference_t  <type>;
template < class type >                                    using          range_difference                   = std::ranges::range_difference_t        <type>;                       
template < class type >                                    using          range_iterator                     = std::ranges::iterator_t                <type>; 
template < class type >                                    using          range_const_iterator               = std::ranges::const_iterator_t          <type>;
template < class type >                                    using          range_sentinel                     = std::ranges::sentinel_t                <type>; 
template < class type >                                    using          range_const_sentinel               = std::ranges::const_sentinel_t          <type>;

template < class type >                                    constexpr int  tuple_size                         = std::tuple_size<type>::value;
template < int index, class type >                         using          tuple_element                      = std::tuple_element<(index>=0) ? std::size_t(index-1) : std::size_t(index+int(std::tuple_size<type>::value)),type>::type;

/// Concepts

template < class type >                                    concept        default_initializable              = std::default_initializable             <type>;
template < class type, class... types >                    concept        constructible_from                 = std::constructible_from                <type,types...>;
template < class type, class... types >                    concept        nothrow_constructible_from         = std::constructible_from                <type,types...>    and std::is_nothrow_constructible       <type,types...>::value;
template < class type >                                    concept        copyable                           = std::copyable                          <type>;
template < class type >                                    concept        nothrow_copyable                   = std::copyable                          <type>             and std::is_nothrow_copy_constructible  <type>::value and std::is_nothrow_copy_assignable  <type>::value;
template < class type >                                    concept        trivially_copyable                 = std::copyable                          <type>             and std::is_trivially_copy_constructible<type>::value and std::is_trivially_copy_assignable<type>::value;
template < class type >                                    concept        movable                            = std::movable                           <type>;
template < class type >                                    concept        nothrow_movable                    = std::movable                           <type>             and std::is_nothrow_move_constructible  <type>::value and std::is_nothrow_move_assignable  <type>::value;
template < class type >                                    concept        trivially_movable                  = std::movable                           <type>             and std::is_trivially_move_constructible<type>::value and std::is_trivially_move_assignable<type>::value;
template < class type >                                    concept        destructible                       = std::destructible                      <type>;
template < class type >                                    concept        nothrow_destructible               = std::destructible                      <type>             and std::is_nothrow_destructible        <type>::value;
template < class type >                                    concept        swappable                          = std::swappable                         <type>;
template < class type >                                    concept        nothrow_swappable                  = std::swappable                         <type>             and std::is_nothrow_swappable           <type>::value;
template < class type, class... types >                    concept        invocable                          = std::invocable                         <type,types...>;
template < class type, class result_type, class... types > concept        invocable_r                        = std::is_invocable_r                    <result_type,type,types...>::value;
template < class type, class type2 >                       concept        predicate                          = std::predicate                         <type,type2>;
template < class type, class type2, class type3 >          concept        relation                           = std::relation                          <type,type2,type3>;

template < class type1, class type2 >                      concept        same_as                            = std::same_as                           <type1,type2>;
template < class type1, class type2 >                      concept        base_of                            = std::is_base_of                        <type1,type2>::value;
template < class type1, class type2 >                      concept        derived_from                       = std::derived_from                      <type1,type2>;
template < class type1, class type2 >                      concept        convertible_to                     = std::convertible_to                    <type1,type2>;
template < class type1, class type2 >                      concept        nothrow_convertible_to             = std::convertible_to                    <type1,type2>      and std::is_nothrow_convertible   <type1,type2>::value;
template < class type1, class type2 >                      concept        assignable_from                    = std::assignable_from                   <type1,type2>;
template < class type1, class type2 >                      concept        nothrow_assignable_from            = std::assignable_from                   <type1,type2>      and noexcept(std::declval<type1>() = std::declval<type2>());
template < class type1, class type2 >                      concept        swappable_with                     = std::swappable_with                    <type1,type2>;
template < class type1, class type2 >                      concept        nothrow_swappable_with             = std::swappable_with                    <type1,type2>      and std::is_nothrow_swappable_with<type1,type2>::value;
template < class type1, class type2 >                      concept        common_with                        = std::common_with                       <type1,type2>;
template < class type1, class type2 >                      concept        common_reference_with              = std::common_reference_with             <type1,type2>;
template < class type1, class type2 >                      concept        layout_compatible_with             = std::is_layout_compatible              <type1,type2>::value;

template < class type >                                    concept        input_iterator                     = std::input_iterator                    <type>;
template < class type >                                    concept        output_iterator                    = std::input_or_output_iterator          <type>;
template < class type >                                    concept        forward_iterator                   = std::forward_iterator                  <type>;
template < class type >                                    concept        bidirectional_iterator             = std::bidirectional_iterator            <type>;
template < class type >                                    concept        random_access_iterator             = std::random_access_iterator            <type>;
template < class type >                                    concept        contiguous_iterator                = std::contiguous_iterator               <type>;
template < class type >                                    concept        input_range                        = std::ranges::input_range               <type>;
template < class type >                                    concept        output_range                       = output_iterator                        <range_iterator<type>>;
template < class type >                                    concept        forward_range                      = std::ranges::forward_range             <type>;
template < class type >                                    concept        bidirectional_range                = std::ranges::bidirectional_range       <type>;
template < class type >                                    concept        random_access_range                = std::ranges::random_access_range       <type>;
template < class type >                                    concept        contiguous_range                   = std::ranges::contiguous_range          <type>;            

/// Operator

template < class type = void >                             using          plus                               = std::plus<type>;
template < class type >                                    concept        plusable                           = requires { std::declval<type >() + std::declval<type >(); };
template < class type1, class type2 >                      concept        plusable_to                        = requires { std::declval<type1>() + std::declval<type2>(); std::declval<type2>() + std::declval<type1>(); };
template < class type1, class type2 >                      using          plus_result                        = decltype ( std::declval<type1>() + std::declval<type2>()  );

template < class type = void >                             using          minus                              = std::minus<type>;
template < class type >                                    concept        minusable                          = requires { std::declval<type >() - std::declval<type >(); };
template < class type1, class type2 >                      concept        minusable_to                       = requires { std::declval<type1>() - std::declval<type2>(); std::declval<type2>() - std::declval<type1>(); };
template < class type1, class type2 >                      using          minus_result                       = decltype ( std::declval<type1>() - std::declval<type2>()  );

template < class type = void >                             using          multiplies                         = std::multiplies<type>;
template < class type >                                    concept        multipliable                       = requires { std::declval<type >() * std::declval<type >(); };
template < class type1, class type2 >                      concept        multipliable_to                    = requires { std::declval<type1>() * std::declval<type2>(); std::declval<type2>() * std::declval<type1>(); };
template < class type1, class type2 >                      using          multiply_result                    = decltype ( std::declval<type1>() * std::declval<type2>()  );

template < class type = void >                             using          divides                            = std::divides<type>;
template < class type >                                    concept        dividable                          = requires { std::declval<type >() / std::declval<type >(); };
template < class type1, class type2 >                      concept        dividable_to                       = requires { std::declval<type1>() / std::declval<type2>(); std::declval<type2>() / std::declval<type1>(); };
template < class type1, class type2 >                      using          divide_result                      = decltype ( std::declval<type1>() / std::declval<type2>()  );

template < class type = void >                             using          modulus                            = std::modulus<type>;
template < class type >                                    concept        modulable                          = requires { std::declval<type >() % std::declval<type >(); };
template < class type1, class type2 >                      concept        modulable_to                       = requires { std::declval<type1>() % std::declval<type2>(); std::declval<type2>() % std::declval<type1>(); };
template < class type1, class type2 >                      using          modulus_result                     = decltype ( std::declval<type1>() % std::declval<type2>()  );

template < class type >                                    using          equal                              = std::equal_to<type>;        
template < class type >                                    concept        equalable                          = requires { std::declval<type >() == std::declval<type >(); };
template < class type1, class type2 >                      concept        equalable_to                       = requires { std::declval<type1>() == std::declval<type2>(); std::declval<type2>() == std::declval<type1>(); };

template < class type >                                    using          compare                            = std::compare_three_way;
template < class type >                                    concept        comparable                         = requires { std::declval<type >() <=> std::declval<type >(); };
template < class type1, class type2 >                      concept        comparable_to                      = requires { std::declval<type1>() <=> std::declval<type2>(); std::declval<type2>() <=> std::declval<type1>(); };
template < class type1, class type2 >                      using          compare_result                     = decltype ( std::declval<type1>() <=> std::declval<type2>()  );

template < class type >                                    concept        printable                          = requires ( type obj ) { std::cout << obj; };
template < class type >                                    concept        inputable                          = requires ( type obj ) { std::cin  >> obj; };

/// Is...type

template < class type >                                    concept        char_type                          = same_as<remove_cv<type>,char> or same_as<remove_cv<type>,wchar_t> or same_as<remove_cv<type>,char8_t> or same_as<remove_cv<type>,char16_t> or same_as<remove_cv<type>,char32_t> or requires { typename type::char_tag;         };
template < class type >                                    concept        int_type                           = ( std::signed_integral  <type> and ( not char_type<type> ) ) or requires { typename type::int_tag;          };
template < class type >                                    concept        unsigned_int_type                  = ( std::unsigned_integral<type> and ( not char_type<type> ) ) or requires { typename type::unsigned_int_tag; };
template < class type >                                    concept        float_type                         = std::floating_point<type>                                    or requires { typename type::float_tag;        };
template < class type >                                    concept        number_type                        = int_type<type> or float_type<type>                           or requires { typename type::number_tag;       };
template < class type >                                    concept        complex_type                       =                                                                 requires { typename type::complex_tag;      };



// Convertible since/until

template < class result_type, int index, class... types >  constexpr bool convertible_since                  = detail::convertible_since_helper<result_type,index,types...>::value;
template < class result_type, int index, class... types >  constexpr bool convertible_until                  = detail::convertible_until_helper<result_type,index,types...>::value;

/// Argument pack

template <            class... types >                     using          first_type_of                      = detail::first_type_of_helper<types...>::type;
template <            class... types >                     using          second_type_of                     = detail::second_type_of_helper<types...>::type;
template <            class... types >                     using          last_type_of                       = detail::last_type_of_helper<types...>::type;
template < int index, class... types >                     using          index_type_of                      = detail::index_type_of_helper<index,types...>::type;

                       constexpr decltype(auto) first_value_of  ( auto&&... args ) { return detail::first_value_of_helper       (std::forward<decltype(args)>(args)...); }
                       constexpr decltype(auto) second_value_of ( auto&&... args ) { return detail::second_value_of_helper      (std::forward<decltype(args)>(args)...); }
                       constexpr decltype(auto) last_value_of   ( auto&&... args ) { return detail::last_value_of_helper        (std::forward<decltype(args)>(args)...); }
template < int index > constexpr decltype(auto) index_value_of  ( auto&&... args ) { return detail::index_value_of_helper<index>(std::forward<decltype(args)>(args)...); }
