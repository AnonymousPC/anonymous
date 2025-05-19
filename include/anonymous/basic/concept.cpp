namespace detail
{ 
    template < class type > 
    constexpr auto get_iterator_concept_tag ( )
    {
        if constexpr ( std::contiguous_iterator<type> )
            return std::contiguous_iterator_tag();
        else if constexpr ( std::random_access_iterator<type> )
            return std::random_access_iterator_tag();
        else if constexpr ( std::bidirectional_iterator<type> )
            return std::bidirectional_iterator_tag();
        else if constexpr ( std::input_iterator<type> )
            return std::input_iterator_tag();
        else
            static_assert(false, "no iterator_concept");
    }

    template < class type >
    using get_iterator_concept = decltype(get_iterator_concept_tag<type>());

    template < class type > 
    constexpr auto get_range_concept_tag ( )
    {
        if constexpr ( std::ranges::contiguous_range<type> )
            return std::contiguous_iterator_tag();
        else if constexpr ( std::ranges::random_access_range<type> )
            return std::random_access_iterator_tag();
        else if constexpr ( std::ranges::bidirectional_range<type> )
            return std::bidirectional_iterator_tag();
        else if constexpr ( std::ranges::input_range<type> )
            return std::input_iterator_tag();
        else
            static_assert(false, "no range_concept");
    }

    template < class type >
    using get_range_concept = decltype(get_range_concept_tag<type>());
    
} // namespace detail


/// Type traits

template < class type >                                    constexpr bool is_abstract                        = std::is_abstract                       <type>                 ::value;
template < class type >                                    constexpr bool is_aggregate                       = std::is_aggregate                      <type>                 ::value;
template < class type >                                    constexpr bool is_array                           = std::is_array                          <type>                 ::value;
template < class type, class type2 >                       constexpr bool is_assignable                      = std::is_assignable                     <type,type2>           ::value;
template < class type >                                    constexpr bool is_bounded_array                   = std::is_bounded_array                  <type>                 ::value;
template < class type >                                    constexpr bool is_class                           = std::is_class                          <type>                 ::value;
template < class type >                                    constexpr bool is_const                           = std::is_const                          <type>                 ::value;
template < class type >                                    constexpr bool is_empty                           = std::is_empty                          <type>                 ::value;
template < class type >                                    constexpr bool is_enum                            = std::is_enum                           <type>                 ::value;
template < class type >                                    constexpr bool is_final                           = std::is_final                          <type>                 ::value;
template < class type >                                    constexpr bool is_function                        = std::is_function                       <type>                 ::value;
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

template < class type >                                    using          iterator_concept                   = detail::get_iterator_concept           <type>;
template < class type >                                    using          iterator_value_type                = std::iter_value_t                      <type>;
template < class type >                                    using          iterator_reference                 = std::iter_reference_t                  <type>;
template < class type >                                    using          iterator_pointer                   = std::iterator_traits                   <type>::pointer;
template < class type >                                    using          iterator_difference_type           = std::iter_difference_t                 <type>;
template < class type >                                    using          range_concept                      = detail::get_range_concept              <type>;
template < class type >                                    using          range_value_type                   = std::ranges::range_value_t             <type>;
template < class type >                                    using          range_reference                    = std::ranges::range_reference_t         <type>;
template < class type >                                    using          range_difference_type              = std::ranges::range_difference_t        <type>;                       
template < class type >                                    using          range_iterator                     = std::ranges::iterator_t                <type>; 
template < class type >                                    using          range_const_iterator               = std::ranges::const_iterator_t          <type>;
template < class type >                                    using          range_sentinel                     = std::ranges::sentinel_t                <type>; 
template < class type >                                    using          range_const_sentinel               = std::ranges::const_sentinel_t          <type>;

template < class type >                                    constexpr int  tuple_size                         = std::tuple_size<type>::value;
template < int index, class type >                         using          tuple_element                      = std::tuple_element<(index>=0) ? std::size_t(index-1) : std::size_t(index+int(std::tuple_size<type>::value)),type>::type;



/// Concepts

template < class type >                                    concept        default_initializable              = std::is_default_constructible          <type>::value; // std::default_initializable checks operator new, which does not accept cv-qualified ones.
template < class type >                                    concept        nothrow_default_initializable      = std::is_nothrow_default_constructible  <type>::value;
template < class type >                                    concept        trivially_default_initializable    = std::is_trivially_default_constructible<type>::value;
template < class type, class... types >                    concept        constructible_from                 = std::constructible_from                <type,types...>;
template < class type, class... types >                    concept        nothrow_constructible_from         = std::is_nothrow_constructible          <type,types...>::value;
template < class type >                                    concept        copyable                           = std::copyable                          <type>;
template < class type >                                    concept        nothrow_copyable                   = std::is_nothrow_copy_constructible     <type>::value and std::is_nothrow_copy_assignable  <type>::value;
template < class type >                                    concept        trivially_copyable                 = std::is_trivially_copy_constructible   <type>::value and std::is_trivially_copy_assignable<type>::value;
template < class type >                                    concept        movable                            = std::movable                           <type>;
template < class type >                                    concept        nothrow_movable                    = std::is_nothrow_move_constructible     <type>::value and std::is_nothrow_move_assignable  <type>::value;
template < class type >                                    concept        trivially_movable                  = std::is_trivially_move_constructible   <type>::value and std::is_trivially_move_assignable<type>::value;
template < class type >                                    concept        destructible                       = std::destructible                      <type>;
template < class type >                                    concept        nothrow_destructible               = std::is_nothrow_destructible           <type>::value;
template < class type >                                    concept        trivially_destructible             = std::is_trivially_destructible         <type>::value;
template < class type >                                    concept        swappable                          = std::swappable                         <type>;
template < class type >                                    concept        nothrow_swappable                  = std::is_nothrow_swappable              <type>::value;
template < class type, class... types >                    concept        invocable                          = std::invocable                         <type,types...>;
template < class type, class result_type, class... types > concept        invocable_r                        = std::is_invocable_r                    <result_type,type,types...>::value;
template < class type, class type2 >                       concept        predicate_for                      = std::predicate                         <type,type2>;
template < class type, class type2, class type3 >          concept        relation_between                   = std::relation                          <type,type2,type3>;

template < class type1, class type2 >                      concept        same_as                            = std::same_as                           <type1,type2>;
template < class type1, class type2 >                      concept        base_of                            = std::derived_from                      <type2,type1>        and ( not std::same_as<type1,type2> ); // std::is_base_of allows private/protected extends, while std::derived_from does not.
template < class type1, class type2 >                      concept        derived_from                       = std::derived_from                      <type1,type2>        and ( not std::same_as<type1,type2> ); // std::derived_from<type,type> (where type is class or union) is true.
template < class type1, class type2 >                      concept        constructible_to                   = std::constructible_from                <type2,type1>;
template < class type1, class type2 >                      concept        nothrow_constructible_to           = std::is_nothrow_constructible          <type2,type1>::value;
template < class type1, class type2 >                      concept        convertible_to                     = std::convertible_to                    <type1,type2>        and constructible_to        <type1,type2>; // Make convertible >= constructible.
template < class type1, class type2 >                      concept        nothrow_convertible_to             = std::is_nothrow_convertible            <type1,type2>::value and nothrow_constructible_to<type1,type2>; // Make convertible >= constructible.
template < class type1, class type2 >                      concept        assignable_from                    = std::assignable_from                   <type1,type2>;
template < class type1, class type2 >                      concept        nothrow_assignable_from            = std::is_nothrow_assignable             <type1,type2>::value;
template < class type1, class type2 >                      concept        swappable_with                     = std::swappable_with                    <type1,type2>;
template < class type1, class type2 >                      concept        nothrow_swappable_with             = std::is_nothrow_swappable_with         <type1,type2>::value;
template < class type1, class type2 >                      concept        common_with                        = std::common_with                       <type1,type2>;
template < class type1, class type2 >                      concept        common_reference_with              = std::common_reference_with             <type1,type2>;
template < class type1, class type2 >                      concept        layout_compatible_with             = std::is_layout_compatible              <type1,type2>::value;        

template < class type >                                    concept        input_iterator                     = std::input_iterator                    <type>;
template < class type >                                    concept        forward_iterator                   = std::forward_iterator                  <type>;
template < class type >                                    concept        bidirectional_iterator             = std::bidirectional_iterator            <type>;
template < class type >                                    concept        random_access_iterator             = std::random_access_iterator            <type>;
template < class type >                                    concept        contiguous_iterator                = std::contiguous_iterator               <type>;
template < class type >                                    concept        input_range                        = std::ranges::input_range               <type>;
template < class type >                                    concept        forward_range                      = std::ranges::forward_range             <type>;
template < class type >                                    concept        bidirectional_range                = std::ranges::bidirectional_range       <type>;
template < class type >                                    concept        random_access_range                = std::ranges::random_access_range       <type>;
template < class type >                                    concept        contiguous_range                   = std::ranges::contiguous_range          <type>;

template < class type >                                    concept        boolean                            = std::same_as<type,bool>;
template < class type >                                    concept        character                          = std::same_as<type,char> or std::same_as<type,signed char> or std::same_as<type,unsigned char> or std::same_as<type,wchar_t> or std::same_as<type,char8_t> or std::same_as<type,char16_t> or std::same_as<type,char32_t>;
template < class type >                                    concept        integral                           = std::signed_integral<type> and not char_type<type>;
template < class type >                                    concept        floating_point                     = std::floating_point<type>;
template < class type >                                    concept        numeric                            = integral<type> or floating_point<type>;

template < class type >                                    concept        hashable                           = std::default_initializable             <std::hash       <type>>;
template < class type >                                    concept        formattable                        = std::default_initializable             <std::formatter  <type,char>>;

   



/// Operator

template < class type >                                    concept        plusable                           = requires { std::declval<type >() + std::declval<type >(); };
template < class type1, class type2 >                      concept        plusable_to                        = requires { std::declval<type1>() + std::declval<type2>(); };
template < class type1, class type2 >                      using          plus_result                        = decltype ( std::declval<type1>() + std::declval<type2>()  );

template < class type >                                    concept        minusable                          = requires { std::declval<type >() - std::declval<type >(); };
template < class type1, class type2 >                      concept        minusable_to                       = requires { std::declval<type1>() - std::declval<type2>(); };
template < class type1, class type2 >                      using          minus_result                       = decltype ( std::declval<type1>() - std::declval<type2>()  );

template < class type >                                    concept        multipliable                       = requires { std::declval<type >() * std::declval<type >(); };
template < class type1, class type2 >                      concept        multipliable_to                    = requires { std::declval<type1>() * std::declval<type2>(); };
template < class type1, class type2 >                      using          multiply_result                    = decltype ( std::declval<type1>() * std::declval<type2>()  );

template < class type >                                    concept        dividable                          = requires { std::declval<type >() / std::declval<type >(); };
template < class type1, class type2 >                      concept        dividable_to                       = requires { std::declval<type1>() / std::declval<type2>(); };
template < class type1, class type2 >                      using          divide_result                      = decltype ( std::declval<type1>() / std::declval<type2>()  );

template < class type >                                    concept        modulable                          = requires { std::declval<type >() % std::declval<type >(); };
template < class type1, class type2 >                      concept        modulable_to                       = requires { std::declval<type1>() % std::declval<type2>(); };
template < class type1, class type2 >                      using          modulus_result                     = decltype ( std::declval<type1>() % std::declval<type2>()  );

template < class type >                                    concept        equalable                          = requires { std::declval<type >() == std::declval<type >(); };
template < class type1, class type2 >                      concept        equalable_to                       = requires { std::declval<type1>() == std::declval<type2>(); };

template < class type >                                    concept        comparable                         = requires { std::declval<type >() <=> std::declval<type >(); };
template < class type1, class type2 >                      concept        comparable_to                      = requires { std::declval<type1>() <=> std::declval<type2>(); };
template < class type1, class type2 >                      using          compare_result                     = decltype ( std::declval<type1>() <=> std::declval<type2>()  );


/// Argument pack

template <            class... types >                     using          first_type_of                      = types...[0];
template <            class... types >                     using          second_type_of                     = types...[1];
template <            class... types >                     using          last_type_of                       = types...[sizeof...(types)-1];
template < int index, class... types >                     using          index_type_of                      = types...[index >= 0 ? index-1 : index+sizeof...(types)];

                       constexpr decltype(auto) first_value_of  ( auto&&... args ) { return args...[0]; }
                       constexpr decltype(auto) second_value_of ( auto&&... args ) { return args...[1]; }
                       constexpr decltype(auto) last_value_of   ( auto&&... args ) { return args...[sizeof...(args)-1]; }
template < int index > constexpr decltype(auto) index_value_of  ( auto&&... args ) { return args...[index >= 0 ? index-1 : index+sizeof...(args)]; }
