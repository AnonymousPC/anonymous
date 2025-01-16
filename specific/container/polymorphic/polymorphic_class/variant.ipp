#pragma once

/// Auxiliary

namespace detail
{
    template < class type >
    constexpr bool all_different<type> = true;

    template < class type, class... types >
    constexpr bool all_different<type,types...> = not ( same_as<type,types> or ... ) and all_different<types...>;

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

    template < class input_type, class... types >
    constexpr int index_of_unique_same_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int index_of_unique_same_type<input_type,type> = same_as<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_same_type<input_type,type,types...> = same_as<input_type,type>                            ? 1 otherwise
                                                                        index_of_unique_same_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                              1 + index_of_unique_same_type<input_type,types...>;
    template < class input_type, class... types >
    constexpr int index_of_unique_convertible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();

    template < class input_type, class type >
    constexpr int index_of_unique_convertible_type<input_type,type> = convertible_to<input_type,type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_convertible_type<input_type,type,types...> = convertible_to<input_type,type>                            ? 1 otherwise
                                                                               index_of_unique_convertible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                            1 + index_of_unique_convertible_type<input_type,types...>;
    template < class input_type, class... types >
    constexpr int index_of_unique_convertible_type = [] { static_assert(false, "you need to specialize it"); return false; } ();
    
    template < class input_type, class type >
    constexpr int index_of_unique_constructible_type<input_type,type> = constructible_from<type,input_type> ? 1 otherwise 0;

    template < class input_type, class type, class... types >
    constexpr int index_of_unique_constructible_type<input_type,type,types...> = constructible_from<type,input_type>                          ? 1 otherwise
                                                                                 index_of_unique_constructible_type<input_type,types...> == 0 ? 0 otherwise
                                                                                                                                                1 + index_of_unique_constructible_type<input_type,types...>;
}

template < class... types >
constexpr variant<types...>::variant ( auto v )
    requires ( same_as<types,decltype(v)> or ... )
{
    base::emplace<detail::index_of_unique_same_type<decltype(v),types...>>(std::move(v));
}

template < class... types >