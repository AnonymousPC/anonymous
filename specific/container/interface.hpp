#pragma once
#include "../../generic/basic/interface.hpp"

namespace ap::experimental
{
    /// Class
    class cpu;
    class cuda;
    class hip;
    class mps;
    class opencl;
    class tbb;

    template < class type, int dim = 1, class device = cpu >                    class array;
    template < class type,              class device = cpu >                    using vector = array<type>;
    template < class type,              class device = cpu >                    using matrix = array<type,2>;
    template < class type, int len,     class device = cpu >                    class static_array;
    template < class type, int len,     class device = cpu >                    using static_vector  = static_array<type,len>;
    template < class type, int len,     class device = cpu >                    class inplace_array;
    template < class type, int len,     class device = cpu >                    using inplace_vector = inplace_array<type,len>;

    // template < class type >                                                     class deque;
    // template < class type >                                                     class list;
    // template < class type, class compare = std::less<type> >                    class priority_queue;
    // template < class type >                                                     class queue;
    // template < class type >                                                     class stack;

    // template < class type,  class compare, class container >                    class basic_set;
    // template < class type1, class type2,   class key_compare, class container > class basic_map;

    template < class type1, class type2 = type1 >                               class pair;
    template < class... types >                                                 class tuple;

    //                                                                             class any;
    // template < class type >                                                     class function;
    // template < class type >                                                     class optional;
    // template < class... types >                                                 class property_tree;
    // template < class... types >                                                 class variant;

    // template < class char_type >                                                class basic_string;
    //                                                                             using string    = basic_string<char>;
    //                                                                             using wstring   = basic_string<wchar_t>;
    //                                                                             using u8string  = basic_string<char8_t>;
    //                                                                             using u16string = basic_string<char16_t>;
    //                                                                             using u32string = basic_string<char32_t>;
    // template < class char_type >                                                class basic_string_view;
    //                                                                             using string_view    = basic_string_view<char>;
    //                                                                             using wstring_view   = basic_string_view<wchar_t>;
    //                                                                             using u8string_view  = basic_string_view<char8_t>;
    //                                                                             using u16string_view = basic_string_view<char16_t>;
    //                                                                             using u32string_view = basic_string_view<char32_t>;
    // template < class char_type >                                                class basic_regex;
    //                                                                             using regex       = basic_regex<char>;
    //                                                                             using wregex      = basic_regex<wchar_t>;


    // template < auto... digits >                                                 class constexpr_index;



    /// Concept
    template < class input_type, class value_type = void, int dim = 0, class device_type = void >
    concept array_type = []
    {
        if constexpr ( requires { typename input_type::array_tag; } )
        {
            static_assert ( requires { typename input_type::value_type; input_type::dimension(); typename input_type::device_type; }, "class provides array_tag but not provides value_type, dimension() and device_type" );
            return ( std::convertible_to<typename input_type::value_type,value_type> or is_void<value_type> ) and
                   ( input_type::dimension() == dim or dim == 0 ) and
                   ( std::same_as<typename input_type::device_type,device_type> or is_void<device_type> );         
        }
        else
            return false;
    } ();

    // template < class input_type, class value_type = void >
    // concept deque_type = []
    // {
    //     if constexpr ( requires { typename input_type::deque_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides deque_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept list_type = []
    // {
    //     if constexpr ( requires { typename input_type::list_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides list_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept priority_queue_type = []
    // {
    //     if constexpr ( requires { typename input_type::priority_queue_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides priority_queue_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept queue_type = []
    // {
    //     if constexpr ( requires { typename input_type::queue_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides queue_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept stack_type = []
    // {
    //     if constexpr ( requires { typename input_type::stack_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides stack_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept set_type = []
    // {
    //     if constexpr ( requires { typename input_type::set_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides set_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class key_type = void, class value_type = void >
    // concept map_type = []
    // {
    //     static_assert ( is_void<key_type> == is_void<value_type>, "must enable or disable both key/value type check at the same time" );
    //     if constexpr ( requires { typename input_type::map_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::key_type; typename input_type::value_type; }, "class provides map_tag but not provides key_type and value_type" );
    //         if constexpr ( is_void<key_type> and is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::key_type,key_type> and std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    template < class input_type, class type1 = void, class type2 = void >
    concept pair_type = []
    {
        if constexpr ( requires { typename input_type::pair_tag; } )
        {
            static_assert ( requires { typename input_type::key_type; typename input_type::value_type; }, "class provides pair_tag but not provides key_type and value_type" );
            return ( std::convertible_to<typename input_type::key_type,  type1> or is_void<type1> ) and
                   ( std::convertible_to<typename input_type::value_type,type2> or is_void<type2> );
        }
        else
            return false;
    } ();

    namespace aux
    {
        template < class input_type, int count, class... types >
        constexpr bool tuple_type_helper = true;

        template < class input_type, int count >
        constexpr bool tuple_type_helper<input_type,count> = true;

        template < class input_type, int count, class type, class... types >
        constexpr bool tuple_type_helper<input_type,count,type,types...> =
            ( input_type::size() - count + 1 == 1 + sizeof...(types) ) and
            ( std::convertible_to<typename input_type::template value_type<count>,type> or is_void<type> ) and []
            {
                if constexpr ( count < input_type::size() )
                    return tuple_type_helper<input_type,count+1,types...>;
                else
                    return true;
            } ();
    }

    template < class input_type, class... types >
    concept tuple_type = []
    {
        if constexpr ( requires { typename input_type::tuple_tag; } )
        {
            static_assert ( requires { typename input_type::template value_type<1>; typename input_type::template value_type<input_type::size()>; input_type::size(); }, "class provides tuple_tag but not provides value_type and size()" );
            return aux::tuple_type_helper<input_type,1,types...>;
        }
        else
            return false;
    } ();

    // template < class input_type, class value_type = void >
    // concept string_type = []
    // {
    //     if constexpr ( requires { typename input_type::string_tag; } )
    //     {
    //         static_assert ( requires { typename input_type::value_type; }, "class provides string_tag but not provides value_type" );
    //         if constexpr ( is_void<value_type> )
    //             return true;
    //         else
    //             return std::convertible_to<typename input_type::value_type,value_type>;
    //     }
    //     else
    //         return false;
    // } ();

    // template < class input_type, class value_type = void >
    // concept general_string_type = char_type<input_type> or
    //                               char_type<remove_extent<input_type>> or
    //                               char_type<remove_pointer<input_type>> or
    //                               string_type<input_type>;

    // template < class input_type, class value_type = void, int dim = 0 >           concept array_type          = ...;
    // template < class input_type, class value_type = void >                        concept deque_type          = ...;
    // template < class input_type, class value_type = void >                        concept list_type           = ...;
    // template < class input_type, class value_type = void >                        concept priority_queue_type = ...;
    // template < class input_type, class value_type = void >                        concept queue_type          = ...;
    // template < class input_type, class value_type = void >                        concept stack_type          = ...;
    // template < class input_type, class key_type = void, class value_type = void > concept pair_type           = ...;
    // template < class input_type, class... value_types >                           concept tuple_type          = ...;
    // template < class input_type, class value_type = void >                        concept set_type            = ...;
    // template < class input_type, class key_type = void, class value_type = void > concept map_type            = ...;
    // template < class input_type, class char_type = void >                         concept string_type         = ...;
    // template < class input_type, class char_type = void >                         concept general_string_type = ...;

    // /// Include
    #include "third_party/device.hpp"
    #include "discrete/discrete.hpp" // First.
    #include "array/array.hpp"
    // #include "chain/chain.hpp"
    // #include "collection/collection.hpp"
    // #include "polymorphic/polymorphic.hpp"
    // #include "string/string.hpp"
    #include "utility/utility.hpp"

    // /// Literal
    // namespace literals
    // {
    //     template < char... index >
    //     constexpr auto           operator ""c   ( )                                { return constexpr_index<index...>();  }
    //     constexpr string         operator ""s   ( const char*     ptr, size_t    ) { return string         ( ptr     );   }
    //     constexpr wstring        operator ""s   ( const wchar_t*  ptr, size_t    ) { return wstring        ( ptr     );   }
    //     constexpr u8string       operator ""s   ( const char8_t*  ptr, size_t    ) { return u8string       ( ptr     );   }
    //     constexpr u16string      operator ""s   ( const char16_t* ptr, size_t    ) { return u16string      ( ptr     );   }
    //     constexpr u32string      operator ""s   ( const char32_t* ptr, size_t    ) { return u32string      ( ptr     );   }
    //     constexpr string_view    operator ""sv  ( const char*     ptr, size_t sz ) { return string_view    ( ptr, sz );   }
    //     constexpr wstring_view   operator ""sv  ( const wchar_t*  ptr, size_t sz ) { return wstring_view   ( ptr, sz );   }
    //     constexpr u8string_view  operator ""sv  ( const char8_t*  ptr, size_t sz ) { return u8string_view  ( ptr, sz );   }
    //     constexpr u16string_view operator ""sv  ( const char16_t* ptr, size_t sz ) { return u16string_view ( ptr, sz );   }
    //     constexpr u32string_view operator ""sv  ( const char32_t* ptr, size_t sz ) { return u32string_view ( ptr, sz );   }
    //     constexpr regex          operator ""rgx ( const char*     ptr, size_t sz ) { return regex (string_view (ptr,sz)); }
    //     constexpr wregex         operator ""rgx ( const wchar_t*  ptr, size_t sz ) { return wregex(wstring_view(ptr,sz)); }
    // }

} // namespace ap
