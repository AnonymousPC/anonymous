module;
#if defined(__GNUC__) and not defined(__clang__)
    #pragma GCC diagnostic ignored "-Wassume"
    #pragma GCC diagnostic ignored "-Wuser-defined-literals"
#elifdef __clang__
    #pragma clang diagnostic ignored "-Wassume"
    #pragma clang diagnostic ignored "-Wuser-defined-literals"
#endif

#define private public

export module anonymous.container;
import std;
import boost;
import anonymous.basic;

export namespace anonymous
{
    /// Class
    template < class type, int dim = 1,                                    class device = cpu > class array;
    template < class type,                                                 class device = cpu > using vector = array<type,1,device>;
    template < class type,                                                 class device = cpu > using matrix = array<type,2,device>;

    template < class type,                                                 class device = cpu > class deque;
    template < class type,                                                 class device = cpu > class forward_list;
    template < class type,                                                 class device = cpu > class list;
    template < class type,               class compare = std::less<type>,  class device = cpu > class priority_queue;
    template < class type,                                                 class device = cpu > class queue;
    template < class type,                                                 class device = cpu > class stack;

    template < class type,               class compare = std::less<type>,  class device = cpu > class set;
    template < class type1, class type2, class compare = std::less<type1>, class device = cpu > class map;
    template < class type,               class hash    = std::hash<type>,  class device = cpu > class unordered_set;
    template < class type1, class type2, class hash    = std::hash<type1>, class device = cpu > class unordered_map;

    template < class type1, class type2 = type1,                           class device = cpu > class pair;
    template < class... types >                                          /*class device = cpu*/ class tuple;

                                                                         /*class device = cpu*/ class any;
    template < class type,                                                 class device = cpu > class function;
    template < class type,                                                 class device = cpu > class optional;
    template < class type1, class type2,                                   class device = cpu > class expected;
    template < class... types >                                          /*class device = cpu*/ class variant;

    template < class type,                                                 class device = cpu > class basic_string;
                                                                                                using string    = basic_string<char>;
                                                                                                using wstring   = basic_string<wchar_t>;
                                                                                                using u8string  = basic_string<char8_t>;
                                                                                                using u16string = basic_string<char16_t>;
                                                                                                using u32string = basic_string<char32_t>;
                                                                                            
    /// Concept
    template < class type > concept array_type = requires { typename type::array_concept; };
    template < class type > concept set_type   = requires { typename type::set_concept;   };
    template < class type > concept map_type   = requires { typename type::map_concept;   };
    template < class type > concept pair_type  = requires { typename type::pair_concept;  };
    template < class type > concept tuple_type = requires { typename type::tuple_concept; };

    /// Include
    #include "macro.cpp"
    #include "discrete/discrete.hpp"
    #include "polymorphic/polymorphic.hpp"
    #include "array/array.hpp"
    // #include "chain/chain.hpp"
    // #include "collection/collection.hpp"
    // #include "string/string.hpp"
    // #include "utility/utility.hpp"

    // /// Global
    // constexpr input_t input = input_t();

    // /// Literal
    // inline namespace literals
    // {
    //     constexpr string         operator ""s   ( const char*     ptr, std::size_t    ) { return string         ( ptr     );   }
    //     constexpr wstring        operator ""s   ( const wchar_t*  ptr, std::size_t    ) { return wstring        ( ptr     );   }
    //     constexpr u8string       operator ""s   ( const char8_t*  ptr, std::size_t    ) { return u8string       ( ptr     );   }
    //     constexpr u16string      operator ""s   ( const char16_t* ptr, std::size_t    ) { return u16string      ( ptr     );   }
    //     constexpr u32string      operator ""s   ( const char32_t* ptr, std::size_t    ) { return u32string      ( ptr     );   }
    // }

} // namespace anonymous

export namespace std
{
    // #include "utility/format/export/std.hpp"
    // #include "utility/hash/export/std.hpp"
    #include "utility/structured_binding/export/std.hpp"
    
} // namespace std
