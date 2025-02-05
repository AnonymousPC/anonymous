#pragma once
#include "../basic/interface.hpp"

namespace ap
{
    template < class type, int dim = 1,                                    class device = cpu > class array;
    template < class type,                                                 class device = cpu > using vector = array<type>;
    template < class type,                                                 class device = cpu > using matrix = array<type,2>;
    template < class type, int len,                                        class device = cpu > class static_array;
    template < class type, int len,                                        class device = cpu > using static_vector  = static_array<type,len>;
    template < class type, int len,                                        class device = cpu > class inplace_array;
    template < class type, int len,                                        class device = cpu > using inplace_vector = inplace_array<type,len>;

    template < class type,                                                 class device = cpu > class deque;
    template < class type,                                                 class device = cpu > class list;
    template < class type,               class compare = std::less<type>,  class device = cpu > class priority_queue;
    template < class type,                                                 class device = cpu > class queue;
    template < class type,                                                 class device = cpu > class stack;

    template < class type,               class compare = std::less<type>,  class device = cpu > class set;
    template < class type1, class type2, class compare = std::less<type1>, class device = cpu > class map;
    template < class type,               class hash    = std::hash<type>,  class device = cpu > class unordered_set;
    template < class type1, class type2, class hash    = std::hash<type1>, class device = cpu > class unordered_map;

    template < class type,                                                 class device = cpu > using complex = device::template complex<type>;
    template < class type1, class type2 = type1,                           class device = cpu > using pair    = device::template pair<type1,type2>;
    template < class... types >                                                                 using tuple   = cpu::template tuple<types...>;

                                                                                                class any;
    template < class type >                                                                     class function;
    template < class type >                                                                     class optional;
    template < class... types >                                                                 class variant;

    template < class type,                                                 class device = cpu > class basic_string;
                                                                                                using string            = basic_string<char>;
                                                                                                using wstring           = basic_string<wchar_t>;
                                                                                                using u8string          = basic_string<char8_t>;
                                                                                                using u16string         = basic_string<char16_t>;
                                                                                                using u32string         = basic_string<char32_t>;
    template < class type,                                                 class device = cpu > class basic_string_view;
                                                                                                using string_view       = basic_string_view<char>;
                                                                                                using wstring_view      = basic_string_view<wchar_t>;
                                                                                                using u8string_view     = basic_string_view<char8_t>;
                                                                                                using u16string_view    = basic_string_view<char16_t>;
                                                                                                using u32string_view    = basic_string_view<char32_t>;



    /// Concept
    template < class type, class value_type = void, int dim = 0 >
    concept array_type = []
    {
        if constexpr ( requires { typename type::array_tag; } )
        {
            static_assert ( requires { typename type::value_type; type::dimension(); }, "class provides array_tag but not provides value_type, dimension()" );
            return ( convertible_to<typename type::value_type,value_type> or is_void<value_type> ) and
                   ( type::dimension() == dim or dim == 0 );      
        }
        else
            return false;
    } ();

    template < class type, class value_type = void >
    concept deque_type = []
    {
        if constexpr ( requires { typename type::deque_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides deque_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void >
    concept list_type = []
    {
        if constexpr ( requires { typename type::list_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides list_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void, class device_type = void >
    concept priority_queue_type = []
    {
        if constexpr ( requires { typename type::priority_queue_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides priority_queue_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void, class device_type = void >
    concept queue_type = []
    {
        if constexpr ( requires { typename type::queue_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides queue_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void, class device_type = void >
    concept stack_type = []
    {
        if constexpr ( requires { typename type::stack_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides stack_tag but not provides value_type" );
            return convertible_to<typename type::value_type, value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void, class device_type = void >
    concept set_type = []
    {
        if constexpr ( requires { typename type::set_tag; } )
        {
            static_assert ( requires { typename type::value_type; typename type::device_type; }, "class provides set_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else
            return false;
    } ();

    template < class type, class key_type = void, class value_type = void, class device_type = void >
    concept map_type = []
    {
        if constexpr ( requires { typename type::map_tag; } ) 
        {
            static_assert ( requires { typename type::key_type; typename type::value_type; typename type::device_type; }, "class provides map_tag but not provides key_type, value_type" );
            return ( convertible_to<typename type::key_type,  key_type  > or is_void<key_type  > ) and
                   ( convertible_to<typename type::value_type,value_type> or is_void<value_type> );
        }
        else
            return false;
    } ();

    template < class type, class key_type = void, class value_type = void >
    concept pair_type = []
    {
        if constexpr ( requires { typename type::pair_tag; } )
        {
            static_assert ( requires { typename type::key_type; typename type::value_type; }, "class provides pair_tag but not provides key_type and value_type" );
            return ( convertible_to<typename type::key_type,  key_type  > or is_void<key_type  > ) and
                   ( convertible_to<typename type::value_type,value_type> or is_void<value_type> );
        }
        else
            return false;
    } ();

    namespace detail
    {
        template < class type, int count, class... value_types >
        constexpr bool tuple_type_helper = true;

        template < class type, int count >
        constexpr bool tuple_type_helper<type,count> = true;

        template < class type, int count, class type1, class... value_types >
        constexpr bool tuple_type_helper<type,count,type1,value_types...> =
            ( type::size() - count + 1 == 1 + sizeof...(value_types) ) and
            ( convertible_to<typename type::template value_type<count>,type1> or is_void<type1> ) and []
            {
                if constexpr ( count < type::size() )
                    return tuple_type_helper<type,count+1,value_types...>;
                else
                    return true;
            } ();
    } // namespace detail

    template < class type, class... value_types >
    concept tuple_type = []
    {
        if constexpr ( requires { typename type::tuple_tag; } )
        {
            static_assert ( requires { typename type::template value_type<1>; typename type::template value_type<type::size()>; type::size(); }, "class provides tuple_tag but not provides value_type and size()" );
            return detail::tuple_type_helper<type,1,value_types...>;
        }
        else
            return false;
    } ();

    template < class type, class value_type = void >
    concept string_type = []
    {
        if constexpr ( requires { typename type::string_tag; } )
        {
            static_assert ( requires { typename type::value_type; }, "class provides string_tag but not provides value_type" );
            return convertible_to<typename type::value_type,value_type> or is_void<value_type>;
        }
        else if constexpr ( not is_void<value_type> )
            return same_as<remove_cvref<type>,value_type> or
                   same_as<remove_extent<remove_cvref<type>>,value_type> or
                   same_as<remove_pointer<remove_cvref<type>>,value_type>;
        else
            return char_type<remove_cvref<type>> or 
                   char_type<remove_extent<remove_cvref<type>>> or
                   char_type<remove_pointer<remove_cvref<type>>>;
    } ();

    namespace detail
    {
        template < class type, class attribute_type >
        struct function_type_helper;

        template < class type, class res_type, class... arg_types >
        struct function_type_helper<type,res_type(arg_types...)>
        {
            constexpr static const bool value = std::is_invocable_r<res_type,type,arg_types...>::value;
        };
    } // namespace detail
    
    template < class type, class attribute_type >
    concept function_type = detail::function_type_helper<type,attribute_type>::value;

    // /// Include
    #include "discrete/discrete.hpp" // First.
    #include "array/array.hpp"
    #include "chain/chain.hpp"
    #include "collection/collection.hpp"
    #include "polymorphic/polymorphic.hpp"
    #include "string/string.hpp"
    #include "utility/utility.hpp"

    /// Literal
    inline namespace literals
    {
        constexpr string         operator ""s   ( const char*     ptr, size_t    ) { return string         ( ptr     );   }
        constexpr wstring        operator ""s   ( const wchar_t*  ptr, size_t    ) { return wstring        ( ptr     );   }
        constexpr u8string       operator ""s   ( const char8_t*  ptr, size_t    ) { return u8string       ( ptr     );   }
        constexpr u16string      operator ""s   ( const char16_t* ptr, size_t    ) { return u16string      ( ptr     );   }
        constexpr u32string      operator ""s   ( const char32_t* ptr, size_t    ) { return u32string      ( ptr     );   }
        constexpr string_view    operator ""sv  ( const char*     ptr, size_t sz ) { return string_view    ( ptr, sz );   }
        constexpr wstring_view   operator ""sv  ( const wchar_t*  ptr, size_t sz ) { return wstring_view   ( ptr, sz );   }
        constexpr u8string_view  operator ""sv  ( const char8_t*  ptr, size_t sz ) { return u8string_view  ( ptr, sz );   }
        constexpr u16string_view operator ""sv  ( const char16_t* ptr, size_t sz ) { return u16string_view ( ptr, sz );   }
        constexpr u32string_view operator ""sv  ( const char32_t* ptr, size_t sz ) { return u32string_view ( ptr, sz );   }
    }

} // namespace ap
