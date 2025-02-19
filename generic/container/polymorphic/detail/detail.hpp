#pragma once

namespace detail
{
    // all_different
    template < class... types >
    constexpr bool all_different = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < >
    constexpr bool all_different<> = true;

    template < class type >
    constexpr bool all_different<type> = true;

    template < class type, class... types >
    constexpr bool all_different<type,types...> = not ( same_as<type,types> or ... ) and all_different<types...>;


    // all_invocable_and_returns_same_type
    template < class input_type, class... types > 
    constexpr bool all_invocable_and_returns_same_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    
    template < class input_type, class type >
    constexpr bool all_invocable_and_returns_same_type<input_type,type> = invocable<input_type,type>;

    template < class input_type, class type, class... types >
    constexpr bool all_invocable_and_returns_same_type<input_type,type,types...> = []
    {
        if constexpr ( ( invocable<input_type,type > and ... and invocable<input_type,types> ) )
            return ( same_as<invoke_result<input_type,type>,invoke_result<input_type,types>> and ... );
        else
            return false;
    } ();

    // find_same_type
    template < class input_type, class... types >
    constexpr int find_same_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int find_same_type<input_type,type> = same_as<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int find_same_type<input_type,type,types...> = same_as<input_type,type>                 ? 1 otherwise
                                                             find_same_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                        1 + find_same_type<input_type,types...>;
    // find_convertible_type
    template < class input_type, class... types >
    constexpr int find_convertible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int find_convertible_type<input_type,type> = convertible_to<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int find_convertible_type<input_type,type,types...> = convertible_to<input_type,type>                 ? 1 otherwise
                                                                    find_convertible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                      1 + find_convertible_type<input_type,types...>;
    // find_constructible_type
    template < class input_type, class... types >
    constexpr int find_constructible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    
    template < class input_type, class type >
    constexpr int find_constructible_type<input_type,type> = constructible_from<type,input_type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int find_constructible_type<input_type,type,types...> = constructible_from<type,input_type>               ? 1 otherwise
                                                                      find_constructible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                          1 + find_constructible_type<input_type,types...>;

    // value_of_same_type
    template < class input_type >
    constexpr decltype(auto) value_of_same_type ( auto&&... args )
    {
        static_assert ( ( same_as<input_type,decay<decltype(args)>> or ... ), "no same type fonud" );
        return index_value_of<find_same_type<input_type,decay<decltype(args)>...>>(std::forward<decltype(args)>(args)...);
    }

    // value_of_same_type_or_default
    template < class input_type >
    constexpr decltype(auto) value_of_same_type_or ( auto&&... args )
    {
        if constexpr ( ( same_as<input_type,decay<decltype(args)>> or ... ) and
                       find_same_type<input_type,decay<decltype(args)>...> != sizeof...(args) ) // Not the last one.
            return value_of_same_type<input_type>(std::forward<decltype(args)>(args)...);
        else
            return last_value_of(std::forward<decltype(args)>(args)...);
    }
}